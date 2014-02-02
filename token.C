
#include "token.h"

#include <Wt/Dbo/Impl>

Token::Token()
{ }

Token::Token(const std::string& v, const Wt::WDateTime& e)
      :value(v),
       expires(e)
{ }
