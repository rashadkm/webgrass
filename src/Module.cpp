#include <pugixml.hpp>
#include <boost/algorithm/string.hpp>
#include <map>
#include "Module.h"

Module::Module(std::string moduleName, WContainerWidget *parent)
  :WContainerWidget(parent) {

  pugi::xml_document doc;
 
  const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/xml/"+ moduleName +".xml";
  pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

  std::cout << "Load result: " << tos.description() << std::endl;
  std::string check= tos.description();
  if(check=="File was not found")
   {
      Wt::WContainerWidget *error = new Wt::WContainerWidget();
      Wt::WText *text1 = new Wt::WText("File was not found", error);
      addWidget(error);
   }
  else{
      pugi::xml_node task_node = doc.child("task");
      pugi::xml_node taskdescription_node = task_node.child("description");
      pugi::xml_node para_node = task_node.child("parameter");
      std::vector<std::string> req_string;
      std::map<std::string,std::vector<std::string> > map;
      std::map<std::string,std::vector<std::string> >::iterator iterate;
      int i=0;
      while(para_node){
          /*first iterating over the required box*/
          std::string flag_required = para_node.attribute("required").value();               
          if(flag_required=="yes")
            { 
              pugi::xml_node require_node = para_node.child("label"); /*if label is available*/                                                 
              std::string nu=require_node.child_value();

              if(nu.empty())
                { pugi::xml_node require_node = para_node.child("description"); /*else description*/
                  req_string.push_back(require_node.child_value());
                  i++;
                }
              else{
                req_string.push_back(require_node.child_value());
                i++;
              }
            }
          else
          {
              pugi::xml_node guisection_node = para_node.child("guisection"); /*iteration over the guisection*/
              std::string someName=guisection_node.child_value();
              if(someName.empty())
              {
                someName = "Optionals";
              }
              boost::algorithm::trim_right(someName);
              boost::algorithm::trim_left(someName);
                                    
              iterate = map.find(someName);
               if (iterate != map.end())
                { pugi::xml_node para_label_node = para_node.child("label");
                  std::string Name=para_label_node.child_value();
                  if(Name.empty())
                  {
                    pugi::xml_node para_label_node = para_node.child("description");
                      Name=para_label_node.child_value();
                   
                  }
                  
                 
                  boost::algorithm::trim_right(Name);
                  boost::algorithm::trim_left(Name);
            
                  
                  iterate->second.push_back(Name);
                }
              else
                {
                  std::vector<std::string> s;
                  pugi::xml_node para_label_node = para_node.child("label");
                    std::string Name=para_label_node.child_value();
                   
                    if(Name.empty())
                    { 
                      pugi::xml_node para_label_node = para_node.child("description");
                        Name=para_label_node.child_value();
                       
                      }
                    boost::algorithm::trim_right(Name);
                    boost::algorithm::trim_left(Name);
                    s.push_back(Name);
                  map[someName]=s;
                }
          }


          para_node = para_node.next_sibling("parameter");
      }

      pugi::xml_node flag_node = task_node.child("flag");

      std::vector<std::string> flag_list;
      while(flag_node){
                        pugi::xml_node option_node = flag_node.child("description");
                        std::string Name=option_node.child_value();
                        boost::algorithm::trim_right(Name);
                        boost::algorithm::trim_left(Name);
                        
                        flag_list.push_back(Name);
                                         
                        flag_node = flag_node.next_sibling("flag");
                      }
      

    // for (std::map<std::string,std::vector<std::string> >::iterator it=map.begin(); it != map.end(); ++it)
    //    {  
    //       std::cout << it->first <<  " => " ;
    //       for(int i=0; i < it->second.size(); i++)
    //       {
    //         puts(it->second[i].c_str());
    //       }

    //    }


      Wt::WContainerWidget *container = new Wt::WContainerWidget();

      Wt::WText *text1 = new Wt::WText(taskdescription_node.child_value(), container);

      std::vector<WContainerWidget *> Container_list;

      for (std::map<std::string,std::vector<std::string> >::iterator it=map.begin(); it != map.end(); ++it)
         {   
            Wt::WContainerWidget *container1 = new Wt::WContainerWidget();
            for(int i=0; i < it->second.size(); i++)
            { 
              Wt::WText *text2 = new Wt::WText(it->second[i], container1);
              Wt::WComboBox *cb = new Wt::WComboBox(container1);
              container1->addWidget(new WBreak());
            }
            container1->setId(it->first); /*for setting id*/
            Container_list.push_back(container1);
         }


      Wt::WContainerWidget *flag_widget = new Wt::WContainerWidget();

      for(std::vector<std::string>::const_iterator h = flag_list.begin(); h != flag_list.end(); ++h)
      {
         Wt::WCheckBox *flag = new Wt::WCheckBox(*h, flag_widget);
         flag->setInline(false); 
      }

      Wt::WContainerWidget *req_container = new Wt::WContainerWidget();
      if(!req_string.empty())
      {
          for(int i=0; i < req_string.size(); i++)
          {
             Wt::WText *text2 =new Wt::WText(req_string[i], req_container);
             Wt::WComboBox *cb = new Wt::WComboBox(req_container);
              req_container->addWidget(new WBreak());
          }

      }

      Wt::WTabWidget *tabW = new Wt::WTabWidget(container);

        // container1->setId("kmk"); /*for setting id*/


      if(!req_string.empty())
      {
      tabW->addTab(req_container,"Required", Wt::WTabWidget::PreLoading);
      }


      tabW->addTab(flag_widget,"Check Options", Wt::WTabWidget::PreLoading);


      for (std::vector<WContainerWidget *>::iterator it=Container_list.begin(); it != Container_list.end(); ++it)
      {
      tabW->addTab(*it,(*it)->id(), Wt::WTabWidget::PreLoading);
      }

      Wt::WMenuItem *tab 
        = tabW->addTab(new Wt::WTextArea("You can close this tab"
                 " by clicking on the close icon."),
           "Attribute");
      tab->setCloseable(true);

      tabW->setStyleClass("wgrass-module-tab");
      addWidget(container);
        // std::cout<<container->findById("kmk"); /*calling with id*/

    }
}

