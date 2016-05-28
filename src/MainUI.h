
//#ifndef _WGRASS_H_
//#define _WGRASS_H_


#include <Wt/WCheckBox>
#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WTimer>
#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>

#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/Ext/Button>
#include <Wt/Ext/Menu>
#include <Wt/Ext/MenuItem>
#include <Wt/Ext/ComboBox>
#include <Wt/WCheckBox>



#include <map>
#include <utility>
#include <string>

#include "WOpenLayers.h"

#include <boost/assign/list_of.hpp> 
#include <Wt/WMessageBox>
#include <Wt/WPopupMenu>
#include <Wt/WPushButton>
#include <Wt/WText>

#include <Wt/WWidget>
#include <Wt/WSuggestionPopup>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WTextArea>

#include <pugixml.hpp>

#include <iostream>
#include "GMenuItem.h"


#include <Wt/Ext/ToolBar>

using namespace std;

using namespace Wt;

class MainUI : public WContainerWidget
{
    public:
        MainUI(WContainerWidget *parent=0);
        virtual ~MainUI();
        void createUI(WContainerWidget *parent);
        
    private:
        WPopupMenu *ssm ;
        WPopupMenu *menuToolBar;
        WPopupMenu *sm ;
        WMenuItem *mi ;
        WMenu *m ;
        WNavigationBar *n;
        WContainerWidget *mainContainer;
        GMenuItem *mnuItem;


};




