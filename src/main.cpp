/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/
#include <Wt/WServer>
#include "WGApplication.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	Wt::WServer server(argv[0]);
    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

  return WRun(argc, argv, &createApplication);


}
