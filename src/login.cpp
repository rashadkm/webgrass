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

#include "login.h"

#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WComboBox>
#include <postgresql/libpq-fe.h>

using namespace std;






Login::Login(WContainerWidget *parent=0)
:WContainerWidget(parent)
{
  //setTitle("VRGeo Login");

//useStyleSheet("styles.css");
anim = WAnimation();

WContainerWidget *mapcontainer = new WContainerWidget(parent);



WVBoxLayout * layout  = new WVBoxLayout();


WBorderLayout *mainlayout = new WBorderLayout();
WContainerWidget *north= new WContainerWidget();


WGridLayout *ulayout = new WGridLayout();


unameWidget = new WContainerWidget();



WLabel *ulabel = new WLabel("Login:");
uname = new WLineEdit();
ulayout->addWidget(ulabel,1,0);
ulayout->addWidget(uname,1,1);

ulayout->setColumnStretch(1,100);



WLabel *plabel = new WLabel(" Password:");
passwd = new WLineEdit();
passwd->setEchoMode(WLineEdit::Password);
ulayout->addWidget(plabel,2,0);
ulayout->addWidget(passwd,2,1);

WLabel *prjlabel = new WLabel(" Project:");
ulayout->addWidget(prjlabel,3,0);
cmbProject = new WComboBox();

conninfo = "dbname = postgres";
PGconn *conn =  PQconnectdb(conninfo);






rememberMe = new WCheckBox("Stay signed in");
ulayout->addWidget(rememberMe,5,1);

WPushButton *login = new WPushButton("Login >>");
login->clicked().connect(this , &Login::checkLogin);
passwd->enterPressed().connect(this , &Login::checkLogin);
login->resize(100,WLength::Auto);
ulayout->addWidget(login,6,0);

WText *Register = new WText("<a href=\"#\">Create an account &gt;&gt; </a>");
ulayout->addWidget(Register,0,1);
Register->clicked().connect(this , &Login::doRegister);

unameWidget->resize(WLength(500),WLength(280));
unameWidget->setLayout(ulayout);
layout->addWidget(unameWidget);

unameWidget->setPositionScheme(Relative);
unameWidget->setOffsets(WLength(100));
unameWidget->setOffsets(WLength(300),Left);

unameWidget->setStyleClass("maindiv");
unameWidget->decorationStyle().setBorder(WBorder(WBorder::Solid));



mapcontainer->resize(500,280);
mapcontainer->setLayout(layout);




}



void Login::doRegister() {

PGconn *conn;

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

conn =  PQconnectdb("/var/lib/postgresql/9.5/main/admin");


string query =  "SELECT * FROM users WHERE uname='" + uname->text().narrow() +  "'";
    PGresult *res = PQexec(conn, query.c_str());





    if(PQntuples(res)!=0) {
        WApplication::instance()->doJavaScript("alert('Userid exists. Please do registration again')");
        return;
        }
    else {

    if( (fname->text()=="") || (passwd1->text().toUTF8()=="") ||
        (UserName->text().narrow() == "") || (email->text().narrow() == "")
      ||(company->text().narrow()== "")) {
           // WApplication::instance()->doJavaScript("alert('All fields are required. Please do registration again')");
            //return;
        }
        else if (UserName->text().narrow().size()<4) {
               // WApplication::instance()->doJavaScript("alert('username too short. Miminum 4 characters required')");

        }else if(passwd1->text().toUTF8().size()<5) {
               // WApplication::instance()->doJavaScript("alert('password too short. Miminum 5 characters required')");
        }
    else {


        string query =  "INSERT INTO users (name,uname,passwd,email,company) VALUES('" +
                fname->text().narrow() + "','" + UserName->text().narrow() + "',md5('" + passwd1->text().toUTF8() + "'),'" +
                email->text().narrow() + "','" + company->text().narrow() + "')";



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
}


void Login::logOut() {

WApplication::instance()->setCookie("wgrass_login", "", 0);


}


void Login::checkLogin() {

PGconn *conn =  PQconnectdb("/var/lib/postgresql/9.5/main/admin");


string query =  "SELECT * FROM users WHERE uname='" + uname->text().narrow() + "' AND passwd=md5('" + passwd->text().toUTF8() + "')";
    PGresult *res = PQexec(conn, query.c_str());





    // if(PQntuples(res)==0) {
    //    WApplication::instance()->doJavaScript("alert('Invalid username/password')");
    //     return;
    // }

    // else {
	      WApplication::instance()->setCookie("wgrass_login", uname->text().narrow(), 60*60*24*24);

      WApplication::instance()->setInternalPath("/start",true);
//}


    }
