#!/bin/bash
#make -f MakefileCutTime SCOPE=verify -j3 auto_gen 1>11 2>erlog &
#tail -F erlog
echo "PWD is $PWD \n"
rootpath=`echo "$PWD"|sed 's/\(.*MME_SGSN_tester\).*/\1/'`
echo "the rootpath is $rootpath\n"
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*function[[:space:]]\+\(\w\+\).*/\3\t\1\t\2;"\tf/' 
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*type[[:space:]]\+[^[:space:]]\+[[:space:]]\+\(\w\+\).*/\3\t\1\t\2;"\tf/'
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*template[[:space:]]\+[^[:space:]]\+[[:space:]]\+\(\w\+\).*/\3\t\1\t\2;"\tf/'
  

grep 'type[[:space:]]\+.*[[:space:]]\+of' tags_ttcn_type > /tmp/ts
sed -i '/type[[:space:]]\+.*[[:space:]]\+of/d' 
sed 's/type\s\+.*\s\+\(\w\+\)\W*$/\1/'
