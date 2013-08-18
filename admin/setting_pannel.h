/************************************************************

Filename: setting_pannel.h

Description: Containes declarations for settings widget in
             pannel

Authors: Gauravjeet Singh, Inderpreet Singh, Shaina Sabaarwal

License: GNU GPL V3

*************************************************************/

#ifndef SETTING_PANNEL_H
#define SETTING_PANNEL_H

#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "../user.h"
#include "../post.h"
#include "../global.h"

using namespace Wt;

//! Class providing the user with various general settings
/*!
   This class allows user to customize the blog. It gives user power to control it's own blog.
   It consist of various things like changing the title, tagline, etc.
*/
class settingPannel: public WContainerWidget
{
public:
//! It renders all the things required to take input from user
     settingPannel(WContainerWidget *parent);
//! It saves all the provided settings
     void saveSettings();

private:
//! Parent Container to all the settings widgets
     WContainerWidget *settingContainer;
//! Input field to input main title
     WLineEdit *titleEdit;
//! Input field to add tagline
     WLineEdit *taglineEdit;
//! Button to save all the changes
     WPushButton *saveButton;
//! dbo smart pointer that points to user admin 
     dbo::ptr<User> userPtr;
     Session session_;
};

#endif
