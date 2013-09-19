/************************************************************

Filename: post_pad.C

Description: widget of admin panel that adds posts

Authors: Gauravjeet Singh, Inderpreet Singh, Shaina Sabarwal

License: GNU GPL V3

*************************************************************/

#include "category_widget.h"

vector <WCheckBox*> allCategories;

CategoryWidget::CategoryWidget(WContainerWidget *parent)
               :WContainerWidget(parent)
{
   categoryContainer = new WContainerWidget(this);
   getCategory();
   
   new WText("Add new", this);
   categoryEdit = new WLineEdit(this);

   saveCategory = new WPushButton("Add", this);
   saveCategory->clicked().connect(this, &CategoryWidget::checkCategory);
}

void CategoryWidget::getCategory()
{
   allCategories.clear();
   {
      dbo::Transaction t(session_);
      CategoryCollection collection = session_.find<Category>();
      for(auto i: collection)
      {
         checkbox = new WCheckBox(i->categoryname, categoryContainer);
         categoryContainer->addWidget(new WBreak());
         allCategories.push_back(checkbox);
      }
      t.commit();
   }
}

void CategoryWidget::checkCategory()
{
   try{
         {
         dbo::Transaction t(session_);
         categoryPointer = session_.find<Category>().where("categoryname = ?").bind(categoryEdit->text().toUTF8());
         t.commit();
         }
         new WText(categoryPointer->categoryname + " already exists",categoryContainer);
      }
   catch(exception& e){
      newCategory();
   }
}
void CategoryWidget::newCategory()
{
   new WText("Loading categories", categoryContainer);
   {
      dbo::Transaction t(session_);
      Category *newCategory = new Category();
      newCategory->categoryname = categoryEdit->text().toUTF8();
      newCategory->categoryLink = "/Category-archives:" + categoryEdit->text().toUTF8();
      dbo::ptr<Category> catPtr = session_.add(newCategory);
      t.commit();
   }
   categoryContainer->clear();
   categoryEdit->setText("");
   getCategory();
}
