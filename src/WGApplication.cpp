/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WBootstrapTheme>
#include "MainUI.h"

#include "WGApplication.h"

#include "login.h"

#include "Startup.h"


WGApplication::WGApplication(const WEnvironment& env)
  : WApplication(env)
{
  /* setCssTheme("polished"); */
  setTheme(new WBootstrapTheme());

  addMetaHeader("viewport", "width = device-width, initial-scale = 1");
 
  root()->addStyleClass("container-fluid");


  internalPathChanged().connect(this, &WGApplication::handlePathChanged);

  WApplication::instance()->setInternalPath("/start", true);
 
}



void WGApplication::handlePathChanged(string loc_string)
{
  std::string current_path = internalPath();
  std::string uname, location, mapset;

         try {
           uname      = this->environment().getCookie("wgrass_login");
           location   = this->environment().getCookie("wgrass_location");
           mapset     = this->environment().getCookie("wgrass_mapset");
         }
         catch (exception& e) {
           cout << "COOKIE EXCEPTION: " << e.what() << endl;
         }

         if(current_path == "/grass")
           {
             root()->clear();
             MainUI * page_entry = new MainUI(root());
             setTitle("GRASS GIS UI");
           }
         else {
           root()->clear();
           Startup* startup = new Startup(uname, root());
           setTitle("Select Location and Mapset");
         }
 
}



/*! \brief 
  Creates a WApplication instance and return it
*/

WApplication *createApplication(const WEnvironment& env)
{

  WGApplication *app = new WGApplication(env);

  app->setTwoPhaseRenderingThreshold(0);

  return app;
}



