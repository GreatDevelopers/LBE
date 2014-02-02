#ifndef AUTH_H_
#define AUTH_H_

#include <Wt/WContainerWidget>

#include <Wt/Auth/AuthModel>
#include <Wt/Auth/AuthWidget>
#include <Wt/Auth/PasswordService>

#include "global.h"

class AuthForm: public WContainerWidget
{
public:
	AuthForm(WContainerWidget *parent);
	void authEvent();
        bool checkAdmin();
private:
	session session_;
	Wt::Auth::AuthWidget *authwidget;

        bool adminLoggedIn;
        WContainerWidget *dashContainer;
};

#endif
