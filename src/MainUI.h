#ifndef MAINUI_H
#define MAINUI_H

#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>
#include <Wt/WMenuItem>
#include <Wt/WPopupMenu>

class MainUI : public Wt::WContainerWidget
{
public:
  MainUI(Wt::WContainerWidget *parent=0);
  virtual ~MainUI();
  void createUI(Wt::WContainerWidget *parent);

};

#endif
