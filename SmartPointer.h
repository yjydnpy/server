#ifndef PROFILE_SMART_POINTER_H
#define PROFILE_SMART_POINTER_H 1

#include "ProfileDecl.h"
#include <memory>

BEGIN_PROFILE_NAMESPACE

template<typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
using UniquePtr = std::unique_ptr<T>;

END_PROFILE_NAMESPACE

#endif /* PROFILE_SMART_POINTER_H */



