#ifndef UTILS_H_DEFINED
#define UTILS_H_DEFINED
#include <string>
#include <iostream>
#include <pugixml.hpp>

#include <Wt/WApplication>

namespace Utils {

  typedef pugi::xml_node XmlNodeType;
  const std::string checkFileExists(const std::string& fname);

  const std::string moduleDocRoot();
  
  void getValueOfAttribute(const XmlNodeType &node, const std::string attr, std::string& value);
  void getValueOfAttribute(const XmlNodeType &node, const char* attr, std::string& value);

  void getValueOfChildNode(const XmlNodeType &node, const char* child, std::string& value);
  void getValueOfChildNode(const XmlNodeType &node, const std::string child, std::string& value);

  void alert( const std::string msg );

  bool get_cookie( const std::string key, std::string& value );

}

#endif
