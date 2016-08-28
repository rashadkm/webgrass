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

  displayBox = new WContainerWidget();

  displayBox->setStyleClass("wgrass-display");

  // Wt::WContainerWidget *maplayer = new Wt::WContainerWidget();
  // WOpenLayers* maprender = new WOpenLayers(maplayer);

#if 0
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

#endif  
}

void Display::addlayer(std::string a){
  displayBox->clear();
  if(a=="raster"){
    std::string file = Wt::WApplication::instance()->docRoot() + "/build/output.jpg";
      Wt::WImage *image = new Wt::WImage(file);
  // image->setStyleClass("wgrass-startup-banner");
  displayBox->addWidget(image);
  displayBox->resize(700,500);
  }
  else if(a=="vector"){
    
    const std::string ol =  "../scripts/ol.js";
const std::string map =  "../scripts/map.js";



std::ifstream file( "../scripts/map.js" );
std::stringstream buffer;

    if ( file )
    {
        

        buffer << file.rdbuf();

        file.close();

        // operations on the buffer...
    }


WApplication::instance()->require(ol);
WApplication::instance()->doJavaScript(buffer.str());
// Wt::WWidget *h = new Wt::WWidget();
// h->doJavaScript(buffer.str());
// displayBox->addWidget(h);

  }

}
