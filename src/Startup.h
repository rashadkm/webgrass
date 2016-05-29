#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBorderLayout>
#include <Wt/WPushButton>
#include <Wt/WGridLayout>
#include <Wt/WGroupBox>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WImage>
#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WSelectionBox>

using namespace Wt;

#include "login.h"
#include "global.h"


using namespace std;

//using namespace boost::filesystem; 


namespace fs = boost::filesystem;


class Startup : public WContainerWidget {

public:
  Startup(std::string wgrass_login, WContainerWidget *parent);

void startWebGrass();
void showFiles( const fs::path & full_path, vector<string>&directories, bool isDir );
void showMapsets(WString location);
void locationUploaded();
void updateLocationAndMapsets(string wgrass_login);
void locationChanged(WString loc_string);
void mapsetChanged(WString map_string);
void makeSelectionBox(WSelectionBox *box, vector<string> dir, string di);
bool checkExistance(std::string directory, std::string cont);

private:

WSelectionBox *mapset;
WSelectionBox *location;
WSelectionBox *WtSelectionBoxMapset;
WSelectionBox *WtSelectionBoxLocation;
string m_location;
string m_mapset;
string m_GrassDataDirectory;


WContainerWidget *unameWidget;
string base_path;
WFileUpload *lupload;

};
