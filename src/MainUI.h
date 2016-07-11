#ifndef MAINUI_H
#define MAINUI_H

#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>
#include <Wt/WMenuItem>
#include <Wt/WPopupMenu>
#include <Wt/WDialog>
#include "Module.h"


class MainUI : public Wt::WContainerWidget
{
public:
  MainUI(Wt::WContainerWidget *parent=0);
  virtual ~MainUI();
  void createUI(Wt::WContainerWidget *parent);
  void openModuleUI(Wt::WMenuItem* gitem);
  
  enum Wt::WDialog::DialogCode code;

  void runModule(Wt::WDialog::DialogCode code);

private:
  Wt::WDialog *dialog;
  Module* mod;
  std::string gmodule;
};

#endif
