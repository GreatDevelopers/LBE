#ifndef TOKEN_H_
#define TOKEN_H_

#include <Wt/WDate>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>

#include "user.h"

namespace dbo = Wt::Dbo;

class Token : public dbo::Dbo<Token>
{
public: Token();
        Token(const std::string& value, const Wt::WDateTime& expires);

        dbo::ptr<user> userPointer;
        std::string value;
        Wt::WDateTime expires;

        template<class Action>
        void persist(Action& a)
        {
           dbo::field(a, value,  "value");
           dbo::field(a, expires,"expires");

           dbo::belongsTo(a, userPointer, "user");
        }
};

#endif
