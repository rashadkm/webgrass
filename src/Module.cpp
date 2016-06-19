#include <pugixml.hpp>
#include "Module.h"

Module::Module(WContainerWidget *parent=0,std::string mod=0)
  :WContainerWidget(parent) {

    pugi::xml_document doc;

  /* input file of menudata*/
  const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/xml/v.buffer.xml";
  pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

  std::cout << "Load result: " << tos.description() << std::endl;

  pugi::xml_node task_node = doc.child("task");
  pugi::xml_node ff_node = task_node.child("description");
  pugi::xml_node para_node = task_node.child("parameter");
  std::vector<std::string> str1;
  int i=0;
  while(para_node){
  cout<<para_node.child_value("label")<<endl;
  cout<<para_node.attribute("required").value()<<endl;
  string jj = para_node.attribute("required").value();
  
  if(jj=="yes")
  { cout<<"i am here"<<endl;
    pugi::xml_node require_node = para_node.child("description");
    str1.push_back(require_node.child_value());
    cout<<require_node.child_value()<<endl;
    cout<<str1[i]<<endl;
    i++;
  }
  para_node = para_node.next_sibling("parameter");
}
  
  string k = "nono";
  cout<<ff_node.child_value()<<endl;
  cout<<mod<<endl;


WApplication::instance()->useStyleSheet("style.css");
Wt::WContainerWidget *container = new Wt::WContainerWidget();

Wt::WText *text1 = new Wt::WText(ff_node.child_value(), container);


Wt::WContainerWidget *container1 = new Wt::WContainerWidget();

Wt::WText *text2 =
    new Wt::WText(str1[0], container1);
Wt::WComboBox *cb = new Wt::WComboBox(container1);
cb->addItem("Map1");
cb->addItem("Map2");
cb->addItem("Map3");

container1->addWidget(new WBreak());
Wt::WText *text3 =
    new Wt::WText(str1[1], container1);
Wt::WComboBox *cb1 = new Wt::WComboBox(container1);
cb1->addItem("Output1");
cb1->addItem("Output2");
cb1->addItem("Output3");



Wt::WTabWidget *tabW = new Wt::WTabWidget(container);

// tabW->addTab(cb,
//        k, Wt::WTabWidget::PreLoading);
tabW->addTab(container1,
       "Required", Wt::WTabWidget::PreLoading);
//tabW->addTab(new Wt::WTextArea(str1[0]),k, Wt::WTabWidget::PreLoading);
tabW->addTab(new Wt::WTextArea("The contents of the tabs are pre-loaded in"
             " the browser to ensure swift switching."),
       "Selection", Wt::WTabWidget::PreLoading);
tabW->addTab(new Wt::WTextArea("You could change any other style attribute of the"
             " tab widget by modifying the style class."
             " The style class 'trhead' is applied to this tab."),
       "Distance", Wt::WTabWidget::PreLoading)->setStyleClass("trhead");

Wt::WMenuItem *tab 
    = tabW->addTab(new Wt::WTextArea("You can close this tab"
             " by clicking on the close icon."),
       "Attribute");
tab->setCloseable(true);

tabW->setStyleClass("tabwidget");
addWidget(container);

}

