set -x
###this is for copying all files in a svn and all .svn folders in a project folder, will rule out many intermediate files
#if [ -z "$1"  ]
#then
#echo "the file name should be given"
#exit
#fi

rm -rf /tmp/zt*
CPT=`pwd`
find ./ -name ".svn" |sed 's#./##' >> /tmp/zt2
ADI=`echo $CPT | awk -F "/" '{print $NF}'`
for i in `cat /tmp/zt2`
do
echo "$i/entries"
sed -n  '/<entry/,/\/>/ {p }  '  "$i/entries" >/tmp/zt
#sed -n  '/<entry/,/\/>/ {p }  '  "$1" >/tmp/zt
sed '/<entry/,/\/>/ {:a; /\/>/! N; s/\n/###/; /\/>/n; ba }; ' /tmp/zt |sed '/kind=\"dir/d' >/tmp/zt1
sed -i 's/.*name=\"\([^"]\+\)\".*$/\1/' /tmp/zt1
CPI=`echo $i |sed 's/\.svn$//' `
sed -i "s#^#$CPI#" /tmp/zt1
#sed -i '$d' /tmp/zt1
sed -i 's#^/[^/]\+/[^/]\+/[^/]\+/##g' /tmp/zt1
#echo "$i" |sed "s/^/$ADI\//" >>/tmp/zt3
echo "$i"  >>/tmp/zt3
cat /tmp/zt1 >> /tmp/zt3
done
#sed -i "s/^/$ADI\//" /tmp/zt2
#cat /tmp/zt2  >>/tmp/zt3
set +x
