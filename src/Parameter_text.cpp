#include "Parameter_text.h"

Parameter_text::Parameter_text() {
  

  }
void Parameter_text::setText(std::string text){
	p_text = text;
}
string Parameter_text::Text(){
	return p_text;
}
void Parameter_text::setName(std::string name){
	p_name = name;
}
string Parameter_text::Name(){
	return p_name;
}
void Parameter_text::setType(std::string type){
	p_type = type;
}
string Parameter_text::Type(){
	return p_type;
}
void Parameter_text::setMult(std::string multiple){
	p_mul = multiple;
}
string Parameter_text::Mult(){
	return p_mul;
}
void Parameter_text::setTabname(std::string tab){
	p_tab = tab;
}
string Parameter_text::Tab(){
	return p_tab;
}
void Parameter_text::isFlag(std::string flag){
	p_flag = flag;
}
string Parameter_text::Flag(){
	return p_flag;
}
void Parameter_text::setFlag_no(int num){
	p_flag_no = num;
}
int Parameter_text::Flag_no(){
	return p_flag_no;
}
