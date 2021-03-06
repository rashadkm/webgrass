#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <pugixml.hpp>
#include <boost/algorithm/string.hpp>
#include <map>
#include <boost/lexical_cast.hpp>
#include <string>

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
#include <Wt/WLineEdit>
#include <Wt/WString>

#include "Parameter.h"

#include "wgrassconfig.h"

using namespace Wt;

class Module : public WContainerWidget {

public:
  Module( std::ifstream& mod, WContainerWidget *parent = 0 );
  
  std::map<std::string,std::vector<Parameter *> > map;
  std::vector<std::string>container_IDs;
  std::vector<std::string>flag_IDs;
  void updateOutput(std::string gg);
  std::string out;
  WContainerWidget *container;
  WTabWidget *tabW;
  // Wt::WMenuItem *tab;
  Wt::WTextArea *ta;
};
