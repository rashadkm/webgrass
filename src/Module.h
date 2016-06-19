#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WToolBar>
#include <Wt/WTabWidget>
#include <Wt/WTextArea>
#include <Wt/WMenuItem>
#include <Wt/WComboBox>
#include <Wt/WText>

#include "wgrassconfig.h"

using namespace Wt;

using namespace std;

namespace fs = boost::filesystem;

class Module : public WContainerWidget {

public:
  Module( WContainerWidget *parent,std::string mod);
  

private:


  WContainerWidget *unameWidget;


};
