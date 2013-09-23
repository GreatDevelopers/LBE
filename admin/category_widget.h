/************************************************************

Filename: post_pad.C

Description: widget of admin panel that adds posts

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh, Amitoj Singh

License: GNU GPL V3

*************************************************************/

#ifndef _CATEGORY_WIDGET_H
#define _CATEGORY_WIDGET_H

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WCheckBox>

#include "../post.h"
#include "../global.h"

using namespace Wt;

//! vector containing all the checked checkboxes
extern vector<WCheckBox*> allCategories;

//! Class providing the widget for adding categories
/*! 
    CategoryWidget class provides with a options to select from existing cateogories or insert a new category. It consist of checkboxes of existing categories and input text field to add new category
*/
class CategoryWidget : public WContainerWidget
{
public:
//! Constructor for rendering the category widget
CategoryWidget(WContainerWidget *parent);
//! Function to retrieve the existing categories
void getCategory();
//! Function to add new Categories
void newCategory();
//! Function to check whether the category already exist or not
void checkCategory();
private:
//! container holding the category widget
WContainerWidget *categoryContainer;
//! Button to save new categories
WPushButton *saveCategory;
//! input field for adding new category
WLineEdit *categoryEdit;
//! Checkboxes to show the checkboxes
WCheckBox* checkbox;
Session session_;
dbo::ptr<Category> categoryPointer;
};

#endif
