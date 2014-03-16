#include "session.h"
#include "token.h"
#include "post.h"
#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>

#include <Wt/Auth/AuthService>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/GoogleService>

using namespace Wt;

namespace {
  const std::string ADMIN_USERNAME = "admin";
  const std::string ADMIN_PASSWORD = "admin";

#ifdef HAVE_CRYPT
  class UnixCryptHashFunction : public Auth::HashFunction
  {
  public:
    virtual std::string compute(const std::string& msg, 
				const std::string& salt) const
    {
      std::string md5Salt = "$1$" + salt;
      return crypt(msg.c_str(), md5Salt.c_str());
    }

    virtual bool verify(const std::string& msg,
			const std::string& salt,
			const std::string& hash) const
    {
      return crypt(msg.c_str(), hash.c_str()) == hash;
    }

    virtual std::string name () const {
      return "crypt";
    }
  };
#endif // HAVE_CRYPT

  Auth::AuthService myAuthService;
  Auth::PasswordService myPasswordService(myAuthService);
}

namespace dbo = Wt::Dbo;

session::session()
	:connection_("laka.db"),
         users_(*this)
{

   connection_.setProperty("show-queries", "true");
   connection_.setDateTimeStorage(Wt::Dbo::SqlDateTime,
                                  Wt::Dbo::backend::Sqlite3::PseudoISO8601AsText);

   setConnection(connection_);

   mapClass<user>("user");
   mapClass<Token>("token");
   mapClass<Post>("post");
   mapClass<Category>("category");
   try {
       createTables();
       {
       dbo::Transaction t(*this);
         dbo::ptr<user> admin = add(new user());
         user *a = admin.modify();
         a->name = ADMIN_USERNAME;
         a->role = user::Admin;

     Auth::User authAdmin
       = users_.findWithIdentity(Auth::Identity::LoginName, a->name);
     myPasswordService.updatePassword(authAdmin, ADMIN_PASSWORD);
      t.commit();
      }
   }
   catch(std::exception& e){
       std::cerr<<e.what()<<std::endl;
       std::cerr<<"Using existing database";
   }
}

void session::configureAuth()
{
   myAuthService.setAuthTokensEnabled(true, "logincookie");
   myAuthService.setEmailVerificationEnabled(true);
   
   Auth::PasswordVerifier *verifier = new Auth::PasswordVerifier();
   verifier->addHashFunction(new Auth::BCryptHashFunction(7));
   myPasswordService.setVerifier(verifier);
   myPasswordService.setAttemptThrottlingEnabled(true);
}

dbo::ptr<user> session::userFunc() const
{
   if(login_.loggedIn())
      return users_.find(login_.user());
   else
      return dbo::ptr<user>();
}

const Wt::Auth::AuthService& session::auth()
{
   return myAuthService;
}

Auth::PasswordService *session::passwordAuth() const
{
  return &myPasswordService;
}

Wt::Auth::Login& session::login()
{
   return login_;
}

BlogUserDatabase& session::users()
{
   return users_;
}
