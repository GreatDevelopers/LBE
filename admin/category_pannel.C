#include "category_pannel.h"

CategoryPannel::CategoryPannel(WContainerWidget *parent):WContainerWidget(parent)
{
	categorycontainer = new WContainerWidget(this);
	new WText("categories coming soon", categorycontainer);
	{
	  dbo::Transaction t(session_);
	  cat_pannel = session_.find<Post>();
	  for(auto k: cat_pannel)
	  {
	        		
		CategoryNames = new WAnchor(WLink(WLink::InternalPath,(k)->postContent), (k)->postContent, categorycontainer);
		categorycontainer->addWidget(new WBreak());
	  } 
	  t.commit();
	}
}
