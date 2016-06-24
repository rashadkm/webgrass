#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WToolBar>

#include "wgrassconfig.h"

using namespace Wt;

using namespace std;

class Toolbar : public WContainerWidget {

public:
  Toolbar( WContainerWidget *parent);
  

private:


  Wt::WToolBar *m_ToolBar;

  void addGrassToolButton(std::string id,
			  std::string tip);


};