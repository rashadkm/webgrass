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

    
      File = new WPopupMenu();
      Settings = new WPopupMenu();
      Raster = new WPopupMenu();
      Vector = new WPopupMenu();
      Imagery = new WPopupMenu();
      Volumes = new WPopupMenu();
      Database = new WPopupMenu();
      Temporal = new WPopupMenu();
      Help = new WPopupMenu();
      

      pugi::xml_document doc;

      pugi::xml_parse_result tos = doc.load_file("/home/mayank/Dropbox/Github/webgrass/menu-xml/menudata2.xml");

      std::cout << "Load result: " << tos.description() << std::endl;
      pugi::xml_node menudata = doc.child("menudata");

      std::string label,help,handler,shortcut,keywords,command,label2,label3;


      for (pugi::xml_node menubar = menudata.child("menubar"); menubar; menubar = menubar.next_sibling("menubar")) 
      {
         for (pugi::xml_node menu = menubar.child("menu"); menu; menu = menu.next_sibling("menu")) 
         {
               label = menu.child_value("label"); 

               for (pugi::xml_node items = menu.child("items"); items; items = items.next_sibling("items")) 
               {
                  for (pugi::xml_node nitem = items.child("menu"); nitem; nitem = nitem.next_sibling("menu")) 
                  {
                     label2 = nitem.child_value("label");
                     file1 = new WPopupMenu();
                     for (pugi::xml_node xitem = nitem.child("items"); xitem; xitem = xitem.next_sibling("items"))
                     {
                        for (pugi::xml_node menuitem = xitem.child("menuitem"); menuitem; menuitem = menuitem.next_sibling("menuitem"))
                        {
                           label3 = menuitem.child_value("label");
                           file1->addItem(label3);
                        }
                     }
                     if(label=="File")
                        File->addMenu(label2,file1);
                     else if(label=="Settings")
                        Settings->addMenu(label2,file1);
                     else if(label=="Raster")
                        Raster->addMenu(label2,file1);
                     else if(label=="Vector")
                        Vector->addMenu(label2,file1);
                     else if(label=="Imagery")
                        Imagery->addMenu(label2,file1);
                     else if(label=="Volumes")
                        Volumes->addMenu(label2,file1);
                     else if(label=="Database")
                        Database->addMenu(label2,file1);
                     else if(label=="Temporal")
                        Temporal->addMenu(label2,file1);
                     else if(label=="Help")
                        Help->addMenu(label2,file1);

                     
                  }
               }
               

         }
      }


            m = new WMenu();
            m->addMenu("File", File);
            m->addMenu("Settings", Settings);
            m->addMenu("Raster", Raster);
            m->addMenu("Vector", Vector);
            m->addMenu("Imagery", Imagery);
            m->addMenu("Volumes", Volumes);
            m->addMenu("Database", Database);
            m->addMenu("Temporal", Temporal);
            m->addMenu("Help", Help);
            

            //n = new WNavigationBar(mainContainer);
            Wt::WNavigationBar *n = new Wt::WNavigationBar(mainContainer);

            n->setResponsive(true);
            n->addMenu(m);

}



