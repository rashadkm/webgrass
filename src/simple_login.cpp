#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WBorderLayout>
#include <Wt/WPushButton>

#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WText>

#include "simple_login.h"

#include <Wt/WLabel>
#include <Wt/Dbo/backend/Sqlite3>


simple_login::simple_login( Wt::WContainerWidget *parent)
: Wt::WContainerWidget(parent)
{
  std::string user_id;
 
  try
    {
      user_id = Wt::WApplication::instance()->environment().getCookie("wg_login");
      if( ! user_id.empty() )
	  Wt::WApplication::instance()->setInternalPath("/start", true);
    }
  catch (std::exception& e)    {    }
  
  this->create_ui();
  
}

void simple_login::create_ui()
{
  Wt::WContainerWidget *container = new Wt::WContainerWidget(this);
  container->setStyleClass("login_container");
  
  Wt::WContainerWidget *container2 = new Wt::WContainerWidget();
  Wt::WVBoxLayout *hbox = new Wt::WVBoxLayout(container2);
  
  
  href_register = new Wt::WText("<a href=\"#\">Create an account </a>");
  hbox->addWidget(href_register);
  href_register->setStyleClass("login_container_elements");
  href_register->clicked().connect(this , &simple_login::show_register);

  href_sign_in = new Wt::WText("<a href=\"#\">Sign In </a>");
  hbox->addWidget(href_sign_in);
  href_sign_in->setStyleClass("login_container_elements");
  href_sign_in->clicked().connect(this , &simple_login::show_sign_in);
  href_sign_in->setHidden(true);
    
 edt_full_name = new Wt::WLineEdit();
 edt_full_name->setEmptyText("Name: provide your name here");
 hbox->addWidget(edt_full_name);
 edt_full_name->setHidden(true);
 edt_full_name->setStyleClass("login_container_elements");

  edt_name = new Wt::WLineEdit();
  edt_name->setEmptyText("user id: a unique id without space or special characters");

  hbox->addWidget(edt_name, 1);
  edt_name->setStyleClass("login_container_elements");
  edt_password = new Wt::WLineEdit();

  edt_password->setEmptyText("password");
  edt_password->setStyleClass("login_container_elements");
  hbox->addWidget(edt_password);
  
  btn_login = new Wt::WPushButton("Login >>");
  container->addWidget(container2);
  container->addWidget(btn_login);
  btn_login->setStyleClass("login_container_button");
  btn_login->clicked().connect(this , &simple_login::check_login);

  this->setStyleClass("login_page");
  
}



#if 0


dbo::Transaction transaction(session);

  User *user = new User();
  user->name = "Joe";
  user->password = "Secret";
  user->role = User::Visitor;
  user->karma = 13;

  dbo::ptr<User> userPtr = session.add(user);

  transaction.commit();

}


#endif
void simple_login::check_login() {

  #if 1

  dbo::backend::Sqlite3 sqlite3("blog.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User>("user");
  dbo::Transaction transaction(session);
  dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");
  transaction.commit();
  std::cerr << "Joe has karma: " << joe->karma << std::endl;
  Wt::WApplication::instance()->setCookie("wg_login", "Joe", 60*60*24*24);
  Wt::WApplication::instance()->setInternalPath("/start", true);
#if 0

  User *user = new User();
  user->name = "Joe";
  user->password = "Secret";
  user->role = User::Visitor;
  user->karma = 13;
  dbo::ptr<User> userPtr = session.add(user);
  transaction.commit();
#endif
  
  #if 0
  session.createTables();
   #endif


#endif
    }
