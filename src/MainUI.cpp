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

      /*top menu */
      m = new WMenu(); 
      
      pugi::xml_document doc;

      /* input file of menudata*/
      const std::string MENUDATA_XML_FILE = WApplication::instance()->docRoot() + "/menu-xml/menudata2.xml";
      pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

      std::cout << "Load result: " << tos.description() << std::endl;

      /* iteration over menudata but since only one is there so */
      pugi::xml_node menudata = doc.child("menudata");

      std::string label,help,handler,shortcut,keywords,command,label2,label3;

      /* iteration over menubar but since only one is there so */
      pugi::xml_node menubar = menudata.child("menubar");
      


         /* iteration over fisrt occurane of menu */
         for (pugi::xml_node menu = menubar.child("menu"); menu; menu = menu.next_sibling("menu")) 
         { 
               std::string firstLevel_label = menu.child_value("label");
               /* first menu creation */
               WPopupMenu *firstLevel = new WPopupMenu();
               m->addMenu(firstLevel_label, firstLevel);
               label = menu.child_value("label"); 
              
               /* iteration over first occurance of items */
               for (pugi::xml_node items = menu.child("items"); items; items = items.next_sibling("items")) 
               {

                  /* iteration over second occurane of menu */
                  for (pugi::xml_node nitem = items.child("menu"); nitem; nitem = nitem.next_sibling("menu")) 
                  {
                     std::string nextLevel_label = nitem.child_value("label");
                     /* submenu creation */
                     WPopupMenu *nextLevel = new WPopupMenu();
                     firstLevel->addMenu(nextLevel_label, nextLevel);
                     label2 = nitem.child_value("label");

                      /* iteration over second occurance of items */
                     for (pugi::xml_node xitem = nitem.child("items"); xitem; xitem = xitem.next_sibling("items"))
                     {

                         /* iteration over internal occurance of menuitem */
                        for (pugi::xml_node menuitem = xitem.child("menuitem"); menuitem; menuitem = menuitem.next_sibling("menuitem"))
                        {
                           label3 = menuitem.child_value("label");
                           nextLevel->addItem(label3);
                        }
                     }

                     
                  }

                  /* iteration over outer occurance of menuitem */
                  for (pugi::xml_node nmitem = items.child("menuitem"); nmitem; nmitem = nmitem.next_sibling("menuitem"))  
                  {
                      std::string nextLevelItem_label = nmitem.child_value("label");     
                     firstLevel->addItem(nextLevelItem_label);
                  }


               }
               

         }
      

            //n = new WNavigationBar(mainContainer);
            Wt::WNavigationBar *n = new Wt::WNavigationBar(mainContainer);

            n->setResponsive(true);
            n->addMenu(m);

}



