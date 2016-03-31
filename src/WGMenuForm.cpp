#include "WGMenuForm.h"


#include <Wt/WDialog>
#include <Wt/WPushButton>
#include <Wt/WHBoxLayout>

#include <iostream>

WGMenuForm::WGMenuForm(std::string cmd,std::string kws)
:WDialog(),command(cmd),keywords(kws) {
	menuForm = new WTabWidget();
setupTabs();
setWindowTitle ("[ " + command + "] " + keywords);
WContainerWidget *contents = this->contents();
contents->addWidget(menuForm);


	WContainerWidget *btnContainer = new WContainerWidget();

	WHBoxLayout *btnLayout = new WHBoxLayout(btnContainer);
	WPushButton *runButton = new WPushButton("Run");
	runButton->clicked().connect(this,&WGMenuForm::RunCommand);
	WPushButton *closeButton = new WPushButton("Close");
	closeButton->clicked().connect(this,&WDialog::reject);
	WPushButton *hlpButton = new WPushButton("Help");
   btnLayout->addWidget(runButton);
   btnLayout->addWidget(closeButton);
   btnLayout->addWidget(hlpButton);
btnContainer->resize(200,WLength::Auto);
contents->addWidget(btnContainer);

show();
}

WGMenuForm::~WGMenuForm() {

}



void WGMenuForm::RunCommand() {

stringstream strm;
strm << "var args='';";
	for(vector<string>::iterator nit = names.begin();nit!=names.end();++nit) {
		string name = *nit;
	strm <<
			"if(document.getElementById('" << name <<"')){var val = document.getElementById('" << name <<"').value;"
			"if(val!=''){"
			"args = args + '" << name << "' + '=' + val + ' '"
			"}}";

		
	}

	for(vector<WCheckBox *>::iterator fit = flboxes.begin();fit!=flboxes.end();++fit) {
		WCheckBox *flg = *fit;
		if( (flg->isChecked()) && (flg->id()!="verbose") && (flg->id()!="quiet") )
		{
			strm <<
			"var val = ' -" + flg->id() + "';"
			"if(val!=''){"
			"args = args  + val;"
			"}";
		}

		else if( (flg->isChecked()) && (flg->id()=="verbose"))
		{
			strm <<	"args = args  + ' --v';";
		}
		else if( (flg->isChecked()) && (flg->id()=="quiet"))
		{
			strm <<	"args = args  + ' --q';";
		}
		
	}
//	strm << oMap->arguments_.createCall("args");
	WApplication::instance()->doJavaScript(strm.str());



}


void WGMenuForm::setParametres(string args) {
this->args = args;
stringstream strm;


string exe, ar;



		string ext;

		if(pgm == "d.vect") {

			vector<string> arguments;
			Tokenize(args,arguments," ");
			vector<string>::iterator it = arguments.begin();
            string args;
			string arg = *it;
			string mapname = arg.substr(4,arg.size());

			exe = "v.out.ogr -c input=" + mapname + "@PERMANENT ";
			args= "dsn=outputs/" + mapname + ".xml type=point,line,boundary,area,face,kernel format=GML";
			string out = WRunCommand(exe,args);
			//cout << out << endl;

			


            exe = "v.info";
            args = mapname + "@PERMANENT" + " -g";
            out = WRunCommand(exe,args);
            stringstream in;
            string n,s,e,w;
            in << out;
            //while (std::getline(in, msg)) {
            getline(in,n);
            getline(in,s);
            getline(in,e);
            getline(in,w);

			strm << "var gml = new OpenLayers.Layer.GML('" + mapname + "', 'outputs/" + mapname + ".xml');map.addLayer(gml);";
            strm << "map.zoomToExtent(new OpenLayers.Bounds(" << w << "," << s << "," << e <<"," << n << "))";
			WApplication::instance()->doJavaScript(strm.str());
              
		    //}
        }

		else if(pgm == "v.in.ogr") {
			if(cmbFormat->currentIndex() == 0) 
				ext = ".shp";
			else
				ext = ".xml";
			string outm = outMap->text().narrow();
            string args;
			exe = "v.in.ogr";
            args ="dsn=data/" + basename + ext  + " output=" + outm + " -o --overwrite";
			string out = WRunCommand(exe,args);
			cmdout->setText(out);

		}
		else {
			exe = pgm;
			string out = WRunCommand(exe,args);
			cmdout->setText(out);
			menuForm->setCurrentIndex(menuForm->count()-1);
		}



}
string WGMenuForm::WRunCommand(string exe,string args) {

string data = exe + " " +  args;
stringstream pout;

const redi::pstreams::pmode mode = redi::pstreams::pstdout|redi::pstreams::pstderr;


redi::ipstream child(data, mode);
char buf[4096];
std::streamsize n;
bool finished[2] = { false, false };
while (!finished[0] || !finished[1])
{
    if (!finished[0])
    {
        while ((n = child.err().readsome(buf, sizeof(buf))) > 0)
            pout.write(buf, n);
        if (child.eof())
        {
            finished[0] = true;
            if (!finished[1])
                child.clear();
        }
    }

    if (!finished[1])
    {
        while ((n = child.out().readsome(buf, sizeof(buf))) > 0)
            pout.write(buf, n).flush();
        if (child.eof())
        {
            finished[1] = true;
            if (!finished[0])
                child.clear();
        }
    }
}
/*
string data = exe + " " +  args;
cout << data << endl;
redi::ipstream in(data, mode);
string msg;
    while (std::getline(in, msg)) {
        pout << msg << endl;
    }
*/
return pout.str();


}

WWidget *WGMenuForm::cmdOutput(string cmd) {

WTextArea *cmdOut = new WTextArea("");
cmdOut->setText(cmd);
return cmdOut;
}


WWidget* WGMenuForm::createTab(string header) {

	WContainerWidget *tab =  new WContainerWidget();

	if(header == "Command Output") {
	cmdout = new WTextArea(tab);
	cmdout->resize(500,350);
	}

	vector< map<string,string> > parameterMaps;
	vector< map<string,string> > flagMaps;

	pugi::xml_document doc;
    pugi::xml_parse_result tos = doc.load_file(getXML(command));

    pugi::xml_node task = doc.child("task");


	for (pugi::xml_node parameter = task.child("parameter"); parameter; parameter = parameter.next_sibling("parameter")) {

		map<string,string> parameterMap;
		string description = parameter.child_value("description");
		string label = parameter.child_value("label");
		string guisection = parameter.child_value("guisection");
        boost::trim(description);
        boost::trim(label);
        boost::trim(guisection);
		parameterMap["desc"] = description;
		parameterMap["label"] = label;
		parameterMap["guisection"] = guisection;

 			for (pugi::xml_attribute_iterator ait = parameter.attributes_begin(); ait != parameter.attributes_end(); ++ait) {
				string key = ait->name();
				string val =  ait->value();
                boost::trim(key);
                boost::trim(val);
				parameterMap[key] = val;
               // cout << key << "::" << val << endl;
			}
		parameterMaps.push_back(parameterMap);
	}


    for (pugi::xml_node flag = task.child("flag"); flag; flag = flag.next_sibling("flag")) {
		map<string,string> flagMap;
		string guisection = flag.child_value("guisection");
		string label = flag.child_value("description");
        boost::trim(guisection);
        boost::trim(label);
		flagMap["label"] = label;
		flagMap["guisection"]=guisection;


		for (pugi::xml_attribute_iterator ait = flag.attributes_begin(); ait != flag.attributes_end(); ++ait) {
			string key = ait->name();
			string val =  ait->value();
            boost::trim(key);
            boost::trim(val);
			flagMap[key] = val;	
		}
		flagMaps.push_back(flagMap);
    }


	
	for(vector<map<string,string> >::iterator mapit = parameterMaps.begin(); mapit!=parameterMaps.end();++mapit) {

		map<string,string> param = *mapit;
		string label = param["label"];
		string desc  = param["desc" ];

		if( (header == "Required") && (param["required"] == "yes") ) {

			if(!label.empty()) 
				WText *wlabel = new WText(label,tab);	
			else
				WText *wlabel = new WText(desc,tab);	

			new WBreak(tab);		
			WLineEdit *text = new WLineEdit(tab);
			text->setId(param["name"]);
			names.push_back(text->id());
			text->resize(300,20);
			new WBreak(tab);


		} //END if( (header == "Required") && (param["required"] == "yes") )

		else if( (header == param["guisection"])  && (param["required"] == "no") ) {

			if(!label.empty())
				WText *wlabel = new WText(label,tab);	
			else
				WText *wlabel = new WText(desc,tab);	

			new WBreak(tab);		
			WLineEdit *text = new WLineEdit(tab);
			text->setId(param["name"]);
			names.push_back(text->id());
			text->resize(300,20);
/*
stringstream strm;
strm << "alert('" << param["name"] <<"');";
WApplication::instance()->doJavaScript(strm.str());
*/
			new WBreak(tab);

		} //END else if(header == param["guisection"])

	} //END for(vector<map<string,string> >

	for(vector<map<string,string> >::iterator flagit = flagMaps.begin(); flagit!=flagMaps.end();++flagit) {

		map<string,string> flagMap = *flagit;
		string label = flagMap["label"];
		string guisection  = flagMap["guisection" ];
		if(guisection == header) {
			WCheckBox *chkFlag = new WCheckBox(label,tab);
			new WBreak(tab);
			chkFlag->setId(flagMap["name"]);
			flboxes.push_back(chkFlag);
			//chkFlag->checked().connect(this,&WGrass::flagChecked);
		}
		else if( (header == "Optional") && (guisection.empty()) ) {
			WCheckBox *chkFlag = new WCheckBox(label,tab);
			new WBreak(tab);
			chkFlag->setId(flagMap["name"]);
			flboxes.push_back(chkFlag);
			//chkFlag->checked().connect(this,&WGrass::flagChecked);
		}
    } //END for(vector<map<string,string> > 

 

	return tab;

}


const char* WGMenuForm::getXML(std::string program) {

	const char* xml = "xml/temp.xml";
	string data ="--interface-description";
	string out = WRunCommand(program,data);
//cout << out << endl;
	ofstream xmlFile;
	xmlFile.open (xml);
	xmlFile << out;
	xmlFile.close();

	return xml;
}

void WGMenuForm::setupTabs() {
vector<string>guisections;
names.clear();
fl.clear();
flboxes.clear();
	guisections.push_back("Required");
	pgm = command;
	
	pugi::xml_document doc;

    pugi::xml_parse_result tos = doc.load_file(getXML(command));

    pugi::xml_node task = doc.child("task");

	string guisection;

    for (pugi::xml_node parameter = task.child("parameter"); parameter; parameter = parameter.next_sibling("parameter")) {
		guisection = parameter.child_value("guisection");
		boost::trim(guisection);
		for(vector<string>::iterator it = guisections.begin();it!=guisections.end();++it)
			if( (guisection == *it) )
				guisection= "";

			if(!guisection.empty())
			guisections.push_back(guisection);
	}

    for (pugi::xml_node flag = task.child("flag"); flag; flag = flag.next_sibling("flag")) {
		guisection = flag.child_value("guisection");
		boost::trim(guisection);
		for(vector<string>::iterator it = guisections.begin();it!=guisections.end();++it) 
			if(*it == guisection)
				guisection= "";
		if(!guisection.empty())	
			guisections.push_back(guisection);
	}



	guisections.push_back("Optional");
	guisections.push_back("Command Output");


		
	for(vector<WWidget*>::iterator it = tabs.begin();it!=tabs.end();++it) {
		WWidget *widget = *it;
		menuForm->removeTab(widget);
	}

		if(pgm == "v.in.ogr") {

	WContainerWidget *tab = new WContainerWidget();
	new WBreak(tab);
	new WBreak(tab);

	new WText("upload vector data",tab);
	new WBreak(tab);
	upload = new WFileUpload(tab);
	upload->setFileTextSize(40);
	upload->setMultiple(true);
	upload->changed().connect(upload, &WFileUpload::upload);
	//upload->uploaded().connect(this, &WGrass::dataUploaded);
	new WBreak(tab);
	new WBreak(tab);

	new WText("Format",tab);
	new WBreak(tab);
	cmbFormat = new WComboBox(tab);
	cmbFormat->addItem("ESRI Shapefile");
	cmbFormat->addItem("GML");
	new WBreak(tab);
	new WText("output map",tab);
	new WBreak(tab);
	outMap = new WLineEdit(tab);
	outMap->resize(300,20);
	new WBreak(tab);
	menuForm->addTab(tab, "Required");
	WContainerWidget *output = new WContainerWidget();
	cmdout = new WTextArea(output);
	cmdout->resize(500,350);

	menuForm->addTab(output, "Command Output");
	tabs.push_back(tab);
	tabs.push_back(output);
	}
else {
	for(vector<string>::iterator it = guisections.begin();it!=guisections.end();++it){
		WWidget *tab = createTab(*it);
		tabs.push_back(tab);
 		menuForm->addTab(tab, *it);
 	}
}

guisections.clear();
}

