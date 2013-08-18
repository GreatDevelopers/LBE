/************************************************************
FileName: post_loop.h

Description: Contains Declarations for post loop

Authors: Gauravjeet Singh, Shaina Sabarwal, Inderpreet SIngh

License: GNU GPL V3

*************************************************************/

#ifndef POST_LOOP_H_
#define POST_LOOP_H_

#include <Wt/WContainerWidget>
#include <vector>
#include <Wt/WTemplate>
#include <Wt/WApplication>
#include <Wt/WText>
#include <Wt/WAnchor>

#include <sstream>
#include <string>

#include "post.h"
#include "global.h"

using namespace Wt;
namespace dbo = Wt::Dbo;
using namespace std;

//! Class for traversing through all the posts
/*!
    This class is inherited from WContainerWidget with purpose of making a widget that can be used to display all the posts at one time. 
This traversal is done through a loop so the name post loop
*/

class PostLoop : public Wt::WContainerWidget
{
public:
	//! Constructor for doing dbo transaction to retrieve all the posts
	PostLoop(Wt::WContainerWidget * parent);
	//! theLoop is the main loop that traverses through all the posts in the blog.
	void theLoop();
        ///! handlePath manages path and shows post according to permalink
        void handlePath();

	Session session_;
private:
	//! allPosts is a collection, where all the posts are stored
        PostCollection allPosts;
        //! string to store the internal path
        std::string postPath;
	std::string cat_str;
        //! Template used when seing a single post, i.e after clicking on title
        WTemplate *singlePostTemplate;
        //! The parent widget that holds all the widgets of the post loop
        WContainerWidget *postContainer;
        //! contentStream for streaming postContent, and subStream to stream postContent until more tag
        stringstream contentStream;
        //! WText for displaying the postContent
        WText *postText;
	//! WText for displaying categories
	WText *postCat;
        //! Anchor for title of post and see more tag
        WAnchor *singlePostName;
};
#endif
