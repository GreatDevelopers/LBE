/************************************************************

Filename: post_pad.C

Description: widget of admin panel that adds posts

Authors: Gauravjeet Singh, Inderpreet Singh, Shaina Sabarwal

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

    categoryContainer = new WContainerWidget(this);
    
    getCategory();

    new WBreak(this);    
    new WText("Add New ", this);
    NewCategory = new WLineEdit(this);

    save_but = new WPushButton("Save", this);
    save_but->clicked().connect(this, &PostPad::NewCat);
    new WBreak(this);

    submitPost = new WPushButton("Submit", this);
    submitPost->clicked().connect(this,&PostPad::getPost);
    postContent.connect(this, &PostPad::storePost);

    dateContainer = new WContainerWidget(this);
    dateEdit = new WLineEdit(dateContainer);
    date = new WDatePicker(dateEdit, dateContainer);
    date->setDate(WDate::currentServerDate());

}

void PostPad :: NewCat()
{
  {
	dbo::Transaction T(session_);
	Category *cat = new Category();
        cat->categoryname = NewCategory->text().toUTF8();
        dbo::ptr <Category> catPtr = session_.add(cat);
	T.commit();
  }
  categoryContainer->clear();
  getCategory();
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
     for(auto j: checked_cat)
      {
	if(j->isChecked()) {
	string_cat.push_back(j->text().toUTF8());}
      }
	copy(string_cat.begin(), string_cat.end(), ostream_iterator<string>(ss,"\n"));

    {
       dbo::Transaction t(session_);	
       Post *newPost = new Post();
       newPost->postName    = postTitle->text().toUTF8();
       newPost->postContent = postContentStr;
       newPost->permalink   = "/" + postLink->text().toUTF8();
       newPost->postDate    = dateEdit->text().toUTF8();
       postPtr = session_.add(newPost);
       catPtr = session_.add(new Category);
       catPtr.modify()->checkedcat = ss.str();
       postPtr.modify()->categories.insert(catPtr);
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
       catPtr.modify()->checkedcat = ss.str();
       postPtr.modify()->categories.insert(catPtr);
       t.commit();
      }
    }
}
void PostPad :: getCategory()
{

    new WText("Categories",categoryContainer);
        {
          dbo::Transaction T(session_);
          dbo::collection <dbo::ptr<Category> > cat_Ptr = session_.find<Category>();
          for(auto i: cat_Ptr)
          {
                checkbox = new WCheckBox(i->categoryname, categoryContainer);
                categoryContainer->addWidget(new WBreak());
                checked_cat.push_back(checkbox);
          }
          T.commit();
        }
}

