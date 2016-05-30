#include <Wt/WApplication>

#include "Startup.h"

Startup::Startup(std::string wgrass_login, WContainerWidget *parent=0)
  :WContainerWidget(parent) {

    WApplication::instance()->useStyleSheet("style.css");

  /* GRASS GIS database library */

  setStyleClass("mainContainer");

  /* image of GRASS GIS */
  Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();

  Wt::WImage *image = new Wt::WImage(Wt::WLink("http://grassmac.wdfiles.com/local--files/start/startup_banner.png"));
  //image->setStyleClass("banner");

  addWidget(image);

  /* layout with the use of grid. grid uses coordinates */
  WContainerWidget *selectionBoxContainer = new WContainerWidget();
  Wt::WHBoxLayout *selectionBoxContainerLayout = new Wt::WHBoxLayout();
  selectionBoxContainer->setLayout(selectionBoxContainerLayout);

  addWidget(new WBreak());

  addWidget(new WText("GRASS GIS data directory"));

  Wt::WSelectionBox *datadir = new Wt::WSelectionBox();

  datadir->resize(400, 30);
  datadir->addItem(GRASS_DATA_DIR);
  addWidget(datadir);

  Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
  WtSelectionBoxLocation = new Wt::WSelectionBox();
  //  WtSelectionBoxLocation->setStyleClass("startup-selectionbox");
  WtSelectionBoxLocation->resize(200,300);
  makeSelectionBox(WtSelectionBoxLocation, "");
  selectionBoxContainerLayout->addWidget(WtSelectionBoxLocation);
  addWidget(selectionBoxContainer);
  WtSelectionBoxLocation->activated().connect(this, &Startup::locationChanged);

  WtSelectionBoxMapset = new Wt::WSelectionBox();
  WtSelectionBoxMapset->activated().connect(this, &Startup::mapsetChanged);
  selectionBoxContainerLayout->addWidget(WtSelectionBoxMapset);
  WtSelectionBoxLocation->setCurrentIndex(-1);


  //  Wt::WGroupBox *groupBox2 = new Wt::WGroupBox("Accessile Mapsets");
  //  grid->addWidget(new WText("Choose Project Location and Mapset"),1,0);

  WPushButton *startWGrass = new WPushButton("Start webGRASS >>");

  startWGrass->setStyleClass("start-button");
  startWGrass->clicked().connect(this , &Startup::startWebGrass);
  addWidget(startWGrass);

}

/* dynamic updation of mapset when location changed and m_location variable */
void Startup::locationChanged( int index ) {
  WtSelectionBoxMapset->clear();
  m_location = WtSelectionBoxLocation->itemText(index).narrow();
  makeSelectionBox(WtSelectionBoxMapset, m_location);

}

/* dynamic updation of the m_mapset variable */
void Startup::mapsetChanged( int index ) {
    m_mapset = WtSelectionBoxMapset->itemText(index).narrow();
}


void Startup::startWebGrass() {

  /* setting the cookies */
  WApplication::instance()->setCookie("wgrass_location", m_location, 60*60*24*24);
  WApplication::instance()->setCookie("wgrass_mapset", m_mapset , 60*60*24*24);

  // std::ofstream grassrc;
  //  grassrc.open ("./grassrc7");
  //  grassrc << "GISDBASE: " + base_path << endl;
  //  grassrc << "LOCATION_NAME: " + slocation << endl;
  //  grassrc << "MAPSET: " + smapset << endl;
  //  grassrc << "GRASS_GUI: text" << endl;
  //  grassrc << "MONITOR: PNG" << endl;
  //  grassrc.close();
  WApplication::instance()->setInternalPath("/grass", true);
}


/* for returning the files in a directory */
void Startup::getFileList( vector<string>& dirlist, std::string subdir, bool recurse_into_subdirs ) {
  const fs::path basedir = std::string(GRASS_DATA_DIR) + "/" + subdir;
  if( fs::exists( basedir ) )  {
    fs::directory_iterator end ;
    for( fs::directory_iterator iter(basedir) ; iter != end ; ++iter ) {
      if ( fs::is_directory( *iter ) )  {
       dirlist.push_back(iter->path().leaf().string() );
      }
    }
  }
}

/* checking whether given directory exists or not */
bool Startup::checkExistance(std::string parent, std::string dir)  {
  const fs::path directory = std::string(GRASS_DATA_DIR) + "/" + parent + "/" + dir;
  return boost::filesystem::exists( directory );
}

/* initial construction of the mapset and Location wizard */
void Startup::makeSelectionBox(WSelectionBox *box, std::string dir) {
  std::vector<string> dirlist;
  getFileList(dirlist, dir, false);
  for( vector<string>::iterator it = dirlist.begin(); it!=dirlist.end(); ++it ) {
  bool isValidLocation = checkExistance(dir, *it);
    if (isValidLocation) {
      box->addItem(*it);
    }
  }
}
