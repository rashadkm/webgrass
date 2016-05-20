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
    	setCssTheme("polished");
      setTheme(new WBootstrapTheme());

      addMetaHeader("viewport", "width = device-width, initial-scale = 1");

      root()->addStyleClass("container-fluid");

   

   WApplication *wapp = WApplication::instance();
std::string uname;
std::string location;
std::string mapset;

            try {
            	uname = wapp->environment().getCookie("wgrass_login");
            	location = wapp->environment().getCookie("wgrass_location");
            	mapset = wapp->environment().getCookie("wgrass_mapset");
            } catch (exception& e) {  cout << "COOKIE EXCEPTION: " << e.what() << endl; }

            if (uname.empty())  {
               new Login(root());
            }
            else if(location.empty() || mapset.empty()) {
                new Startup(uname, root());
                wapp->setTitle("Select Location and Mapset");
            }
            else {
               new MainUI(root());

            }
}



    /*! \brief 
    Creates a WApplication instance and return it
	*/

WApplication *createApplication(const WEnvironment& env)
{



  WApplication *app = new WGApplication(env);


  app->setTwoPhaseRenderingThreshold(0);
    /*! \brief 
    Sets the application title.
    */
  app->setTitle("GRASS GIS Web UI");

  app->useStyleSheet("styles.css");

  //app->useStyleSheet("ows.css");

  return app;
}



