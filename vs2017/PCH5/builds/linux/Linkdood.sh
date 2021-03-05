cd /opt/Linkdood
export LD_LIBRARY_PATH=./resources/app/node_modules/vrv-static/lib/vimsdk/linux/:$LD_LIBRARY_PATH
export LD_PRELOAD=./resources/app/node_modules/vrv-static/lib/vimsdk/linux/libcrypto.so.1.1
export LD_PRELOAD=./resources/app/node_modules/vrv-static/lib/vimsdk/linux/libssl.so.1.1
./Linkdood
