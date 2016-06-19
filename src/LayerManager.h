#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WCheckBox>
#include <Wt/WSelectionBox>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WMenuItem>
#include <Wt/WPopupMenu>

#include "wgrassconfig.h"

using namespace Wt;

using namespace std;

namespace fs = boost::filesystem;

class LayerManager : public WContainerWidget {

public:
  LayerManager( WContainerWidget *parent);
  

private:


  WSelectionBox *WtSelectionBoxMap;
  WContainerWidget *unameWidget;


};
