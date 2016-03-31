/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#include "WOpenLayers.h"
#include <Wt/WApplication>
#include <Wt/WContainerWidget>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>


using namespace Wt;


using namespace std;

WOpenLayers::WOpenLayers(WContainerWidget *parent)
:arguments_(this,"arguments")
{
  setImplementation(new WContainerWidget());

WApplication *app = WApplication::instance();
const std::string oluri =  "OL/lib/OpenLayers.js";
app->require(oluri);

  if (parent)
    parent->addWidget(this);

    std::stringstream strm;




strm <<
"""function initialize() {"
"""OpenLayers.ProxyHost = \"/cgi-bin/proxy.cgi?url=\";"
"""map = new OpenLayers.Map('" + this->id()+ "', {"
""" allOverlays: true,maxExtent: new OpenLayers.Bounds(-180,-90,90,180),"
"""controls: [new OpenLayers.Control.PanZoom()]});"
"""navigate = new OpenLayers.Control.Navigation({title:\"Pan Map\" });"
"""map.addControl(new OpenLayers.Control.LayerSwitcher());"
"""map.addControl(new OpenLayers.Control.MousePosition());"
"""map.addControl(navigate);"
"}initialize();";




    WApplication::instance()->doJavaScript(strm.str());
  

}

WOpenLayers::~WOpenLayers()
{ }




void WOpenLayers::render(WFlags<RenderFlag> flags)
{
  if (flags & RenderFull) {
  WCompositeWidget::render(flags);
  }
}
