#include <Wt/WApplication>
#include <Wt/WPaintedWidget>
#include <Wt/WContainerWidget>
#include <Wt/WPainter>
#include <Wt/WTable>
#include <Wt/WEnvironment>



#include <Wt/WFileUpload>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBorderLayout>
#include <Wt/WPushButton>
#include <Wt/WGridLayout>

#include <Wt/Http/Request>
#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WDialog>
#include <Wt/WSlider>
#include <Wt/WText>

using namespace Wt;

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "postgresql/libpq-fe.h"

#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WComboBox>

using namespace std;



class Login : public WContainerWidget {

public:
  Login(WContainerWidget *parent);


void checkLogin();


void logOut();

void doRegister();

void projectSelected();


private:
WLineEdit *uname;
WLineEdit *passwd;
WText * username;
WCheckBox *rememberMe;
WLineEdit *fname  ;
WLineEdit *UserName;
WLineEdit *passwd1 ;
WLineEdit *passwd2 ;
WComboBox *cmbProject;
WLineEdit *email;
WLineEdit *company;
WText *lbl_Uname,*lbl_passwd;
WDialog *d;
WLineEdit *newPrj;
WAnimation anim;
WPushButton *login;
WApplication *wapp;

WContainerWidget *unameWidget;


};
