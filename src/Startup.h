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

using namespace Wt;

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WComboBox>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>


using namespace std;

namespace fs = boost::filesystem;


class Startup : public WContainerWidget {

public:
  Startup(std::string wgrass_login, WContainerWidget *parent);

void startWebGrass();
void show_files( const fs::path & full_path, vector<string>&directories, bool isDir );
void showMapsets(WString location);
void locationUploaded();
void updateLocationAndMapsets(string wgrass_login);
void comboChanged(WString thisi);
void combo1Changed(WString thisee);

private:

WSelectionBox *mapset;
WSelectionBox *location;
WSelectionBox *cb1;
string k;
string l;

WAnimation anim;
WContainerWidget *unameWidget;
string base_path;
WFileUpload *lupload;

};
