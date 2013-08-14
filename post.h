#ifndef POST_H_
#define POST_H_

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/SqlConnection>

#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/WBreak>

#include <string>

using namespace std;
using namespace Wt;
namespace dbo = Wt::Dbo;

class Post;

typedef dbo::collection< dbo::ptr<Post> > PostCollection;

class Post {
public: string postName, postContent, permalink, postDate;

	template<class Action>
	void persist(Action& a) {
	dbo::field(a, postName,    "postname");
	dbo::field(a, postDate,    "postdate");
	dbo::field(a, permalink,   "permalink");
	dbo::field(a, postContent, "postcontent");
	}
};

#endif
