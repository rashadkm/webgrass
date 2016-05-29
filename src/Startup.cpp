#include "Startup.h"

/* for returning the files in a directory */
void Startup::showFiles( const fs::path & directory, vector<string>&directories, bool recurse_into_subdirs = true )
{
  if( fs::exists( directory ) )    {
    fs::directory_iterator end ;
    for( fs::directory_iterator iter(directory) ; iter != end ; ++iter ) {
      if ( fs::is_directory( *iter ) )  {
	  directories.push_back(iter->path().leaf().string() );	  
	}
      }
  }
}

/* checking whether given directory exists or not */
bool Startup::checkExistance(std::string directory, std::string path)  {
  return boost::filesystem::exists( path + "/" + directory ); 
}


/* initial construction of the mapset and Location wizard */
void Startup::makeSelectionBox(WSelectionBox *box, vector<string> dir, string di) {
  for(vector<string>::iterator it = dir.begin();it!=dir.end();++it)  {
    bool isValidLocation = checkExistance(*it, di);
    if (isValidLocation) {
      box->addItem(*it);
    } 
  }
}

Startup::Startup(std::string wgrass_login, WContainerWidget *parent=0)
  :WContainerWidget(parent) {

    WApplication::instance()->useStyleSheet("style.css");
    
  /* GRASS GIS database library */
  m_GrassDataDirectory = "/home/mayank/webgrassdata";

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
  
  datadir->resize(200, 25);
  
  datadir->addItem(m_GrassDataDirectory);
  addWidget(datadir);
    
  const fs::path fi= m_GrassDataDirectory;
  vector<string> dir;
  showFiles(fi,dir,true);
 
  Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
  WtSelectionBoxLocation = new Wt::WSelectionBox(); 
  //  WtSelectionBoxLocation->setStyleClass("startup-selectionbox");
  WtSelectionBoxLocation->resize(200,300);
  makeSelectionBox(WtSelectionBoxLocation, dir, m_GrassDataDirectory);
  selectionBoxContainerLayout->addWidget(WtSelectionBoxLocation);
  addWidget(selectionBoxContainer);
  
  /* capturing the click */
  WtSelectionBoxLocation->sactivated().connect(this, &Startup::locationChanged); 

    
  WtSelectionBoxMapset = new Wt::WSelectionBox(); 
  WtSelectionBoxMapset->sactivated().connect(this, &Startup::mapsetChanged);
  selectionBoxContainerLayout->addWidget(WtSelectionBoxMapset);


  //  Wt::WGroupBox *groupBox2 = new Wt::WGroupBox("Accessile Mapsets");
  //  grid->addWidget(new WText("Choose Project Location and Mapset"),1,0);

  WPushButton *startWGrass = new WPushButton("Start webGRASS >>");

  startWGrass->setStyleClass("start-button");
  startWGrass->clicked().connect(this , &Startup::startWebGrass);
  addWidget(startWGrass);
  
}


/* dynamic updation of mapset when location changed and m_location variable */
void Startup::locationChanged(WString loc_string){ 
       
  m_location = loc_string.narrow();
  
  WtSelectionBoxMapset->clear();
  vector<string> directories;
  string hh=m_GrassDataDirectory;
  string gg=hh+(string)"/";
  string jj=gg+m_location;

  const fs::path fii= gg + m_location;

  showFiles(fii,directories,true );
  makeSelectionBox(WtSelectionBoxMapset,directories,jj);

}


/* dynamic updation of the m_mapset variable */
void Startup::mapsetChanged(WString map_string){  
	
  //  cout<<map_string.narrow()<<endl;
  m_mapset = map_string.narrow();
}



void Startup::startWebGrass() {

  //  cout<<m_location<<endl;   cout<<m_mapset<<endl;

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









