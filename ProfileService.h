#ifndef PROFILE_H
#define PROFILE_H 1

#include "ProfileDecl.h"

BEGIN_PROFILE_NAMESPACE

class ProfileServiceHandle;

ProfileServiceHandle *initProfileSrevice();

void reloadProfileService(ProfileServiceHandle *service);
void shutdownProfileService(ProfileServiceHandle *service);

END_PROFILE_NAMESPACE

#endif /* PROFILE_H */
