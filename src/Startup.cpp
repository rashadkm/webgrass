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
#include <Wt/WGroupBox>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WImage>

#include <Wt/Http/Request>
#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WDialog>
#include <Wt/WSlider>
#include <Wt/WText>
#include <Wt/WFileUpload>
#include <Wt/WLink>

using namespace Wt;

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "login.h"
#include "global.h"


#include <Wt/WLabel>
#include <Wt/WRandom>
#include <Wt/WSelectionBox>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include "Startup.h"

using namespace std;

using namespace boost::filesystem; 

void Startup::show_files( const path & directory, vector<string>&directories, bool recurse_into_subdirs = true )
{
if( exists( directory ) )
{
directory_iterator end ;
for( directory_iterator iter(directory) ; iter != end ; ++iter )
{
cout << directory << endl;
if ( is_directory( *iter ) )
{
  directories.push_back(iter->path().leaf().string() );

}

}
}
}







Startup::Startup(std::string wgrass_login,WContainerWidget *parent=0)
:WContainerWidget(parent)
{

anim = WAnimation();



WContainerWidget *mainContainer = new WContainerWidget(parent);
mainContainer->resize(1000,600);

Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();

mainContainer->setLayout(vbox);



location = new WSelectionBox(); 

Wt::WImage *image = new Wt::WImage(Wt::WLink("http://grassmac.wdfiles.com/local--files/start/startup_banner.png"));
image->resize(50,200);
image->setWidth(5);
vbox->addWidget(image,0.20);


Wt::WGridLayout *grid = new Wt::WGridLayout();
vbox->addLayout(grid);

grid->addWidget(new WText("                                   "),0,0);


grid->addWidget(new WText("GIS Data Directory    "),0,1);



Wt::WSelectionBox *datadir = new Wt::WSelectionBox();
datadir->resize(200,25);
datadir->addItem("/home/mayank/webgrassdata");   
grid->addWidget(datadir,0,2);




const fs::path fi= "/home/mayank/webgrassdata";
vector<string> dir;
show_files(fi,dir,true);
Wt::WSelectionBox *cb = new Wt::WSelectionBox();
cb->resize(200,240);
cb->addItem(dir[0]);
cb->addItem(dir[1]);
cb->addItem(dir[2]);
cb->setCurrentIndex(1); 


cb->sactivated().connect(this, &Startup::comboChanged);


Wt::WPushButton *button3 = new Wt::WPushButton("New");
Wt::WPushButton *button4 = new Wt::WPushButton("Rename");
Wt::WPushButton *button5 = new Wt::WPushButton("Delete");



Wt::WGroupBox *groupBox = new Wt::WGroupBox("Project Location");
groupBox->setWidth(200);
groupBox->addWidget(cb);


groupBox->addWidget(button3);
groupBox->addWidget(button4);
groupBox->addWidget(button5);
groupBox->resize(200,300);



const fs::path fii= "/home/mayank/webgrassdata/newLocation";
vector<string> dir2;
show_files(fii,dir2,true);
Wt::WSelectionBox *cb1 = new Wt::WSelectionBox(mainContainer);
cb1->resize(200,240);
cb1->addItem(dir2[1]);
cb1->addItem(dir2[0]);
cb1->addItem(dir2[2]);
cb1->setCurrentIndex(0);


cb1->sactivated().connect(this, &Startup::combo1Changed);

Wt::WPushButton *button = new Wt::WPushButton("New");
Wt::WPushButton *button1 = new Wt::WPushButton("Rename");
Wt::WPushButton *button2 = new Wt::WPushButton("Delete");

Wt::WGroupBox *groupBox2 = new Wt::WGroupBox("Accessile Mapsets");
groupBox2->setWidth(200);
groupBox2->addWidget(cb1);
groupBox2->addWidget(button);
groupBox2->addWidget(button1);
groupBox2->addWidget(button2);
groupBox2->resize(200,300);

grid->addWidget(new WText("Choose Project Location and Mapset"),1,1);
grid->addWidget(new WText("##############################"),1,2);



grid->addWidget(groupBox,2,1);
grid->addWidget(groupBox2,2,2);




location->resize(320,240);

mapset = new WSelectionBox();



WPushButton *startWGrass = new WPushButton("Start webGRASS >>");
startWGrass->clicked().connect(this , &Startup::startWebGrass);
grid->addWidget(new WText(k),3,1);
startWGrass->resize(150,30);
grid->addWidget(startWGrass,3,2);
grid->addWidget(new WText("  "),1,3);



grid->setRowStretch(1, 1);
grid->setRowStretch(2, 1);

grid->setColumnStretch(3, 1);
grid->setColumnStretch(0, 1);


}

void Startup::comboChanged(WString thisi){
	
	cout<<thisi.narrow()<<endl;
	k=thisi.narrow();
}

void Startup::combo1Changed(WString thisee){
	
	cout<<thisee.narrow()<<endl;
	l=thisee.narrow();
}



void Startup::startWebGrass() {

	cout<<k<<endl;
	cout<<l<<endl;

 WApplication::instance()->setCookie("wgrass_location", k, 60*60*24*24);
 WApplication::instance()->setCookie("wgrass_mapset", l, 60*60*24*24);	

 WApplication::instance()->redirect("/");
}









