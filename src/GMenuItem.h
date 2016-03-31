#ifndef _GMENUITEM_H_
#define _GMENUITEM_H_
#include <Wt/Ext/MenuItem>



using namespace Wt;
class GMenuItem : public Wt::Ext::MenuItem {



public:
std::string label,help,handler,shortcut,keywords,command;
GMenuItem(std::string lbl,std::string cmd,std::string keywords);
~GMenuItem();
void menuItemActivated();


};
#endif
