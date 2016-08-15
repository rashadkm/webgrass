
#include "MainUI.h"

#include "../thirdparty/pstream/pstream.h"

MainUI::MainUI(WContainerWidget *parent)
:WContainerWidget(parent) {
  createUI(parent);
}

MainUI::~MainUI() { }

void MainUI::createUI(Wt::WContainerWidget *parent) {

  Wt::WMenu *menu =  new Wt::WMenu();

  pugi::xml_document doc;

  /* input file of menudata*/
  const std::string MENUDATA_XML_FILE = Wt::WApplication::instance()->docRoot() + "/menu-xml/menudata.xml";
  pugi::xml_parse_result tos = doc.load_file(MENUDATA_XML_FILE.c_str());

  ///std::cout << "Load result: " << tos.description() << std::endl;

  /* iteration over menudata but since only one is there so */
  pugi::xml_node menudata_node = doc.child("menudata");
  /* iteration over menubar but since only one is there so */
  pugi::xml_node menubar_node = menudata_node.child("menubar");

  /* iteration over fisrt occurane of menu */
  pugi::xml_node menu_node = menubar_node.child("menu");
  while( menu_node ) {
    /* first menu creation */
    Wt::WPopupMenu *firstLevel = new Wt::WPopupMenu();
    menu->addMenu(menu_node.child_value("label"), firstLevel);
    /* iteration over first occurance of items */
    pugi::xml_node menu_items_node = menu_node.child("items");
    while( menu_items_node ) {
       /* iteration over second occurane of menu */
       pugi::xml_node menu_items_menu_node = menu_items_node.child("menu");
       while( menu_items_menu_node ) {
          /* submenu creation */
          Wt::WPopupMenu *nextLevel = new Wt::WPopupMenu();
          firstLevel->addMenu(menu_items_menu_node.child_value("label"), nextLevel);
          /* iteration over second occurance of items */
          pugi::xml_node menu_items_menu_items_node = menu_items_menu_node.child("items");
          while ( menu_items_menu_items_node ) {
             /* iteration over internal occurance of menuitem */
             pugi::xml_node menu_items_menu_items_menuitem_node = menu_items_menu_items_node.child("menuitem");
             while( menu_items_menu_items_menuitem_node ) {

	       Wt::WMenuItem *nextLevelMenuItem = new Wt::WMenuItem(menu_items_menu_items_menuitem_node.child_value("label"));
	       nextLevelMenuItem->setId(menu_items_menu_items_menuitem_node.child_value("command"));
	       nextLevelMenuItem->triggered().connect(this, &MainUI::openModuleUI);
	       nextLevel->addItem(nextLevelMenuItem);
	       
	       menu_items_menu_items_menuitem_node = menu_items_menu_items_menuitem_node.next_sibling("menuitem");
             }
             menu_items_menu_items_node = menu_items_menu_items_node.next_sibling("items");
          }
          menu_items_menu_node = menu_items_menu_node.next_sibling("menu");
       }

       /* iteration over outer occurance of menuitem */
       pugi::xml_node menu_items_menuitem_node = menu_items_node.child("menuitem");
       while ( menu_items_menuitem_node ) {
	 Wt::WMenuItem *firstLevelMenuItem = new Wt::WMenuItem(menu_items_menuitem_node.child_value("label"));
	 firstLevelMenuItem->setId(menu_items_menuitem_node.child_value("command"));
	 firstLevelMenuItem->triggered().connect(this, &MainUI::openModuleUI);
	 firstLevel->addItem(firstLevelMenuItem);
	 menu_items_menuitem_node = menu_items_menuitem_node.next_sibling("menuitem");
       }
       
       menu_items_node = menu_items_node.next_sibling("items");
       
       menu_node = menu_node.next_sibling("menu");
    }
  }
  

  Wt::WNavigationBar *naivgationbar = new Wt::WNavigationBar();
  naivgationbar->setResponsive(true);
  naivgationbar->addMenu(menu);
  addWidget(naivgationbar);

  Wt::WContainerWidget *displaycontainer = new Wt::WContainerWidget();
  displaymanager = new Display(displaycontainer);
  Wt::WContainerWidget *toolbarcontainer = new Wt::WContainerWidget();
  toolbar = new Toolbar(toolbarcontainer);
  Wt::WPushButton *ok = new Wt::WPushButton("Load");
  ok->clicked().connect(this, &MainUI::Load);
  // std::cout<<(toolbar->layEr)<<std::endl;
  // std::string f = (toolbar->layEr);
  // if(!f.empty())
  // {
  //   std::cout<<"hihi"<<std::endl;
  //   displaymanager->addlayer();
  // }
  // Toolbar* toolbar = new Toolbar(toolbarcontainer);

  addWidget(toolbar);
  addWidget(ok);
  //addWidget(new WBreak());
  Wt::WContainerWidget *textContainer1 = new Wt::WContainerWidget();
  textContainer1->setStyleClass("wgrass-text-label");
  Wt::WHBoxLayout *hbox2 = new Wt::WHBoxLayout();
  textContainer1->setLayout(hbox2);

  Wt::WText *item = new Wt::WText("Layertree");
  item->setStyleClass("wgrass-text-label");
  hbox2->addWidget(item);
  
  item = new Wt::WText("Display");
  item->setStyleClass("wgrass-text-label");
  hbox2->addWidget(item);
  textContainer1->setMargin(-30, Wt::Bottom);
  addWidget(textContainer1);


  Wt::WContainerWidget *textContainer = new Wt::WContainerWidget();  

  Wt::WHBoxLayout *hbox1 = new Wt::WHBoxLayout();
  textContainer->setLayout(hbox1);

  Wt::WContainerWidget *layercontainer = new Wt::WContainerWidget();

  LayerManager* layermanager = new LayerManager(layercontainer);

  // Wt::WContainerWidget *displaycontainer = new Wt::WContainerWidget();
  // displaymanager = new Display(displaycontainer);
  hbox1->addWidget(layermanager);
  hbox1->addWidget(displaymanager,1);
  textContainer->setMargin(-10, Wt::Left);
  addWidget(textContainer);

  Wt::WNavigationBar *footer = new Wt::WNavigationBar();
  footer->setStyleClass("wgrass-footer");
  footer->setHeight(-30);
  // footer->setResponsive(true);
  // footer->setPositionScheme(Relative);
  // footer->setOffsets(0,Wt::Bottom);
  addWidget(footer);
}

void MainUI::Load(){
  std::cout<<(toolbar->layEr)<<std::endl;
  std::string b = toolbar->layEr;
  std::string c = toolbar->type;
  if(c=="vector"){
        std::string a;
        a = "g.region vect="+b+" -ap";
        runCommand(a);
        a = "v.out.ogr input="+b+" type=line output=../temp/1.shp format=GeoJSON --overwrite";
        runCommand(a);
      }
  else if(c=="raster"){
        std::string a;
        a = "g.region rast="+b+" -ap";
        runCommand(a);
        a = "r.out.gdal input="+b+" output=../temp/dd.tif type=Byte --overwrite";
        runCommand(a);
        a = "r.colors.out map="+b+" rules=../temp/rules1.txt --overwrite";
        runCommand(a);
        a = "gdal_translate -of JPEG -scale -co worldfile=yes -expand rgb ../temp/dd.tif ../temp/2.jpg";
        runCommand(a);
  }


  displaymanager->addlayer(c);
}

void MainUI::runCommand(std::string a){

  std::string command = a;
  redi::ipstream proc("../scripts/init_grass.sh "+ command);     
  std::string line;
  std::cout.flush();


  while (std::getline(proc.out(), line)){
    std::cout << "stdout: " << line << '\n';
    
  }

  
}

void MainUI::openModuleUI(Wt::WMenuItem* gitem) {
  gmodule = gitem->id();
  std::string file = Wt::WApplication::instance()->docRoot() + "/xml/"+ gmodule +".xml";
  std::ifstream my_file(file.c_str());
  if (my_file.fail())
  {
    WApplication::instance()->doJavaScript("alert('Module not implemented')");
  }

  else{

  
  dialog = new Wt::WDialog(gmodule);
  Wt::WPushButton *run = new Wt::WPushButton("RUN", dialog->footer());
  run->setDefault(true);
  run->clicked().connect(this, &MainUI::runModule);
  // run->clicked().connect(dialog, &Wt::WDialog::accept);

  Wt::WPushButton *cancel = new Wt::WPushButton("Cancel", dialog->footer());
  cancel->clicked().connect(dialog, &Wt::WDialog::reject);
  Wt::WContainerWidget *mo = new Wt::WContainerWidget(dialog->contents());

    std::cout<<"alert check"<<std::endl;
    mod = new Module(my_file, mo);
  
  
  std::cout<<"Module created"<<std::endl;
  dialog->rejectWhenEscapePressed();
  dialog->finished().connect(this, &MainUI::deleteModule);
  dialog->show();
}

}

void MainUI::deleteModule(Wt::WDialog::DialogCode code){
  delete dialog;
}
void MainUI::runModule(){
  // if (code == Wt::WDialog::Accepted)
  {
        std::cout<<(mod->findById("Main"))->objectName()<<"check"<<endl;
        std::map<std::string,std::vector<Parameter *> > mop = mod->map;
        std::vector<std::string>list= mod->container_IDs;
        std::vector<std::string>flag_list= mod->flag_IDs;

        std::string command = gmodule+" "+"[-";
        for (std::vector<std::string>::iterator it=flag_list.begin(); it != flag_list.end(); ++it) /*creation of widgets*/
                 {   
                    

                      std::string d = *it;
                      // std::cout<<d<<endl;
                      WCheckBox *cb = dynamic_cast<WCheckBox *>(((mod->findById("Main")))->findById(d));
                      // std::cout<<cb->isChecked()<<"see here"<<std::endl;
                      // std::string value = cb->checkState();
                      if(cb->isChecked())
                      {
                      command = command + d;
                    }
                    

                 }
        command = command + "] ";
        for (std::vector<std::string>::iterator it=list.begin(); it != list.end(); ++it) /*creation of widgets*/
                 {   
                    

                      std::string d = *it;
                      // std::cout<<d<<endl;
                      WLineEdit *edit = dynamic_cast<WLineEdit *>(((mod->findById("Main")))->findById(d));
                      // std::cout<<(edit->text()).toUTF8()<<std::endl;
                      std::string value = (edit->text()).toUTF8();
                      if(!value.empty())
                      {
                      command = command + d+"="+value + " ";
                    }
                    

                 }
        std::cout<<command<<std::endl;
            // redi::ipstream proc("grass70 $HOME/grassdata/newLocation/PERMANENT", redi::pstreams::pstdout | redi::pstreams::pstdin );
            //   std::string line;
            //   std::cout.flush();
            //   while (std::getline(proc.out(), line)){
            //     std::cout << "stdout: " << line << '\n';
            // }
        // std::string t = "g.gisenv";
        //v.buffer --interface-description
            //redi::ipstream proc("export GRASS_PNG_AUTO_WRITE=TRUE;export GRASS_PNG_COMPRESSION=9;export GRASS_TRANSPARENT=TRUE;export GRASS_TRUECOLOR=TRUE;export LD_LIBRARY_PATH=/usr/lib/grass70/lib; export GISBASE=/usr/lib/grass70/; export GISDBASE=/home/mayank/Dropbox/Github/webgrass/grassdata; export GISRC=/home/mayank/Dropbox/Github/webgrass/.webgrass/rc; export PATH=/usr/lib/grass70/bin:/usr/lib/grass70/scripts:$PATH;export GIS_LOCK=77;v.buffer --interface-description");
            // redi::ipstream proc("export GRASS_PNG_AUTO_WRITE=TRUE; export GRASS_PNG_COMPRESSION=9; export GRASS_TRANSPARENT=TRUE; export GRASS_TRUECOLOR=TRUE; export LD_LIBRARY_PATH=/usr/lib/grass70/lib; export GISBASE=/usr/lib/grass70/; export GISDBASE=/home/mayank/grassdata1; export GISRC=/home/mayank/.grass7/rc; export PATH=/usr/lib/grass70/bin:/usr/lib/grass70/scripts:$PATH; g.guienv");
             redi::ipstream proc("../scripts/init_grass.sh "+ command);     
             //redi::ipstream proc("printenv"); 
              std::string line;
              std::cout.flush();
        //       while (proc >> line) {
        //     std::cout << line << std::endl;
        // }
              std::string send_output="";
              while (std::getline(proc.out(), line)){
                std::cout << "stdout: " << line << '\n';
                send_output = send_output + line+'\n';
                
              }
              mod->updateOutput(send_output);

              // redi::ipstream proc1("ls");  
              // std::string line1;
              // std::cout.flush();
              // while (std::getline(proc1.out(), line1)){
              //   std::cout << "stdout: " << line1 << '\n';
              // }
    }
    // delete dialog;
}
