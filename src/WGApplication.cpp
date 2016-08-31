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
#if defined(BUILD_WITH_OAUTH)
#include "Authentication.h"
#endif

#include "simple_login.h"

WGApplication::WGApplication(const Wt::WEnvironment& env)
: Wt::WApplication(env) {

  setTheme(new Wt::WBootstrapTheme());
 
  addMetaHeader("viewport", "width = device-width, initial-scale = 1");

  Wt::WApplication::instance()->setInternalPath("/", false);
  
  internalPathChanged().connect(this, &WGApplication::handle_path_changed);
  
  #if defined(BUILD_WITH_OAUTH)  
  Wt::WApplication::instance()->setInternalPath("/Auth", true);
  #else
  Wt::WApplication::instance()->setInternalPath("/start", true);  
  #endif
  
  WApplication::instance()->useStyleSheet("style.css");

}

void WGApplication::handle_path_changed(std::string loc_string) {

 const std::string current_path = internalPath();

 std::string uname;
 try
   {
     uname = this->environment().getCookie("wg_login");
   }
 catch (std::exception& e)
   {

   }

 
#if 1
     root()->clear();
     simple_login * main_ui = new simple_login( root() );
     this->setTitle("Login");
 #else
 if(current_path == "/grass")
   {
     root()->clear();
     MainUI * main_ui = new MainUI( root() );
     this->setTitle("GRASS GIS UI");
   }
 else if(current_path == "/start")
   {
     root()->clear();
     Startup* startup = new Startup( root() );
     this->setTitle("Select Location and Mapset");
   }
 else{
   root()->clear();
   #if defined(BUILD_WITH_OAUTH)    
   Authentication* auth = new Authentication( root() );
   this->setTitle("Authorization");
   #endif
 }

#endif
}


/*! \brief
  Creates a WApplication instance and return it
*/
WGApplication *createApplication(const Wt::WEnvironment& env) {

  WGApplication *app = new WGApplication(env);
  app->setTwoPhaseRenderingThreshold(0);
  return app;
}
