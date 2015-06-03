set -x
#get the zip file from the url adress and open ttcn3 files
if [ -z  "$1"  ]
then
echo "please set the url address"
exit
fi

url=`echo $1 |sed -n '/artifact/p'`
if [ ! -z "$url" ]
then
Suf=`date +%m-%d-%H-%M`
echo "$Suf"
ZipFile=archive_$Suf.zip
Dir=archive_$Suf
wget $1/*zip*/archive.zip -O  $ZipFile
  if [ $? -ne 0  ]
  then
   exit
   echo "download zip file fail"
  fi
else
ZipFile=$1.zip
Dir=$1
fi
unzip -d  $Dir  $ZipFile 
cd $Dir 
find . -type f |while read file ; do mv "$file" `echo $file| tr -d ' ' `;  done
vim `find ./ -name "*.TTCN3*"`
set +x
