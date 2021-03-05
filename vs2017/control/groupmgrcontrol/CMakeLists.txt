cmake_minimum_required(VERSION 3.0.0)

#工程名
project(groupmgrcontrol)

#预定义宏
ADD_DEFINITIONS(-DCONTROL_EXPORT)

#
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS,5.01 /MANIFEST:NO /DEBUG")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Release/LddPlugins)

#设置包含的库目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} )
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sdk/pc_win/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/clientsdk/include/interface)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/clientsdk/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/log)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/sdk/thirdlib/jsoncpp/json)
INCLUDE_DIRECTORIES("$ENV{LOG4CPLUS_ROOT}/include")

#设置链接库所在目录路径
link_directories(${CMAKE_SOURCE_DIR}/sdk/pc_win/lib)
link_directories(${CMAKE_SOURCE_DIR}/clientsdk/lib)
link_directories(${CMAKE_SOURCE_DIR}/log)
link_directories(${CMAKE_SOURCE_DIR}/build_out/Release)
link_directories(${CMAKE_SOURCE_DIR}/sdk/thirdlib/jsoncpp/lib)
link_directories("$ENV{LOG4CPLUS_ROOT}/lib")

#设置搜索源码
aux_source_directory(. SRCS)
aux_source_directory( ${CMAKE_CURRENT_SOURCE_DIR}/core SRCS)

#生成动态库
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRCS}) 
TARGET_LINK_LIBRARIES(${PROJECT_NAME} log4cplusS  utils)


