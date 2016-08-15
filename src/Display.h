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
#include <Wt/WImage>
#include "Draw.h"
#include "WOpenLayers.h"

#include "wgrassconfig.h"

using namespace Wt;

using namespace std;


class Display : public WContainerWidget {

public:
  Display( WContainerWidget *parent);
  WOpenLayers *maprender;
  void addlayer(std::string a);
  // Draw *p;

private:


  WSelectionBox *WtSelectionBoxDisplay;
  Wt::WToolBar *m_ToolBar;
  WContainerWidget *displayBox;

  void addDisplayToolButton(std::string id,
        std::string tip);



};
