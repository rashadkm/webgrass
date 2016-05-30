#ifndef _VR_WGrassLayerManager_H_
#define _VR_WGrassLayerManager_H_

#include <Wt/WTreeView>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WModelIndex>
#include <Wt/WPopupMenu>



#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#include <pugixml.hpp>

using namespace Wt;
using namespace std;

namespace fs = boost::filesystem;





class WGrassLayerManager : public WTreeView {

  private:

    WStandardItemModel *model;


    WModelIndex modelIndex;





    string layername_;



    vector<string> baselist;


  public:

    /*! \brief
    Constructor - Creates the LayerTree
    Arguments - VROpenLayers instance used to activate OpenLayers controls.
    */
    WGrassLayerManager();

    /*! \brief
    Default Destructor.
    */
   ~WGrassLayerManager();


    WStandardItemModel* GetModel() const;


/*

    WPopupMenu *popup_;

    WStandardItemModel* GetModel() const;

    void LayerChecked(WStandardItem*);

    void ActivateControls(WStandardItem*,string,string);

    void showPopup(const WModelIndex&, const WMouseEvent&);

    void popupAction();

    void NewLayer();

    void EditLayer();

    void RemoveLayer();

    void ZoomToAll();

    void OpenAttributeTable();

    void setModelIndex(const WModelIndex&);

    WModelIndex getModelIndex();

    void SetModelIndex(string);

    void RemoveAndAddLayer(string);

    void AddItem(WString,bool activate=false);

    string checkAndReturn();

    void SetLayerName(string);

    void CreateShapeFile(string);

    void AddMapToProjectTree(string,string,bool,bool);

    void AppendBaseList(VRGPXLayer*);

    void AppendEditList(VRPostGisLayer*);

    string GetLayerName();

    VRGPXLayer* GetBaseLayerByName(string);

    VRPostGisLayer* GetEditLayerByName(string);

    VRGmlLayer* GetGmlLayerByName(string);

    bool IsGoogleAdded();

    void SetGoogleAdded(bool);

    void NewGPXLayer();

    void NewGMLLayer();

    void LoadGPXLayer();

    void LoadTrackLog();

    void ToggleLayerVisibility(string lname);

    void SetCurrentLayer(string lname);

    void LoadGmlLayer();

	void NewCsvLayer();

	void getFieldNames(string);

	vector<string> getFieldMap();

	void setFieldMap(vector<string>);

   WStandardItem *baseLayers,*adminLayers,*stateLayers, *prjLayers;

   WStandardItem* baseItem(WString item);

   void createAdminBoundaryTree();

   void createStateLayersTree(string);

   void show_files( const fs::path&, vector<string>&,bool );

   void LoadData(vector<string>&,string,bool);

   WStandardItem *prevLyr;

   string getLayerType(string);

   void addGmlLayer(string);
*/


};

#endif
