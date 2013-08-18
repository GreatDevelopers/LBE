/************************************************************************
FileName:  auth.C

Description: Holds the definition of class for Authentication widget

Details:
auth.C files contains a definition of class named AuthForm that is inherited 
from WContainer widget, this class is then used in main WApplication for creating 
an auth form.

Author: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh

License: GNU GPL V3

**************************************************************************/
#include "auth.h"
#include "admin/dashboard.h"

#include <Wt/WDateTime>

AuthForm::AuthForm(WContainerWidget *parent)
	:WContainerWidget(parent)
	{
                setLogin = false;
		session_.login().changed().connect(this,&AuthForm::authEvent);
                authEvent();
 

		authWidget = new Wt::Auth::AuthWidget(Session::auth(), session_.users(),
						session_.login());
		
		authWidget->model()->addPasswordAuth(&Session::passwordAuth());

		authWidget->processEnvironment();

                registerAdmin();
                                
		this->addWidget(authWidget);
	}

	void AuthForm::authEvent() {
	if(session_.login().loggedIn()){
		Wt::log("notice") << "User" << session_.login().user().id()
					<<"logged in.";
            dashContainer = new WContainerWidget(this);
            new dashboard(dashContainer);
            setLogin = true;
	}
	else {
		Wt::log("notice") << "User logged out.";
                if(setLogin)
                {
                 cout<<setLogin;
                 dashContainer->clear();
                }
             }
	}

void AuthForm :: registerAdmin()
{
   try{
        {
        dbo::Transaction t(session_);
        dbo::ptr<User> admin = session_.find<User>().where("name=?").bind("admin");
        std::string adminString = admin->name;
        t.commit();
        }
   }
   catch(exception& e){
      {
      dbo::Transaction t(session_);
      User *newUser = new User();
      newUser->name = "admin";
      dbo::ptr<User> newAdmin = session_.add(newUser);
      t.commit();
      }
      authWidget->registerNewUser();
   }
}
