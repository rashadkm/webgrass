#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WToolBar>
#include <Wt/WMenuItem>
#include <Wt/WPopupMenu>



#include "wgrassconfig.h"

using namespace Wt;

using namespace std;

class Toolbar : public WContainerWidget {

public:
  Toolbar( WContainerWidget *parent);
  std::string layEr;
  std::string type;

private:


  Wt::WToolBar *m_ToolBar;

  void addGrassToolButton(std::string id,
			  std::string tip);
  void openVec(Wt::WMenuItem* gitem);
  void openRas(Wt::WMenuItem* gitem);
  std::string command1;
  std::string command2;
  Wt::WPushButton *vecTOR;
  Wt::WPushButton *rasTER;
  Wt::WPopupMenu *addFiles2;
  Wt::WPopupMenu *addFiles1;
  void grassCommand1();
  void grassCommand2();


};