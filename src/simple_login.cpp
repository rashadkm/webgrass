#include <Wt/WApplication>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WText>

#include "simple_login.h"
#include "Utils.h"
#include <Wt/Dbo/backend/Sqlite3>

simple_login::simple_login( Wt::WContainerWidget *parent)
: Wt::WContainerWidget(parent)
{
  this->create_ui();  
}

void simple_login::check_login()
{

  const std::string s  = edt_name->text().narrow();
  dbo::backend::Sqlite3 sqlite3("blog.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User>("user");
  dbo::Transaction transaction(session);
  int count = 0;
  count =  session.query<int>("select count(1) from user").where("name = ?").bind(s);
  if ( count > 0 )
    {
      Wt::WApplication::instance()->setCookie("wg_login", s, 60*60*24*24);
      Wt::WApplication::instance()->setInternalPath("/start", false);
      Wt::WApplication::instance()->redirect("/");
    }
  else
    {
      Utils::alert("Invalid user name: " + s );
    }
}    

void simple_login::create_ui()
{
  Wt::WContainerWidget *container = new Wt::WContainerWidget(this);
  container->setStyleClass("login_container");
  
  Wt::WContainerWidget *login_container = new Wt::WContainerWidget(container);
  Wt::WVBoxLayout *hbox = new Wt::WVBoxLayout(login_container);
  
  href_register = new Wt::WText("<a href=\"#\">Create an account </a>");
  href_register->setStyleClass("login_container_elements");
  href_register->clicked().connect(this , &simple_login::show_register);
  hbox->addWidget(href_register);

  href_sign_in = new Wt::WText("<a href=\"#\">Sign In </a>");
  href_sign_in->setStyleClass("login_container_elements");
  href_sign_in->clicked().connect(this , &simple_login::show_sign_in);
  href_sign_in->setHidden(true);
  hbox->addWidget(href_sign_in);
    
  edt_full_name = new Wt::WLineEdit();
  edt_full_name->setEmptyText("Name: provide your name here");
  edt_full_name->setHidden(true);
  edt_full_name->setStyleClass("login_container_elements");
  hbox->addWidget(edt_full_name);
  
  edt_name = new Wt::WLineEdit();
  edt_name->setEmptyText("user id: a unique id without space or special characters");
  edt_name->setStyleClass("login_container_elements");
  hbox->addWidget(edt_name, 1);
    
  edt_password = new Wt::WLineEdit();
  edt_password->setEmptyText("password");
  edt_password->setStyleClass("login_container_elements");
  hbox->addWidget(edt_password);
  
  btn_login = new Wt::WPushButton("Login >>");
  btn_login->setStyleClass("login_container_button");
  btn_login->clicked().connect(this , &simple_login::check_login);
  container->addWidget(btn_login);
  
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

#if 0
void simple_login::check_login()
{

  const std::string s  = edt_name->text().narrow();

  Wt::WApplication::instance()->setCookie("wg_login", s, 60*60*24*24);
    
  dbo::backend::Sqlite3 sqlite3("blog.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User>("user");
  dbo::Transaction transaction(session);

  dbo::ptr<User> query_user = session.find<User>().where("name = ?").bind(s);
  transaction.commit();

  if ( query_user )
    {
      std::cerr << s << " has karma: " << query_user->karma << std::endl;
      Wt::WApplication::instance()->setCookie("wg_login", s, 60*60*24*24);
      Wt::WApplication::instance()->setInternalPath("/start", true);
    }
  else
    {
      Utils::alert(s);
    }
    

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



}
#endif
