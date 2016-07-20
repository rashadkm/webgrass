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

class Parameter_text {

public:
  Parameter_text();
  void setText(std::string text);
  void setName(std::string name);
  void setType(std::string attribute);
  void setMult(std::string multiple);
  void isFlag(std::string flag="No");
  void setFlag_no(int n);
  void setTabname(std::string tab);
  string Text();
  string Name();
  string Type();
  string Mult();
  string Flag();
  int Flag_no();
  string Tab();
private:

  string p_text;
  string p_name;
  string p_type;
  string p_mul;
  string p_flag;
  int p_flag_no;
  string p_tab;
};