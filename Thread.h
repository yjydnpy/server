#ifndef PROFILE_THREAD_H
#define PROFILE_THREAD_H 1

#include "ProfileDecl.h"
#include <thread>
#include <mutex>
#include <condition_variable>

BEGIN_PROFILE_NAMESPACE

typedef std::thread Thread;
typedef std::mutex Mutex;
typedef std::shared_mutex SharedMutex;
typedef std::condition_variable ConditionVariable;
typedef std::condition_variable_any ConditionVariableAny;

template<typename T>
using LockGuard = std::lock_guard<T>;

template<typename T>
using UniqueLock = std::unique_lock<T>;

END_PROFILE_NAMESPACE

#endif /* PROFILE_THREAD_H */
