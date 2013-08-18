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
class Category;
typedef dbo::collection< dbo::ptr<Post> > PostCollection;
typedef dbo::collection< dbo::ptr<Category> > CategoryCollection;
class Post {
public: string postName, postContent, permalink;

	dbo::collection <dbo::ptr<Category> > categories;
	template<class Action>
	void persist(Action& a) {
	dbo::field(a, postName,    "postname");
	dbo::field(a, permalink,   "permalink");
	dbo::field(a, postContent, "postcontent");
	
	dbo::hasMany(a, categories, dbo::ManyToMany, "post_cat");
	}
};

class Category {
public: string categoryname, checkedcat;

	dbo::collection <dbo::ptr<Post> > posts;
	template<class Action>
	void persist(Action& a) {
	dbo::field(a, categoryname, "categoryname");
	dbo::field(a, checkedcat, "checkedcat");

	dbo::hasMany(a, posts, dbo::ManyToMany, "post_cat");
	}
};
#endif
