/************************************************************

Filename: dashboard.C

Description: Provides a admin dashboard 

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh, Amitoj Singh

License: GNU GPL V3

*************************************************************/

#include "dashboard.h"

dashboard::dashboard(WContainerWidget *parent):WContainerWidget(parent)
   {
     defaultContainer = new WContainerWidget(this);
     adminTab = new WTabWidget(defaultContainer);
     adminTab->addTab(new PostPad(defaultContainer), "add-post", WTabWidget::PreLoading);
     adminTab->addTab(new settingPannel(defaultContainer), "settings", WTabWidget::PreLoading);
     adminTab->addTab(new allPost(defaultContainer), "all-posts", WTabWidget::PreLoading);
   }

