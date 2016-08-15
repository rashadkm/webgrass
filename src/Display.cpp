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
    
//     const std::string ol =  "../scripts/ol.js";
// const std::string map =  "../scripts/map.js";
// std::stringstream strm;
// strm<<
// """var geojsonObject = {'type': 'FeatureCollection', 'crs': { 'type': 'name', 'properties': { 'name': 'urn:ogc:def:crs:OGC:1.3:CRS84' } }, 'features': [{ 'type': 'Feature', 'properties': { 'DN': 2 }, 'geometry': { 'type': 'Polygon', 'coordinates': [ [ [ 13.559093915055664, 52.545214330050563 ], [ 13.559633429050496, 52.545205649772548 ], [ 13.559633415380715, 52.545214636296755 ], [ 13.559093915055664, 52.545214330050563 ] ] ] } }]};"
// """var vectorSource = new ol.source.Vector({"
// """        features: (new ol.format.GeoJSON()).readFeatures(geojsonObject)"
// """     });"
// """   var vectorLayer = new ol.layer.Vector({"
// """     source: vectorSource"
// """      });"
// """      var map = new ol.Map({"
// """        layers: ["
// """       new ol.layer.Tile({"
// """         source: new ol.source.OSM()"
// """       }),"
// """       vectorLayer"
// """    ],"
// """ target: 'map',"
// """     controls: ol.control.defaults({"
//          """ attributionOptions:  ({"
//            """ collapsible: false"
//           """})"
//         """}),"
//         """view: new ol.View({"
//           """center: ol.proj.transform([13.55936,52.54521], 'EPSG:4326', 'EPSG:3857'),"
        
//         """zoom: 19,"
//         """rotation:0"
//         """})"
//       """});";
// WApplication::instance()->require(ol);
// WApplication::instance()->doJavaScript(strm.str());
// WApplication::instance()->doJavaScript();
  }

}