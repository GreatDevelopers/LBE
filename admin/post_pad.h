/************************************************************

Filename: post_pad.h

Description: widget of admin panel that adds posts

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet Singh, Amitoj Singh

License: GNU GPL V3 

*************************************************************/

#ifndef _POST_PAD_H
#define _POST_PAD_H

#include <Wt/WTextEdit>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/WLineEdit>
#include <Wt/WJavaScript>
#include <Wt/WTextEdit>
#include <Wt/WCheckBox>
#include <Wt/WDatePicker>
#include <sstream>

#include "../post.h"
#include "../global.h"
#include "category_widget.h"

using namespace Wt;
using namespace std;
//! Class providing with widgets required for adding post
/*!
   PostPad class provides with a editor to write a post and a mechanisim to store that post in the database so that we can retrive it later.
*/
class PostPad : public WContainerWidget
{

public:
    //! Constructor that renders the editor
    PostPad(WContainerWidget *parent);
    //! Function to store the post in database
    void storePost(std::string postContent);
    //! Function to get the post from editor to string
    void getPost();
   
    Session session_;
private:
    //! Container to hold the editor, date and the category menu
    WContainerWidget *postEditor, *dateContainer;
    //! LineEdit for title of post and date
    WLineEdit *postTitle, *dateEdit;
    //! Button, when fired starts function getPost()
    WPushButton *submitPost;
    //! LineEdit for the permalink of post
    WLineEdit *postLink;
    //! Dbo pointer to point to the last published post
    dbo::ptr<Post> postPtr;
    //! Dbo pointer to point to the last published post
    dbo::ptr<Category> catPtr;
    //! Date picker for adding date to each post
    WDatePicker *date;
    //! JSignal to interact with C++ and Javascript events
    /*!
        Basically it helps in getting all the content from editor that are in a specific html id and store them in string
    */
    JSignal<std::string> postContent;
  
    std::stringstream strm; 
    //!bool variable to indicate whether the post is published or not
    bool published;

};
#endif
