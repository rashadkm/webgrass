#ifndef _WGMenuForm_H_
#define _WGMenuForm_H

#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/WTextArea>
#include <Wt/WComboBox>
#include <Wt/WLineEdit>
#include <Wt/WFileUpload>
#include <Wt/WTabWidget>
#include <Wt/WCheckBox>
#include <Wt/WDialog>
#include <Wt/WBreak>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/assign/list_of.hpp> 
#include <boost/bind.hpp>  
#include <boost/asio.hpp> 
#include <boost/array.hpp> 
#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>


#include "pugixml/pugixml.hpp"
#include "pstream.h"
#include "global.h"

using namespace Wt;
using namespace std;

class WGMenuForm :public WDialog{

private:
	WFileUpload *upload;
	std::string basename;
	std::string FQN;
	std::string pgm;
	WTabWidget *menuForm;
	std::vector<std::string> names;
	std::vector<std::string> fl;
	std::string args;
	WText *uploadedInfo;
	WLineEdit *edit;
	std::vector<WCheckBox*> flboxes;
	std::vector <WWidget *> tabs;
	std::stringstream pstream;
	WContainerWidget *btnContainer;
	WTextArea *cmdout;
	int count;
	WContainerWidget  *upContainer;
	WComboBox *cmbFormat;
	WLineEdit *outMap;
std::string label,help,handler,shortcut,keywords,command;
public:
WGMenuForm(std::string cmd,std::string kws=0);
~WGMenuForm();

void setupTabs();
const char* getXML(std::string program);
WWidget* createTab(std::string header);


	void setupTabs(std::string);
	void RunCommand();
	void setParametres(std::string);
	std::string WRunCommand(std::string exe,std::string args);
	WWidget* cmdOutput(std::string cmd);

};
#endif
