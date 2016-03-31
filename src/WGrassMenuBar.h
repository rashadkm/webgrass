#ifndef _WGrassMenuBar_H_
#define _WGrassMenuBar_H_

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/Ext/Button>
#include <Wt/Ext/Menu>
#include <Wt/Ext/MenuItem>
#include <Wt/Ext/ToolBar>
#include <Wt/Ext/ComboBox>
#include <Wt/WCheckBox>
#include <Wt/WPushButton>

#include "pugixml/pugixml.hpp"

#include <iostream>
#include "GMenuItem.h"

using namespace Wt;

class WGrassMenuBar : public WContainerWidget {

   private:
      WApplication *wapp;
GMenuItem *mnuItem;
   public:

    /*! \brief 
    Constructor - Creates the MenuBar and Menu.
    LayerTree instance is passed as an argument which is saved
    in the instance of VRLayerTree (ltree).    
    */
    WGrassMenuBar(WContainerWidget *parent = 0);

    /*! \brief 
    Default Destructor.    
    */
   ~WGrassMenuBar();
   
   void onAddVector();

   void onAddRaster();

    /*
 
    void LoadShpLayer();

    void AddBaseMap();

    void AddGoogleMap(string type);

    void NewSHPLayer();

    void NewGPXLayer();

    void NewGMLLayer();

    void LoadGmlLayer();

    void LoadGPXLayer();

    void EditLayerSchema();

    void LoadTrackLog();

    void AboutUs();

   void LogOut();

   void SetLoggedIn(string loggedin);

	void NewCSVLayer();
*/

};

#endif
