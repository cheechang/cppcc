#!/bin/bash
cd $1
sed -i "" 's/\("version": "\).*/\1'"$2"'",/g' package.json
export PATH=$PATH:/Users/admin/.yarn/bin:/usr/local/bin:/usr/bin
yarn