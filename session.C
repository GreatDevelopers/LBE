/************************************************************************
FileName:  session.C

Description: Holds the definition of class for Application Session

Details:
session.C file contains a definition of class named Session that is inherited 
from Wt::Dbo::Session, this class provides a common session to be used by all

Author: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh

License: GNU GPL V3

**************************************************************************/

#include "session.h"
#include "user.h"
#include "post.h"

#include <Wt/Auth/AuthService>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/GoogleService>
#include <Wt/Auth/FacebookService>
#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>

//! Object of class Auth Service and Password Service
/*!
   myAuthService is object of class Wt::Auth::AuthService and myPasswordService is a object of Wt::Auth::PasswordService, it takes myAuthService as parameter
*/
namespace {

	Wt::Auth::AuthService myAuthService;
	Wt::Auth::PasswordService myPasswordService(myAuthService);
}

void Session::configureAuth()
{
	myAuthService.setAuthTokensEnabled(true,"logincookie");
	myAuthService.setEmailVerificationEnabled(true);

	Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
	verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
	myPasswordService.setVerifier(verifier);
	myPasswordService.setAttemptThrottlingEnabled(true);
	myPasswordService.setStrengthValidator
		(new Wt::Auth::PasswordStrengthValidator());

}

Session::Session(): connection_("laka.db")
{
  connection_.setProperty("show-queries", "true");

  setConnection(connection_);

  mapClass<User>("user");
  mapClass<Post>("post");
  mapClass<AuthInfo>("auth_info");
  mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<AuthInfo::AuthTokenType>("auth_token");
  mapClass<Category> ("category");

  try {
    createTables();
    std::cerr << "Created database." << std::endl;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Using existing database";
  }

  users_ = new UserDatabase(*this);
}

Session::~Session()
{
  delete users_;
}

Wt::Auth::AbstractUserDatabase& Session::users()
{
  return *users_;
}

dbo::ptr<User> Session::user() const
{
  if (login_.loggedIn()) {
    dbo::ptr<AuthInfo> authInfo = users_->find(login_.user());
    return authInfo->user();
  } else
    return dbo::ptr<User>();
}

const Wt::Auth::AuthService& Session::auth()
{
  return myAuthService;
}

const Wt::Auth::PasswordService& Session::passwordAuth()
{
  return myPasswordService;
}

