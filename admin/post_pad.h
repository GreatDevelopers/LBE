/************************************************************

Filename: post_pad.h

Description: widget of admin panel that adds posts

Authors: Gauravjeet Singh, Inderpreet SIngh, Shaina Sabarwal

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
#include <sstream>

#include "../post.h"
#include "../global.h"

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
    //! Function to get the categories 
    void getCategory();
    //! Function to add new categories into Category table
    void NewCat();
    //! Vector of check boxes
    vector <WCheckBox *> checked_cat;
    //! vector of strings to store checkedboxex texts
    vector <string> string_cat;   
    //! string stream to copy the vector content into string stream
    stringstream ss; 
    Session session_;
private:
    //! Container to hold the editor, and the category menu
    WContainerWidget *postEditor, *categoryContainer;
    //! LineEdit for title of post
    WLineEdit *postTitle;
    //! Button, when fired starts function NewCat()
    WPushButton *save_but;
    //! Button, when fired starts function getPost()
    WPushButton *submitPost;
    //! LineEdit for the permalink of post
    WLineEdit *postLink;
    //! LineEdit for new category
    WLineEdit *NewCategory;
    //! Checkboxes to show categories
    WCheckBox *checkbox;
    //! Dbo pointer to point to the last published post
    dbo::ptr<Post> postPtr;
    //! Dbo pointer to point to the last published post
    dbo::ptr<Category> catPtr;
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
