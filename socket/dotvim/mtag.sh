set -x
###for debug command
# -printf '-d %p '
#gdb `find srcdir -type d -printf '-d %p\n'` prog
#find ~/ttcn/ttcn3libs \( -name  generated -o  -name .svn \)  -prune -o  \( -name "*.c"  -o  -name "*.h" -o  -name "*.cpp"   \) -printf '-d %p\n' >flist
#sed 's/^\(.*\)\/.*$/\1/' flist |sort  |uniq |sed  '/[[:space:]]\+/d'
###final
#find ~/ttcn/ttcn3libs \( -name  generated -o  -name .svn \)  -prune -o  \( -name "*.c"  -o  -name "*.h" -o  -name "*.cpp"   \) -printf '-d %p\n' |sed 's/^\(.*\)\/.*$/\1/' |sort  |uniq |sed  '/^-d[[:space:]].*[[:space:]]\+/d'
#gdb `find ~/ttcn/ttcn3libs \( -name  generated -o  -name .svn \)  -prune -o  \( -name "*.c"  -o  -name "*.h" -o  -name "*.cpp"   \) -printf '-d %p\n' |sed 's/^\(.*\)\/.*$/\1/' |sort|uniq|sed '/^-d[[:space:]].*[[:space:]]\+/d'`
##find ~/ttcn/ttcn3libs \( -name  generated -o  -name .svn \)  -prune -o  \( -name "*.c"  -o  -name "*.h" -o  -name "*.cpp"   \) -printf 'dir %p\n' |sed 's/^\(.*\)\/.*$/\1/' |sort  |uniq |sed  '/^dir[[:space:]].*[[:space:]]\+/d'


#if [ -z "$1"  ]
#then
#echo "the default directory is ~/ttcn/MME_SGSG_tester"
#
#TESTER_DIR=~/ttcn/MME_SGSN_tester/
#else 
#
#TESTER_DIR="$1"
#
#fi
TESTER_DIR=`echo "$PWD"|sed 's/\(.*MME_SGSN_tester\).*/\1/'`

FUN_TAG=tags_ttcn
TEMP_TAG=tags_ttcn_temp 
TYPE_TAG=tags_ttcn_type 

ctags -R --extra=f  --exclude=generated 
ctags -a --exclude=generated --extra=f -R ~/ttcn/ttcn3libs
ctags -a --exclude=generated --extra=f -R ~/ttcn/TBPT

#
grep -nH -r  -e  "^[[:space:]]*function[[:space:]]*[^[:space:]]\+[[:space:]]*("   --include=*.ttcn $TESTER_DIR  >$TESTER_DIR/$FUN_TAG
# grep -r -nH -e  "^[[:space:]]*template[[:space:]]\+[^[:space:]]\+[[:space:]]\+[^[:space:]]\+"  --include=*.ttcn  $TESTER_DIR |grep -v -e ',' -e ')' -e '=' >$TESTER_DIR/$TEMP_TAG
grep -r -nH -e  "^[[:space:]]*template[[:space:]]\+[^[:space:]]\+[[:space:]]\+[^[:space:]]\+"  --include=*.ttcn  $TESTER_DIR  >$TESTER_DIR/$TEMP_TAG
#
#grep -r -nH -e "^[[:space:]]*type[[:space:]]\+[^[:space:]]\+[[:space:]]\+[^[:space:]]\+" --include=*.ttcn  $TESTER_DIR >$TESTER_DIR/$TYPE_TAG

grep -r -nH -e  "^[[:space:]]*type[[:space:]]\+\w\+[[:space:]]\+\w\+"  --include=*.ttcn  $TESTER_DIR >$TESTER_DIR/$TYPE_TAG
#
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*function[[:space:]]\+\(\w\+\).*/\3\t\1\t\2;"\tf/' $TESTER_DIR/$FUN_TAG >>tags
# 
#
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*template[[:space:]]\+[^[:space:]]\+[[:space:]]\+\(\w\+\).*/\3\t\1\t\2;"\tf/' $TESTER_DIR/$TEMP_TAG >>tags
#


grep 'type[[:space:]]\+.*[[:space:]]\+of' $TESTER_DIR/$TYPE_TAG > /tmp/ts
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*type\s\+.*\s\+\(\w\+\)\W*$/\3\t\1\t\2;"\tf/' /tmp/ts >>tags
sed  '/type[[:space:]]\+.*[[:space:]]\+of/d'  $TESTER_DIR/$TYPE_TAG  >/tmp/tc
sed 's/\(.*\):\([[:digit:]]\+\):[[:space:]]*type[[:space:]]\+[^[:space:]]\+[[:space:]]\+\(\w\+\).*/\3\t\1\t\2;"\tf/'  /tmp/tc >>tags
mv tags tags_unsort
grep -i "f$" tags_unsort  > tags
#sed -i  '/[^f]$/d' ./tags
 
find ./ -name "*.ttcn" -type f -printf "%f\t%p\t1;\"\tF\n" >>tags 
mv tags tags_unsort
sort tags_unsort > tags

#this is for svn repo file list
cd $TESTER_DIR
svn status -v  >/tmp/fl_svn
grep -v '^?' /tmp/fl_svn  >/tmp/fl_svn_cl
sed  's/.*[[:space:]]\+\([^[:space:]]\+\)$/\1/' /tmp/fl_svn_cl >.svn/flist
cd - 
set +x
