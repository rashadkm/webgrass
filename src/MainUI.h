#ifndef MAINUI_H
#define MAINUI_H

#include <iostream>
#include <pugixml.hpp>
#include <cstring>
#include <boost/filesystem.hpp>


#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WToolBar>
#include <Wt/WApplication>
#include <Wt/WLabel>

#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>
#include <Wt/WMenuItem>
#include <Wt/WPopupMenu>
#include <Wt/WDialog>

#include "Module.h"
#include "LayerManager.h"
#include "Display.h"
#include "Toolbar.h"


class MainUI : public Wt::WContainerWidget
{
public:
  MainUI(const std::string s, Wt::WContainerWidget *parent=0);
  virtual ~MainUI();
  void createUI(Wt::WContainerWidget *parent);
  void openModuleUI(Wt::WMenuItem* gitem);
  


  void runModule();
  void Load();
  void runCommand(std::string a);
  void deleteModule(Wt::WDialog::DialogCode code);
  Display* displaymanager;
  Toolbar* toolbar;

 private:
    std::string rc_file_name;
};

#endif
