#include "GMenuItem.h"
#include <Wt/WDialog>
#include <Wt/WPushButton>
#include <Wt/WHBoxLayout>

#include <iostream>


#include "WGMenuForm.h"

using namespace std;
using namespace Wt;
GMenuItem::GMenuItem(std::string lbl,std::string cmd,std::string kws)
:Wt::Ext::MenuItem(lbl),
label(lbl),
command(cmd),
keywords(kws){

this->activated().connect(this,&GMenuItem::menuItemActivated);

}
GMenuItem::~GMenuItem(){}


void GMenuItem::menuItemActivated() {

WGMenuForm *form= new WGMenuForm(command,keywords);

}


