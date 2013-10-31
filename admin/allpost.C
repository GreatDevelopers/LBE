/*******************************************************

Filename: allpost.C

Description: Widget of admin panel that contain all posts

Authors: Gauravjeet Singh, Shiana Sabarwal, Inderpreet Singh Amitoj Singh

License: GNU GPL V3

******************************************************/

#include "allpost.h"

string allpostsTemplate;
allPost::allPost(WContainerWidget *parent)
       :WContainerWidget(parent)
{
    allContainer =new WContainerWidget(this);
    {
       editButton=new WPushButton("Edit",this);

       editButton->clicked().connect(this,&allPost::edit);
       deleteButton= new WPushButton("delete",this);
       deleteButton->clicked().connect(this,&allPost::postDelete);

       dbo::Transaction T(session_);
       storedPost=session_.find<Post>();
       allLoop();

       T.commit();
     }
}

void allPost::allLoop()
{
    for (auto i:storedPost)
    {
      container=new WContainerWidget(this);
      new WText(i->postName,container);
      new WBreak(container);
      link=new WCheckBox(i->permalink,container);
       linkCollection.push_back(link);
    }
}

void allPost::edit()
{   
    for(auto k: linkCollection)
    {
       if(k->isChecked())
       {
          selectedPost = k->text().toUTF8();
       }
    }
   container->hide();
    
{
    dbo::Transaction t(session_);
    dbo::ptr<Post> allPostPtr= session_.find<Post>().where("permalink = ?").bind(selectedPost);
   
    updateContainer= new WContainerWidget(this);
    updateName=new WLineEdit(allPostPtr->postName,updateContainer);
    new WBreak(updateContainer);
    updateContent =new WTextArea(allPostPtr->postContent,updateContainer);
    updateContent ->setStyleClass("updateContent");
    new WBreak(updateContainer);
    updateDate=new WLineEdit(allPostPtr->postDate,updateContainer);
    updateButton=new WPushButton("update",updateContainer);
    updateButton->clicked().connect(this,&allPost::update);
    t.commit();
}
}

void allPost::postDelete()
{
    container->hide();
    containerDelete=new WContainerWidget(this);
    new WBreak(this);
    new WText("WARNING! Are you sure you want to delete?",containerDelete);
    new WBreak(containerDelete);
    yes = new WPushButton("Yes",containerDelete);
    yes->clicked().connect(this,&allPost::deleted);
    cancel = new WPushButton("cancel",containerDelete); 
    cancel->clicked().connect(this, &allPost::allLoop);
    }

void allPost::deleted()
{
      containerDelete->hide();
      for(auto k: linkCollection)
      {
         if(k->isChecked())
         {
           selectedPost =k->text().toUTF8();	
         }
      }
     new WBreak(this);
     new WText("Post is deleted successfully",this);    
    dbo::Transaction t(session_);
    dbo::ptr<Post> allPostPtr= session_.find<Post>().where("permalink=?").bind(selectedPost);
    allPostPtr.remove();
    t.commit();
}

void allPost::update()
{
    updateContainer->hide();
 
    dbo::Transaction t(session_);
    dbo::ptr<Post> allPostPtr= session_.find<Post>().where("permalink = ?").bind(selectedPost);
    allPostPtr.modify()->postName    =  updateName->text().toUTF8();
    allPostPtr.modify()->postDate    =  updateDate->text().toUTF8();
    allPostPtr.modify()->postContent =  updateContent->text().toUTF8();
    t.commit();
    new WBreak(this);
    new WText("Post is updated sucessfully",this);
}
