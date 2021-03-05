cmake_minimum_required(VERSION 3.0.0)

#工程名
project(updatecontrol)
ADD_DEFINITIONS(-DCONTROL_EXPORT)

#
if(WIN32)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS,5.01 /MANIFEST:NO /DEBUG")    
endif(WIN32)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Release/LddPlugins)

#设置包含的库目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/clientsdk/include/interface)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/clientsdk/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/log)
if(WIN32)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sdk/thirdlib/jsoncpp/json)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sdk/pc_win/include)
    INCLUDE_DIRECTORIES("$ENV{LOG4CPLUS_ROOT}/include")
elseif(UNIX)  
    INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/sdk/pc-linux/${LINUX_PROCESS_LIBRARY_DIR}/include)	
endif()

#设置链接库所在目录路径
link_directories(${CMAKE_SOURCE_DIR}/clientsdk/lib)
#link_directories(${CMAKE_SOURCE_DIR}/log)
link_directories(${CMAKE_SOURCE_DIR}/build_out/Release)
if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/sdk/pc_win/lib)
    link_directories(${CMAKE_SOURCE_DIR}/sdk/thirdlib/jsoncpp/lib)
    link_directories("$ENV{ZLIB_ROOT}/xp/lib")
    link_directories("$ENV{LOG4CPLUS_ROOT}/lib")
elseif(UNIX)
    link_directories(${CMAKE_SOURCE_DIR}/sdk/pc-linux/${LINUX_PROCESS_LIBRARY_DIR}/lib)
endif()

#设置搜索源码
aux_source_directory(. SRCS)
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/core SRCS)

#生成动态库
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRCS}) 
if(WIN32)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} log4cplusS utils lib_json_md)
elseif(UNIX)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME}  utils jsoncpp.a)
endif()

