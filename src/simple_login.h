#ifndef simple_login_h_defined
#define simple_login_h_defined


#include <Wt/Dbo/Dbo>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>

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

class simple_login : public Wt::WContainerWidget
{

public:
  simple_login(Wt::WContainerWidget *parent = 0);

  std::string login_id;
private:

  void show_sign_in()
  {
    this->toggle(true);
    btn_login->setText( "Login >>" );
  }
  
  void show_register()
  {
    this->toggle(false);
    btn_login->setText( "Register >>" );
  }
  
  void toggle(bool t)
  {
    edt_full_name->setHidden(t);
    href_sign_in->setHidden(t);
    href_register->setHidden(!t);
  }
  
  void create_ui();
 
  void check_login();
 
  
  Wt::WLineEdit *edt_name, *edt_password, *edt_full_name;
 
  Wt::WPushButton *btn_login;
  
  Wt::WText *href_register, *href_sign_in;
  
};
#endif
