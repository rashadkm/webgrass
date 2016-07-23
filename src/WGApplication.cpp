/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#include <Wt/WApplication>
#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WBootstrapTheme>

#include "WGApplication.h"
#include "MainUI.h"
#include "Startup.h"
#include "login.h"


WGApplication::WGApplication(const Wt::WEnvironment& env)
: Wt::WApplication(env) {

  setTheme(new Wt::WBootstrapTheme());
 
  addMetaHeader("viewport", "width = device-width, initial-scale = 1");
  
  internalPathChanged().connect(this, &WGApplication::handlePathChanged);
  
  Wt::WApplication::instance()->setInternalPath("/login", true);
  
  WApplication::instance()->useStyleSheet("style.css");

}

void WGApplication::handlePathChanged(std::string loc_string) {

 std::string current_path = internalPath();
 std::string uname, location, mapset;

try {
uname      = this->environment().getCookie("wgrass_login");
location   = this->environment().getCookie("wgrass_location");
mapset     = this->environment().getCookie("wgrass_mapset");
         }
catch (exception& e) {
	   //           cout << "COOKIE EXCEPTION: " << e.what() << endl;
         }

if(current_path == "/grass")
           {
root()->clear();
             MainUI * page_entry = new MainUI(root());
setTitle("GRASS GIS UI");
}
else if(current_path == "/start") {
root()->clear();
Startup* startup = new Startup(uname, root());
setTitle("Select Location and Mapset");
}

else
{
  root()->clear();
Login* login = new Login(root());
setTitle("Select Location and Mapset");
}

}


/*! \brief
  Creates a WApplication instance and return it
*/
WGApplication *createApplication(const Wt::WEnvironment& env) {

  WGApplication *app = new WGApplication(env);
  app->setTwoPhaseRenderingThreshold(0);
  return app;
}
