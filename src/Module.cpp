
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

      WApplication::instance()->doJavaScript("alert('Module not implemented')");
      // Wt::WContainerWidget *error = new Wt::WContainerWidget();
      // Wt::WText *text1 = new Wt::WText("File was not found", error);
      // addWidget(error);
   }
  else{
      pugi::xml_node task_node = doc.child("task");
      pugi::xml_node taskdescription_node = task_node.child("description");
      pugi::xml_node para_node = task_node.child("parameter");
      // std::map<std::string,std::vector<Text_Gui *> > map;
      // std::vector<Wt::WText *> Text;
      std::cout<<"check 1"<<std::endl;
      std::vector<std::vector<std::string> > flags_l;  /*flags will be stored here*/
      std::map<std::string,std::vector<Overall *> >::iterator iterate; /*tab name and elements under it*/
      std::cout<<"check 2"<<std::endl;
      int i=0;
      int j=0;
      while(para_node){
          /*first iterating over the required box*/
          std::string someName;
          std::string flag_required = para_node.attribute("required").value();  

          /*setting the name of the tab*/             
          if(flag_required=="yes")
            { 
              someName= "Required";
            }
          else
          {
              pugi::xml_node guisection_node = para_node.child("guisection"); /*iteration over the guisection*/
              someName=guisection_node.child_value();
              if(someName.empty())
              {
                someName = "Optionals";
              }
              boost::algorithm::trim_right(someName);
              boost::algorithm::trim_left(someName);
          }

          std::cout<<"check 3"<<std::endl;
          pugi::xml_node values_node = para_node.child("values"); /*iteration over the values if present*/
          iterate = map.find(someName);   /*if tab with the name is already present*/
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
        
              std::cout<<"check 4"<<std::endl;
              Overall *Over = new Overall();
              Over->Name_op->setText(Name);
              std::string attribute_name = para_node.attribute("name").value();
              Over->Name_op->setName(attribute_name);
              std::string attribute_type = para_node.attribute("type").value();
              Over->Name_op->setType(attribute_type);
              std::cout<<"check 5"<<std::endl;
               if(values_node)
               {
                pugi::xml_node value_node = values_node.child("value");
                std::vector<std::string> flags;
                while(value_node){
                     pugi::xml_node name_node = value_node.child("name");
                 std::string v=name_node.child_value();
                 // std::cout<<v<<std::endl;
                 flags.push_back(v);  /*storing values flags in vector*/
                 value_node = value_node.next_sibling("value");
               }
               flags_l.push_back(flags);
               std::string flot = boost::lexical_cast<std::string>(i); /*setId only takes string*/
                Over->Name_op->setId(flot);
                Over->Name_op->setObjectName("flag"); /*if flag is present*/
                i++;
               }
         
              iterate->second.push_back(Over); /*tab name as first and elements in second of the map*/
            }
          else
            {
              std::vector<Overall *> s;
              pugi::xml_node para_label_node = para_node.child("label");
                std::string Name=para_label_node.child_value();
               
                if(Name.empty())
                { 
                  pugi::xml_node para_label_node = para_node.child("description");
                    Name=para_label_node.child_value();
                   
                  }
                boost::algorithm::trim_right(Name);
                boost::algorithm::trim_left(Name);

                pugi::xml_node values_node = para_node.child("values");

                std::cout<<"check 6"<<std::endl;
                Overall *Over = new Overall();
                std::cout<<"check 61"<<std::endl;
                (Over->Name_op)->setText(Name);
                std::cout<<"check 62"<<std::endl;
                std::string attribute_name = para_node.attribute("name").value();
                (Over->Name_op)->setName(attribute_name);
                std::cout<<"check 63"<<std::endl;
                std::string attribute_type = para_node.attribute("type").value();
                (Over->Name_op)->setType(attribute_type);
                std::cout<<"check 7"<<std::endl;
                if(values_node)
               {
                pugi::xml_node value_node = values_node.child("value");
                std::vector<std::string> flags;
                while(value_node){
                     pugi::xml_node name_node = value_node.child("name");
                 std::string v=name_node.child_value();
                 // std::cout<<v<<std::endl;
                 flags.push_back(v);
                 value_node = value_node.next_sibling("value");
               }
               flags_l.push_back(flags);
               std::string flot = boost::lexical_cast<std::string>(i);
                Over->Name_op->setId(flot);
                Over->Name_op->setObjectName("flag");
                i++;
               }

               std::cout<<"check 8"<<std::endl;
                s.push_back(Over);
              map[someName]=s;
            }
          
          para_node = para_node.next_sibling("parameter");
      }

      pugi::xml_node flag_node = task_node.child("flag");

      std::vector<std::string> flag_list;  /*flag list without any heading*/
      while(flag_node){
                        pugi::xml_node option_node = flag_node.child("description");
                        std::string Name=option_node.child_value();
                        boost::algorithm::trim_right(Name);
                        boost::algorithm::trim_left(Name);
                        
                        flag_list.push_back(Name);
                                         
                        flag_node = flag_node.next_sibling("flag");
                      }
      


      // std::string str;
      // while (in >> str) {
      //     std::cout << str << std::endl;
      // }

      Wt::WContainerWidget *container = new Wt::WContainerWidget();
      container->setId("Main");
      container->setObjectName("yes");

      Wt::WText *text1 = new Wt::WText(taskdescription_node.child_value(), container);

      std::vector<WContainerWidget *> Container_list;

      for (std::map<std::string,std::vector<Overall *> >::iterator it=map.begin(); it != map.end(); ++it) /*creation of widgets*/
         {   
            Wt::WContainerWidget *container1 = new Wt::WContainerWidget();
            for(int i=0; i < it->second.size(); i++)
            { 
              container1->addWidget((it->second[i])->Name_op);
              Wt::WLineEdit *cb = new Wt::WLineEdit(container1);
              (it->second[i])->container_op=cb;
              container1->addWidget(new WBreak());
              std::string stre = ((it->second[i])->Name_op)->objectName();
              std::cout<<((it->second[i])->Name_op)->Name()<<std::endl;
              std::cout<<((it->second[i])->Name_op)->Type()<<std::endl;
              if(stre=="flag")         /*if flag is present then creation of checkboxes*/
              {
                std::string f = ((it->second[i])->Name_op)->id();
                int num = boost::lexical_cast<int>(f);
                // std::cout<<num<<std::endl;
                std::vector<std::string> flag_iterat = flags_l[num];
                for (std::vector<std::string>::iterator i = flag_iterat.begin(); i != flag_iterat.end(); ++i)
                  {
                    // std::cout << *i << ' ';
                    Wt::WCheckBox *flag = new Wt::WCheckBox(*i, container1);
                    flag->setInline(true); 

                  }
              }             
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


      Wt::WTabWidget *tabW = new Wt::WTabWidget(container);

        // container1->setId("kmk"); /*for setting id*/

      int t;
      for (std::vector<WContainerWidget *>::iterator it=Container_list.begin(); it != Container_list.end(); ++it)
      {
      tabW->addTab(*it,(*it)->id(), Wt::WTabWidget::PreLoading);
              // std::string j = (*it)->id();
              // std::cout<<j<<std::endl;
              // if(j=="Selection")
              // {
              //   t = indexOf(*it);
              //   std::cout<<t<<"okok"<<std::endl;
              // }
      }
      // tabW->setCurrentIndex(3);

      tabW->addTab(flag_widget,"Check Options", Wt::WTabWidget::PreLoading);

      Wt::WMenuItem *tab 
        = tabW->addTab(new Wt::WTextArea("You can close this tab"
                 " by clicking on the close icon."),
           "Attribute");
      tab->setCloseable(true);

      tabW->setStyleClass("wgrass-module-tab");
      addWidget(container);
        // std::cout<<container->findById("kmk"); /*calling with id*/

      // redi::ipstream proc("grass70 $HOME/grassdata/newLocation/PERMANENT", redi::pstreams::pstdout | redi::pstreams::pstdin );
      // // redi::ipstream in("ls");
      // std::string line;
      // std::cout.flush();
      // while (std::getline(proc.out(), line)){
      //   std::cout << "stdout: " << line << '\n';
    // }

    }
}

