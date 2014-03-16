#include "auth.h"
#include <Wt/WText>
#include "admin/dashboard.h"

AuthForm::AuthForm(WContainerWidget *parent)
	 :WContainerWidget(parent)
{
   adminLoggedIn = false;
   session_.login().changed().connect(this, &AuthForm::authEvent);
   authEvent();
   authwidget = new Auth::AuthWidget(session::auth(), session_.users(), session_.login());

   authwidget->model()->addPasswordAuth(session_.passwordAuth());


   authwidget->processEnvironment();

   this->addWidget(authwidget);
}

void AuthForm::authEvent()
{

   if(session_.login().loggedIn())
   {
      if(checkAdmin()){
         dashContainer = new WContainerWidget(this);
         new dashboard(dashContainer);
         adminLoggedIn = true;
      }
      else{ 
         new WText("Thanks for registering, fella :D", dashContainer);
      }
   }
   else
   {
      std::cout<<"you are not logged in bai";
      if(adminLoggedIn)
      {
         dashContainer->clear();
      }
   }
}

bool AuthForm::checkAdmin()
{
   if(session_.userFunc() && session_.userFunc()->role == user::Admin)
      return true;
   else
      return false;
}
