#include "ProfileService.h"
#include "signal.h"
#include "Thread.h"
#include "Endpoint.h"

BEGIN_PROFILE_NAMESPACE

class ProfileService
{
private:
  ShardMutex instanceMutex;
  Atomic<uintptr_t> loadter;

public:
  ProfileService();
  ~ProfileService();

  int32_t Reload();
  int32_t Load();
};

class ProfileServiceHandle
{
public:
  ProfileServiceHandle();
  ~ProfileServiceHandle();

  int32_t Init();
  void Start();
  void Join();
  void Reload() {
  }

private:
  void runService();
  int32_t initEndpoint();
  void loadEndpoint(const String &path);
  void freeEndpoint(ProfileEndpoint *endpoint);
  static int32_t handleTask(ProfileEndpoint *endpoint, const std::string &model);

private:
  SharedPtr<ProfileService> service;
  Thread serviceThread;
  vector<ProfileEndpoint *> endpoints;

  
  Mutex runningMutex;
  ConditionVariable runningCond;
  bool running;
};

ProfileServiceHandle::ProfileServiceHandle() : running(true)
{
}

ProfileServiceHandle::~ProfileServiceHandle()
{
  Join();
}

ProfileServiceHandle::handleTask(ProfileEndpoint *endpoint, const std::string &model)
{
  auto handle = static_cast<ProfileServiceHandle *>(endpoint->detector);
  int32_t rc = SUCCESS;
  
}

void ProfileServiceHandle::freeEndpoint(ProfileEndpoint *endpoint)
{
  if (endpoint->handle) {
    dlclose(endpoint->handle);     
  }
  free(endpoint);
}

int32_t ProfileServiceHandle::initEndpoint()
{
  string str;
  loadEndpoint(str);
  return SUCCESS;
}

int32_t ProfileServiceHandle::Init(const )
{
  int32_t st;
  signal(SIGPIPE, SIG_IGN);
  service.reset(new ProfileService);
  if (PROFILE_FAILED(st = service->load())) {
	return st;
  }
  if (PROFILE_FAILED(initEndpoint())) {
    return INNER_ERROR;
  }
  return SUCCESS;
}

void ProfileServiceHandle::Start()
{
  serviceThread = Thread(Runnable(this, &ProfileServiceHandle::runService));
}

void ProfileServiceHandle::ShutDown()
{
	for (auto endpoint : endpoints) {
		if (endpoint->fini != nullptr) {
			endpoint->fini(endpoint);
		}
	}
	UniqueLock<Mutex> lock(runningMutex);
	running = false;
	runningCond.notify_all();
	
}

void ProfileServiceHandle::Join()
{
	serviceThread.join();
}

int32_t ProfileService::Load(const map<String, String> &config)
{
	
}

int32_t ProfileService::Reload()
{

}

END_PROFILE_NAMESPACE


