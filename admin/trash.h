
#include <Wt/WTemplate>
#include <Wt/WContainerWidget>
#include <Wt/WTextArea>
#include <Wt/WLineEdit>
#include <Wt/WButtonGroup>
#include <Wt/WRadioButton>
#include <Wt/WPushButton>

#include "../post.h"
#include "../global.h"

class trashExplorer: public WContainerWidget{
public:
	trashExplorer(WContainerWidget *parent);
	void listPosts();
	session session_;
private:
	string selectedPost;
        PostCollection deletedPosts;
	WContainerWidget *dustbin;
	WPushButton *restoreButton;
	WRadioButton *link;
	WButtonGroup *linkGroup;
        
}	
