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

  #if 1

  Wt::WContainerWidget *w = new Wt::WContainerWidget();
  Wt::WVBoxLayout * layout  = new Wt::WVBoxLayout(w);

  
  uname = new Wt::WLineEdit();
  uname->setEmptyText("user name");
  layout->addWidget(uname);
  
  passwd = new Wt::WLineEdit();
  layout->addWidget(passwd);

  passwd->setEmptyText("password");

  this->addWidget(w);
  Wt::WPushButton *btn_login = new Wt::WPushButton("Login >>");
  this->addWidget(btn_login);
  btn_login->setStyleClass("wgrass-lpage-elements");
  btn_login->clicked().connect(this , &simple_login::checkLogin);
  
  this->setStyleClass("wgrass-lpage");
  
 
#endif
}



void simple_login::doRegister() {

  
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

WApplication::instance()->setCookie("wgrass_login", "", 0);


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
