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

#include "wgrassconfig.h"

using namespace Wt;

using namespace std;

namespace fs = boost::filesystem;

class Startup : public WContainerWidget {

public:
  Startup(std::string wgrass_login, WContainerWidget *parent);
  void startWebGrass();
  void getFileList( vector<string>& dirlist, std::string subdir, bool recurse_into_subdirs = false );
  void showMapsets(WString location);
  void locationUploaded();
  void updateLocationAndMapsets(string wgrass_login);
  void locationChanged(int index);
  void mapsetChanged(int index);
  void makeSelectionBox(WSelectionBox *box, std::string dir);
  bool checkExistance(std::string parent, std::string dir);

private:

  WSelectionBox *WtSelectionBoxMapset;
  WSelectionBox *WtSelectionBoxLocation;
  WContainerWidget *unameWidget;

  string m_location;
 string m_mapset;

};
