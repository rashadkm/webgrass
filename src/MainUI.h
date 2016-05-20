
//#ifndef _WGRASS_H_
//#define _WGRASS_H_




#include <Wt/WCheckBox>
#include <Wt/WLabel>
#include <Wt/WRandom>
#include<Wt/WTimer>
#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>


#include <map>
#include <utility>
#include <string>

#include "WOpenLayers.h"

#include <boost/assign/list_of.hpp> 


#include <Wt/WWidget>
#include <Wt/WSuggestionPopup>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WTextArea>

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
        WPopupMenu *sm ;
        WMenuItem *mi ;
        WMenu *m ;
        WNavigationBar *n;
        WContainerWidget *mainContainer;


};




