#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBorderLayout>
#include <Wt/WGridLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WFileUpload>
#include <Wt/WTabWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WNavigationBar>
#include <Wt/WMenuItem>
#include <Wt/WMessageBox>
#include <Wt/WPopupMenu>


using namespace Wt;


#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


#include "MainUI.h"
#include "global.h"
#include <pugixml.hpp>



#include <boost/assign/list_of.hpp> 
#include <boost/bind.hpp>  


#include <boost/asio.hpp> 
#include <boost/assign/list_of.hpp> 
#include <boost/array.hpp> 
#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>


#if defined(BOOST_POSIX_API) 
#   include <sys/wait.h> 
#endif 

//namespace bp = boost::process; 

#define INLINE_JAVASCRIPT(...) #__VA_ARGS__

#include "pstream.h"
#include "WGrassLayerManager.h"

#include "WGrassMenuBar.h"


MainUI::MainUI(WContainerWidget *parent)
:WContainerWidget(parent) {

	createUI(parent);
	
}
MainUI::~MainUI() { }


void MainUI::createUI(WContainerWidget *parent) { 

			WContainerWidget *mainContainer = new WContainerWidget(parent);

			//setTheme(new WBootstrapTheme());

            //addMetaHeader("viewport", "width = device-width, initial-scale = 1");

            //root()->addStyleClass("container-fluid");

            ssm = new WPopupMenu();
            ssm->addItem("Menu Item 121");

            sm = new WPopupMenu();
            sm->addItem("Menu Item 11");
#define SUBMENU_TEST
#ifdef SUBMENU_TEST
            mi = new WMenuItem("Menu Item 12");
            mi->addStyleClass("dropdown-submenu");
            mi->setMenu(ssm);
            sm->addItem(mi);
#else
            sm->addMenu("Menu Item 12", ssm);
#endif

            sm->addItem("Menu Item 13");

            m = new WMenu();
            m->addMenu("Test 1", sm);
            m->addItem("Test 2");
            m->addItem("Test 3");

            //n = new WNavigationBar(mainContainer);
            Wt::WNavigationBar *n = new Wt::WNavigationBar(mainContainer);

            n->setResponsive(true);
            n->addMenu(m);

}



