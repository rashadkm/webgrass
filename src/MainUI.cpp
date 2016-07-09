
#include <iostream>
#include <pugixml.hpp>
#include <cstring>

#include <Wt/WContainerWidget>
#include <Wt/WPopupMenu>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WToolBar>
#include <Wt/WApplication>
#include <Wt/WDialog>
#include <Wt/WLabel>

#include "MainUI.h"
#include "LayerManager.h"
#include "Display.h"
#include "Toolbar.h"
#include "pstream.h"

MainUI::MainUI(WContainerWidget *parent)
:WContainerWidget(parent) {
  createUI(parent);
}

MainUI::~MainUI() { }

void MainUI::createUI(Wt::WContainerWidget *parent) {

  Wt::WMenu *menu =  new Wt::WMenu();

  pugi::xml_document doc;

  /* input file of menudata*/
  const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/menu-xml/menudata.xml";
  pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

  ///std::cout << "Load result: " << tos.description() << std::endl;

  /* iteration over menudata but since only one is there so */
  pugi::xml_node menudata_node = doc.child("menudata");
  /* iteration over menubar but since only one is there so */
  pugi::xml_node menubar_node = menudata_node.child("menubar");

  /* iteration over fisrt occurane of menu */
  pugi::xml_node menu_node = menubar_node.child("menu");
  while( menu_node ) {
    /* first menu creation */
    Wt::WPopupMenu *firstLevel = new Wt::WPopupMenu();
    menu->addMenu(menu_node.child_value("label"), firstLevel);
    /* iteration over first occurance of items */
    pugi::xml_node menu_items_node = menu_node.child("items");
    while( menu_items_node ) {
       /* iteration over second occurane of menu */
       pugi::xml_node menu_items_menu_node = menu_items_node.child("menu");
       while( menu_items_menu_node ) {
          /* submenu creation */
          Wt::WPopupMenu *nextLevel = new Wt::WPopupMenu();
          firstLevel->addMenu(menu_items_menu_node.child_value("label"), nextLevel);
          /* iteration over second occurance of items */
          pugi::xml_node menu_items_menu_items_node = menu_items_menu_node.child("items");
          while ( menu_items_menu_items_node ) {
             /* iteration over internal occurance of menuitem */
             pugi::xml_node menu_items_menu_items_menuitem_node = menu_items_menu_items_node.child("menuitem");
             while( menu_items_menu_items_menuitem_node ) {

	       Wt::WMenuItem *nextLevelMenuItem = new Wt::WMenuItem(menu_items_menu_items_menuitem_node.child_value("label"));
	       nextLevelMenuItem->setId(menu_items_menu_items_menuitem_node.child_value("command"));
	       nextLevelMenuItem->triggered().connect(this, &MainUI::openModuleUI);
	       nextLevel->addItem(nextLevelMenuItem);
	       
	       menu_items_menu_items_menuitem_node = menu_items_menu_items_menuitem_node.next_sibling("menuitem");
             }
             menu_items_menu_items_node = menu_items_menu_items_node.next_sibling("items");
          }
          menu_items_menu_node = menu_items_menu_node.next_sibling("menu");
       }

       /* iteration over outer occurance of menuitem */
       pugi::xml_node menu_items_menuitem_node = menu_items_node.child("menuitem");
       while ( menu_items_menuitem_node ) {
	 Wt::WMenuItem *firstLevelMenuItem = new Wt::WMenuItem(menu_items_menuitem_node.child_value("label"));
	 firstLevelMenuItem->setId(menu_items_menuitem_node.child_value("command"));
	 firstLevelMenuItem->triggered().connect(this, &MainUI::openModuleUI);
	 firstLevel->addItem(firstLevelMenuItem);
	 menu_items_menuitem_node = menu_items_menuitem_node.next_sibling("menuitem");
       }
       
       menu_items_node = menu_items_node.next_sibling("items");
       
       menu_node = menu_node.next_sibling("menu");
    }
  }
  

  Wt::WNavigationBar *naivgationbar = new Wt::WNavigationBar();
  naivgationbar->setResponsive(true);
  naivgationbar->addMenu(menu);
  addWidget(naivgationbar);

  Wt::WContainerWidget *toolbarcontainer = new Wt::WContainerWidget();
  Toolbar* toolbar = new Toolbar(toolbarcontainer);

  addWidget(toolbar);

  //addWidget(new WBreak());
  Wt::WContainerWidget *textContainer1 = new Wt::WContainerWidget();
  textContainer1->setStyleClass("wgrass-text-label");
  Wt::WHBoxLayout *hbox2 = new Wt::WHBoxLayout();
  textContainer1->setLayout(hbox2);

  Wt::WText *item = new Wt::WText("Layertree");
  item->setStyleClass("wgrass-text-label");
  hbox2->addWidget(item);
  
  item = new Wt::WText("Display");
  item->setStyleClass("wgrass-text-label");
  hbox2->addWidget(item);
  textContainer1->setMargin(-30, Wt::Bottom);
  addWidget(textContainer1);


  Wt::WContainerWidget *textContainer = new Wt::WContainerWidget();  

  Wt::WHBoxLayout *hbox1 = new Wt::WHBoxLayout();
  textContainer->setLayout(hbox1);

  Wt::WContainerWidget *layercontainer = new Wt::WContainerWidget();

  LayerManager* layermanager = new LayerManager(layercontainer);

  Wt::WContainerWidget *displaycontainer = new Wt::WContainerWidget();
  Display* displaymanager = new Display(displaycontainer);
  hbox1->addWidget(layermanager);
  hbox1->addWidget(displaymanager,1);
  textContainer->setMargin(-10, Wt::Left);
  addWidget(textContainer);

  Wt::WNavigationBar *footer = new Wt::WNavigationBar();
  footer->setStyleClass("wgrass-footer");
  footer->setHeight(-30);
  // footer->setResponsive(true);
  // footer->setPositionScheme(Relative);
  // footer->setOffsets(0,Wt::Bottom);
  addWidget(footer);
}

void MainUI::openModuleUI(Wt::WMenuItem* gitem) {
  const std::string gmodule = gitem->id();
  int flag = 0;
  dialog = new Wt::WDialog(gmodule);
  Wt::WPushButton *run = new Wt::WPushButton("RUN", dialog->footer());
  run->setDefault(true);
  run->clicked().connect(dialog, &Wt::WDialog::accept);

  Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
  cancel->clicked().connect(dialog, &Wt::WDialog::reject);
  Wt::WContainerWidget *mo = new Wt::WContainerWidget(dialog->contents());
  mod = new Module(gmodule, mo);
  dialog->rejectWhenEscapePressed();
  dialog->finished().connect(this, &MainUI::runModule);
  dialog->show();
}

void MainUI::runModule(Wt::WDialog::DialogCode code){
std::cout<<(mod->findById("Main"))->objectName()<<"check"<<endl;
std::map<std::string,std::vector<Text_Gui *> >mop = mod->map;
for (std::map<std::string,std::vector<Text_Gui *> >::iterator it=mop.begin(); it != mop.end(); ++it) /*creation of widgets*/
         {   
            
            for(int i=0; i < it->second.size(); i++)
            { 
              std::cout<<"got it"<<std::endl;
              std::cout<<(it->second[i])->text()<<std::endl;
              std::string stre = ((it->second[i]))->objectName();
              std::cout<<((it->second[i]))->Name()<<std::endl;
              std::cout<<((it->second[i]))->Type()<<std::endl;
              // if(stre=="flag")         /*if flag is present then creation of checkboxes*/
              // {
              //   std::string f = ((it->second[i]))->id();
              //   int num = boost::lexical_cast<int>(f);
              //   // std::cout<<num<<std::endl;
              //   std::vector<std::string> flag_iterat = flags_l[num];
              //   for (std::vector<std::string>::iterator i = flag_iterat.begin(); i != flag_iterat.end(); ++i)
              //     {
              //       // std::cout << *i << ' ';
              //       Wt::WCheckBox *flag = new Wt::WCheckBox(*i, container1);
              //       flag->setInline(true); 

              //     }
              // }             
              // container1->addWidget(new WBreak());
            }

         }
    // redi::ipstream proc("grass70 $HOME/grassdata/newLocation/PERMANENT", redi::pstreams::pstdout | redi::pstreams::pstdin );
    //   std::string line;
    //   std::cout.flush();
    //   while (std::getline(proc.out(), line)){
    //     std::cout << "stdout: " << line << '\n';
    // }
    redi::ipstream proc("export GRASS_PNG_AUTO_WRITE=TRUE; export GRASS_PNG_COMPRESSION=9; export GRASS_TRANSPARENT=TRUE; export GRASS_TRUECOLOR=TRUE; export LD_LIBRARY_PATH=/usr/lib/grass70/lib; export GISBASE=/usr/lib/grass70/; export GISDBASE=/home/mayank/grassdata1; export GISRC=/home/mayank/.grass7/rc; export PATH=/usr/lib/grass70/bin:/usr/lib/grass70/scripts:$PATH; g.gisenv");
    // redi::ipstream proc("export GRASS_PNG_AUTO_WRITE=TRUE; export GRASS_PNG_COMPRESSION=9; export GRASS_TRANSPARENT=TRUE; export GRASS_TRUECOLOR=TRUE; export LD_LIBRARY_PATH=/usr/lib/grass70/lib; export GISBASE=/usr/lib/grass70/; export GISDBASE=/home/mayank/grassdata1; export GISRC=/home/mayank/.grass7/rc; export PATH=/usr/lib/grass70/bin:/usr/lib/grass70/scripts:$PATH; g.guienv");
    // redi::ipstream proc("g.guienv");      
      std::string line;
      std::cout.flush();
//       while (proc >> line) {
//     std::cout << line << std::endl;
// }
      while (std::getline(proc.out(), line)){
        std::cout << "stdout: " << line << '\n';
      }

      // redi::ipstream proc1("ls");  
      // std::string line1;
      // std::cout.flush();
      // while (std::getline(proc1.out(), line1)){
      //   std::cout << "stdout: " << line1 << '\n';
      // }
}
