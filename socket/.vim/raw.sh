set -x
if [ -z "$1"  ]
then
echo "the file name should be given"
exit
fi
##source file contain 00000: 01 02 09
 sed  's/.*:\(.*\)/\1/' $1 |sed ':a;N;s/\n//g; s/ //g;  ba' |sed ':a;N;s/\n//g; s/ //g;  ba' |sed "s/^/'/" |sed "s/$/'O/" > $1.raw  
# sed ':a;N;s/\n//g; s/ //g;  ba' dd |sed ':a;N;s/\n//g; s/ //g;  ba'
set +x
