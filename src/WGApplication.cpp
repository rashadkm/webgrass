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
  , user_id("")
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
  try {
    user_id = this->environment().getCookie("wg_login");
  }
  catch(std::runtime_error e) {
    std::cerr << e.what();
  }

  if ( this->user_id.empty() )
    {
      root()->clear();
      simple_login *login_ui = new simple_login();
      root()->addWidget( login_ui );
      this->setTitle("GRASS GIS - Login");
    }
  else
    {
      root()->clear();
      Wt::WApplication::instance()->setInternalPath("/start", true);
    }

  if(current_path == "/grass")
    {
      root()->clear();
      const std::string fn = "/tmp/grassrc_" + user_id;
      root()->addWidget( new MainUI( fn ) );
      this->setTitle("GRASS GIS - WebUI");
    }
  else if(current_path == "/start")
    {
      root()->clear();
      Startup *s = new Startup( user_id );
      const std::string fn = "/tmp/grassrc_" + user_id;
      s->set_rc_file_name( fn );
      root()->addWidget( s );
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
