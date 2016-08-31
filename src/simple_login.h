#ifndef simple_login_h_defined
#define simple_login_h_defined


#include <Wt/Dbo/Dbo>
#include <string>

namespace dbo = Wt::Dbo;

class User {
public:
  enum Role {
    Visitor = 0,
    Admin = 1,
    Alien = 42
  };

  std::string name;
  std::string password;
  Role        role;
  int         karma;

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, name,     "name");
    dbo::field(a, password, "password");
    dbo::field(a, role,     "role");
    dbo::field(a, karma,    "karma");
  }
};

class simple_login : public Wt::WContainerWidget {

public:
  simple_login(Wt::WContainerWidget *parent = 0);

void checkLogin();

void logOut();

 void show_register();
 
 void show_sign_in();

void projectSelected();


private:
 
 Wt::WLineEdit *edt_name, *edt_password, *edt_full_name;
 
 Wt::WPushButton *btn_login;

 Wt::WText *href_register, *href_sign_in;




 
Wt::WCheckBox *rememberMe;
Wt::WLineEdit *fname  ;
Wt::WLineEdit *UserName;
Wt::WLineEdit *passwd1 ;
Wt::WLineEdit *passwd2 ;
Wt::WComboBox *cmbProject;
Wt::WLineEdit *email;
Wt::WLineEdit *company;
Wt::WText *lbl_Uname,*lbl_passwd;
Wt::WDialog *d;
Wt::WLineEdit *newPrj;
Wt::WAnimation anim;
Wt::WPushButton *login;
Wt::WContainerWidget *unameWidget;

};
#endif
