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
       new WAnchor(WLink(WLink::InternalPath, k->categoryLink), k->categoryname + " ", postContainer);
       }
   }

}

void PostLoop::handlePath()
{
   pathString = WApplication::instance()->internalPath();
   postContainer->clear();

   try 
   {
    {
     dbo::Transaction t(session_);
     dbo::ptr<Post> postPtr = session_.find<Post>().where("permalink = ?").bind(pathString);
     filterPosts.insert(postPtr);
     t.commit();
    }
   }
   catch(std::exception &e)
   {
    {
     dbo::Transaction t(session_);
     dbo::ptr<Category> categoryPtr = session_.find<Category>().where("categoryLink = ?").bind(pathString);
     filterPosts = categoryPtr->posts;
     t.commit();
    }
   } 
   
    for(auto p : filterPosts)
    {
    singlePostTemplate = new WTemplate(this);
    singlePostTemplate->setTemplateText(postTemplate);
    singlePostTemplate->bindString("post-name",    p->postName);
    singlePostTemplate->bindString("post-content", p->postContent);
    singlePostTemplate->bindString("post-date",    p->postDate);
    } 
}

/*
void PostLoop::categoryFilter()
{
   postContainer->clear();
   new WText("<h2>" + pathString + "</h2>", postContainer);
   {
    dbo::Transaction t(session_);
    dbo::ptr<Category> categoryPtr = session_.find<Category>().where("categoryLink = ?").bind(pathString);
     int i = 1;
    for (auto x: categoryPtr->posts)
    {
      cout<<"___"<<i<<"___"<<x->postName<<"____";

      WAnchor *postLink = new WAnchor(WLink(WLink::InternalPath, "/"+x->postName), x->postName, postContainer);
      WTemplate *filterLoop = new WTemplate(this);
      filterLoop->setTemplateText(loopTemplate);
      filterLoop->bindString("post-date",    x->postDate);
      filterLoop->bindWidget("post-title",   postLink);
      filterLoop->bindString("post-content", x->postContent);
      
      i++;
    }
    t.commit();
    }
}*/
