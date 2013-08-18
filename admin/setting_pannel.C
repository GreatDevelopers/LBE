/************************************************************

Filename: setting_pannel.C

Description: Provides with a settings widget in admin pannel

Authors: Gauravjeet Singh, Inderpreet Singh, Shaina Sabaarwal

License: GNU GPL V3

*************************************************************/

#include "setting_pannel.h"
#include <Wt/WBreak>
#include <Wt/WApplication>

settingPannel::settingPannel(WContainerWidget *parent):WContainerWidget(parent)
{
   settingContainer = new WContainerWidget(this);

   new WText("Title of Blog: ", settingContainer);
   titleEdit = new WLineEdit(settingContainer); 
  
   settingContainer->addWidget(new WBreak());
  
   new WText("Tagline of Blog: ", settingContainer);
   taglineEdit = new WLineEdit(settingContainer);

   settingContainer->addWidget(new WBreak());

   saveButton = new WPushButton("Save", settingContainer);
   saveButton->clicked().connect(this, &settingPannel::saveSettings);
}

void settingPannel::saveSettings()
{
   {
     dbo::Transaction t(session_);
     userPtr = session_.find<User>().where("name = ?").bind("admin");
     userPtr.modify()->title = titleEdit->text().toUTF8();
     userPtr.modify()->tagline = taglineEdit->text().toUTF8(); 
     t.commit();
   }
   new WText("Settings saved, refresh to see changes", this);
}

