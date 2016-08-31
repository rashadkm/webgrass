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

namespace fs = boost::filesystem;

class Startup : public Wt::WContainerWidget
{
public:
  Startup( Wt::WContainerWidget *parent=0 );
  
  void startWebGrass();
    
  void locationUploaded();
  
  void updateLocationAndMapsets(const std::string& wgrass_login);
  
  void locationChanged(int index);
  
  void mapsetChanged(int index);

  void sign_out();

private:

    
  void makeSelectionBox(Wt::WSelectionBox *box, const std::string& dir);
  
  bool checkExistance(const std::string& parent, const std::string& dir);

  void getFileList( std::vector<std::string>& dirlist, const std::string& subdir, bool recurse_into_subdirs = false );
  
  void showMapsets(const Wt::WString& location);

  Wt::WSelectionBox *WtSelectionBoxMapset;
  Wt::WSelectionBox *WtSelectionBoxLocation;
  Wt::WContainerWidget *unameWidget;

  std::string location;
  std::string mapset;

};
