/******************************************************
FileName: session.h
*
Description: File for creating a presistence class for User and mapping authinfo with user. 
*
Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh
*
License: GNU GPL V3
*
******************************************************/

#ifndef USER_H_
#define USER_H_

#include <Wt/Dbo/Dbo>
#include <Wt/Auth/Dbo/AuthInfo>
/**
Wt::Dbo is a C++ ORM for making database driven applications with Witty
*/

namespace dbo = Wt::Dbo;

class User;

/**
mapping AuthInfo with our User Class and for the ease referring it to as AuthInfo 
*/

typedef Wt::Auth::Dbo::AuthInfo<User> AuthInfo;

/**
Definition of class User
*/

class User {
public:

/** 
adding a persist function, persist function is used to create tables in database,
*/
	User();
	
	std::string name, title, tagline, category;
	template <class Action>
	void persist(Action& a)
	{
		dbo::field(a, name, "name" );
                dbo::field(a, title, "title");
                dbo::field(a, tagline,"tagline");
	}
};

#endif
