#ifndef PROFILE_ENDPOINT_MODULE_H
#define PROFILE_ENDPOINT_MODULE_H 1

#include "ProfileDecl.h"

extern "C" {

struct ProfileTask {
  String content;
  int32_t uid;
};

enum EndpointLogLevel
{
  ENDPOINT_LOG_LEVEL_TRACE = 0,
  ENDPOINT_LOG_LEVEL_DEBUG,
  ENDPOINT_LOG_LEVEL_INFO,
  ENDPOINT_LOG_LEVEL_WARN,
  ENDPOINT_LOG_LEVEL_ERROR,
  ENDPOINT_LOG_LEVEL_FATAL,
  ENDPOINT_LOG_LEVEL_ASSERT,
};

typedef void (*EndpointLogger)(EndpointLogLevel level,
							   const char *func, const char *file,
							   const std::string &model, int32_t flags,
							   ProfileTask *tasks, size_t numTasks);

typedef int32_t (*ProfileSink)(ProfileEndpoint *endpoint,
							   const std::string &model, int32_t  flags,
							   ProfileTask *tasks, size_t numTasks);


typedef struct ProfileTask ProfileTask;

struct ProfileEndpoint
{
  void *handle;
  void *userData;
  int32_t (*init)(ProfileEndpoint *, const vector<pair<string, string>> &, ProfileSink);
  void (*fini)(ProfileEndpoint *);
  EndpointLogLevel level;
};

int32_t loadProfieEndpoint(void *handle);

}
#endif

#define ENDPOINT_LOG_TRACE_ENABLED(ENDPOINT) ((ENDPOINT)->level <= ENDPOINT_LOG_LEVEL_TRACE)
#define ENDPOINT_LOG_DEBUG_ENABLED(ENDPOINT) ((ENDPOINT)->level <= ENDPOINT_LOG_LEVEL_DEBUG)
#define ENDPOINT_LOG_INFO_ENABLED(ENDPOINT) ((ENDPOINT)->level <= ENDPOINT_LOG_LEVEL_INFO)
#define ENDPOINT_LOG_WARN_ENABLED(ENDPOINT) ((ENDPOINT)->level <= ENDPOINT_LOG_LEVEL_WARN)
#define ENDPOINT_LOG_ERROR_ENABLED(ENDPOINT) ((ENDPOINT)->level <= ENDPOINT_LOG_LEVEL_ERROR)
#define ENDPOINT_LOG_FATAL_ENABLED(ENDPOINT) ((ENDPOINT)->level <= ENDPOINT_LOG_LEVEL_FATAL)

#define ENDPOINT_LOG_TRACE(ENDPOINT, ...) (ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_TRACE, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)

#define ENDPOINT_LOG_DEBUG(ENDPOINT, ...)                                                               \
	do {                                                                                                  \
	if (ENDPOINT_LOG_DEBUG_ENABLED(ENDPOINT)) {                                                         \
	(ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_DEBUG, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);      \
	}                                                                                                   \
	} while (false)

#define ENDPOINT_LOG_INFO(ENDPOINT, ...)                                                                \
	do {                                                                                                  \
	if (ENDPOINT_LOG_INFO_ENABLED(ENDPOINT)) {                                                          \
	(ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_INFO, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);       \
	}                                                                                                   \
	} while (false)

#define ENDPOINT_LOG_WARN(ENDPOINT, ...)                                                                \
	do {                                                                                                  \
	if (ENDPOINT_LOG_WARN_ENABLED(ENDPOINT)) {                                                          \
	(ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_WARN, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);       \
	}                                                                                                   \
	} while (false)

#define ENDPOINT_LOG_ERROR(ENDPOINT, ...)                                                               \
	do {                                                                                                  \
	if (ENDPOINT_LOG_ERROR_ENABLED(ENDPOINT)) {                                                         \
	(ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);      \
	}                                                                                                   \
	} while (false)

#define ENDPOINT_LOG_FATAL(ENDPOINT, ...)                                                               \
	do {                                                                                                  \
	if (ENDPOINT_LOG_FATAL_ENABLED(ENDPOINT)) {                                                         \
	(ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_FATAL, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);      \
	}                                                                                                   \
	} while (false)

#define ENDPOINT_LOG_ASSERT(ENDPOINT, ...)                                                              \
	do {                                                                                                  \
	(ENDPOINT)->logger(ENDPOINT_LOG_LEVEL_ASSERT, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);       \
	} while (false)

#endif /* PROFILE_ENDPOINT_MODULE_H */