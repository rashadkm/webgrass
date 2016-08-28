#ifndef MODULE_H_DEFINED
#define MODULE_H_DEFINED
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <pugixml.hpp>
#include <boost/algorithm/string.hpp>
#include <map>
#include <boost/lexical_cast.hpp>
#include <string>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WToolBar>
#include <Wt/WTabWidget>
#include <Wt/WTextArea>
#include <Wt/WMenuItem>
#include <Wt/WComboBox>
#include <Wt/WText>
#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WString>
#include <Wt/WDialog>

#include "Parameter.h"

#include "Utils.h"

#include "wgrassconfig.h"

class Module : public Wt::WDialog {

public:
  Module( std::string mod);

  bool createUI();

  typedef Utils::XmlNodeType XmlNodeType;
  
  std::map<std::string,std::vector<Parameter *> > map;
  std::vector<std::string>container_IDs;
  std::vector<std::string>flag_IDs;
  void updateOutput(std::string gg);
  std::string out;
  //  Wt::WContainerWidget *container;
  Wt::WTabWidget *tabW;
  // Wt::WMenuItem *tab;
  Wt::WTextArea *ta;

    typedef struct ParameterStruct {
      std::string tab, label, name, type;
      int tabindex;
      
     
      
  }ParameterType;

    void execute();
    //    const int getMinimumRequiredWidth() { return minimumRequiredWidth; }
    
 private:

    int minimumRequiredWidth;
    
  std::string theName;
  typedef std::vector<std::string> StringList;
  typedef StringList::iterator StringListIterator;  
  StringList theListOfTabNames;

  typedef std::pair<std::string, int>PairType;
  typedef std::map<std::string, int> TabIndexMap;
  typedef TabIndexMap::iterator TabIndexMapIterator;  
  TabIndexMap theTabIndexNameMap;

  typedef std::vector<ParameterType> ParameterList;
  typedef ParameterList::iterator ParameterListIterator;  
  ParameterList theParameterList;

  Wt::WTextArea *theOutputTab;
  int theOutputTabIndex;
  
  int estimatedHeight;
  int estimatedWidth;

  bool parseParameterNode(const XmlNodeType& node, bool isFlag);

  bool createAllTabs(const std::string& s);

  int createContainerWidgetForTab(const std::string& tname);

  void  addTabForOutput( );

  const std::string getIdForParameterWidget(const std::string t, const std::string n)
  {
    #ifdef DEBUG_TRACE
    std::cerr << "getIdForParameterWidget(t, n) = "
	      << this->id() +  "_" + this->getMangledName() +  "_" + mangleString(t, ' ') +  "_" + n
	      << std::endl;
    #endif
    
    return (this->id() +  "_" + this->getMangledName() +  "_" + mangleString(t, ' ') +  "_" + n ) ;
  }

  void updateMinimumRequiredWidth(const size_t label_size)
  {
    estimatedWidth = label_size > estimatedWidth ? label_size : estimatedWidth;
  }

  
  const std::string getMangledName()
  {
    return mangleString(theName, '.');
  }
  
  const std::string mangleString(const std::string str, char c)
  {
    std::string s = str;
    std::replace( s.begin(), s.end(), c, '_'); 
    return  s;
  }

  bool is_special_flag(std::string flag_name)
  {
    if( flag_name == "verbose" || flag_name == "quiet" || flag_name == "overwrite" )
      return true;
    
    return false;
  }
  
 
};


#endif
