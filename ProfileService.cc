#include "ProfileService.h"
#include "signal.h"
#include "Thread.h"
#include "Endpoint.h"

BEGIN_PROFILE_NAMESPACE

class ProfileService
{
public:
	ProfileService();
	~ProfileService();

	int32_t Reload();
	int32_t load();
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




