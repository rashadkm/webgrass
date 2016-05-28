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

      menuToolBar = new WPopupMenu();
      menuToolBar->addItem("Mewafea");

      pugi::xml_document doc;

    pugi::xml_parse_result tos = doc.load_file("/home/mayank/Dropbox/Github/webgrass/menu-xml/menudata.xml");

    std::cout << "Load result: " << tos.description() << std::endl;
    pugi::xml_node menudata = doc.child("menudata");

      std::string label,help,handler,shortcut,keywords,command;

   for (pugi::xml_node menubar = menudata.child("menubar"); menubar; menubar = menubar.next_sibling("menubar")) 
   {
      for (pugi::xml_node menu = menubar.child("menu"); menu; menu = menu.next_sibling("menu")) 
      {
            label = menu.child_value("label"); //FILE
         //Wt::WMenu *LayerMenu = new Wt::WMenu();
         menuToolBar->addItem(label);



            for (pugi::xml_node items = menu.child("items"); items; items = items.next_sibling("items")) 
            {
               for (pugi::xml_node nitem = items.child("menu"); nitem; nitem = nitem.next_sibling("menu")) 
               {
                     label = nitem.child_value("label"); //WORKSPACE
                  //Wt::WMenu *subMenu1 = new Wt::WMenu();
                  //LayerMenu->addItem(label,subMenu1);
                  for (pugi::xml_node xitem = nitem.child("items"); xitem; xitem = xitem.next_sibling("items")) 
                  {
                     for (pugi::xml_node menuitem = xitem.child("menuitem"); menuitem; menuitem = menuitem.next_sibling("menuitem")) 
                     {
                        label = menuitem.child_value("label");
                        help = menuitem.child_value("help");
                           handler = menuitem.child_value("handler");
                           shortcut = menuitem.child_value("shortcut");
                        keywords = menuitem.child_value("keywords");
                        command = menuitem.child_value("command");
                 
                        //mnuItem = new GMenuItem(label,command,keywords);




                                     
                        //subMenu1->addItem(mnuItem);

                     }
                  }
               }

            for (pugi::xml_node imenu = items.child("menuitem"); imenu; imenu = imenu.next_sibling("menuitem")) 
            {
               label = imenu.child_value("label"); //GEORECTIFY
               //LayerMenu->addItem(label);

            }

         }
      }
   }

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
            mi->setMenu(menuToolBar);
            sm->addItem(mi);
#else
            sm->addMenu("Menu Item 12", menuToolBar);
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



