#include <Wt/WApplication>
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


simple_login::simple_login(Wt::WContainerWidget *parent)
: Wt::WContainerWidget(parent)
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
  btn_login->clicked().connect(this , &simple_login::checkLogin);

  this->setStyleClass("login_page");
  
}


void simple_login::show_sign_in() {
  edt_full_name->setHidden(true);
  href_sign_in->setHidden(true);
  href_register->setHidden(false);
  btn_login->setText( "Login >>" );
}
void simple_login::show_register() {

  href_register->setHidden(true);
  href_sign_in->setHidden(false);
  edt_full_name->setHidden(false);
  btn_login->setText( "Register >>" );


#if 0


dbo::Transaction transaction(session);

  User *user = new User();
  user->name = "Joe";
  user->password = "Secret";
  user->role = User::Visitor;
  user->karma = 13;

  dbo::ptr<User> userPtr = session.add(user);

  transaction.commit();


  
  //PGconn *conn;

d = new WDialog();
  d->setWindowTitle("Registration form");
  d->resize(300,480);
new WBreak(d->contents());

new WText("Full name <br/>",d->contents());
fname = new WLineEdit(d->contents());
fname->setTextSize(30);

new WText("<br/>Username <br/>",d->contents());
UserName = new WLineEdit(d->contents());
UserName->setTextSize(30);

new WText("<br/>Password <br/>",d->contents());
passwd1 = new WLineEdit(d->contents());
passwd1->setTextSize(30);
passwd1->setEchoMode(WLineEdit::Password);

new WText("<br/>Retype Password <br/>",d->contents());
passwd2 = new WLineEdit(d->contents());
passwd2->setTextSize(30);
passwd2->setEchoMode(WLineEdit::Password);

new WText("<br/>Email <br/>",d->contents());
email = new WLineEdit(d->contents());
email->setTextSize(30);

new WText("<br/>Company <br/>",d->contents());
company = new WLineEdit(d->contents());
company->setTextSize(30);

WText *error = new WText("",d->contents());

new WText("<br/> <br/>",d->contents());

     (new WPushButton("Register", d->contents()))
    ->clicked().connect(d, &WDialog::accept);


     (new WPushButton("cancel", d->contents()))
    ->clicked().connect(d, &WDialog::reject);





  if(d->exec() == WDialog::Accepted)
  {

 error->setText("Password Mismatch");
    if (passwd1->text() != passwd2->text()) {
       //WApplication::instance()->doJavaScript("alert('Password mismatch. Please do registration again')");
      //return;
    }

    res = PQexec(conn, query.c_str());

if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {

        PQclear(res);
        PQfinish(conn);
//WApplication::instance()->doJavaScript("alert('Thank')");
    }
else {WApplication::instance()->doJavaScript("alert('Thankyou for registering')");

/*

WDialog *readme = new WDialog();
  readme->setWindowTitle("ReadMe");
  d->resize(200,200);
new WBreak(readme->contents());
*/





}

  }
}
  //PQclear(res);
    }
#endif
}


void simple_login::logOut() {

  Wt::WApplication::instance()->setCookie("wgrass_login", "", 0);


}


void simple_login::checkLogin() {

  #if 1

  dbo::backend::Sqlite3 sqlite3("blog.db");
  dbo::Session session;
  session.setConnection(sqlite3);
  session.mapClass<User>("user");
  dbo::Transaction transaction(session);
  dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");
  transaction.commit();
  std::cerr << "Joe has karma: " << joe->karma << std::endl;
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
