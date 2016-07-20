#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include <Wt/WLineEdit>
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
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WSelectionBox>


#include "Parameter_text.h"
#include "wgrassconfig.h"

using namespace Wt;

using namespace std;

namespace fs = boost::filesystem;

class Parameter {

public:
  Parameter();
  Parameter_text *Name_op;
  WLineEdit *container_op;

};