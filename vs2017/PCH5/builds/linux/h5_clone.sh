#!/bin/bash

#参数说明 1源码路径 2版本号 3版本号的第四位 4.mark值 5.svnaddresskey值  6打包类>型 xp版本 还是标准版 7deviceinfo linux-xxx linux各个版本

echo $1
cd  $1

sed -i -r 's/(version").*"/\1: "'$2'"/' package.json 
sed -i -r 's/(deviceInfo").*"/\1: "'$7'"/' package.json 

sed -i "s/deviceInfo: this.platform.platforminfo().deviceInfo/deviceInfo: '$7'/g" src/main/SDKService.js



#yarn

