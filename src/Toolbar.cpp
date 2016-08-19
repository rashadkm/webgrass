#include "Toolbar.h"
#include "../thirdparty/pstream/pstream.h"


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

  addFiles1 = new Wt::WPopupMenu();
  addFiles2 = new Wt::WPopupMenu();

  vecTOR = new Wt::WPushButton("Add Vector");
  
  

  rasTER = new Wt::WPushButton("Add Raster");
 
  command1 = "g.list type=vector";
  command2 = "g.list type=raster";

  grassCommand1();
  grassCommand2();

  vecTOR->setMenu(addFiles1);
  rasTER->setMenu(addFiles2);

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
  selectionBoxContainer->addWidget(vecTOR);
  selectionBoxContainer->addWidget(rasTER);
  addWidget(selectionBoxContainer);
}

void Toolbar::openVec(Wt::WMenuItem* gitem) {
  // std::cout<<(gitem->text())<<std::endl;
  // displaymanager->addlayer();
  type="vector";
  layEr = (gitem->text()).narrow();
  std::cout<<layEr<<std::endl;
}
void Toolbar::openRas(Wt::WMenuItem* gitem) {
  
  type="raster";
  
  layEr = gitem->text().narrow();
  
  std::cout<<layEr<<std::endl;
}

void Toolbar::grassCommand1(){
  
    redi::ipstream proc("../scripts/init_grass.sh "+ command1);     

              std::string line;
              std::cout.flush();

              
              while (std::getline(proc.out(), line)){
                Wt::WMenuItem *item = addFiles1->addItem(line);
                item->triggered().connect(this, &Toolbar::openVec);
                
              }

}
void Toolbar::grassCommand2(){
  
    redi::ipstream proc("../scripts/init_grass.sh "+ command2);     

              std::string line;
              std::cout.flush();

              
              while (std::getline(proc.out(), line)){
                Wt::WMenuItem *item = addFiles2->addItem(line);
                item->triggered().connect(this, &Toolbar::openRas);
                
              }

}