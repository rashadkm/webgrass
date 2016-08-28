
#include <assert.h>

//#define DEBUG_TRACE 1
#include "Module.h"

#include <Wt/WCheckBox>
#include <Wt/WSuggestionPopup>

#include "../thirdparty/pstream/pstream.h"

int Module::createContainerWidgetForTab(const std::string& tname)
{
  int tindex = -1;
  StringListIterator it =  std::find( theListOfTabNames.begin(), theListOfTabNames.end(), tname );
  
  if ( it == theListOfTabNames.end() )
    {
      tindex = tabW->count();
      theListOfTabNames.push_back( tname );
      theTabIndexNameMap.insert ( std::pair<std::string,int>( tname, tindex ) );      
      Wt::WContainerWidget *newTab = new Wt::WContainerWidget( this->contents() );      

      //      updateMinimumRequiredWidth( tname.size() );
      estimatedWidth = estimatedWidth + (tname.size() * 10 ) + 20;
      //      std::cerr << "tname=" << tname << "; tname.size()=" << tname.size() << "; tname.size()*2=" << tname.size() * 2 <<  "; estimatedWidth=" << estimatedWidth << std::endl;

      Wt::WVBoxLayout *layout = new Wt::WVBoxLayout();
      tabW->addTab( newTab, tname, Wt::WTabWidget::PreLoading );
      newTab->setLayout( layout );
    }
  else
    {
      TabIndexMapIterator mapIt = theTabIndexNameMap.find( tname );
      tindex = mapIt->second;
    }

  assert( tindex != -1 );
  
  return tindex;
}

bool Module::parseParameterNode(const Module::XmlNodeType& node, bool isFlag)
{
  std::string parameter_tab, parameter_name, parameter_type;
  int parameter_tabindex = -1;

  std::string attr_value;
  Utils::getValueOfAttribute( node, "required", attr_value );
  if(attr_value == "yes")
    {
      parameter_tab = "Required";
    }
  else
    {
      std::string node_value;
      Utils::getValueOfChildNode( node, "guisection", node_value );
      if( !node_value.empty() )
	{
	  parameter_tab = node_value;
	}
      else
	{
	  parameter_tab =  "Optional";	
	}
    }
  
  parameter_tabindex = createContainerWidgetForTab( parameter_tab );
  
  std::string parameter_label;
  Utils::getValueOfChildNode( node, "label", parameter_label );
  
  if( parameter_label.empty() )
    {
      Utils::getValueOfChildNode( node, "description", parameter_label );
    }




  //      if( isFlag )	parameter.label = "flag_" + parameter.label;
      
  Utils::getValueOfAttribute( node, "name", parameter_name );

  if( isFlag )
    parameter_type = "flag"; //bool
  else
    Utils::getValueOfAttribute( node, "type", parameter_type );
  
  #ifdef DEBUG_TRACE
  std::cerr << "parameter with name '" << parameter_name
  	    << "' has tabindex '" << parameter_tabindex
  	    << "' and tabname '" << parameter_tab
  	    << "'" << std::endl;
  #endif



  Wt::WContainerWidget *tab = dynamic_cast<Wt::WContainerWidget*>( tabW->widget(parameter_tabindex) );

  Wt::WFormWidget *parameterWidget = NULL;
Wt::WSuggestionPopup::Options contactOptions;
contactOptions.highlightBeginTag = "<span class=\"highlight\">";
contactOptions.highlightEndTag = "</span>";
contactOptions.listSeparator = ',';
contactOptions.whitespace = " \\n";
contactOptions.wordSeparators = "-., \"@\\n;";
contactOptions.appendReplacedText = ",";

Wt::WSuggestionPopup *sp = new Wt::WSuggestionPopup(
	    Wt::WSuggestionPopup::generateMatcherJS(contactOptions),
	    Wt::WSuggestionPopup::generateReplacerJS(contactOptions),
	    tab);

  if ( parameter_type != "flag" )
    {
      Wt::WLabel *label = new Wt::WLabel( parameter_label + " [" + parameter_name + "]" , tab );
   parameterWidget = new Wt::WLineEdit( tab );
//parameterWidget->setEmptyText("....");

      label->setBuddy( parameterWidget );
      tab->layout()->addWidget( label );
    }
  else
    {
    parameterWidget = new Wt::WCheckBox( parameter_label, tab );			  
    }
  if( parameterWidget != NULL)
    {
      const std::string widgetId = getIdForParameterWidget( parameter_tab , parameter_name );
      parameterWidget->setId( widgetId );
      estimatedHeight += 10;
      tab->layout()->addWidget( parameterWidget );
    }




  XmlNodeType values_node = node.child("values");
  
  /*iteration over the values if present*/  
  if(values_node)
    {
      
      for( XmlNodeType value_node = values_node.child( "value" );
	   value_node != NULL;
	   value_node = value_node.next_sibling( "value" ) ) 
	{
	  
	  std::string name;
	  Utils::getValueOfChildNode( value_node, "name", name );
	  //Utils::getValueOfChildNode( value_node, "description", description );
	  assert( !name.empty() );

// Populate the underlying model with suggestions:
sp->addSuggestion(name);



	}
      sp->forEdit(parameterWidget);
    }



    ParameterType parameter;
    parameter.tab = parameter_tab;
parameter.name = parameter_name;
parameter.type = parameter_type;
parameter.label = parameter_label;
parameter.tabindex = parameter_tabindex;
theParameterList.push_back( parameter );



}

bool Module::createAllTabs(const std::string& xml_string)
{

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_string( xml_string.c_str() );
  
  if ( !result )
    {
      std::cout << "Error description: " << result.description() << "\n";
      return false;
    }
  
  XmlNodeType task_node = doc.child( "task" );
  XmlNodeType taskdescription_node = task_node.child( "description" );
  XmlNodeType para_node = task_node.child( "parameter" );

  //int parameterCount = 0;
  
  for( XmlNodeType parameter_node = task_node.child( "parameter" );
       parameter_node != NULL;
       parameter_node = parameter_node.next_sibling( "parameter" ) ) 
    {
      parseParameterNode( parameter_node, false );
      //      ++parameterCount;
    }
  
  for( XmlNodeType flag_node = task_node.child( "flag" );
       flag_node != NULL;
       flag_node = flag_node.next_sibling( "flag" ) ) 
    {
      parseParameterNode( flag_node, true );

    }  

  addTabForOutput( );
  
  //  if (parameterCount < 1 ) return false;

  int H = estimatedHeight < 420 ? 420 : estimatedHeight;
  int W = estimatedWidth; // + 100 < 400 ? 400 : estimatedWidth + 100;
  //  std::cerr << "      W=" << W << std::endl;
    //8 - 50
  this->resize( W  , H );

  
  return true;
}

void Module::addTabForOutput( )
{
  Wt::WContainerWidget *tab = new Wt::WContainerWidget( this->contents() );
  Wt::WVBoxLayout *layout = new Wt::WVBoxLayout( tab );
  
  theOutputTab = new Wt::WTextArea("...");
  layout->addWidget( theOutputTab );
  
  tabW->addTab( tab, "Command Output", Wt::WTabWidget::PreLoading );
  
  theOutputTabIndex = tabW->count() - 1;

  assert( theOutputTabIndex != -1 );
}

bool Module::createUI()
{
  assert( !theName.empty() );

  std::string xmlstring = Utils::checkFileExists( Utils::moduleDocRoot() + theName + ".xml" );
  
  if ( xmlstring.empty() )
    {
      WApplication::instance()->doJavaScript( "alert('Module not implemented')" );
      return false;
    }

  #ifdef DEBUG_TRACE
  std::cerr << xmlstring << std::endl;
  #endif
  
  tabW = new Wt::WTabWidget( this->contents() );
  tabW->setId( this->id() +  "_" + this->getMangledName() );
  
  if( createAllTabs(xmlstring) )
    {
    return true;
    }
  
  return false;
}

Module::Module(std::string name)
  : theName(name)
  , minimumRequiredWidth(1)
  , theOutputTabIndex(-1)
  , estimatedHeight(0)
  , estimatedWidth(200)
{
#if 1

 this->setModal(false);

  Wt::WPushButton *buttonRun = new Wt::WPushButton("Run", this->footer());
  buttonRun->setDefault(true);
  
  //    if (wApp->environment().ajax())       ok->disable();
  
  Wt::WPushButton *buttonClose = new Wt::WPushButton("Close", this->footer());
  this->rejectWhenEscapePressed();
  /*
   * Reject the dialog when close is clicked
   */
  buttonClose->clicked().connect(this, &Wt::WDialog::reject);
  buttonRun->clicked().connect(this, &Module::execute);
  
  
  /*
   * Accept the dialog
   */
  // ok->clicked().connect(std::bind([=] () {
  // 	if (edit->validate())
  // 	    dialog->accept();
  // }));
  

    /*
     * Process the dialog result.
     */
    // dialog->finished().connect(std::bind([=] () {
    // 	if (dialog->result() == Wt::WDialog::Accepted)
    // 	    out->setText("New location: " + edit->text());
    // 	else
    // 	    out->setText("No location selected.");

    // 	delete dialog;
    // }));
#else  
  pugi::xml_document doc;
 
  // const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/xml/"+ moduleName +".xml";
  pugi::xml_parse_result tos = doc.load(moduleName);

  std::cout << "Load result: " << tos.description() << std::endl;

  {
      pugi::xml_node task_node = doc.child("task");
      pugi::xml_node taskdescription_node = task_node.child("description");
      pugi::xml_node para_node = task_node.child("parameter");

      std::vector<std::vector<std::string> > flags_l;  /*flags will be stored here*/
      std::map<std::string,std::vector<Parameter *> >::iterator iterate; /*tab name and elements under it*/
      // std::cout<<"check 2"<<std::endl;
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

          // std::cout<<"check 3"<<std::endl;
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
        
              // std::cout<<"check 4"<<std::endl;
              Parameter *parameter = new Parameter();
              (parameter->Name_op)->setText(Name);
              std::string attribute_name = para_node.attribute("name").value();
              (parameter->Name_op)->setName(attribute_name);
              std::string attribute_type = para_node.attribute("type").value();
              (parameter->Name_op)->setType(attribute_type);
              (parameter->Name_op)->setTabname(someName);
              // std::cout<<"check 5"<<std::endl;
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
               // std::string flot = boost::lexical_cast<std::string>(i); /*setId only takes string*/
                parameter->Name_op->setFlag_no(i);
                parameter->Name_op->isFlag("flag"); /*if flag is present*/
                i++;
               }
         
              iterate->second.push_back(parameter); /*tab name as first and elements in second of the map*/
            }
          else
            {
              std::vector<Parameter *> s;
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

                // std::cout<<"check 6"<<std::endl;
                Parameter *parameter = new Parameter();
                // std::cout<<"check 61"<<std::endl;
                (parameter->Name_op)->setText(Name);
                // std::cout<<"check 62"<<std::endl;
                std::string attribute_name = para_node.attribute("name").value();
                (parameter->Name_op)->setName(attribute_name);
                // std::cout<<"check 63"<<std::endl;
                std::string attribute_type = para_node.attribute("type").value();
                (parameter->Name_op)->setType(attribute_type);
                parameter->Name_op->setTabname(someName);
                // std::cout<<"check 7"<<std::endl;
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
               // std::string flot = boost::lexical_cast<std::string>(i);
                parameter->Name_op->setFlag_no(i);
                parameter->Name_op->isFlag("flag");
                i++;
               }

               // std::cout<<"check 8"<<std::endl;
                s.push_back(parameter);
              map[someName]=s;
            }
          
          para_node = para_node.next_sibling("parameter");
      }

      pugi::xml_node flag_node = task_node.child("flag");

      std::vector<Wt::WText *> flag_list;  /*flag list without any heading*/
      while(flag_node){
                        pugi::xml_node option_node = flag_node.child("description");
                        std::string Name=option_node.child_value();
                        boost::algorithm::trim_right(Name);
                        boost::algorithm::trim_left(Name);
                        Wt::WText *check_box = new Wt::WText(Name);
                        std::string check_id = flag_node.attribute("name").value();
                        check_box->setId(check_id);
                        flag_list.push_back(check_box);
                                         
                        flag_node = flag_node.next_sibling("flag");
                      }
      


      container = new Wt::WContainerWidget();                
      container->setId("Main");
      container->setObjectName("yes");

      Wt::WText *text1 = new Wt::WText(taskdescription_node.child_value(), container);

      std::vector<WContainerWidget *> Container_list;

      for (std::map<std::string,std::vector<Parameter *> >::iterator it=map.begin(); it != map.end(); ++it) /*creation of widgets*/
         {   


            Wt::WContainerWidget *container1 = new Wt::WContainerWidget();
            for(int i=0; i < it->second.size(); i++)
            { 
              Wt::WText *text1 = new Wt::WText(((it->second[i])->Name_op)->Text());
              container1->addWidget(text1);
              Wt::WLineEdit *cb = new Wt::WLineEdit(container1);
              std::string con_ID = ((it->second[i])->Name_op)->Name();
              cb->setId(con_ID);
              // std::cout<<"bibibi"<<cb<<std::endl;
              container_IDs.push_back(con_ID);
              (it->second[i])->container_op=cb;
              container1->addWidget(new WBreak());
              std::string stre = ((it->second[i])->Name_op)->Flag();

              if(stre=="flag")         /*if flag is present then creation of checkboxes*/
              {
                int num = ((it->second[i])->Name_op)->Flag_no();
                // int num = boost::lexical_cast<int>(f);
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

      for(std::vector<Wt::WText *>::iterator h = flag_list.begin(); h != flag_list.end(); ++h)
      {
         Wt::WCheckBox *flag = new Wt::WCheckBox((*h)->text(), flag_widget);
         flag->setInline(false); 
         flag->setId((*h)->id());
         flag_IDs.push_back((*h)->id());
      }


      // Wt::WTabWidget *tabW = new Wt::WTabWidget(container);
      tabW = new Wt::WTabWidget(container);
      // container->addWidget(tabW);
        // container1->setId("kmk"); /*for setting id*/

      
      for (std::vector<WContainerWidget *>::iterator it=Container_list.begin(); it != Container_list.end(); ++it)
      {
      tabW->addTab(*it,(*it)->id(), Wt::WTabWidget::PreLoading);

      }
      // tabW->setCurrentIndex(3);
      ta = new Wt::WTextArea();
      ta->resize(450,230);
      tabW->addTab(flag_widget,"Check Options", Wt::WTabWidget::PreLoading);
      std::string output = out;
      Wt::WMenuItem *tab = tabW->addTab(ta,"Output", Wt::WTabWidget::PreLoading);
      // tab->setCloseable(true);

      tabW->setStyleClass("wgrass-module-tab");
      addWidget(container);


    }
#endif
}
void Module::execute( )
{
  std::stringstream command_sstream;

  command_sstream << "GISRC=/tmp/grassrc ";
  command_sstream << theName << " ";

  /* Walk through list of ParameterStruct */
  for (ParameterListIterator it = theParameterList.begin(); it != theParameterList.end(); ++it) 
    {   
      const std::string pname = (*it).name;
      const std::string ptab = (*it).tab;
      const std::string ptype = (*it).type;



      const std::string idToFind = getIdForParameterWidget(ptab, pname);

      if( ptype == "flag")
	{
	  Wt::WCheckBox *check = dynamic_cast<Wt::WCheckBox *>(  tabW->findById( idToFind )  );
	  
	  assert( check!=NULL );
	  
	  if ( check!= NULL && check->isChecked() )
	    {
	      //check for special flags
	      if( is_special_flag(pname) )
		command_sstream <<  "-";
	     
		
	      command_sstream <<  "-" << pname << " ";
	    }
	}
      else
	{
	  //std::cerr << idToFind << std::endl;
	  Wt::WLineEdit *edit = dynamic_cast<Wt::WLineEdit *>(  tabW->findById( idToFind )  );
	  
	  assert( edit!=NULL );
	  
	  if (edit!= NULL  )
	    {
	      const std::string   pvalue = edit->text().narrow();

	      if( !pvalue.empty()  )
		command_sstream <<  pname << "=" << pvalue << " ";
	    }
	}

    }

#if defined(DEBUG_TRACE)
  Utils::alert( command_sstream.str() );
#endif

      assert( theOutputTabIndex != -1 );
      this->tabW->setCurrentIndex( theOutputTabIndex );

  std::stringstream output_sstream;
  
  redi::pstream gcommand_pstream(command_sstream.str(), redi::pstreams::pstdout|redi::pstreams::pstderr);

#if 0  
  char buf[1024];
  std::streamsize n;
  bool finished = false;
  while (!finished)
    {
      while ((n = gcommand_pstream.err().readsome(buf, sizeof(buf))) > 0)
	{
	  output_sstream.write(buf, n);
	  theOutputTab->setText( output_sstream.str() );
	}
      
      if (gcommand_pstream.eof())
	{
	  finished = true;
	  gcommand_pstream.clear();
	}
    }
   
#else
 
  std::string buf;
  while ( getline( gcommand_pstream.out(), buf ) )
    output_sstream << buf << std::endl;
  
  gcommand_pstream.clear( );

  //  output_sstream << command_sstream.str()    << std::endl << std::endl
    
  while ( getline( gcommand_pstream.err(), buf ) )
    output_sstream << buf << std::endl;
  
  gcommand_pstream.clear();
  
  theOutputTab->setText( output_sstream.str() );
#endif  

  
  
	
}

void Module::updateOutput(std::string gg ) {
    // tabW->removeTab(tab);
    out=out+gg;
    //    std::cout<<"terminal"<<gg<<std::endl;
    ta->setText(out);
    // Wt::WMenuItem *tab = tabW->addTab(new Wt::WTextArea(out),"Output");
}
