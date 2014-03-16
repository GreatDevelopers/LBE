/*******************************************************

Filename: allpost.C

Description: Widget of admin panel that contain all posts

Authors: Gauravjeet Singh, Shiana Sabarwal, Inderpreet Singh Amitoj Singh

License: GNU GPL V3

******************************************************/

#include "allpost.h"

allPost::allPost(WContainerWidget *parent)
       :WContainerWidget(parent),
	postContent(this, "getPostContent")
{
    allContainer =new WContainerWidget(this);
    {
       editButton=new WPushButton("Edit",this);
       linkGroup = new WButtonGroup();

       editButton->clicked().connect(this,&allPost::edit);
       deleteButton= new WPushButton("delete",this);
       deleteButton->clicked().connect(this,&allPost::postDelete);

       dbo::Transaction T(session_);
       storedPost = session_.find<Post>();
       allLoop();

       T.commit();
     }
    postContent.connect(this, &allPost::update);
}

void allPost::allLoop()
{

     for (auto i:storedPost)
    {
    container=new WContainerWidget(this);
    container->setStyleClass("post-view-admin");
      (new WText(i->postName,container))->setStyleClass("post-title-admin");
      new WBreak(container);
      link=new WRadioButton(i->permalink,container);
      linkGroup->addButton(link);
    }
}

void allPost::edit()
{  
   WRadioButton *selectedbtn = linkGroup->checkedButton(); 
   selectedPost = selectedbtn->text().toUTF8();
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

    //WApplication::instance()->require("../resources/epic_editor/js/epiceditor.js");
    //std::stringstream strm;
    //strm<<"var editor = new EpicEditor().load();";
    //WApplication::instance()->doJavaScript(strm.str());

    //updateContentEditor = new WContainerWidget(this);
    //updateContentEditor->setId("epiceditor");


    updateButton=new WPushButton("update",updateContainer);
    updateButton->clicked().connect(this,&allPost::update);
    t.commit();
}
}
/*
void allPost::getupdate()
{ 
    std::stringstream strm2;
    strm2<<postContent.createCall("editor.getElement('previewer').getElementById('epiceditor-preview').innerHTML");
    WApplication::instance()->doJavaScript(strm2.str());  
}*/

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
     WRadioButton *selectedbtn = linkGroup->checkedButton();
     string selectedpost = selectedbtn->text().toUTF8();
     new WBreak(this);
     new WText("Post is deleted successfully",this);    
    dbo::Transaction t(session_);
    //post_ = session_.query< dbo::ptr<Post> >("DELETE FROM post WHERE permalink=?").bind(selectedPost);
    session_.execute("delete from post where permalink = ?").bind(selectedPost);
    //dbo::ptr<Post> allPostPtr = session_.find<Post>.where("permalink = ?").bind(selectedPost);
    //dbo::ptr<Post> allPostPtr= session_.find<Post>().where("permalink = ?").bind(selectedPost);

    try{	
    dbo::ptr<Post> allPostPtr= session_.find<Post>().where("permalink=?").bind(selectedPost);
    std::string a = allPostPtr->permalink;
    }
    catch(std::exception &e){
    cout<<"deleted_________________________________";
   }
    t.commit();
}

void allPost::update()
{
    updateContainer->hide();
    container->show(); 
    dbo::Transaction t(session_);
    dbo::ptr<Post> allPostPtr= session_.find<Post>().where("permalink = ?").bind(selectedPost);
    allPostPtr.modify()->postName    =  updateName->text().toUTF8();
    allPostPtr.modify()->postDate    =  updateDate->text().toUTF8();
    allPostPtr.modify()->postContent =  updateContent->text().toUTF8(); 
    t.commit();
    new WBreak(this);
    new WText("Post is updated sucessfully",this);
}
