#! /bin/sh
#参数说明 1.包名 2.生成包路径 3打包版本  4平台信息（fangde是方德 yinhe是银河  zhaoxin是兆芯  longxin是龙芯）
rm     CMakeCache.txt
cp -r bash.sh Linkdood.sh  ../../bin/linux*unpacked
cmake -DCMAKE_BUILD_TYPE=Release -DPRODUCT_NAME=$1 -DPRODUCT_PATH=$2 -DPRODUCT_VERSION=$3 -DPLATFORM_INFO=$4  .

touch $2/unpack.log
make  package -j5 >> $2/unpack.log
