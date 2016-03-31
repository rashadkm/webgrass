#include "WGrassMenuBar.h"
#include "GMenuItem.h"
#include "WGMenuForm.h"
WGrassMenuBar::WGrassMenuBar(WContainerWidget *parent)
:WContainerWidget(parent)
 {
  
    Ext::ToolBar *menuToolBar = new Ext::ToolBar(this);


	pugi::xml_document doc;

    pugi::xml_parse_result tos = doc.load_file("menu-xml/menudata.xml");

    pugi::xml_node menudata = doc.child("menudata");

	std::string label,help,handler,shortcut,keywords,command;

   for (pugi::xml_node menubar = menudata.child("menubar"); menubar; menubar = menubar.next_sibling("menubar")) 
   {
      for (pugi::xml_node menu = menubar.child("menu"); menu; menu = menu.next_sibling("menu")) 
      {
	      label = menu.child_value("label"); //FILE
         Ext::Menu *LayerMenu = new Ext::Menu();
         menuToolBar->addButton(label, LayerMenu);


            for (pugi::xml_node items = menu.child("items"); items; items = items.next_sibling("items")) 
            {
               for (pugi::xml_node nitem = items.child("menu"); nitem; nitem = nitem.next_sibling("menu")) 
               {
	               label = nitem.child_value("label"); //WORKSPACE
                  Ext::Menu *subMenu1 = new Ext::Menu();
                  LayerMenu->addMenu(label,subMenu1);
                  for (pugi::xml_node xitem = nitem.child("items"); xitem; xitem = xitem.next_sibling("items")) 
                  {
                     for (pugi::xml_node menuitem = xitem.child("menuitem"); menuitem; menuitem = menuitem.next_sibling("menuitem")) 
                     {
                        label = menuitem.child_value("label");
                        help = menuitem.child_value("help");
   		               handler = menuitem.child_value("handler");
   		               shortcut = menuitem.child_value("shortcut");
                        keywords = menuitem.child_value("keywords");
                        command = menuitem.child_value("command");
   		     
                        mnuItem = new GMenuItem(label,command,keywords);




                                     
                        subMenu1->add(mnuItem);

                     }
                  }
               }

            for (pugi::xml_node imenu = items.child("menuitem"); imenu; imenu = imenu.next_sibling("menuitem")) 
            {
               label = imenu.child_value("label"); //GEORECTIFY
               LayerMenu->addItem(label);

            }

         }
      }
   }


	Ext::ToolBar *toolbar=new Ext::ToolBar(this);







WPushButton *addraster,*addrasterv,*addvector,*addvectorv,*addcmd,
*addlayerg, *addoverlay,*deletelayer,*showattrib;

	addraster = new WPushButton("");
	addraster->resize(30,30);
	addraster->setIcon("icons/grass/layer-raster-add.png");
	addraster->setToolTip("Add raster map layer");

	addrasterv = new WPushButton("");
	addrasterv->resize(30,30);
	addrasterv->setIcon("icons/grass/layer-shaded-relief-add.png");
	addrasterv->setToolTip("Add various raster-based map layer");
	
	addvector = new WPushButton("");
	addvector->setIcon("icons/grass/layer-vector-add.png");
	addvector->resize(30,30);
	addvector->setToolTip("Add vector map layer");	
   addvector->clicked().connect(this,&WGrassMenuBar::onAddVector);

	addvectorv = new WPushButton("");
	addvectorv->setIcon("icons/grass/layer-vector-chart-add.png");
	addvectorv->resize(30,30);	
	addvectorv->setToolTip("Add various vector-based map layer");

	addcmd = new WPushButton("");
	addcmd->setIcon("icons/grass/layer-command-add.png");
	addcmd->resize(30,30);
	addcmd->setToolTip("Add command layer");

   addlayerg = new WPushButton("");
	addlayerg->setIcon("icons/grass/layer-group-add.png");
	addlayerg->resize(30,30);
	addlayerg->setToolTip("Add layer group");


   addoverlay = new WPushButton("");
	addoverlay->setIcon("icons/grass/layer-grid-add.png");
	addoverlay->resize(30,30);
	addoverlay->setToolTip("Add grid or vector labels overlay");


	deletelayer = new WPushButton("");
	deletelayer->setIcon("icons/grass/layer-remove.png");
	deletelayer->resize(30,30);
	deletelayer->setToolTip("Delete selected layer");

	showattrib = new WPushButton("");
	showattrib->setIcon("icons/grass/table.png");
	showattrib->resize(30,30);
	showattrib->setToolTip("Show attribute table");



	toolbar->add(addraster);
	toolbar->add(addrasterv);
	toolbar->add(addvector);
	toolbar->add(addvectorv);
	toolbar->add(addcmd);
	toolbar->add(addlayerg);
	toolbar->add(addoverlay);
	toolbar->add(deletelayer);
	toolbar->add(showattrib);









/*
north= new WContainerWidget(this);
//cout << logged << endl;
new WText("Logged as:  ",north);
logg = new WText(logged,north);
new WText("    ",north);
WText *logout = new WText("<a href=\"#\">Logout</a>",north);
logout->clicked().connect(this , &VRMenuBar::LogOut);

new WText("    ",north);

north->setStyleClass("login");
*/
    
    //toolBar->addSeparator();

   // toolBar->add(basemap);

//toolBar->add(north);

/*
mnuLoadProject->activated().connect(this, &VRMenuBar::LoadProject);
mnuSaveProject->activated().connect(this, &VRMenuBar::SaveProject);


mnuEditLayer->activated().connect(this, &VRMenuBar::EditLayer);
mnuNewGmlVector->activated().connect(this, &VRMenuBar::LoadGmlLayer);
mnuTrackLog->activated().connect(this, &VRMenuBar::AddGPSTracklog);
*/
//basemap->activated().connect(this, &VRMenuBar::AddBaseMap);

//mnuLoadShpLayer->activated().connect(this, &VRMenuBar::LoadShpLayer);       //Shapefile


}

WGrassMenuBar :: ~WGrassMenuBar() { }


void WGrassMenuBar::onAddVector() {

WGMenuForm *form= new WGMenuForm("d.vect");
}
void WGrassMenuBar::onAddRaster() {

WGMenuForm *form= new WGMenuForm("d.rast");
}
/*
void VRMenuBar::SetLoggedIn(string l) {
logg->setText(l);
}
void VRMenuBar::LogOut() {
north->hide();
logg->setText("");
WApplication::instance()->setCookie("vrgeo", "", 0);
WApplication::instance()->setCookie("uname", "", 0);
WApplication::instance()->redirect("/?vrgeo=editor");
//WApplication::instance()->redirect("/lsi/vrgeo/edit/login");
}

void VRMenuBar::AboutUs() {
WDialog *dlg = new WDialog();

dlg->setWindowTitle("About Us");

WContainerWidget * ww = new WContainerWidget(dlg->contents());
new WBreak(dlg->contents());
new WBreak(dlg->contents());
;
WText *text = new WText(dlg->contents());
WString t = "VRGeo 0.12<br/><br/>"
"Developed and maintained by Lab for Spatial Informatics (LSI)<br/> IIIT Hyderabad<br/><br/>"
"Contact: <br/> Dr. K.S Rajan - rajan at iiit dot ac dot in <br/>"
"Mohammed Rashad K.M rashadkm at gmail dot com";
text->setText(t);
new WBreak(dlg->contents());
new WBreak(dlg->contents());
  WPushButton *okButton = new WPushButton("ok",dlg->contents());
  okButton->clicked().connect(dlg, &WDialog::accept);

    if(dlg->exec() == WDialog::Accepted) {
    delete dlg;
    dlg= 0;
    }
}

void VRMenuBar::LoadShpLayer() {

}
void VRMenuBar::AddBaseMap() {

}



void VRMenuBar::AddGoogleMap(string type)
{


}

void VRMenuBar::NewSHPLayer() {
ltree->NewLayer();
//wapp->setInternalPath("/addlayer");

}

void VRMenuBar::NewGMLLayer() {
ltree->NewGMLLayer();
}

void VRMenuBar::LoadGmlLayer() {
ltree->LoadGmlLayer();
}

void VRMenuBar::NewGPXLayer() {
ltree->NewGPXLayer();
} 

void VRMenuBar::LoadGPXLayer() {
ltree->LoadGPXLayer();
} 

void VRMenuBar::EditLayerSchema() {
ltree->EditLayer();
} 

void VRMenuBar::LoadTrackLog() {
ltree->LoadTrackLog();
}

void VRMenuBar::NewCSVLayer() {
ltree->NewCsvLayer();
}
*/
