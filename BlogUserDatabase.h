
#ifndef BLOG_USER_DATABASE_H_
#define BLOG_USER_DATABASE_H_

#include <Wt/Auth/AbstractUserDatabase>
#include <Wt/Dbo/Types>

#include "user.h"
#include "token.h"

namespace dbo = Wt::Dbo;

class BlogUserDatabase : public Wt::Auth::AbstractUserDatabase
{
public:
  BlogUserDatabase(dbo::Session& session);

  virtual Transaction *startTransaction();

  dbo::ptr<user> find(const Wt::Auth::User& user) const;
  Wt::Auth::User find(dbo::ptr<user> user) const;

  virtual Wt::Auth::User findWithId(const std::string& id) const;

  virtual Wt::Auth::User findWithIdentity(const std::string& provider,
					  const Wt::WString& identity) const;

  virtual void addIdentity(const Wt::Auth::User& user,
			   const std::string& provider,
			   const Wt::WString& identity);

  virtual Wt::WString identity(const Wt::Auth::User& user,
			       const std::string& provider) const;

  virtual void removeIdentity(const Wt::Auth::User& user,
			      const std::string& provider);

  virtual Wt::Auth::PasswordHash password(const Wt::Auth::User& user) const;
  virtual void setPassword(const Wt::Auth::User& user,
			   const Wt::Auth::PasswordHash& password);

  virtual Wt::Auth::User::Status status(const Wt::Auth::User& user) const;
  virtual void setStatus(const Wt::Auth::User& user,
			 Wt::Auth::User::Status status);

  virtual Wt::Auth::User registerNew();

  virtual void addAuthToken(const Wt::Auth::User& user,
			    const Wt::Auth::Token& token);
  virtual void removeAuthToken(const Wt::Auth::User& user,
			       const std::string& hash);
  virtual Wt::Auth::User findWithAuthToken(const std::string& hash) const;

  virtual int failedLoginAttempts(const Wt::Auth::User& user) const;
  virtual void setFailedLoginAttempts(const Wt::Auth::User& user, int count);

  virtual Wt::WDateTime lastLoginAttempt(const Wt::Auth::User& user)
    const;
  virtual void setLastLoginAttempt(const Wt::Auth::User& user,
				   const Wt::WDateTime& t);

private:
  dbo::Session& session_;
  mutable dbo::ptr<user> user_;

  struct WithUser {
    WithUser(const BlogUserDatabase& self, const Wt::Auth::User& user);
    ~WithUser();

    dbo::Transaction transaction;
  };

  void getUser(const std::string& id) const;
};

#endif // USER_H_
