CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (WebGRASS)
ADD_EXECUTABLE(wgrass.wt
src/WGrass.cpp
src/WGApplication.cpp
src/WOpenLayers.cpp
src/global.cpp
src/main.cpp
src/login.cpp
src/selectLocationAndMapset.cpp
src/WGrassLayerManager.cpp
src/WGrassMenuBar.cpp
src/GMenuItem.cpp
src/WGMenuForm.cpp
)
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#need an actual cmake gdal find package
include_directories("/usr/include/gdal")
FIND_PACKAGE( Wt REQUIRED )
IF (NOT Wt_FOUND)
  MESSAGE (SEND_ERROR "Wt dependency was not found!")
ENDIF (NOT Wt_FOUND)
INCLUDE_DIRECTORIES( ${Wt_INCLUDE_DIR} )
#ADD_DEPENDENCIES(wgrass.wt wt wthttp)
TARGET_LINK_LIBRARIES(wgrass.wt 
${Wt_LIBRARY}
${Wt_HTTP_LIBRARY}
${Wt_EXT_LIBRARY}
boost_filesystem boost_signals boost_system pq /usr/lib/x86_64-linux-gnu/libpugixml.so.1 )

