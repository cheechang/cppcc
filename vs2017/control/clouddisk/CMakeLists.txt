cmake_minimum_required(VERSION 3.0.0)

#
project(clouddisk)
#
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS,5.01 /MANIFEST:NO /DEBUG")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
find_package (Qt5 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR} )
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/log)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sdk/thirdlib/jsoncpp/json)
if(APPLE)
	INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/sdk/pc_mac/include)
	INCLUDE_DIRECTORIES("$ENV{LOG4CPLUS_ROOT_XP}/include")
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Release/)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Debug/)
	endif()
elseif(WIN32)
	INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/sdk/pc_win/include)
	INCLUDE_DIRECTORIES("$ENV{LOG4CPLUS_ROOT_XP}/include")
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Release/)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Debug/)
	endif()
elseif(UNIX)

endif(APPLE)

add_definitions(-DCLOUDDISK_EXPORT)

aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR} SRCS)
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/Common SRCS)
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/Controls SRCS)
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/Interface SRCS)
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/Utils SRCS)

link_directories(${CMAKE_SOURCE_DIR}/sdk/thirdlib/jsoncpp/lib)
link_directories("$ENV{LOG4CPLUS_ROOT_XP}/lib")
#生成动态库
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRCS} ${PROJECT_SOURCE_DIR}/Resources/clouddisk.qrc)

if(APPLE)
#qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)
elseif(WIN32)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} log4cplusS lib_json_md)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})

#qt5_use_modules(${PROJECT_NAME} Core Gui Widgets) 
elseif(UNIX)
#qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)  
endif(APPLE)
 

