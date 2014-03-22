#include "trash.h"

trashExplorer::trashExplorer(WContainerWidget *parent)
	      : WContainerWidget(parent);
{
  link = new WButtonGroup();
   restoreButton = new WPushButton("Restore", this);
   deletedPosts = session_.find<Post>().where("status = ?").bind("deleted");
   listPosts();
}

void trashExplorer :: listPosts()
{
   for(auto i : deletedPosts){
     dustbin=new WContainerWidget(this);
     dustbin->setStyleClass("post-view-admin");
      (new WText(i->postName,dustbin))->setStyleClass("post-title-admin");
      new WBreak(container);
      link=new WRadioButton(i->permalink,dustbin);
      linkGroup->addButton(link);
    }
}

