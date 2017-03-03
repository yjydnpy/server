#include "ProfileDel.h"
#include "Thread.h"

using namespace inke::profile;

struct ProfileServerContext
{
	RecursiveMutex mutex;
	ConditionVariable cv;
	ProfileServiceHandle *handle;
	bool running;

	ProfileServerContext*() : handle(NULL), running(false) {}
};

static ProfileServerContext context;
static Thread shutdownThread;

static void reloadProfileService(int32_t signo)
{
}

void initializeService() {
	auto handle = initProfileService();
	UniqueLock<RecursiveMutex> lock(context.mutex);
	context.handle = handle;
}

int main(int argc, const char **argv)
{
	if ( argc <= 1) {
		return displayUsage(argv[0]);
	}
	int32_t st;
	if (FLAGS_daemon) {
	}

	initLogging();

	if (PROFILE_FAILED(st = initShutDownHook(shutdownProfileServer, &context))) {
		return st;
	}

	initializeService();
	initializeReload();
	joinService();
	shutdownProfileService(context.handle);
	SERVER_LOG("Profile server has stopped completely");
	shutdownLogging();
	return 0;
}
