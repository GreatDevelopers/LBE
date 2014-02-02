#ifndef USER_H_
#define USER_H_

#include <Wt/Dbo/Dbo>
#include <Wt/WString>
#include <Wt/Dbo/Types>
#include <Wt/WDateTime>

namespace dbo = Wt::Dbo;
using namespace Wt;

class Token;

typedef dbo::collection< dbo::ptr<Token> > Tokens;

class user{
public: user();
	enum Role{
	Visitor = 0,
	Admin   = 1
	};

	Role role;
        Tokens authTokens;
        WString name;
        std::string password, passwordMethod, passwordSalt;
        int failedLoginAttempts;
        Wt::WDateTime lastLoginAttempt;

	template<class Action>
	void persist(Action& a){	
		dbo::field(a, name,                "name" );
                dbo::field(a, role,                "role");
                dbo::field(a, password,            "password");
                dbo::field(a, passwordSalt,        "password_salt");
                dbo::field(a, passwordMethod,      "password_method");
                dbo::field(a, lastLoginAttempt,    "last_login_attempts");
                dbo::field(a, failedLoginAttempts, "failed_login_attempts");
 
                dbo::hasMany(a, authTokens, dbo::ManyToOne, "user");


	}
};

DBO_EXTERN_TEMPLATES(user);

#endif
