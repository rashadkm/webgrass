
#include "LayerManager.h"

LayerManager::LayerManager(WContainerWidget *parent=0)
  :WContainerWidget(parent) {

    WApplication::instance()->useStyleSheet("style.css");


  addWidget(new WBreak());



  WContainerWidget *selectionBoxContainer = new WContainerWidget();
  selectionBoxContainer->setStyleClass("displayContainer");
  selectionBoxContainer->resize(200,3000);
  // Wt::WHBoxLayout *selectionBoxContainerLayout = new Wt::WHBoxLayout();
  // selectionBoxContainer->setLayout(selectionBoxContainerLayout);
   

  Wt::WCheckBox *cb;
  Wt::WCheckBox *cb1;
  Wt::WCheckBox *cb2;

  cb1 = new Wt::WCheckBox("Map 1",selectionBoxContainer);
  cb1->setChecked(true);
  //cb1->setInline(false);
  Wt::WPopupMenu *popup = new Wt::WPopupMenu();
  popup->addItem("Remove");
  popup->addSeparator();
  popup->addItem("Rename");
  // Wt::WPushButton *button = new Wt::WPushButton(selectionBoxContainer);
  // button->setMenu(popup);
  selectionBoxContainer->addWidget(new WBreak());


  cb2 = new Wt::WCheckBox("Map 2",selectionBoxContainer);
  // Wt::WPushButton *button1 = new Wt::WPushButton(selectionBoxContainer);
  // button1->setMenu(popup);
  selectionBoxContainer->addWidget(new WBreak());


  cb = new Wt::WCheckBox("Map 3",selectionBoxContainer);
  // Wt::WPushButton *button2 = new Wt::WPushButton(selectionBoxContainer);
  // button2->setMenu(popup);
  selectionBoxContainer->addWidget(new WBreak());




  WtSelectionBoxMap = new Wt::WSelectionBox();
  WtSelectionBoxMap->setStyleClass("layertree");
  WtSelectionBoxMap->resize(200,3000);
  // WtSelectionBoxMap->addItem(cb1);
  // WtSelectionBoxMap->addItem(cb2);
  // WtSelectionBoxMap->addItem(cb);
  selectionBoxContainer->addWidget(WtSelectionBoxMap);
  addWidget(selectionBoxContainer);


  

}

