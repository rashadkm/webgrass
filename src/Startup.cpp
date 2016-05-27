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

void Startup::show_files( const path & directory, vector<string>&directories, bool recurse_into_subdirs = true )// for returning the files in a directory
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

bool Startup::checkExistance(std::string directory, std::string cont) // checking whether given directory exists or not 
{ 	
	
	string f = cont+"/"+directory;
	cout<<f<<endl;
	return boost::filesystem::exists( f ); 
}


void Startup::makeSelectionBox(WSelectionBox *box, vector<string> dir, string di)// initial construction of the mapset and Location wizard
{

		for(vector<string>::iterator it = dir.begin();it!=dir.end();++it)
		{
			bool isValidLocation = checkExistance(*it, di);
			cout<<isValidLocation<<endl;
			if (isValidLocation) 
				{ box->addItem(*it); } 
		}

		//box->setCurrentIndex(0); 
}



Startup::Startup(std::string wgrass_login, WContainerWidget *parent=0)
:WContainerWidget(parent)
{

anim = WAnimation();

m_GrassDataDirectory = "/home/mayank/webgrassdata"; // GRASS GIS database library
m_GrassMapsetDirectory = "/home/mayank/webgrassdata/testLocation"; // GRASS GIS initial location directory




WContainerWidget *mainContainer = new WContainerWidget(parent);
mainContainer->resize(1000,600);

Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout(); // vbox to divide the layout in vertical direction

mainContainer->setLayout(vbox);



location = new WSelectionBox(); 

Wt::WImage *image = new Wt::WImage(Wt::WLink("http://grassmac.wdfiles.com/local--files/start/startup_banner.png")); // image of GRASS GIS
image->resize(50,200);
image->setWidth(5);
vbox->addWidget(image,0.20);


Wt::WGridLayout *grid = new Wt::WGridLayout(); // layout with the use of grid. grid uses coordinates 
vbox->addLayout(grid);

grid->addWidget(new WText("                                   "),0,0); // spacing for better layout


grid->addWidget(new WText("GIS Data Directory    "),0,1);



Wt::WSelectionBox *datadir = new Wt::WSelectionBox(); // selection box for GRASS GIS database directory
datadir->resize(200,25);
datadir->addItem(m_GrassDataDirectory);   
grid->addWidget(datadir,0,2);




const fs::path fi= m_GrassDataDirectory;
vector<string> dir;
show_files(fi,dir,true);
WtSelectionBoxLocation = new Wt::WSelectionBox(); // selection box GRASS location
WtSelectionBoxLocation->resize(200,240);
makeSelectionBox(WtSelectionBoxLocation,dir,m_GrassDataDirectory);
WtSelectionBoxLocation->sactivated().connect(this, &Startup::locationChanged); // capturing the click




Wt::WPushButton *button3 = new Wt::WPushButton("New");
Wt::WPushButton *button4 = new Wt::WPushButton("Rename");
Wt::WPushButton *button5 = new Wt::WPushButton("Delete");



Wt::WGroupBox *groupBox = new Wt::WGroupBox("Project Location");  // grouping of the combo box
groupBox->setWidth(200);
groupBox->addWidget(WtSelectionBoxLocation);
//groupBox->addWidget(button3);
//groupBox->addWidget(button4);
//groupBox->addWidget(button5);
groupBox->resize(200,300);





const fs::path fii= m_GrassMapsetDirectory;
vector<string> dir2;
show_files(fii,dir2,true);
WtSelectionBoxMapset = new Wt::WSelectionBox(mainContainer); // selection box GRASS mapset
WtSelectionBoxMapset->resize(200,240);
makeSelectionBox(WtSelectionBoxMapset,dir2,m_GrassMapsetDirectory);
WtSelectionBoxMapset->sactivated().connect(this, &Startup::mapsetChanged);



Wt::WPushButton *button = new Wt::WPushButton("New");
Wt::WPushButton *button1 = new Wt::WPushButton("Rename");
Wt::WPushButton *button2 = new Wt::WPushButton("Delete");

Wt::WGroupBox *groupBox2 = new Wt::WGroupBox("Accessile Mapsets");
groupBox2->setWidth(200);
groupBox2->addWidget(WtSelectionBoxMapset);
//groupBox2->addWidget(button);
//groupBox2->addWidget(button1);
//groupBox2->addWidget(button2);
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





void Startup::locationChanged(WString loc_string){ // dynamic updation of mapset when location changed and m_location variable
	
	cout<<loc_string.narrow()<<endl;
	m_location =loc_string.narrow();
	WtSelectionBoxMapset->clear();

	vector<string> directories;
	string hh=m_GrassDataDirectory;
	string gg=hh+(string)"/";
	string jj=gg+m_location;

	const fs::path fii= gg + m_location;

	show_files(fii,directories,true );
	makeSelectionBox(WtSelectionBoxMapset,directories,jj);

}



void Startup::mapsetChanged(WString map_string){  // dynamic updation of the m_mapset variable
	
	cout<<map_string.narrow()<<endl;
	m_mapset = map_string.narrow();
}



void Startup::startWebGrass() {

	cout<<m_location<<endl;
	cout<<m_mapset<<endl;

 WApplication::instance()->setCookie("wgrass_location", m_location, 60*60*24*24); // setting the cookies
 WApplication::instance()->setCookie("wgrass_mapset", m_mapset , 60*60*24*24);	

 // std::ofstream grassrc;
 //  grassrc.open ("./grassrc7");
 //  grassrc << "GISDBASE: " + base_path << endl;
 //  grassrc << "LOCATION_NAME: " + slocation << endl;
 //  grassrc << "MAPSET: " + smapset << endl;
 //  grassrc << "GRASS_GUI: text" << endl;
 //  grassrc << "MONITOR: PNG" << endl;
 //  grassrc.close();
 WApplication::instance()->redirect("/");
}









