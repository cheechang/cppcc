#!/bin/bash
rm -rf $1/vrv-static/lib/vimsdk/win32
rm -rf $1/vrv-static/lib/vimsdk/linux
cp -R $1/vrv-static $1/node_modules/
rm -rf $1/node_modules/vrv-static/lib/vimsdk/win32
rm -rf $1/node_modules/vrv-static/lib/vimsdk/linux
cp -R $1/vrv-robotjs $1/node_modules/
cd $1
export PATH=$PATH:/Users/admin/.yarn/bin:/usr/local/bin:/usr/bin
yarn dist