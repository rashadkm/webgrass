/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#include <Wt/WApplication>
#include <Wt/WEnvironment>


#include <iostream>

using namespace Wt;
using namespace std;

class WGApplication: public WApplication {
 public:
  	WGApplication(const WEnvironment& env);

};

WApplication *createApplication(const WEnvironment& env);


