/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/
#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED

#include <Wt/WApplication>
#include <Wt/WEnvironment>
class WGApplication: public Wt::WApplication
{

 public:

  WGApplication(const Wt::WEnvironment& env);
  
  void handle_path_changed(std::string loc_string);
  
 private:
  std::string user_id;
};

WGApplication *createApplication(const Wt::WEnvironment& env);

#endif
