/*
  (C) 2011 Lab for Spatial Informatics, IIIT-H,India
  This program is free software under the GNU General Public
  License (>=v2). Read the file COPYING for details.
  @author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#include <Wt/WApplication>
#include <Wt/WBootstrapTheme>

#include "WGApplication.h"
#include "MainUI.h"
#include "Startup.h"
#if defined(BUILD_WITH_OAUTH)
#include "Authentication.h"
#endif

#include "simple_login.h"

WGApplication::WGApplication(const Wt::WEnvironment& env)
  : Wt::WApplication(env)
{
  
  setTheme(new Wt::WBootstrapTheme());
 
  addMetaHeader("viewport", "width = device-width, initial-scale = 1");

  Wt::WApplication::instance()->setInternalPath("/", false);
  
  internalPathChanged().connect(this, &WGApplication::handle_path_changed);
  
#if defined(BUILD_WITH_OAUTH)  
  Wt::WApplication::instance()->setInternalPath("/Auth", true);
#else
  Wt::WApplication::instance()->setInternalPath("/login", true);  
#endif
  
  WApplication::instance()->useStyleSheet("style.css");

}

void WGApplication::handle_path_changed(std::string current_path)
{

  root()->clear();
  
  if(current_path == "/login")
    {
      root()->addWidget(new simple_login());
      this->setTitle("GRASS GIS - Login"); 
    }
  else if(current_path == "/grass")
    {
      root()->addWidget(new MainUI());
      this->setTitle("GRASS GIS - WebUI");
    }
  else if(current_path == "/start")
    {
      root()->addWidget(new Startup());
      // Startup* startup = new Startup( root() );
      this->setTitle("GRASS GIS - Select location and mapset");
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
