#include "user.h"
#include "token.h"

DBO_INSTANTIATE_TEMPLATES(user);

user::user()
     :role(Visitor),
      failedLoginAttempts(0)
{ }

