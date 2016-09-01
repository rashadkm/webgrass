#include <fstream>

#include "Utils.h"
#include <boost/algorithm/string.hpp>

#include <Wt/WEnvironment>

namespace Utils {

  const std::string moduleDocRoot()
  {
    return Wt::WApplication::instance()->docRoot() + "/xml/";
  }

  const std::string checkFileExists(const std::string& fname)
    {
      std::ifstream stream(fname);     
      return std::string(std::istreambuf_iterator<char>(stream), {});
    }

  void getValueOfAttribute(const XmlNodeType &node, const char* attr, std::string& value)
  {
  if( node != NULL && node.attribute(attr) != NULL )
      value = node.attribute(attr).value();
    else
      {
	//TODO: use logger
#if defined(DEBUG_TRACE)
	std::cerr << "node != NULL && node.attribute('" << attr <<"') != NULL false" << std::endl;
#endif	
      }
    return;    
  }

  void getValueOfAttribute(const XmlNodeType &node, const std::string attr, std::string& value)
  {
    getValueOfAttribute( node, attr.c_str(), value );
    return;
  
  }

  void getValueOfChildNode(const XmlNodeType &node, const char* child, std::string& value)
    
  {
    if( node != NULL && node.child(child) != NULL )
      {
	value = node.child(child).child_value();
	boost::algorithm::trim(value);
	//	boost::algorithm::trim_right(value);
	//	boost::algorithm::trim_left(value);
      }
    else
      {
	//TODO: use logger
#if defined(DEBUG_TRACE)	
	std::cerr << "node != NULL && node.child('" << child <<"') != NULL false" << std::endl;
#endif	
      }
    return;
  }
    
  void getValueOfChildNode(const XmlNodeType &node, const std::string child, std::string& value)
  {
    getValueOfChildNode( node, child.c_str(), value );
    return;
  }

  void alert(const std::string msg)
  {
    Wt::WApplication::instance()->doJavaScript( "alert('" + msg  + "');" );
  }

  bool get_cookie( const std::string key, std::string& value )
  {
    bool ret = false;
#if 0    
    try
      {
	value = Wt::WApplication::instance()->environment().getCookie(key);
	if( ! value.empty() )
	  ret = true;
      }
    catch(std::exception e)
      {
	std::cerr << "Exception:" << e.what() << std::endl;
	ret = false;
      }
#endif
    return ret;
  }
}
