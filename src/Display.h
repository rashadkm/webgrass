#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WSelectionBox>
#include <Wt/WApplication>
#include <Wt/WToolBar>


#include "wgrassconfig.h"

using namespace Wt;

using namespace std;


class Display : public WContainerWidget {

public:
  Display( WContainerWidget *parent);


private:


  WSelectionBox *WtSelectionBoxDisplay;
  Wt::WToolBar *m_ToolBar;

  void addDisplayToolButton(std::string id,
        std::string tip);



};
