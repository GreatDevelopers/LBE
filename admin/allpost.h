#ifndef ALLPOST_H_
#define ALLPOST_H_

#include <Wt/WTemplate>
#include <Wt/WContainerWidget>
#include <sstream>
#include <string>
#include <Wt/WPushButton>
#include <Wt/WTextArea>
#include <Wt/WLineEdit>
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>

#include "../post.h"
#include "../global.h"

using namespace Wt;
namespace dbo=Wt::Dbo;
using namespace std;

//! Class providing widgets required for edditing and deleting posts
class allPost:public WContainerWidget
{
public:
   //! Constructor that load all the posts from database
   allPost(WContainerWidget *parent);
   //! Function which display all the post
   void allLoop();
   //! Function which open a editor for editing
   void edit();
   //! Function which updates to database
   void update();
   //! Function which gives warning before deletion
   void postDelete();
   //! Function which deletes da post from database
   void deleted();
   void getupdate();

   session session_;
private:
   //! vector which show checkBoxes
  // vector <WCheckBox*> linkCollection;
   //! variable which store selectedPost
   string selectedPost;
   //! variable which store all the posts
   PostCollection storedPost;
   //! TextArea for the content
   WTextArea *updateContent;
   bool delete_post;
   //! containers
   WContainerWidget *allContainer,*updateContentEditor, *updateContainer,*container,*containerDelete;
   //! checkBox which show title
   WRadioButton* link;
   WButtonGroup* linkGroup;

   WLineEdit *updateName,*updateDate,*updateTime;

   WPushButton *editButton,*deleteButton,*updateButton,*yes,*cancel;
 
};
#endif
