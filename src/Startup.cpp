#include <Wt/WApplication>

#include "Startup.h"

Startup::Startup(std::string wgrass_login, WContainerWidget *parent=0)
  :WContainerWidget(parent) {



  setStyleClass("mainContainer");

  /* image of GRASS GIS */
  Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();

  Wt::WImage *image = new Wt::WImage(Wt::WLink("http://grassmac.wdfiles.com/local--files/start/startup_banner.png"));
  image->setStyleClass("wgrass-startup-banner");



  addWidget(image);



  addWidget(new WBreak());

  Wt::WText *text = new Wt::WText("GRASS GIS data directory");
  text->setMargin(20, Wt::Bottom);
  text->setMargin(10, Wt::Right);
  text->setStyleClass("text");
  addWidget(text);

  Wt::WSelectionBox *datadir = new Wt::WSelectionBox();

  datadir->resize(400, 30);
  datadir->addItem(GRASS_DATA_DIR);
  datadir->setStyleClass("wgrass-data-dir");
  datadir->setMargin(20, Wt::Bottom);
  addWidget(datadir);


  /* Name of boxes in hbox */
  Wt::WContainerWidget *textContainer = new Wt::WContainerWidget();
  textContainer->setStyleClass("wgrass-text-label");
  Wt::WHBoxLayout *hbox1 = new Wt::WHBoxLayout();
  textContainer->setLayout(hbox1);

  Wt::WText *item = new Wt::WText("Project Location");
  item->setStyleClass("wgrass-text-label");
  hbox1->addWidget(item);
  
  item = new Wt::WText("Project Mapsets");
  item->setStyleClass("wgrass-text-label");
  hbox1->addWidget(item);
  textContainer->setMargin(-20, Wt::Bottom);
  addWidget(textContainer);


    /* Location Box and Selection Box in a hbox */
  WContainerWidget *selectionBoxContainer = new WContainerWidget();
  Wt::WHBoxLayout *selectionBoxContainerLayout = new Wt::WHBoxLayout();
  selectionBoxContainer->setLayout(selectionBoxContainerLayout);
  Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
  WtSelectionBoxLocation = new Wt::WSelectionBox();


  /* Location Selection box */
  WtSelectionBoxLocation->setStyleClass("wgrass-startup-selectionbox");
  WtSelectionBoxLocation->resize(200,300);
  makeSelectionBox(WtSelectionBoxLocation, "");
  selectionBoxContainerLayout->addWidget(WtSelectionBoxLocation);
  WtSelectionBoxLocation->setCurrentIndex(-1);
  addWidget(selectionBoxContainer);
  WtSelectionBoxLocation->activated().connect(this, &Startup::locationChanged);

  /* Mapset Selection box*/
  WtSelectionBoxMapset = new Wt::WSelectionBox();
  WtSelectionBoxMapset->activated().connect(this, &Startup::mapsetChanged);
  selectionBoxContainerLayout->addWidget(WtSelectionBoxMapset);
  

  WPushButton *startWGrass = new WPushButton("Start webGRASS >>");

  startWGrass->setStyleClass("wgrass-start-button");
  startWGrass->clicked().connect(this , &Startup::startWebGrass);
  addWidget(startWGrass);

}

/* dynamic updation of mapset when location changed and m_location variable */
void Startup::locationChanged( int index ) {
  WtSelectionBoxMapset->clear();
  m_location = WtSelectionBoxLocation->itemText(index).narrow();
  makeSelectionBox(WtSelectionBoxMapset, m_location);
  WtSelectionBoxMapset->setCurrentIndex(-1);

}

/* dynamic updation of the m_mapset variable */
void Startup::mapsetChanged( int index ) {
    m_mapset = WtSelectionBoxMapset->itemText(index).narrow();
}


void Startup::startWebGrass() {

  /* setting the cookies */
  std::ofstream rcfile;
rcfile.open("/tmp/grassrc");


  if (rcfile.is_open())
  {std::cout<<"file open"<<std::endl;

    rcfile << "MAPSET: "+m_mapset+"\n";
    std::string str(GRASS_DATA_DIR);
    rcfile << "GISDBASE:" << GRASS_DATA_DIR << std::endl;
    rcfile << "LOCATION_NAME: "+m_location+"\n";
    rcfile << "GUI: text\n";
    rcfile.close();
  }


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
