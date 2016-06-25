#include "Toolbar.h"

void
Toolbar::addGrassToolButton(const std::string id, const std::string tip)  {
  Wt::WPushButton *toolButton = new Wt::WPushButton();
  toolButton->setStyleClass("wgrass-toolbar-icons");
  const std::string iconFile = "./icons/grass/" + id + ".png";
  toolButton->decorationStyle().setBackgroundImage (iconFile);
  toolButton->setToolTip(tip);
  toolButton->setMargin(3, Wt::Right);
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
  addGrassToolButton("layer-raster-more", "add various raster map layers");
  addGrassToolButton("layer-vector-add", "add vector map layer");
  addGrassToolButton("layer-vector-more", "add various vector map layers");
  addGrassToolButton("layer-more", "add various overlays");
  addGrassToolButton("layer-remove", "remove selected map layers");
  addGrassToolButton("table", "show attribute data for selected vector map");
  addGrassToolButton("layer-import", "import/link raster or vector data");
  addGrassToolButton("help", "grass manual");

  selectionBoxContainer->addWidget(m_ToolBar);
  addWidget(selectionBoxContainer);
}
