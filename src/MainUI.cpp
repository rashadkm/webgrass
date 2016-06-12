
#include <iostream>
#include <pugixml.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPopupMenu>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WToolBar>
#include <Wt/WApplication>

#include "MainUI.h"
#include "LayerManager.h"
#include "Display.h"
#include "Toolbar.h"
MainUI::MainUI(WContainerWidget *parent)
:WContainerWidget(parent) {
      //root()->clear();
      createUI(parent);

}
MainUI::~MainUI() { }


void MainUI::createUI(Wt::WContainerWidget *parent) {

  Wt::WMenu *menu =  new Wt::WMenu();

  pugi::xml_document doc;

  /* input file of menudata*/
  const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/menu-xml/menudata2.xml";
  pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

  std::cout << "Load result: " << tos.description() << std::endl;

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
                nextLevel->addItem(menu_items_menu_items_menuitem_node.child_value("label"));
                menu_items_menu_items_menuitem_node = menu_items_menu_items_menuitem_node.next_sibling("menuitem");
             }
             menu_items_menu_items_node = menu_items_menu_items_node.next_sibling("items");
          }
          menu_items_menu_node = menu_items_menu_node.next_sibling("menu");
       }

       /* iteration over outer occurance of menuitem */
       pugi::xml_node menu_items_menuitem_node = menu_items_node.child("menuitem");
       while ( menu_items_menuitem_node ) {
          firstLevel->addItem(menu_items_menuitem_node.child_value("label"));
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
  textContainer1->setStyleClass("text");
  Wt::WHBoxLayout *hbox2 = new Wt::WHBoxLayout();
  textContainer1->setLayout(hbox2);

  Wt::WText *item = new Wt::WText("Layertree");
  item->setStyleClass("text");
  hbox2->addWidget(item);
  
  item = new Wt::WText("Display");
  item->setStyleClass("text");
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
}
