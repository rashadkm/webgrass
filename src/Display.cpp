
#include "Display.h"

void
Display::addDisplayToolButton(const std::string id, const std::string tip)  {
  Wt::WPushButton *toolButton = new Wt::WPushButton();
  toolButton->setStyleClass("wgrass-toolbar-icons");
  const std::string iconFile = "./icons/grass/" + id + ".png";
  toolButton->decorationStyle().setBackgroundImage (iconFile);
  toolButton->setToolTip(tip);
  toolButton->setMargin(3, Wt::Right);
  toolButton->setId("wgrass-tool-" + id);
  toolButton->resize(20, 30); //can we put this in css?
  d_ToolBar->addButton(toolButton);
  
}

Display::Display(WContainerWidget *parent=0)
  :WContainerWidget(parent) {


  addWidget(new WBreak());


  WContainerWidget *selectionBoxContainer = new WContainerWidget();


  selectionBoxContainer->setStyleClass("displayContainer");
  WtSelectionBoxDisplay = new Wt::WSelectionBox();
  WtSelectionBoxDisplay->setStyleClass("layertree");
  WtSelectionBoxDisplay->resize(5000,500);


  d_ToolBar = new Wt::WToolBar();

  addDisplayToolButton("show", "Display map");
  addDisplayToolButton("layer-redraw", "layer redraw");
  addDisplayToolButton("erase", "layer erase");
  addDisplayToolButton("pointer", "pointer");
  addDisplayToolButton("info", "query raster/vector maps");
  addDisplayToolButton("pan", "pan");
  addDisplayToolButton("zoom-in", "zoom in");
  addDisplayToolButton("zoom-out", "zoom out");
  addDisplayToolButton("zoom-extent", "zoom to selected map layers");
  addDisplayToolButton("zoom-last", "return to previous zoom");
  addDisplayToolButton("zoom-more", "various zoom options");
  addDisplayToolButton("layer-raster-analyze", "analyze map");
  addDisplayToolButton("overlay-add", "add map elements");
  addDisplayToolButton("map-export", "save display to file");
  addDisplayToolButton("print", "print");

  selectionBoxContainer->addWidget(d_ToolBar);
  selectionBoxContainer->addWidget(WtSelectionBoxDisplay);
  addWidget(selectionBoxContainer);


  

}



