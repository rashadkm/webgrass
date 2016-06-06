
#include <iostream>
#include <pugixml.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPopupMenu>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WToolBar>
#include <Wt/WApplication>

#include "MainUI.h"
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
  Wt::WToolBar *toolBar = new Wt::WToolBar();

  Wt::WPushButton *mapdisplay = new Wt::WPushButton();
  mapdisplay->setStyleClass("mapdisplay");
  mapdisplay->setMargin(3, Wt::Right);
  mapdisplay->setToolTip("start new map display");

  Wt::WPushButton *create = new Wt::WPushButton();
  create->setStyleClass("create");
  create->setMargin(3, Wt::Right);
  create->setToolTip("create new workspace");

  Wt::WPushButton *open = new Wt::WPushButton();
  open->setStyleClass("open");
  open->setMargin(3, Wt::Right);
  open->setToolTip("open existing workspace");

  Wt::WPushButton *save = new Wt::WPushButton();
  save->setStyleClass("save");
  save->setMargin(3, Wt::Right);
  save->setToolTip("save current workspace");

  Wt::WPushButton *layeropen = new Wt::WPushButton();
  layeropen->setStyleClass("layeropen");
  layeropen->setMargin(3, Wt::Right);
  layeropen->setToolTip("add multiple layers");

  Wt::WPushButton *addraster = new Wt::WPushButton();
  addraster->setStyleClass("addraster");
  addraster->setMargin(3, Wt::Right);
  addraster->setToolTip("add raster map layer");

  Wt::WPushButton *addvarraster = new Wt::WPushButton();
  addvarraster->setStyleClass("addvarraster");
  addvarraster->setMargin(3, Wt::Right);
  addvarraster->setToolTip("add various raster map layers");

  Wt::WPushButton *addvector = new Wt::WPushButton();
  addvector->setStyleClass("addvector");
  addvector->setMargin(3, Wt::Right);
  addvector->setToolTip("add vector map layer");

  Wt::WPushButton *addvarvector = new Wt::WPushButton();
  addvarvector->setStyleClass("addvarvector");
  addvarvector->setMargin(3, Wt::Right);
  addvarvector->setToolTip("add various vector map layers");

  Wt::WPushButton *overlay = new Wt::WPushButton();
  overlay->setStyleClass("overlay");
  overlay->setMargin(3, Wt::Right);
  overlay->setToolTip("add various overlays");

  Wt::WPushButton *addgroup = new Wt::WPushButton();
  addgroup->setStyleClass("addgroup");
  addgroup->setMargin(3, Wt::Right);
  addgroup->setToolTip("add group");

  Wt::WPushButton *removelayer = new Wt::WPushButton();
  removelayer->setStyleClass("removelayer");
  removelayer->setMargin(3, Wt::Right);
  removelayer->setToolTip("remove selected map layers");

  Wt::WPushButton *edit = new Wt::WPushButton();
  edit->setStyleClass("edit");
  edit->setMargin(3, Wt::Right);
  edit->setToolTip("edit selected vector map");

  Wt::WPushButton *table = new Wt::WPushButton();
  table->setStyleClass("table");
  table->setMargin(3, Wt::Right);
  table->setToolTip("show attribute data for selected vector map");

  Wt::WPushButton *import = new Wt::WPushButton();
  import->setStyleClass("import");
  import->setMargin(3, Wt::Right);
  import->setToolTip("import/link raster or vector data");

  Wt::WPushButton *calculator = new Wt::WPushButton();
  calculator->setStyleClass("calculator");
  calculator->setMargin(3, Wt::Right);
  calculator->setToolTip("raster map calculator");

  Wt::WPushButton *georectify = new Wt::WPushButton();
  georectify->setStyleClass("georectify");
  georectify->setMargin(3, Wt::Right);
  georectify->setToolTip("georectifier");

  Wt::WPushButton *modeler = new Wt::WPushButton();
  modeler->setStyleClass("modeler");
  modeler->setMargin(3, Wt::Right);
  modeler->setToolTip("graphical modeler");

  Wt::WPushButton *composer = new Wt::WPushButton();
  composer->setStyleClass("composer");
  composer->setMargin(3, Wt::Right);
  composer->setToolTip("cartographic composer");

  Wt::WPushButton *scriptload = new Wt::WPushButton();
  scriptload->setStyleClass("scriptload");
  scriptload->setMargin(3, Wt::Right);
  scriptload->setToolTip("lauch user defined script");

  Wt::WPushButton *guisettings = new Wt::WPushButton();
  guisettings->setStyleClass("guisettings");
  guisettings->setMargin(3, Wt::Right);
  guisettings->setToolTip("gui settings");

  Wt::WPushButton *manual = new Wt::WPushButton();
  manual->setStyleClass("manual");
  manual->setMargin(3, Wt::Right);
  manual->setToolTip("grass manual");

  toolBar->addButton(mapdisplay);
  toolBar->addButton(create);
  toolBar->addButton(open);
  toolBar->addButton(save);
  toolBar->addButton(layeropen);
  toolBar->addButton(addraster);
  toolBar->addButton(addvarraster);
  toolBar->addButton(addvector);
  toolBar->addButton(addvarvector);
  toolBar->addButton(overlay);
  toolBar->addButton(addgroup);
  toolBar->addButton(removelayer);
  toolBar->addButton(edit);
  toolBar->addButton(table);
  toolBar->addButton(import);
  toolBar->addButton(calculator);
  toolBar->addButton(georectify);
  toolBar->addButton(modeler);
  toolBar->addButton(composer);
  toolBar->addButton(scriptload);
  toolBar->addButton(guisettings);
  toolBar->addButton(manual);

  addWidget(toolBar);

}
