cmake_minimum_required (VERSION 2.8)

project (WebGRASS)


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set( GRASS_DATA_DIR "$ENV{HOME}/grassdata" CACHE PATH "Location of grassdata directory. Default is $HOME/grassdata")

find_package( Wt REQUIRED )
if (NOT Wt_FOUND)
  message (FATAL_ERROR "Wt dependency was not found!")
endif (NOT Wt_FOUND)
include_directories( ${Wt_INCLUDE_DIR} )

find_package( Boost REQUIRED
  QUIET
  1.35.0
  COMPONENTS filesystem signals system
  )
include_directories( ${Boost_INCLUDE_DIRS} )


find_path(PUGIXML_INCLUDE_DIR NAMES pugixml.hpp)
find_library(PUGIXML_LIBRARY NAMES pugixml)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set( GRASS_DATA_DIR "$ENV{HOME}/grassdata" CACHE PATH "Location of grassdata directory. Default is $HOME/grassdata")

SET(GCC_COVERAGE_LINK_FLAGS "-lgdal")
#relpace GRASS_INSTALL_DIR with find_program(g.gisenv)
set( GRASS_INSTALL_DIR "/usr/lib/grass70" CACHE PATH "Location of grass install directory. Default is /usr/lib/grass70")

set( GISRC_FILE "$ENV{HOME}/.grass7/rc" CACHE PATH "Location of grass rc file. Default is $ENV{HOME}/.grass7/rc")

configure_file(${CMAKE_SOURCE_DIR}/wgrassconfig.h.in
  ${CMAKE_BINARY_DIR}/wgrassconfig.h @ONLY
  )

configure_file(${CMAKE_SOURCE_DIR}/scripts/init_grass.sh.in
  ${CMAKE_BINARY_DIR}/init_grass.sh @ONLY
  )

configure_file(${CMAKE_SOURCE_DIR}/scripts/start_webgrass.sh.in
  ${CMAKE_BINARY_DIR}/start_webgrass.sh @ONLY
  )

add_definitions(${GCC_COVERAGE_LINK_FLAGS})

add_executable(wgrass.wt
src/MainUI.cpp
src/WGApplication.cpp
src/main.cpp
src/LayerManager.cpp
src/Display.cpp
src/Toolbar.cpp
src/Startup.cpp
src/Module.cpp
src/Parameter_text.cpp
src/Parameter.cpp
src/Authentication.cpp
)

target_link_libraries(wgrass.wt
  ${Wt_LIBRARY} ${Wt_HTTP_LIBRARY}
  ${Boost_LIBRARIES}
  ${PUGIXML_LIBRARY}
 )

configure_file(
  ${CMAKE_SOURCE_DIR}/wgrassconfig.h.in
  ${CMAKE_BINARY_DIR}/wgrassconfig.h @ONLY
  )

include_directories( ${CMAKE_BINARY_DIR} )
include_directories(${CMAKE_SOURCE_DIRECTORY}/thirdparty/pstream.h)

message(STATUS "GRASS_DATA_DIR=${GRASS_DATA_DIR}")
#aptitude install libwt-dev libwthttp-dev libwtdbo-dev libwtdbosqlite-dev
#aptitude install libboost-system-dev libboost-singals-dev libboost-filesystem-dev
#aptitude install libpugixml-dev