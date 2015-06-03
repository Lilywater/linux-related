#set -x
##for opening the latest created files in some folder
if [ -z "$1" ]
then
 Scope=./
else
 Scope="$1"
fi
echo $Scope
#Files=`find $Scope -name "*.log"|ls -l `

#echo "$Files"
#Files=$(find $Scope -name "*.log"|xargs ls -l | awk '{print $6 "-" $7 "-" $8 " " $9}' |   grep  `ls -tl $Scope |head -2 |awk '{ print $6 "-"  $7 "-"  $8 }' |sed -n '/[^-]/p'` |awk '{print $2}' |sed ':a; N; s/\n/ /; ba')
Files=$(find $Scope -name "*.log"|xargs ls -l | awk '{print $6 "-" $7 "-" $8 " " $9}' |   grep  `ls -tl  |head -2 |awk '{ print $6 "-"  $7 "-"  $8 }' |sed -n '/[^-]/p'`  |awk '{print $2}' |sed ':a; N; s/\n/ /; ba'  )
echo $Files
vim $Files
set +x


