cmake_minimum_required(VERSION 3.0.0)

#工程名
project(utils)

#设置输出路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build_out/Release)

#设置库目录
INCLUDE_DIRECTORIES("$ENV{ZLIB_ROOT}/xp/include") 
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/sdk/pc_win/include)	
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR} )

#link_directories("$ENV{ZLIB_ROOT}/xp/lib")
#生成静态库
aux_source_directory(. SRCS)
ADD_LIBRARY(${PROJECT_NAME} ${SRCS}) 
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} ZLibWrapLib.lib)


