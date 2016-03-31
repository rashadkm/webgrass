/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBorderLayout>
#include <Wt/WGridLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WFileUpload>
#include <Wt/WTabWidget>
#include <Wt/WVBoxLayout>

using namespace Wt;


#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


#include "WGrass.h"
#include "global.h"
#include "pugixml/pugixml.hpp"



#include <boost/assign/list_of.hpp> 
#include <boost/bind.hpp>  


#include <boost/asio.hpp> 
#include <boost/assign/list_of.hpp> 
#include <boost/array.hpp> 
#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>


#if defined(BOOST_POSIX_API) 
#   include <sys/wait.h> 
#endif 

//namespace bp = boost::process; 

#define INLINE_JAVASCRIPT(...) #__VA_ARGS__

#include "pstream.h"
#include "WGrassLayerManager.h"

#include "WGrassMenuBar.h"


WGrass::WGrass(WContainerWidget *parent)
:WContainerWidget(parent) {

	createUI(parent);
	
}
WGrass::~WGrass() { }



void WGrass::createUI(WContainerWidget *parent) { 


	parent->setStyleClass("maindiv");

	WContainerWidget *mapcontainer = new WContainerWidget(parent);

	WBorderLayout *mainlayout = new WBorderLayout(mapcontainer);

	WContainerWidget *MapsAndLayerTree = new WContainerWidget();
	mainlayout->addWidget(MapsAndLayerTree,WBorderLayout::Center);



   WGrassLayerManager *ltree = new WGrassLayerManager();



  WOpenLayers	*oMap = new WOpenLayers();
  	oMap->resize(640, 480);
  	oMap->decorationStyle().setBorder(WBorder(WBorder::Solid));
//	oMap->getArgs().connect(this,&WGrass::setParametres);
   oMap->setPositionScheme(Relative);


   WHBoxLayout *hbox =  new WHBoxLayout();
   //hbox->setResizable(0);
   hbox->addWidget(oMap);

	WGridLayout *layout = new WGridLayout(MapsAndLayerTree);
   layout->addLayout(hbox, 0, 1);   
   layout->setRowStretch(1, 1);
   layout->setColumnStretch(1, 1);
   layout->addWidget(ltree, 0, 0);   
   layout->setColumnResizable(0);


	WGrassMenuBar *menuBar = new WGrassMenuBar();
	mainlayout->addWidget(menuBar,WBorderLayout::North);








    putenv((char *)"GIS_LOCK=$$");
    putenv((char *)"GISBASE=/usr/lib/grass64");
    putenv((char *)"PATH=$PATH:/usr/lib/grass64/bin:/usr/lib/grass64/scripts");
    putenv((char *)"LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/grass64/lib");
    putenv((char *)"GISRC=grassrc7");
    putenv((char *)"GRASS_WIDTH=640");
    putenv((char *)"GRASS_HEIGHT=480");
    putenv((char *)"GRASS_PNG_MAPPED=TRUE");
    putenv((char *)"GRASS_PNG_READ=TRUE");


	
}


void WGrass::dataUploaded() {

		string clientfile = upload->clientFileName().narrow();

		string spoolfile =upload->spoolFileName();

		vector<Http::UploadedFile> ufiles;
		ufiles = upload->uploadedFiles();


		for(vector<Http::UploadedFile>::iterator it = ufiles.begin();it!=ufiles.end();++it) {
			Http::UploadedFile uf = *it;
			string spfile = uf.clientFileName();
			basename = spfile.substr(0,(spfile.size()-4));
			string move;
			int res;
			move = "/bin/cp " + uf.spoolFileName() + " data/" +  uf.clientFileName();
			res = system (move.c_str());
			if(res!=0)
			{
				WApplication::instance()->doJavaScript("alert('error in uploading');");
				return;
			}


			//uploadedInfo->setText(basename);

		
		}



}
void WGrass::simplePopup(WContainerWidget *parent)
  {
    popup = createAliasesMatchingPopup(parent);
    popup->setModel(createDrugsModel());
    popup->setMinimumSize(150, Wt::WLength::Auto);
    popup->setMaximumSize(Wt::WLength::Auto, 300);
    //popup->activated().connect(this,&WGrass::makeTabs);


    edit = new Wt::WLineEdit(parent);
    edit->resize(250, Wt::WLength::Auto);
    popup->forEdit(edit);
//	edit->enterPressed().connect(this,&WGrass::makeTabs);
	edit->setEmptyText("specify a grass module: eg: g.list");


  }




  WSuggestionPopup* WGrass::createAliasesMatchingPopup(WContainerWidget *parent)
  {

    std::string matcherJS = INLINE_JAVASCRIPT
      (
       function (edit) {
	 var value = edit.value;

	 return function(suggestion) {
	   if (!suggestion)
	     return value;
	   
	   var i, il,
	     names = suggestion.split(';'),
	     val = value.toUpperCase(),
	     matchedAliases = [],
	     matched = null;

	   if (val.length) {
	     for (i = 0, il = names.length; i < il; ++i) {
	       var name = names[i];
	       if (name.length >= val.length
		   && name.toUpperCase().substr(0, val.length) == val) {
		 // This name matches
		 name = "<b>" + name.substr(0, val.length) + "</b>"   + name.substr(val.length);

		 if (i == 0) // it's the product name
		   matched = name;
		 else // it's an alias
		   matchedAliases.push(name);
	       }
	     }
	   }

	   // Let '...' always match
	   if (names[0] == "...")
	     matched = names[0];

	   if (matched || matchedAliases.length) {
	     if (!matched)
	       matched = names[0];

	     if (matchedAliases.length)
	       matched += " (" + matchedAliases.join(", ") + ")";

	     return { match : true,
		      suggestion : matched };
	   } else {
	     return { match : false,
		      suggestion : names[0] };
	   }
	 }
       }
       );

    std::string replacerJS = INLINE_JAVASCRIPT
      (
       function (edit, suggestionText, suggestionValue) {
	 edit.value = suggestionValue.trim();

	 if (edit.selectionStart)
	   edit.selectionStart = edit.selectionEnd = suggestionValue.length;
       }
       );

    return new Wt::WSuggestionPopup(matcherJS, replacerJS, parent);
  }


WStandardItemModel* WGrass::createDrugsModel()
  {
	  WStandardItemModel *prjmodel = new WStandardItemModel();
      const char* items[]= {"v.buffer","v.build","v.clean","v.in.ogr","v.out.ogr","d.vect","g.list","g.gisenv","v.info",
            "v.db.addcol","v.db.addtable","v.db.connect","v.db.droptable","v.db.select","v.db.update"};

        for(int i =0;i<15;i++)
	        prjmodel->appendRow(new WStandardItem(items[i]));
	  prjmodel->sort(0);

	  return prjmodel;

    }
