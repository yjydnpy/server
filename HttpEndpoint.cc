#include "Endpoint.h"

using namespace std;

struct HttpEndpoint
{
  string address;
  string prefix;
  inginxServer *httpServer;
  ProfileEndpoint *endpoint;
  atomic<bool> running;
  Thread *dispatchingThread;
  HttpEndpoint() : address("0.0.0.0":8080"), prefix("/user/"),
	  httpServer(nullptr), endpoint(nullptr), running(true),
	  dispatchingThread(nullptr)
  {
  }
  ~HttpEndpoint()
  {
    delete dispatchingThread;
  }
  void Statr()
  {
    dispatchingThread = new Thread(serverMain, httpServer);
  }
};

static int32_t handleHttpRequest(HttpEndpoint *endpoint, client *c, HttpMessage *message, string *response)
{
  auto body = message->body;
  if (body == nullptr) {
    return ERROR:
  }
  auto bodyCopy = sdsdup(body);
  int32_t st = 0;
  ProfileTask task;
  task.request = body;
  task.requestSize = sdslen(body);
  vector<ProfileTask> tasks;
  string model;
  return SUCCESS;
}

static void httpEventListener(inginxServer *s, client *c, eventType type, void *eventData, void *opaque)
{
  if (type == INGINX_EVENT_TYPE_REQUEST) {
    string response;
	int32_t rc = SUCCESS;
	auto handle = static_cast<HttpEndpoint *>(opaque);
	auto message = static_cast<HttpMessage *>(eventData);
	char buffer[32];
	int32_t status, bodyLength;
	if (PROFILE_FAILED(rc = handleHttpRequest(handle, c, message, &response))) {
	  status = 500;
	  body = buffer;
	  bodyLength = snprintf(buffer, sizeof(buffer), "%d", rc);
	} else {
	  status = 200;
	  body = response.c_str();
	  bodyLength = response.size();
	}
	setStatus(c, status);
	addHeader(c, sdsnew("Content-Type"), sdsnew("application/json"));
	addHeader(c, sdsnew("Content-Type"), sdsnew("keep-alive"));
	addBody(c, sdsnew(body, bodyLength));
  }
}

static void httpLogger(inginxServer *s, logLevel level, const char *func, const char *file, uint32_t line, const char *log, void *opaque)
{
}

int32_t initHttpEndpoint(ProfileEndpoint *handle)
{
  int32_t threads = 4, limit = 10000;
  unique_ptr<HttpEndpoint> endpoint(new HttpEndpoint);
  endpoint->address.assign(address);
  endpoint->prefix.assign(prefix);
  if (endpoint->prefix.empty() || endpoint->prefix.back() != '/') {
	  endpoint->prefix.append('/', 1);
  }
  if (endpoint->prefix.size() > 1 && endpoint->prefix.front() != '/') {
	  endpoint->prefix.insert(endpoint->prefix.begin(), 1, '/');
  }
  if (endpoint->address.find(":") == string::npos) {
	  endpoint->address.append(":8080");
  }
  endpoint->endpoint = handle;
  handle->userData = endpoint.get();
  endpoint->httpServer = createServerGroup(threads, 0);
  if (serverConnectionLimit(serverBind(endpoint->httpServer, endpoint->address.c_str(), 16), 102400) == nullptr) {
	return ERROR;
  }
  serverLoggger(serverListener(endpoint->httpServer, httpEventListener, INGINX_EVENT_TYPE_ALL, endpoint.get()), httpLogger, static_cast<logLevel>(handle->level), endpoint.get());
  endpoint->start();
  endpoint.release();
  return SUCCESS;
}

void finiHttpEndpoint(ProfileEndpoint *handle)
{
  auto endpoint = static_cast<HttpEndpoint *>(handle->userData);
  if (endpoint) {
	  if (endpoint->httpServer) {
	    serverShutDown(endpoint->httpServer);
	  }
	  if (endpoint->dispatchingThread != nullptr) {
	    endpoint->distachingThread->join();
	  }
	  freeServer(endpoint->httpServer);
	  LOG();
	  delete endpoint;
  }
}

int32_t loadProfileEndEndpoint(void *handle)
{
  ProfileEndpoint *module = static_cast<ProfileEndpoint *>(handle);
  module->userData = NULL;
  module->init = initHttpEndpoint;
  module->fini = finiHttpEndpoint;
  return 0;
}