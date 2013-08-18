/************************************************************

Filename: category_pannel.h

Description: Containes declarations for category display widget 
	     in pannel

Authors: Shaina Sabarwal, Gauravjeet Singh, Inderpreet Singh

License: GNU GPL V3

*************************************************************/

#ifndef _CATEGORYPANNEL_H
#define _CATEGORYPANNEL_H

#include <Wt/WContainerWidget>
#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WBreak>

#include "../user.h"
#include "../post.h"
#include "../global.h"

class CategoryPannel :public WContainerWidget
{
  public:
  //! 
  CategoryPannel(WContainerWidget *parent);
  //!
  WContainerWidget *categorycontainer;
  
  private:
  //!
  WAnchor *CategoryNames;
  //!  
  PostCollection cat_pannel;
  //!
  Session session_;
};
#endif
 
