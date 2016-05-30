#include "WGrassLayerManager.h"
#include <Wt/WRandom>
#include <Wt/WRadioButton>


using namespace std;

WGrassLayerManager::WGrassLayerManager()
{

resize(250,480);

 setSelectionMode(SingleSelection);
 //expandToDepth(1);
 setAttributeValue("oncontextmenu","event.cancelBubble = true; event.returnValue = false; return false;");


 model = new WStandardItemModel(0, 1, this);
 model->setHeaderData(0, Horizontal,
				 boost::any(string("Layer Tree")));


setModel(model);



}
WGrassLayerManager::~WGrassLayerManager() { }

/*
void VRLayerTree::createAdminBoundaryTree() {
    vector<string> states;
    LoadData(states,"/var/www/lsi/vrgeo/edit/data",true);
    for(vector<string>::iterator it = states.begin();it!=states.end();it++) {
        stateLayers = baseItem(*it);
        adminLayers->appendRow(stateLayers);
        adminlist.push_back(*it);
        createStateLayersTree(*it);
    }
}

WStandardItem* VRLayerTree::baseItem(WString item) {
  WStandardItem *result = new WStandardItem(item);
  return result;

}
void VRLayerTree::createStateLayersTree(string state) {
    vector<string> dists;
    string path = "/var/www/lsi/vrgeo/edit/data/" + state;
    LoadData(dists,path,false);
    WStandardItem *st = new WStandardItem(state);
    st->setFlags(ItemIsSelectable|ItemIsUserCheckable);
    st->setCheckState(Unchecked);
    stateLayers->appendRow(st);
    for(vector<string>::iterator it = dists.begin();it!=dists.end();it++){
        string dist =*it;
        WStandardItem *district = new WStandardItem(dist);
        district->setFlags(ItemIsSelectable|ItemIsUserCheckable);
        district->setCheckState(Unchecked);
        stateLayers->appendRow(district);
        adminlist.push_back(dist);
    }

}

void VRLayerTree::LoadData(vector<string>& dirs, string path, bool isDir)
{



    show_files(path, dirs,isDir ) ;

    std::sort(dirs.begin(), dirs.end());
    dirs.erase(std::unique(dirs.begin(), dirs.end()), dirs.end());



}

void VRLayerTree::show_files( const fs::path & full_path, vector<string>& directories,bool isDir=true )
{

  unsigned long file_count = 0;
  unsigned long dir_count = 0;
  unsigned long other_count = 0;
  unsigned long err_count = 0;


  if ( fs::is_directory( full_path ) )
  {

    fs::directory_iterator end_iter;
    for ( fs::directory_iterator dir_itr( full_path );
          dir_itr != end_iter;
          ++dir_itr )
    {
      try
      {
        if(isDir) {
            if ( fs::is_directory( dir_itr->status() ) )
                directories.push_back(dir_itr->path().filename());
        }
        else  {

            string fullname = dir_itr->path().filename();

 fs::path path1(fullname.c_str());

string result1 = fs::basename (path1);
        directories.push_back(result1);
//std::cout << "\nFound: " << result1 << "\n";

        }

      }
      catch ( const std::exception & ex )
      {
        ++err_count;
        std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
      }
    }

  }
  else // must be a file
  {
    //std::cout << "\nFound: " << full_path.file_string() << "\n";
  }

}



*/

WStandardItemModel* WGrassLayerManager::GetModel()const {
return model;
}



/*
void VRLayerTree::AddItem(WString item,bool activate) {

WStandardItem *result = new WStandardItem(item);;
result->setCheckable(true);
      result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
      //model->appendRow(result);

}
/*

 void VRLayerTree::showPopup(const WModelIndex& item, const WMouseEvent& event) {
    if (event.button() == WMouseEvent::RightButton) {

      if (!isSelected(item))
	select(item);

     // delete popup_;

      setModelIndex(item);

      popup_ = new WPopupMenu();
      popup_->addItem("New Layer");
      popup_->addItem("Edit Layer");
      popup_->addItem("Remove Layer");
      popup_->addItem("Zoom to layer extent");
      popup_->addItem("Open attribute table");
      popup_->addItem("Properties");



      popup_->aboutToHide().connect(this, &VRLayerTree::popupAction);
      popup_->popup(event);
    }
  }


  void VRLayerTree::popupAction() {
    if (popup_->result()) {

      WString text = popup_->result()->text();
      delete popup_;
      popup_ = 0;
	if(text == "New Layer")
		NewLayer();

	else if(text == "Edit Layer")
		EditLayer();

	else if(text == "Remove Layer")
		RemoveLayer();

	else if(text == "Zoom to layer extent")
        ZoomToAll();

    else if(text == "Open attribute table")
        OpenAttributeTable();


} else {
      delete popup_;
      popup_ = 0;
    }
  }



void VRLayerTree::AddMapToProjectTree(string layername_,string ltype,bool activate=true,bool checked=true) {

   string iurl;





   if(ltype == "MULTIPOLYGON")
      iurl = "icons/mIconPolygonLayer.png";
   else if(ltype == "MULTILINESTRING")
      iurl = "icons/mIconLineLayer.png";
   else if(ltype == "MULTIPOINT")
      iurl = "icons/mIconPointLayer.png";





WStandardItem *result = new WStandardItem(layername_);
result->setIcon(iurl);
result->setCheckable(true);
      result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
      if(checked)
          result->setCheckState(Checked);
      else
          result->setCheckState(Unchecked);

      prjLayers->appendRow(result);
if(activate)
    ActivateControls(result, layername_,ltype);


}

void VRLayerTree::setModelIndex(const WModelIndex& item){
modelIndex = item;
}

WModelIndex VRLayerTree::getModelIndex(){
return modelIndex;
}

void VRLayerTree::NewLayer() {


  std::stringstream strm;



addLayerDialog = new VRAddLayerDialog(project);


}


void VRLayerTree::EditLayer() {

editLayerDialog = new VREditLayerDialog();
  if(editLayerDialog->exec() == WDialog::Accepted)
      editLayerDialog->UpdateTableDefinition();

}

void VRLayerTree::RemoveLayer() {


stringstream strm;


WModelIndex index = getModelIndex();
	string lname;
if(this->isSelected(index))
{
  WStandardItem *layer =  model->itemFromIndex(index);
      lname = layer->text().narrow();

vector<VRGPXLayer *>temp;

temp = baseLayerList;
baseLayerList.clear();
for(vector<VRGPXLayer *>::iterator it = temp.begin();it!=temp.end();++it) {
VRGPXLayer *clayer = *it;
 if(lname.compare(clayer->GetLayerName()) != 0 )
            baseLayerList.push_back(*it);

}


vector<VRPostGisLayer *>temp2;

temp2 = editLayerList;
editLayerList.clear();
for(vector<VRPostGisLayer *>::iterator it = temp2.begin();it!=temp2.end();++it) {
VRPostGisLayer *clayer = *it;
 if(lname.compare(clayer->GetLayerName()) != 0 )
            editLayerList.push_back(*it);

}


//for(vector<VRShapeLayer *>::iterator it = baseLayerList.begin();it!=baseLayerList.end();++it)
//cout << (*it)->GetLayerName() << endl;

if(
    (lname == "Google Streets")     ||
    (lname == "Google Physical")    ||
    (lname == "Google Hybrid")      ||
    (lname == "Google Satellite")   ||
    (lname == "Bing Maps")          ||
    (lname == "OpenStreetMap"))
{
//addbasemap = false;
SetGoogleAdded(false);
}

      strm <<"var lyr = map.getLayersByName(\"" + lname + "\");if(lyr[0]!=undefined){map.removeLayer(lyr[0]);}";
      WApplication::instance()->doJavaScript(strm.str());



        } //end if




   for (int row = 0; row < model->rowCount(); ++row) {
	for (int col = 0; col < model->columnCount(); ++col) {
	  WStandardItem *layer =  model->item(row, col);

		if (layer->text().narrow() == lname )
            model->removeRow(row);

        }

   }




}//end of remove layer


void VRLayerTree::ZoomToAll() {


    WModelIndex index = getModelIndex();
	string lname;
    if(this->isSelected(index)){
        WStandardItem *layer =  model->itemFromIndex(index);
        lname = layer->text().narrow();

        stringstream strm;
        string state, district;
        string extent;
        if(!lname.empty()) {
        VRGPXLayer* lyr =  GetBaseLayerByName(lname);
        if(lyr != NULL) {
            //extent = lyr->getExtent();
        }
        else {
            VRPostGisLayer *lyr = GetEditLayerByName(lname);
            if(lyr!=NULL) {
                extent = lyr->getExtent();
               cout << extent << endl;
            }
            else{
                VRGmlLayer *lyr = GetGmlLayerByName(lname);
              //  if(lyr!=NULL)
                    //extent = lyr->getExtent();
            }
        }
        }

    //cout << extent << endl;

    if(!extent.empty())
        WApplication::instance()->doJavaScript(extent);


    }

}


void VRLayerTree::AppendBaseList(VRGPXLayer *layer) {
baseLayerList.push_back(layer);
}

void VRLayerTree::AppendEditList(VRPostGisLayer *layer) {
editLayerList.push_back(layer);
}




void VRLayerTree::OpenAttributeTable()
{

stringstream strm;

WModelIndex index = getModelIndex();
	string lname;
WStandardItemModel *attrModel;
VRGPXLayer *layer;
if(this->isSelected(index))
{
  WStandardItem *lyrItem =  model->itemFromIndex(index);
      lname = lyrItem->text().narrow();
    for(vector<VRGPXLayer *>::iterator baseIt = baseLayerList.begin();baseIt!=baseLayerList.end();++baseIt) {
       layer = *baseIt;
       if(layer->GetLayerName() == lname) {
           attrModel = layer->GetAttributeModel();
            break;
        }
}

attrDialog = new VRAttributeDialog(layer->GetLayerName(),attrModel);

  if(attrDialog->exec() == WDialog::Accepted)
  {

  }

}


}


void VRLayerTree::SetLayerName(string name) {
layername_ = name;
}
string VRLayerTree::GetLayerName() {
return layername_;
}
VRPostGisLayer* VRLayerTree::GetEditLayerByName(string name) {
    for(vector<VRPostGisLayer *>::iterator layerIt = editLayerList.begin(); layerIt!=editLayerList.end();++layerIt)  {
  //      VRMessageBox::info((*layerIt)->GetLayerName());
        if( (*layerIt)->GetLayerName() == name)
            return (*layerIt);

    }
    return NULL;
}



VRGmlLayer* VRLayerTree::GetGmlLayerByName(string name) {
    for(vector<VRGmlLayer *>::iterator layerIt = gmlLayerList.begin(); layerIt!=gmlLayerList.end();++layerIt)  {
        if( (*layerIt)->GetLayerName() == name)
            return (*layerIt);

    }
    return NULL;
}


VRGPXLayer* VRLayerTree::GetBaseLayerByName(string name) {
    for(vector<VRGPXLayer *>::iterator layerIt = baseLayerList.begin(); layerIt!=baseLayerList.end();++layerIt)  {
        if( (*layerIt)->GetLayerName() == name)
            return (*layerIt);

    }
    return NULL;
}

void VRLayerTree::RemoveAndAddLayer(string name) {


}

bool VRLayerTree::IsGoogleAdded() {
return googleadded;
}

void VRLayerTree::SetGoogleAdded(bool b) {
googleadded= b;
}


void VRLayerTree::NewGPXLayer() {
gpxLayerDialog = new VRGPXLayerDialog();
  if(gpxLayerDialog->exec() == WDialog::Accepted) {

    layername_ = gpxLayerDialog->GetLayerName();


    if(!layername_.empty()) {
    VRGPXLayer * gpx =new VRGPXLayer(layername_,"GPX");

    WStandardItem *result = new WStandardItem(layername_);
    result->setCheckable(true);
          result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
          result->setCheckState(Checked);
          //model->appendRow(result);
       baseLayerList.push_back(gpx);


    }

  }
}

void VRLayerTree::LoadGPXLayer() {
loadGPXDialog = new VRLoadGPXDialog();
  if(loadGPXDialog->exec() == WDialog::Accepted) {

    layername_ = loadGPXDialog->GetLayerName();
    if(!layername_.empty()) {
    VRGPXLayer * gpx =new VRGPXLayer(layername_,"GPX");

      WStandardItem *result = new WStandardItem(layername_);
      result->setCheckable(true);
      result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
      result->setCheckState(Checked);
       model->appendRow(result);
       baseLayerList.push_back(gpx);
    }

  }
}




void VRLayerTree::LoadGmlLayer() {
loadGmlDialog = new VRLoadGmlDialog();
  if(loadGmlDialog->exec() == WDialog::Accepted) {

    layername_ = loadGmlDialog->GetLayerName();
    if(!layername_.empty()) {
    VRGmlLayer * gml =new VRGmlLayer(layername_,"GML","green");

      WStandardItem *result = new WStandardItem(layername_);
      result->setCheckable(true);
      result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
      result->setCheckState(Checked);
      model->appendRow(result);
      gmlLayerList.push_back(gml);
    }

  }
}




void VRLayerTree::LoadTrackLog() {

trackLogDialog = new VRTrackLogDialog();
  if(trackLogDialog->exec() == WDialog::Accepted) {


WStandardItemModel *csvModel = trackLogDialog->csvModel;
WStandardItemModel *csvOriginal = trackLogDialog->csvOriginal;
bool reverse = trackLogDialog->reverse;
string clientfile = trackLogDialog->clientfile;
if(csvModel->rowCount() < 1)
return;

  pugi::xml_document doc;

    //[code_modify_add
    // add node with some name
    pugi::xml_node gpx = doc.append_child("gpx");


gpx.append_attribute("creator") = "LSI http://lsi.iiit.ac.in";
gpx.append_attribute("version") = "1.0";
gpx.append_attribute("xmlns")   = "http://www.topografix.com/GPX/1/0";
gpx.append_attribute("xmlns:xsi")= "http://www.w3.org/2001/XMLSchema-instance";
gpx.append_attribute("xsi:schemaLocation") = "http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd";


    // add description node with text child
    pugi::xml_node trk = gpx.append_child("trk");

    pugi::xml_node name = trk.append_child("name");
    name.append_child(pugi::node_pcdata).set_value("waypoints");


 pugi::xml_node trkseg = trk.append_child("trkseg");






pugi::xml_node trkpt,time,ele;


 for (int row = 0; row < csvOriginal->rowCount(); ++row) {

trkpt =trkseg.append_child("trkpt");
if(reverse==false) {
trkpt.append_attribute("lat") = csvOriginal->item(row, 0)->text().narrow().c_str();
trkpt.append_attribute("lon") = csvOriginal->item(row, 2)->text().narrow().c_str();
}
else {
trkpt.append_attribute("lat") = csvOriginal->item(row, 2)->text().narrow().c_str();
trkpt.append_attribute("lon") = csvOriginal->item(row, 0)->text().narrow().c_str();
}
pugi::xml_node ele = trkpt.append_child("ele");
ele.append_child(pugi::node_pcdata).set_value(csvOriginal->item(row, 4)->text().narrow().c_str());
pugi::xml_node time = trkpt.append_child("time");
time.append_child(pugi::node_pcdata).set_value("2008-07-10T19:17:21Z");

}




string fname = clientfile.substr(0,clientfile.size()-4);

string lowercase = fname;

std::transform(fname.begin(), fname.end(), fname.begin(), ::tolower);


string gpx_filename= "GPX/" + fname + ".gpx";



doc.save_file(gpx_filename.c_str(),"", pugi::format_default & ~pugi::format_indent) ;

    VRGPXLayer * tlog =new VRGPXLayer(fname,"GPX");

      WStandardItem *result = new WStandardItem(fname);
      result->setCheckable(true);
      result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
      result->setCheckState(Checked);
      model->appendRow(result);
       baseLayerList.push_back(tlog);






}

}
void VRLayerTree::NewGMLLayer() {

gmlLayerDialog = new VRGMLLayerDialog();
  if(gmlLayerDialog->exec() == WDialog::Accepted) {

    layername_ = gmlLayerDialog->GetLayerName();


    if(!layername_.empty()) {



    VRGmlLayer* gml =new VRGmlLayer(layername_,"GML","green");

    WStandardItem *result = new WStandardItem(layername_);
    result->setCheckable(true);
          result->setFlags(ItemIsSelectable|ItemIsUserCheckable);
          result->setCheckState(Checked);
          model->appendRow(result);
       gmlLayerList.push_back(gml);


    }

  }
}

void VRLayerTree::NewCsvLayer() {



newCsvDialog = new VRNewCsvDialog(fieldnames);
  if(newCsvDialog->exec() == WDialog::Accepted) {

    layername_ = newCsvDialog->GetLayerName();
//newCsvDialog->cww();

    if(!layername_.empty()) {


    }

  }


}
void VRLayerTree::getFieldNames(string fname){
vector<string> fnames;
Tokenize(fname,fnames,",");

setFieldMap(fnames);
}

vector<string> VRLayerTree::getFieldMap() {
return fieldnames;
}
void VRLayerTree::setFieldMap(vector<string>fmap) {
fieldnames = fmap;
}
*/
