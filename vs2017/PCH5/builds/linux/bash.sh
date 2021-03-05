#!/bin/bash

echo "Kill the old precess......"
PROCESS=`ps -ef | grep "Linkdood$" | grep -v grep | grep -v PPID|awk '{ print $2}'`
for i in $PROCESS
do
  echo "Kill the linkdood process [ $i ]"
  kill -9 $i
done

PROCESSHTTPD=`ps -ef | grep "linkdoodHttpd$" | grep -v grep | grep -v PPID|awk '{ print $2}'`
for j in $PROCESSHTTPD
do
  echo "Kill the linkdoodHttpd process [ $j ]"
  kill -9 $j
done

PROCESSSCREEN=`ps -ef | grep "screenshot" | grep -v grep | grep -v PPID|awk '{ print $2}'`
for k in $PROCESSSCREEN
do
  echo "Kill the screenshot process [ $k ]"
  kill -9 $k
done

loginNames=`who | awk '{print $1}' | uniq`
for loginName in $loginNames
do
  echo "the loginName [ $loginName ]"
  homeDir=`cat /etc/passwd | grep $loginName | awk -F: '{print $6}'`
  strName=$homeDir/.local/share/Linkdood/Global@vrv
  if [ -f "$strName" ]; then
      rm $homeDir/.local/share/Linkdood/Global@vrv
  fi
done

echo "start replace file......"
#DEBNAME=/home/loongson/桌面/WebChatSetup_1.2.1_all.deb
DEBNAME=$1
TAR_PATH=${DEBNAME%/*}

cd ${TAR_PATH}
tar -xvzf $1

cp -r ${TAR_PATH}/Linkdood/* /opt/Linkdood/
#mv /opt/Vwork/liblddplugin.so* /opt/Vwork/sdkplugins/
#mv /opt/Vwork/config.cfg /opt/Vwork/sdkplugins/
rm -r ${TAR_PATH}/Linkdood

echo "replace finish!"

chmod +x /opt/Linkdood/linkdoodHttpd
nohup /opt/Linkdood/linkdoodHttpd >/dev/null 2>&1 &
/opt/Linkdood/Linkdood


