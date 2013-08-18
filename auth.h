/******************************************************
FileName: auth.h

Description: Contains Declarations of class AuthForm

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh

License: GNU GPL V3

******************************************************/

#ifndef AUTH_H_
#define AUTH_H_
#include <Wt/WContainerWidget>

#include <Wt/Auth/AuthModel>
#include <Wt/Auth/AuthWidget>
#include <Wt/Auth/PasswordService>

#include "global.h"

//! Class for Authentication Forms
/*!
  This class is inherited from WContainer Widget, it configures and displays the authentication form.
  All the authentication related tasks are handlend by this Class
*/

class AuthForm : public Wt::WContainerWidget 
{
private:
//! Container for the dashboard
      WContainerWidget *dashContainer;
      Session session_;
public:	

//! A constructor for Authentication Form
/*! A constructor that accepts a WContainerWidget as a parent, then checks if there is a change in user session (logged in or logout) and depending upon that calls a function n authEvent, which performs the related authentication task.
	It creates and configures AuthWidget from Wt::Auth::AuthWidget which gives us the front end part of our Authentication form. 
*/
	AuthForm(Wt::WContainerWidget *parent);

//! A function that performs Authentication task
/*!
authEvent() is called by constructor whenever there is a change in the state of session (logs in or logs out), and depending upon that auth event performs the necessary task 
It also logs whenever a user logs in or logs out
*/
	void authEvent();
//! A function to provide the register facility
/*!
   registerAdmin() is called in the constructor of this class, It first checks whether the admin is already registered or not. If not, it provides with the registration values otherwise those fields are not visible.
*/
        void registerAdmin();
//! AuthWidget, making a common widget for all auth related things like login, register and logout
         Wt::Auth::AuthWidget *authWidget;
         bool setLogin;

};
#endif
