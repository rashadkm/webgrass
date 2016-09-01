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

  const std::string user_id  = edt_name->text().narrow();

  dbo::backend::Sqlite3 sqlite3( Wt::WApplication::instance()->docRoot() + "/simple.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User>("user");
  dbo::Transaction transaction(session);
  
  if ( btn_login->text() == "Register >>")
    {
      User *user = new User();
      user->name = user_id;
      user->password = "password";
      user->role = User::Visitor;
      user->karma = 6;
      dbo::ptr<User> userPtr = session.add(user);
      transaction.commit(); 
    }
  else
    {
      int count = 0;
      count =  session.query<int>("select count(1) from user").where("name = ?").bind(user_id);
      if ( count > 0 )
	{
	  Wt::WApplication::instance()->setCookie("wg_login", user_id, 60*60*24*24);
	  Wt::WApplication::instance()->setInternalPath("/start", false);
	  Wt::WApplication::instance()->redirect("/");
	}
      else
	{
	  Utils::alert("Invalid user name: " + user_id );
	}
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
