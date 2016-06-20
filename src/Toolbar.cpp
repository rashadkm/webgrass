
#include "Toolbar.h"

Toolbar::Toolbar(WContainerWidget *parent=0)
  :WContainerWidget(parent) {

  WContainerWidget *selectionBoxContainer = new WContainerWidget();

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
  //table->setStyleClass("table");
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

  selectionBoxContainer->addWidget(toolBar);
  addWidget(selectionBoxContainer);


  

}

