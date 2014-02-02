#ifndef SESSION_H_
#define SESSION_H_

#include <Wt/Auth/Login>

#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>

#include "BlogUserDatabase.h"

namespace Wt{
   namespace auth{
      class passwordService;
   }
}

namespace dbo = Wt::Dbo;

class session : public dbo::Session
{
public:
	session();
	static void configureAuth();
	BlogUserDatabase& users();
	Wt::Auth::Login& login();

        dbo::ptr<user>  userFunc() const;
        static const Wt::Auth::AuthService& auth();
	Wt::Auth::PasswordService *passwordAuth() const;


private:
	dbo::backend::Sqlite3 connection_;
	BlogUserDatabase users_;
	Wt::Auth::Login login_;
};

#endif
