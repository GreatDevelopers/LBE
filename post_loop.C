/******************************************************

FileName: post_loop.C

Description: Holds the definition of class for posts widget

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh, Amitoj Singh

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
          
	  postText = new WText(contentStream.str());
	  
	  WTemplate* loop = new WTemplate(postContainer);
	  loop->setTemplateText(loopTemplate);
	  loop->bindWidget("post-title",   singlePostName);
	  loop->bindWidget("post-content", postText);
	  loop->bindString("post-date",    i->postDate);
     loop->bindString("post-time",    i->timeString);
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
    singlePostTemplate->bindString("post-date",    postPtr->postDate);
    singlePostTemplate->bindString("post-time",    postPtr->timeString);
    t.commit();
   }
}
