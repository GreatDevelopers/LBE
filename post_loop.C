/******************************************************

FileName: post_loop.C

Description: Holds the definition of class for posts widget

Author: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh

License GNU GPL V3

***********************************************************/ 

#include "post_loop.h"
#include "add_theme.h"

#include <Wt/WLink>

string loopTemplate;
string postTemplate;

PostLoop::PostLoop(WContainerWidget *parent)
    :WContainerWidget(parent)
{
    postContainer = new WContainerWidget(this);
    {
      dbo::Transaction T(session_);
      allPosts = session_.find<Post>();
      theLoop();
      T.commit();
    }
}

void PostLoop::theLoop()
{
     handleThemeFile();
  
     for (auto i:allPosts)
	{
          singlePostName = new WAnchor(WLink(WLink::InternalPath,(i)->permalink), (i)->postName, postContainer);
          contentStream.str("");
          
          contentStream<<(i)->postContent;
	  for(auto k:i->categories)
	  cat_str = (k)->checkedcat;
          
	  postText = new WText(contentStream.str());
	  postCat = new WText(cat_str);
	  WTemplate* loop = new WTemplate(postContainer);
	  loop->setTemplateText(loopTemplate);
	  loop->bindWidget("post-title",   singlePostName);
	  loop->bindWidget("post-content", postText);
	  loop->bindWidget("categories", postCat);
        }
}

void PostLoop::handlePath()
{
   postContainer->clear();
   singlePostTemplate = new WTemplate(this);
   singlePostTemplate->setTemplateText(postTemplate);

   postPath = WApplication::instance()->internalPath();
   {
    dbo::Transaction t(session_);
    dbo::ptr<Post> postPtr = session_.find<Post>().where("permalink = ?").bind(postPath);
    singlePostTemplate->bindString("post-name",    postPtr->postName);
    singlePostTemplate->bindString("post-content", postPtr->postContent);
    singlePostTemplate->bindString("categories", cat_str);
    t.commit();
   }
}
