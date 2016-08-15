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
  m_ToolBar->addButton(toolButton);
  
}

Display::Display(WContainerWidget *parent=0)
  :WContainerWidget(parent) {


  addWidget(new WBreak());


  WContainerWidget *selectionBoxContainer = new WContainerWidget();


  selectionBoxContainer->setStyleClass("displayContainer");
  // WtSelectionBoxDisplay = new Wt::WSelectionBox();
  displayBox = new WContainerWidget();
   // WtSelectionBoxDisplay->resize(1100,500);
  displayBox->setStyleClass("wgrass-display");

   // p = new Draw(640,480);
  // addlayer();
  
  m_ToolBar = new Wt::WToolBar();

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

  selectionBoxContainer->addWidget(m_ToolBar);
  selectionBoxContainer->addWidget(new WBreak());
  selectionBoxContainer->addWidget(displayBox);
  addWidget(selectionBoxContainer);

}

void Display::addlayer(std::string a){
  displayBox->clear();
  if(a=="raster"){
      Wt::WImage *image = new Wt::WImage(Wt::WLink("../temp/2.jpg"));
  // image->setStyleClass("wgrass-startup-banner");
  displayBox->addWidget(image);
  displayBox->resize(700,500);
  }
  else if(a=="vector"){
    WApplication::instance()->doJavaScript("map.addLayer('../temp/1.shp')");
  }

}