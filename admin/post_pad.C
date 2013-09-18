/************************************************************

Filename: post_pad.C

Description: widget of admin panel that adds posts

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh, Amitoj Singh

License: GNU GPL V3

*************************************************************/

#include "post_pad.h"

PostPad :: PostPad (WContainerWidget *parent)
        : WContainerWidget(parent),
	postContent(this,"getPostContent")
{
    published = false;
    WApplication::instance()->require("../resources/epic_editor/js/epiceditor.js");
    strm<<"var editor = new EpicEditor().load();";
    WApplication::instance()->doJavaScript(strm.str());

    postTitle = new WLineEdit(this);
    postTitle->setEmptyText("Title of post");

    postLink = new WLineEdit(this);
    postLink->setEmptyText("Permalink");

    postEditor = new WContainerWidget(this);
    postEditor->setId("epiceditor");   

    submitPost = new WPushButton("Submit", this);
    submitPost->clicked().connect(this,&PostPad::getPost);
    postContent.connect(this, &PostPad::storePost);
    timeContainer= new WContainerWidget(this);
    time = new WTime();
    timeString=time->currentServerTime().toString("hh:mm:ss AP");
    timeEdit=new WLineEdit(this);
    time->fromString(timeString,"hh:mm:ss AP");
    timeEdit->setText(timeString);

    dateContainer = new WContainerWidget(this);
    dateEdit = new WLineEdit(dateContainer);
    date = new WDatePicker(dateEdit, dateContainer);
    date->setDate(WDate::currentServerDate());
    
}

void PostPad :: getPost()
{   
    strm<<postContent.createCall("editor.getElement('previewer').getElementById('epiceditor-preview').innerHTML");
    WApplication::instance()->doJavaScript(strm.str());  
}

void PostPad :: storePost(std::string postContentStr)
{
    if(!published)
    {
      {
       dbo::Transaction t(session_);
       Post *newPost = new Post();
       newPost->postName    = postTitle->text().toUTF8();
       newPost->postContent = postContentStr;
       newPost->permalink   = "/" + postLink->text().toUTF8();
       newPost->postDate    = dateEdit->text().toUTF8();
       newPost->timeString  = timeString.toUTF8();
       postPtr = session_.add(newPost);
       t.commit();
      }
      published = true;
    }
    else
    {
      {
       dbo::Transaction t(session_);
       postPtr.modify()->postName = postTitle->text().toUTF8();
       postPtr.modify()->postContent = postContentStr;
       postPtr.modify()->permalink = "/" + postLink->text().toUTF8();
       postPtr.modify()->postDate = dateEdit->text().toUTF8();
       postPtr.modify()->timeString = timeString.toUTF8();
       t.commit();
      }
    }
}

