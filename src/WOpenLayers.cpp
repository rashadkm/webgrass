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
const std::string oluri =  "../scripts/ol.js";
const std::string map =  "../scripts/map.js";
app->require(oluri);

  if (parent)
    parent->addWidget(this);

    std::stringstream strm;




strm <<
"";




    WApplication::instance()->doJavaScript(map);
  

}

WOpenLayers::~WOpenLayers()
{ }




void WOpenLayers::render(WFlags<RenderFlag> flags)
{
  if (flags & RenderFull) {
  WCompositeWidget::render(flags);
  }
}
