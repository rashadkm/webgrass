#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WMenu>

#include <Wt/WNavigationBar>
#include <Wt/WMenuItem>
#include <Wt/WPopupMenu>

#include "Startup.h"
#include "Utils.h"

Startup::Startup(const std::string user_id, Wt::WContainerWidget *parent)
  :Wt::WContainerWidget(parent)
{

  setStyleClass("mainContainer");

  Wt::WPopupMenu *popup = new Wt::WPopupMenu( );
  Wt::WMenuItem *mitem_sign_out = new Wt::WMenuItem( "Sign Out" );
  mitem_sign_out->clicked().connect(this , &Startup::sign_out);
  popup->addItem(mitem_sign_out);
  //  popup->addItem("About");



  Wt::WPushButton *href_log_off = new Wt::WPushButton( user_id );
  href_log_off->setMenu(popup);
  href_log_off->setStyleClass("href_log_off");
  addWidget(href_log_off);
 
  addWidget(new Wt::WBreak());
  addWidget(new Wt::WBreak());
    
  Wt::WImage *image = new Wt::WImage(Wt::WLink("http://grassmac.wdfiles.com/local--files/start/startup_banner.png"));
  image->setStyleClass("wgrass-startup-banner");

  addWidget(image);

  addWidget(new Wt::WBreak());
  
  const std::string data_dir_text = std::string("GRASS GIS data directory: ") + std::string(GRASS_DATA_DIR);
  Wt::WLabel *text = new Wt::WLabel( data_dir_text );
  text->setMargin(20, Wt::Bottom);
  text->setMargin(10, Wt::Right);
  text->setStyleClass("text");
  addWidget(text);

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
  WtSelectionBoxLocation->resize(200,400);
  makeSelectionBox(WtSelectionBoxLocation, "");
  selectionBoxContainerLayout->addWidget(WtSelectionBoxLocation);
  WtSelectionBoxLocation->setCurrentIndex(-1);
  addWidget(selectionBoxContainer);
  WtSelectionBoxLocation->activated().connect(this, &Startup::locationChanged);

  /* Mapset Selection box*/
  WtSelectionBoxMapset = new Wt::WSelectionBox();
  WtSelectionBoxMapset->activated().connect(this, &Startup::mapsetChanged);
  selectionBoxContainerLayout->addWidget(WtSelectionBoxMapset);
  

  Wt::WPushButton *startWGrass = new Wt::WPushButton("Start webGRASS >>");

  startWGrass->setStyleClass("wgrass-start-button");
  startWGrass->clicked().connect(this , &Startup::startWebGrass);
  addWidget(startWGrass);

}

/* dynamic updation of mapset when location changed and location variable */
void Startup::locationChanged( int index )
{
  WtSelectionBoxMapset->clear();
  this->location = WtSelectionBoxLocation->itemText(index).narrow();
  makeSelectionBox(WtSelectionBoxMapset, location);
  WtSelectionBoxMapset->setCurrentIndex(-1);

}

/* dynamic updation of the mapset variable */
void Startup::mapsetChanged( int index )
{
  this->mapset = WtSelectionBoxMapset->itemText(index).narrow();
}
void Startup::sign_out( )
{
  Wt::WApplication::instance()->setCookie("wg_login", "", 0);
  Wt::WApplication::instance()->setInternalPath("/login", false);
  Wt::WApplication::instance()->redirect("/");
}
void Startup::startWebGrass( )
{

  /* setting the cookies */
  std::ofstream rcfile;
  
  rcfile.open("/tmp/grassrc");

  if (rcfile.is_open())
  {
    rcfile << "MAPSET: "+mapset+"\n";
    std::string str(GRASS_DATA_DIR);
    rcfile << "GISDBASE: "+str+"\n";
    rcfile << "LOCATION_NAME: "+location+"\n";
    rcfile << "GUI: text\n";
    rcfile.close();
  }
  //  WApplication::instance()->setCookie("wgrass_user", user_name, 60*60*24*24);

  Wt::WApplication::instance()->setInternalPath("/grass", true);
}


/* for returning the files in a directory */
void Startup::getFileList( std::vector<std::string>& dirlist, const std::string& subdir, bool recurse_into_subdirs )
{
  const fs::path basedir = std::string(GRASS_DATA_DIR) + "/" + subdir;
  if( fs::exists( basedir ) )
    {
      fs::directory_iterator end ;
      for( fs::directory_iterator iter(basedir) ; iter != end ; ++iter )
	{
	  if ( fs::is_directory( *iter ) )
	    {
	      dirlist.push_back(iter->path().leaf().string() );
	    }
	}
    }
}

/* checking whether given directory exists or not */
bool Startup::checkExistance(const std::string& parent, const std::string& dir)
{
  const fs::path directory = std::string(GRASS_DATA_DIR) + "/" + parent + "/" + dir;
  return boost::filesystem::exists( directory );
}

/* initial construction of the mapset and Location wizard */
void Startup::makeSelectionBox(Wt::WSelectionBox *box, const std::string& dir)
{
  std::vector<std::string> dirlist;
  getFileList(dirlist, dir, false);
  for( std::vector<std::string>::iterator it = dirlist.begin(); it!=dirlist.end(); ++it )
    {
      bool isValidLocation = checkExistance(dir, *it);
      if (isValidLocation)
	{
	  box->addItem(*it);
	}
    }
}
