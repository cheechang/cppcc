ssh -p 10022 builder@172.16.8.9 mkdir /data/packages/client/pcr/comm/%1
scp -P 10022 *.exe  *.yml builder@172.16.8.9:/data/packages/client/pcr/comm/%1
ssh -p 10022 builder@172.16.8.9 chmod  -R 777 /data/packages/client/pcr/comm/%1
pause