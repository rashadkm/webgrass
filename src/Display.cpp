
#include "Display.h"

Display::Display(WContainerWidget *parent=0)
  :WContainerWidget(parent) {

    WApplication::instance()->useStyleSheet("style.css");


  addWidget(new WBreak());


  WContainerWidget *selectionBoxContainer = new WContainerWidget();


  selectionBoxContainer->setStyleClass("displayContainer");
  WtSelectionBoxDisplay = new Wt::WSelectionBox();
  WtSelectionBoxDisplay->setStyleClass("layertree");
  WtSelectionBoxDisplay->resize(5000,3000);


  Wt::WToolBar *toolBar = new Wt::WToolBar();

  Wt::WPushButton *displaymap = new Wt::WPushButton();
  displaymap->setStyleClass("displaymap");
  displaymap->setMargin(3, Wt::Right);
  displaymap->setToolTip("Display map");

  Wt::WPushButton *redraw = new Wt::WPushButton();
  redraw->setStyleClass("redraw");
  redraw->setMargin(3, Wt::Right);
  redraw->setToolTip("layer redraw");

  Wt::WPushButton *erase = new Wt::WPushButton();
  erase->setStyleClass("erase");
  erase->setMargin(3, Wt::Right);
  erase->setToolTip("layer erase");

  Wt::WPushButton *pointer = new Wt::WPushButton();
  pointer->setStyleClass("pointer");
  pointer->setMargin(3, Wt::Right);
  pointer->setToolTip("pointer");

  Wt::WPushButton *info = new Wt::WPushButton();
  info->setStyleClass("info");
  info->setMargin(3, Wt::Right);
  info->setToolTip("query raster/vector maps");

  Wt::WPushButton *pan = new Wt::WPushButton();
  pan->setStyleClass("pan");
  pan->setMargin(3, Wt::Right);
  pan->setToolTip("pan");

  Wt::WPushButton *zoomin = new Wt::WPushButton();
  zoomin->setStyleClass("zoom-in");
  zoomin->setMargin(3, Wt::Right);
  zoomin->setToolTip("zoom in");

  Wt::WPushButton *zoomout = new Wt::WPushButton();
  zoomout->setStyleClass("zoom-out");
  zoomout->setMargin(3, Wt::Right);
  zoomout->setToolTip("zoom out");

  Wt::WPushButton *zoomextent = new Wt::WPushButton();
  zoomextent->setStyleClass("zoom-extent");
  zoomextent->setMargin(3, Wt::Right);
  zoomextent->setToolTip("zoom to selected map layers");

  Wt::WPushButton *zoomlast = new Wt::WPushButton();
  zoomlast->setStyleClass("zoom-last");
  zoomlast->setMargin(3, Wt::Right);
  zoomlast->setToolTip("return to previous zoom");

  Wt::WPushButton *zoommore = new Wt::WPushButton();
  zoommore->setStyleClass("zoom-more");
  zoommore->setMargin(3, Wt::Right);
  zoommore->setToolTip("various zoom options");

  Wt::WPushButton *analyze = new Wt::WPushButton();
  analyze->setStyleClass("analyze");
  analyze->setMargin(3, Wt::Right);
  analyze->setToolTip("analyze map");

  Wt::WPushButton *addelements = new Wt::WPushButton();
  addelements->setStyleClass("addelements");
  addelements->setMargin(3, Wt::Right);
  addelements->setToolTip("add map elements");

  Wt::WPushButton *mapexport = new Wt::WPushButton();
  mapexport->setStyleClass("mapexport");
  mapexport->setMargin(3, Wt::Right);
  mapexport->setToolTip("save display to file");

  Wt::WPushButton *print = new Wt::WPushButton();
  print->setStyleClass("print");
  print->setMargin(3, Wt::Right);
  print->setToolTip("print");


  toolBar->addButton(displaymap);
  toolBar->addButton(redraw);
  toolBar->addButton(erase);
  toolBar->addButton(pointer);
  toolBar->addButton(info);
  toolBar->addButton(pan);
  toolBar->addButton(zoomin);
  toolBar->addButton(zoomout);
  toolBar->addButton(zoomextent);
  toolBar->addButton(zoomlast);
  toolBar->addButton(zoommore);
  toolBar->addButton(analyze);
  toolBar->addButton(addelements);
  toolBar->addButton(mapexport);
  toolBar->addButton(print);

  selectionBoxContainer->addWidget(toolBar);
  selectionBoxContainer->addWidget(WtSelectionBoxDisplay);
  addWidget(selectionBoxContainer);


  

}



