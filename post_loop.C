/******************************************************

FileName: post_loop.C

Description: Holds the definition of class for posts widget

Author: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh

License GNU GPL V3

***********************************************************/ 

#include "post_loop.h"
#include "add_theme.h"

#include <Wt/WLink>

string loopTemplate, postTemplate;

PostLoop::PostLoop(WContainerWidget *parent)
         :WContainerWidget(parent)
{
    postContainer      = new WContainerWidget(this);
    categoryCollection = new WContainerWidget(this);
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
     categoryCollection = new WContainerWidget(this);
     categoryCollection->setStyleClass("category-container");

     for (auto i:allPosts)
     {
        singlePostName = new WAnchor(WLink(WLink::InternalPath,(i)->permalink), (i)->postName, postContainer);

        WTemplate* loop = new WTemplate(postContainer);
        loop->setTemplateText(loopTemplate);
        loop->bindString("post-date",    i->postDate);
        loop->bindWidget("post-title",   singlePostName);
        loop->bindString("post-content", i->postContent);

        for(auto k:i->categories)
        {
          category = new WAnchor(WLink(WLink::InternalPath, k->categoryLink), k->categoryname + " ", categoryCollection);
          category->setStyleClass("post-content");
        }
     }

}

void PostLoop::handlePath()
{
   pathString = WApplication::instance()->internalPath();
   postContainer->clear();
   categoryCollection->clear();
   try
   {
      categoryFilter();
   }
   catch(std::exception &e)
   {
      permalinkFilter();
   }
}

void PostLoop::permalinkFilter()
{
   {
    dbo::Transaction t(session_);
    dbo::ptr<Post> postPtr = session_.find<Post>().where("permalink = ?").bind(pathString);
    singlePostTemplate = new WTemplate(this);
    singlePostTemplate->setTemplateText(postTemplate);
    singlePostTemplate->bindString("post-name",    postPtr->postName);
    singlePostTemplate->bindString("post-content", postPtr->postContent);
    singlePostTemplate->bindString("post-date",    postPtr->postDate);
    t.commit();
   }
}

void PostLoop::categoryFilter()
{
   postContainer->clear();
   new WText("<h2>" + pathString + "</h2>", postContainer);
   {
     dbo::Transaction t(session_);
     dbo::ptr<Category> categoryPtr = session_.find<Category>().where("categoryLink = ?").bind(pathString);
     
     for (auto x: categoryPtr->posts)
     {
      WTemplate *filterLoop = new WTemplate(this);
      filterLoop->setTemplateText(loopTemplate);
      filterLoop->bindString("post-date",    x->postDate);
      filterLoop->bindString("post-title",   x->postName);
      filterLoop->bindString("post-content", x->postContent);      
     }

     t.commit();
    }
}
