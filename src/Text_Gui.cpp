#include "Text_Gui.h"

Text_Gui::Text_Gui() {
  

  }
void Text_Gui::setName(std::string name){
	t_name = name;
}
string Text_Gui::Name(){
	return t_name;
}
void Text_Gui::setType(std::string type){
	t_type = type;
}
string Text_Gui::Type(){
	return t_type;
}
void Text_Gui::setMult(std::string multiple){
	t_mul = multiple;
}
string Text_Gui::Mult(){
	return t_mul;
}
