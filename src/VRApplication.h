#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include "VRMessageBox.h"

#include "VRGeo.h"
#include <iostream>

using namespace Wt;
using namespace std;



class VRApplication: public WApplication {


 public:
  	VRApplication(const WEnvironment& env);
	VRGeo* vrgeo;
    void changeView(string);
};

WApplication *createEditorApplication(const WEnvironment& env);


