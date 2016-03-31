/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#ifndef _WGRASS_H_
#define _WGRASS_H_




#include <Wt/WCheckBox>
#include <Wt/WLabel>
#include <Wt/WRandom>
#include<Wt/WTimer>
#include <Wt/WContainerWidget>


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

class WGrass : public WContainerWidget
{
  public:
    WGrass(WContainerWidget *parent=0);
    virtual ~WGrass();
    void createUI(WContainerWidget *parent);
	void dataUploaded();



	void simplePopup(WContainerWidget *parent);
	WSuggestionPopup* createAliasesMatchingPopup(WContainerWidget *parent);
	WStandardItemModel* createDrugsModel();
	void flagChecked();


  private:
	WFileUpload *upload;
	WOpenLayers *oMap;
	string basename;
	string FQN;
	string pgm;
	WTabWidget *menuForm;
	vector<string> names;
	vector<string> fl;
	string args;
	WText *uploadedInfo;
	WLineEdit *edit;
	WSuggestionPopup *popup;
	vector<WCheckBox*> flboxes;
	stringstream pstream;
	WContainerWidget *btnContainer;
	WTextArea *cmdout;
	int count;
	vector <WWidget *> tabs;
	WContainerWidget  *upContainer;
	WComboBox *cmbFormat;
	WLineEdit *outMap;





};
#endif



