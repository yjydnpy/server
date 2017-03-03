#ifndef PORFILE_DECL_H
#define PROFILE_DECL_H 1

#include <stdint.h>
#include <string>
#include <functional>
#include <limits>

#define BEGIN_PROFILE_NAMESPACE namespace inke { namespace profile {
#define END_PROFILE_NAMESPACE }}

#define SUCCESS (0)

BEGIN_PROFILE_NAMESPACE
using namespace std;
typedef string String;
typedef int int32_t;
END_PROFILE_NAMESPACE

#endif /* PROFILE_DECL_H */
