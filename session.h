/******************************************************
FileName: session.h
*
Description: Contains Declarations of class Session
*
Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh
*
License: GNU GPL V3
*
******************************************************/

#ifndef SESSION_H_
#define SESSION_H_

#include <Wt/Auth/Login>

#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>

#include "user.h"

namespace dbo = Wt::Dbo;

typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

//! Class for Application Session
/*!
   This class is inherited from Wt::dbo::Session. It provides with a common sesion, which handles the complete application.
   All the Session related task like transaction etc are handled by with this class
*/
class Session : public dbo::Session
{
	public:
		//!A function that configures the Authentication Session related tasks
		/*!
		   This function is called in a main function, after the start of Wt server.
		   It does various configuration needed to start basic authentication of application.
		*/
		static void configureAuth();

		//! Constructor for class Session
		/*! This is constructor for class Session. No arguments are provided.
		    It is used to start a different session everytime we start this application
		*/
		Session();

		//! Destructor for class Session
		/*!
		    This is destructor for class Session. It destroys the session when we close this application.
		*/
		~Session();

		//! It returns the ponter of user stored in the database
		dbo::ptr<User> user() const;

		//! It returns reference to Wt::Auth::AbstractUserDatabase
		Wt::Auth::AbstractUserDatabase& users();

		//! It returns object login_ that signals the change in login state.
		Wt::Auth::Login& login() {return login_; }

		//! It returns object of Wt::Auth::AuthService
		static const Wt::Auth::AuthService& auth();

		//! It returns object of Wt::Auth::PasswordService
		static const Wt::Auth::PasswordService& passwordAuth();

	private:
		//! It is used to make connection to the database
		dbo::backend::Sqlite3 connection_;

		//! A pointer object that serves as a basic dbo implementation
		UserDatabase *users_;

		//! It fires a signal everytime there is change in login state
		Wt::Auth::Login login_;

//		std::string sqliteDb;
};

#endif
