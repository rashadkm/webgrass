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

bool Startup::checkExistance(std::string directory, std::string cont) 
{ 	
	//cout<<"fff"<<endl;
	string f = cont+"/"+directory;
	cout<<f<<endl;
	return boost::filesystem::exists( f ); 
}






Startup::Startup(std::string wgrass_login, WContainerWidget *parent=0)
:WContainerWidget(parent)
{

anim = WAnimation();

m_GrassDataDirectory = "/home/mayank/webgrassdata";
m_GrassMapsetDirectory = "/home/mayank/webgrassdata/newLocation";




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
datadir->addItem(m_GrassDataDirectory);   
grid->addWidget(datadir,0,2);




const fs::path fi= m_GrassDataDirectory;
vector<string> dir;
show_files(fi,dir,true);
Wt::WSelectionBox *cb = new Wt::WSelectionBox();
cb->resize(200,240);


for(vector<string>::iterator it = dir.begin();it!=dir.end();++it)
{
	bool isValidLocation = checkExistance(*it, m_GrassDataDirectory);
	cout<<isValidLocation<<endl;
	if (isValidLocation) 
		{ cb->addItem(*it); } 
}
 


// bool isValidLocation = checkExistance(dir[0], m_GrassDataDirectory);
// if (isValidLocation) 
// 	{ cb->addItem(dir[0]); } 
// cb->addItem(dir[1]);
// cb->addItem(dir[2]);

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



const fs::path fii= m_GrassMapsetDirectory;
vector<string> dir2;
show_files(fii,dir2,true);
Wt::WSelectionBox *cb1 = new Wt::WSelectionBox(mainContainer);
cb1->resize(200,240);

for(vector<string>::iterator it2 = dir2.begin();it2!=dir2.end();++it2)
{
	bool isValidLocation = checkExistance(*it2, m_GrassMapsetDirectory);
	cout<<isValidLocation<<endl;
	if (isValidLocation) 
		{ cb1->addItem(*it2); } 
}


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

startWGrass->resize(150,30);
grid->addWidget(startWGrass,3,2);
grid->addWidget(new WText("  "),1,3);



grid->setRowStretch(1, 1);
grid->setRowStretch(2, 1);

grid->setColumnStretch(3, 1);
grid->setColumnStretch(0, 1);


}

void Startup::comboChanged(WString loc_string){
	
	cout<<loc_string.narrow()<<endl;
	m_location =loc_string.narrow();
}

void Startup::combo1Changed(WString map_string){
	
	cout<<map_string.narrow()<<endl;
	m_mapset =map_string.narrow();
}



void Startup::startWebGrass() {

	cout<<m_location<<endl;
	cout<<m_mapset<<endl;

 WApplication::instance()->setCookie("wgrass_location", m_location, 60*60*24*24);
 WApplication::instance()->setCookie("wgrass_mapset", m_mapset , 60*60*24*24);	

 WApplication::instance()->redirect("/");
}









