/************************************************************** 
 Purpose : main app file of Laka Engine 

 Author  : Gauravjeet Singh, Inderpreet Singh, Shaina Sabarwal

 License : GNU GPL V3

***************************************************************/
#include "laka_engine.h"
#include "admin/setting_pannel.h"
#include "add_theme.h"

#include <Wt/WLink>
#include <Wt/WStackedWidget>

string mainTemplate;

LakaEngine::LakaEngine(const WEnvironment &env)
    :WApplication(env)
{
   useStyleSheet("themes/yanni/style.css");

   applySettings();

   cout<<"__________title_______"<<titleString<<endl;
   cout<<"_________tagline______"<<taglineString<<endl;

   if(titleString == "")
   titleString = "Lakaness";

   if(taglineString == "")
   taglineString="Give a height to your thoughts";
   
   setTitle(titleString);
   useStyleSheet("resources/default.css");
   clicked = false;

   container = new WContainerWidget(root());
   container->setStyleClass("container");

   headerContainer = new WContainerWidget();

   authForm = new AuthForm(headerContainer);

   postLoop = new PostLoop(container);
   
   headerPanel = new WPanel(root());
   headerPanel->setTitle("Login/Sign up");
   headerPanel->setCentralWidget(headerContainer);
   headerPanel->setCollapsible(true);
   headerPanel->setCollapsed(false);
   WAnimation animation(WAnimation::SlideInFromTop, WAnimation::EaseOut, 100);
   headerPanel->setAnimation(animation);

   main = new WTemplate(root());
   main->setTemplateText(mainTemplate);
   main->bindString("tagline",    taglineString);
   main->bindString("title",      titleString);
   main->bindWidget("postloop",   postLoop);

   internalPathChanged().connect(this, &LakaEngine::handlePathChange);

   handlePathChange();
}

void LakaEngine::applySettings()
{
   try{
        {
        dbo::Transaction t(session_);
        dbo::ptr<User> userPtr = session_.find<User>().where("name = ?").bind("admin");
        titleString = userPtr->title;
        taglineString=userPtr->tagline;
        t.commit();
        }
   }
   catch(exception& e)
   {
       cout<<"Register first";
   }
}

void LakaEngine::handlePathChange()
{
    std::string path = internalPath();
   if(path == "/")
    {
       container->clear();
       postLoop = new PostLoop(container);
       main->bindWidget("postloop",   postLoop);
    }
   else 
    {
      postLoop->handlePath();
    }
}

WApplication *createApplication(const WEnvironment &env)
{
    return new LakaEngine(env);
}


int main(int argc, char **argv)
{
   try{
		Wt::WServer server(argv[0]);

		server.setServerConfiguration(argc,argv, WTHTTP_CONFIGURATION);
		server.addEntryPoint(Wt::Application, createApplication);

		Session::configureAuth();

		if(server.start()){
			Wt::WServer::waitForShutdown();
			server.stop();
		}
	} catch (Wt::WServer::Exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (std::exception &e) {
		std::cerr<< "exception" << e.what() <<std::endl;
	}
 }
