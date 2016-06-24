
#include "Toolbar.h"

void
Toolbar::addGrassToolButton(const std::string id, const std::string tip)  {
  Wt::WPushButton *toolButton = new Wt::WPushButton();
  toolButton->setStyleClass("wgrass-toolbar-icons");
  const std::string iconFile = "./icons/grass/" + id + ".png";
  toolButton->decorationStyle().setBackgroundImage (iconFile);
  toolButton->setToolTip(tip);
  toolButton->setId("wgrass-tool-" + id);
  toolButton->resize(20, 30); //can we put this in css?
  m_ToolBar->addButton(toolButton);
  
}

Toolbar::Toolbar(WContainerWidget *parent=0)
  :WContainerWidget(parent) {

  WContainerWidget *selectionBoxContainer = new WContainerWidget();

  m_ToolBar = new Wt::WToolBar();

  addGrassToolButton("layer-open", "add multiple layers");
  addGrassToolButton("layer-raster-add", "add raster map layer");
    
  //  layeropen->setMargin(3, Wt::Right);
  //layeropen->setToolTip("add multiple layers");
    /*
  Wt::WPushButton *addraster = new Wt::WPushButton();
  addraster->setStyleClass("wgrass-toolbar-icons");
  //  addraster->setMargin(3, Wt::Right);
  addraster->setToolTip("add raster map layer");

  Wt::WPushButton *addvarraster = new Wt::WPushButton();
  addvarraster->setStyleClass("wgrass-toolbar-icons");
  //  addvarraster->setMargin(3, Wt::Right);
  addvarraster->setToolTip("add various raster map layers");

  Wt::WPushButton *addvector = new Wt::WPushButton();
  addvector->setStyleClass("wgrass-toolbar-icons");
  //  addvector->setMargin(3, Wt::Right);
  addvector->setToolTip("add vector map layer");

  Wt::WPushButton *addvarvector = new Wt::WPushButton();
  addvarvector->setStyleClass("wgrass-toolbar-icons");
  //  addvarvector->setMargin(3, Wt::Right);
  addvarvector->setToolTip("add various vector map layers");

  Wt::WPushButton *overlay = new Wt::WPushButton();
  overlay->setStyleClass("wgrass-toolbar-icons");
  //  overlay->setMargin(3, Wt::Right);
  overlay->setToolTip("add various overlays");

  Wt::WPushButton *addgroup = new Wt::WPushButton();
  addgroup->setStyleClass("wgrass-toolbar-icons");
  //addgroup->setMargin(3, Wt::Right);
  addgroup->setToolTip("add group");

  Wt::WPushButton *removelayer = new Wt::WPushButton();
  removelayer->setStyleClass("wgrass-toolbar-icons");
  //removelayer->setMargin(3, Wt::Right);
  removelayer->setToolTip("remove selected map layers");

  Wt::WPushButton *table = new Wt::WPushButton();
  table->setStyleClass("wgrass-toolbar-icons");
  //table->setMargin(3, Wt::Right);
  table->setToolTip("show attribute data for selected vector map");

  Wt::WPushButton *import = new Wt::WPushButton();
  import->setStyleClass("wgrass-toolbar-icons");
  //import->setMargin(3, Wt::Right);
  import->setToolTip("import/link raster or vector data");

  Wt::WPushButton *manual = new Wt::WPushButton();
  manual->setStyleClass("wgrass-toolbar-icons");
  //  manual->setMargin(3, Wt::Right);
  manual->setToolTip("grass manual");
    */
  /*
  toolBar->addButton(layeropen);
  toolBar->addButton(addraster);
  toolBar->addButton(addvarraster);
  toolBar->addButton(addvector);
  toolBar->addButton(addvarvector);
  toolBar->addButton(overlay);
  toolBar->addButton(addgroup);
  toolBar->addButton(removelayer);
  toolBar->addButton(table);
  toolBar->addButton(import);
  toolBar->addButton(manual);
  */
  selectionBoxContainer->addWidget(m_ToolBar);
  addWidget(selectionBoxContainer);


  

}

