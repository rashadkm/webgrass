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

class Text_Gui : public WText {

public:
  Text_Gui();
  void setName(std::string name);
  void setType(std::string attribute);
  void setMult(std::string multiple);
  string Name();
  string Type();
  string Mult();
  
private:

  string t_name;
  string t_type;
  string t_mul;

};