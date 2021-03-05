cmake_minimum_required(VERSION 3.0.0)

#
project(screenshot)

#
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)

#
if(WIN32)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Release)
	elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Debug)
	endif()
elseif(APPLE)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/bin)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'" )
elseif(UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/bin)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'" )
endif(WIN32)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


#
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/ )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/sdk/pc_win/include )
#
aux_source_directory(. SRCS)
link_directories(${EXECUTABLE_OUTPUT_PATH})
#
if(APPLE)
	add_executable(${PROJECT_NAME} ${SRCS} res.qrc ${CMAKE_CURRENT_SOURCE_DIR}/screenshot.rc)
elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SRCS} res.qrc ${CMAKE_CURRENT_SOURCE_DIR}/screenshot.rc)
elseif(UNIX)
	add_executable(${PROJECT_NAME} ${SRCS} res.qrc ${CMAKE_CURRENT_SOURCE_DIR}/screenshot.rc)
endif(APPLE)
#
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets Qml Quick )  

TARGET_LINK_LIBRARIES(${PROJECT_NAME} utils)

#add_custom_command(TARGET screenshot POST_BUILD COMMAND install_name_tool  -rpath  $ENV{QTLIB} @executable_path/../Frameworks ${PROJECT_SOURCE_DIR}/../build_out/bin/screenshot COMMENT "screenshot-comment")




