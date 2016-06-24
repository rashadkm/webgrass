#include <pugixml.hpp>
#include <boost/algorithm/string.hpp>
#include "Module.h"

Module::Module(std::string moduleName, WContainerWidget *parent)
  :WContainerWidget(parent) {

    pugi::xml_document doc;

  /* input file of menudata*/
  const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/xml/v.buffer.xml";
  pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

  //  std::cout << "Load result: " << tos.description() << std::endl;

  pugi::xml_node task_node = doc.child("task");
  pugi::xml_node taskdescription_node = task_node.child("description");
  pugi::xml_node para_node = task_node.child("parameter");
  std::vector<std::string> name;
  std::vector<std::string> str1;
  int i=0;
  while(para_node){
                      //  cout<<para_node.child_value("label")<<endl;
                      //  cout<<para_node.attribute("required").value()<<endl;
                       std::string jj = para_node.attribute("required").value();
                        
                        if(jj=="yes")
                        { 
                          pugi::xml_node require_node = para_node.child("label");
                          //std::cout<<"ff0"<<require_node.child_value()<<"fvfv";
                          std::string nu=require_node.child_value();

                                    if(nu.empty())
                                       { pugi::xml_node require_node = para_node.child("description");
                                          str1.push_back(require_node.child_value());
                                          std::cout<<require_node.child_value()<<std::endl;
                                          std::cout<<str1[i]<<std::endl;
                                          i++;
                                      }
                                      else{
                                           str1.push_back(require_node.child_value());
                                          std::cout<<require_node.child_value()<<std::endl;
                                          std::cout<<str1[i]<<std::endl;
                                          i++;
                                      }
                        }
                        else{
                            std::cout<<para_node.child_value("guisection")<<std::endl;
                            pugi::xml_node guisection_node = para_node.child("guisection");
                            std::string someName=guisection_node.child_value();
                            boost::algorithm::trim_right(someName);
                            boost::algorithm::trim_left(someName);
                            std::cout<<"ss"<<someName<<"dd";
                            if (std::find(name.begin(), name.end(), someName) == name.end()) {
                              // someName not in name, add it
                              name.push_back(someName);
                            }
                        }

                        para_node = para_node.next_sibling("parameter");
                }

  pugi::xml_node flag_node = task_node.child("flag");
  while(flag_node){

                    pugi::xml_node flagguisection_node = flag_node.child("guisection");
                    std::string nu=flagguisection_node.child_value();
                    if(!nu.empty())
                    {
                        std::string someName=flagguisection_node.child_value();
                        boost::algorithm::trim_right(someName);
                        boost::algorithm::trim_left(someName);
                        std::cout<<"ss"<<someName<<"dd";
                        if (std::find(name.begin(), name.end(), someName) == name.end()) {
                          // someName not in name, add it
                          name.push_back(someName);
                        }
                    }
                   
                    flag_node = flag_node.next_sibling("flag");
  }
  
//   for (std::vector<std::string>::const_iterator i = name.begin(); i != name.end(); ++i)
//     { std::cout<<"hoo";
//       std::cout<<"hpp";

//       std::cout << *i ;
//       std::cout<<"hihi";
// }
  // std::string k = "nono";
  //  cout<<taskdescription_node.child_value()<<endl;
  // std::cout<<name<<std::endl;


Wt::WContainerWidget *container = new Wt::WContainerWidget();

Wt::WText *text1 = new Wt::WText(taskdescription_node.child_value(), container);


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

// container1->setId("kmk");
// std::cout<<container1<<"kmkmk";

// Wt::WString cell = Wt::WString("Item ({1}, {2})").arg("row").arg("column");
// Wt::WText *clcl = new Wt::WText("Item 1");

Wt::WTabWidget *tabW = new Wt::WTabWidget(container);

// tabW->addTab(cb,
//        k, Wt::WTabWidget::PreLoading);
tabW->addTab(container1,
       "Required", Wt::WTabWidget::PreLoading);
//tabW->addTab(new Wt::WTextArea(str1[0]),k, Wt::WTabWidget::PreLoading);

for (std::vector<std::string>::const_iterator h = name.begin(); h != name.end(); ++h)
{
  
tabW->addTab(new Wt::WTextArea("The contents of the tabs are pre-loaded in"
             " the browser to ensure swift switching."),
       *h, Wt::WTabWidget::PreLoading);
}


// tabW->addTab(new Wt::WTextArea("The contents of the tabs are pre-loaded in"
//              " the browser to ensure swift switching."),
//        "Test", Wt::WTabWidget::PreLoading);
// tabW->addTab(new Wt::WTextArea("You could change any other style attribute of the"
//              " tab widget by modifying the style class."
//              " The style class 'trhead' is applied to this tab."),
//        "Distance", Wt::WTabWidget::PreLoading)->setStyleClass("trhead");



Wt::WMenuItem *tab 
    = tabW->addTab(new Wt::WTextArea("You can close this tab"
             " by clicking on the close icon."),
       "Attribute");
tab->setCloseable(true);

tabW->setStyleClass("tabwidget");
addWidget(container);
// std::cout<<container->findById("kmk");

}

