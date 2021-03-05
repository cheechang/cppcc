#!/bin/bash
mv $1/bin/Linkdood-$2.dmg $1/bin/Linkdood_V$2.dmg
mkdir $1/package-signed
cp $1/bin/*.dmg $1/package-signed/
cp $1/bin/*.dmg /Users/admin/Desktop/jenkins/workspace/h5-mac/