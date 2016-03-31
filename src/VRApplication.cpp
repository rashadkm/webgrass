#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WLabel>
#include <Wt/WRandom>

#include "global.h"

#include "VRApplication.h"
#include "VRFeatureInfo.h"
#include "VRMessageBox.h"
#include "login.h"

VRApplication::VRApplication(const WEnvironment& env)
:WApplication(env)
{
	setCssTheme("polished");

   WApplication *wapp = WApplication::instance();

   internalPathChanged().connect(this, &VRApplication::changeView);

   new VRGeo(root(),EDITOR);
   wapp->setTitle("VRGeo Editor");







  


/*
    string uname,prj;

string addlayer,vrg;

   map<string,vector<string> > pmap = env.getParameterMap();

  vector<string> vrgeo = pmap["vrgeo"];

   if(vrgeo.size() == 1) {

      vrg  = *env.getParameter("vrgeo");
        if(vrg == EDITOR) {

            try {
            	uname = wapp->environment().getCookie("vrgeo");
            	prj = wapp->environment().getCookie("project");
            } catch (exception& e) {  cout << "COOKIE EXCEPTION: " << e.what() << endl; }

            if (prj.empty() || uname.empty())  {
               new Login(root());
            }
            else {
                new VRGeo(root(),vrg);
                wapp->setTitle("VRGeo Editor");
            }
        }
        else if(vrg == VIEWER) {
            wapp->setTitle("VRGeo Viewer");
            new VRGeo(root(),vrg);
	     }

   }
*/
    
}



    /*! \brief 
    Creates a WApplication instance and return it
	*/
void VRApplication::changeView(string path) {
cerr << path << " CCC" << endl;
}
WApplication *createEditorApplication(const WEnvironment& env)
{



  WApplication *app = new VRApplication(env);


  app->setTwoPhaseRenderingThreshold(0);
    /*! \brief 
    Sets the application title.
    */

  app->useStyleSheet("style/orange/style.css");
  app->useStyleSheet("products.css");
  app->useStyleSheet("styles.css");

  app->useStyleSheet("ows.css");

 

  return app;
}



