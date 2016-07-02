#include <stdlib.h>
#include <fstream>
#include <iostream>

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
#include <Wt/WCheckBox>

#include "wgrassconfig.h"

using namespace Wt;

class Module : public WContainerWidget {

public:
  Module( std::string mod, WContainerWidget *parent = 0 );
 

};
