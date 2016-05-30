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
