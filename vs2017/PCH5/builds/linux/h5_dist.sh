#!/bin/bash
#编译
#参数说明1源码路径2打包类型xp版本 还是标准版

cp -r $1/vrv-static $1/node_modules/vrv-static
rm -rf $1/node_modules/vrv-static/lib/vimsdk/darwin
rm -rf $1/node_modules/vrv-static/lib/vimsdk/darwin
cd $1
yarn dist:dir
