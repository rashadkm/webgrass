#include <Wt/WApplication>
#include <Wt/WPaintedWidget>
#include <Wt/WContainerWidget>
#include <Wt/WPainter>
#include <Wt/WTable>
#include <Wt/WEnvironment>



#include <Wt/WFileUpload>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBorderLayout>
#include <Wt/WPushButton>
#include <Wt/WGridLayout>

#include <Wt/Http/Request>
#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WDialog>
#include <Wt/WSlider>
#include <Wt/WText>
#include <Wt/WFileUpload>

using namespace Wt;

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "login.h"
#include "global.h"


#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WSelectionBox>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include "selectLocationAndMapset.h"

using namespace std;

using namespace boost::filesystem; 
void selectLocationAndMapset::show_files( const path & directory, vector<string>&directories, bool recurse_into_subdirs = true )
{
if( exists( directory ) )
{
directory_iterator end ;
for( directory_iterator iter(directory) ; iter != end ; ++iter )
{
cout << directory << endl;
if ( is_directory( *iter ) )
{
directories.push_back(iter->path().leaf() );
//if( recurse_into_subdirs ) show_files(*iter) ;
}
//else
//cout << iter->native_file_string() << " (file)\n" ;
}
}
}


void selectLocationAndMapset::showMapsets(WString location) {
mapset->clear();
vector<string> directories;
const fs::path full_path ="./" + base_path + "/" + location.narrow() ;
show_files(full_path,directories,true );
for(vector<string>::iterator it = directories.begin();it!=directories.end();++it)
 mapset->addItem(*it);


}




selectLocationAndMapset::selectLocationAndMapset(std::string wgrass_login,WContainerWidget *parent=0)
:WContainerWidget(parent)
{
  //setTitle("VRGeo Login"); 

//useStyleSheet("styles.css");
anim = WAnimation();



WContainerWidget *mainContainer = new WContainerWidget(parent);


location = new WSelectionBox();




location->resize(320,240);

mainContainer->addWidget(location);

mapset = new WSelectionBox();


updateLocationAndMapsets(wgrass_login);
location->sactivated().connect(this, &selectLocationAndMapset::showMapsets);
mapset->resize(320,240);

mainContainer->addWidget(mapset);


mainContainer->addWidget(new WBreak());
mainContainer->addWidget(new WText("Upload Location"));
mainContainer->addWidget(new WBreak());
lupload = new WFileUpload();
lupload->setFileTextSize(50);
mainContainer->addWidget(lupload);
lupload->changed().connect(lupload, &WFileUpload::upload);
lupload->uploaded().connect(this, &selectLocationAndMapset::locationUploaded);
mainContainer->addWidget(new WBreak());
mainContainer->addWidget(new WBreak());
mainContainer->addWidget(new WBreak());
WPushButton *startWGrass = new WPushButton("Start webGRASS >>");
startWGrass->clicked().connect(this , &selectLocationAndMapset::startWebGrass);
startWGrass->resize(150,30);
mainContainer->addWidget(startWGrass);






mainContainer->resize(640,480);



}
void selectLocationAndMapset::locationUploaded() {

//if(isZipFile() { }
string cmd = "unzip -o" + lupload->spoolFileName() + " -d /home/rashad/code/wgrass/" + base_path;
system(cmd.c_str());
updateLocationAndMapsets(base_path);
}
void selectLocationAndMapset::updateLocationAndMapsets(string wgrass_login) {
location->clear();
mapset->clear();
vector<string> directories;
base_path = wgrass_login;
const fs::path full_path ="./" + base_path;
show_files(full_path,directories,true );
for(vector<string>::iterator it = directories.begin();it!=directories.end();++it) {
 
location->addItem(*it);
if(it == directories.begin())
{
mapset->clear();
vector<string> directories;
const fs::path full_path ="./" + base_path + "/" + *it ;
show_files(full_path,directories,true );
for(vector<string>::iterator it = directories.begin();it!=directories.end();++it)
 mapset->addItem(*it);
}
}
}
void selectLocationAndMapset::startWebGrass() {
string slocation = location->currentText().narrow();
string smapset = mapset->currentText().narrow();
 WApplication::instance()->setCookie("wgrass_location", location->currentText().narrow(), 60*60*24*24);
 WApplication::instance()->setCookie("wgrass_mapset", mapset->currentText().narrow(), 60*60*24*24);	


 std::ofstream grassrc;
  grassrc.open ("./grassrc7");
  grassrc << "GISDBASE: " + base_path << endl;
  grassrc << "LOCATION_NAME: " + slocation << endl;
  grassrc << "MAPSET: " + smapset << endl;
  grassrc << "GRASS_GUI: text" << endl;
  grassrc << "MONITOR: PNG" << endl;
  grassrc.close();
 WApplication::instance()->redirect("/");
}









