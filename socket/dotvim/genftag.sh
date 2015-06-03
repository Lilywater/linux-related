#!/bin/sh 
# (find . -path ./generated -prune  -o -name ".svn" -prune -o -type f -printf "%f\t%p\t1\n" | \
   (echo "!_TAG_FILE_SORTED        2       /2=foldcase/";
     (find . -path ./generated -prune  -o  -name .svn  -prune -o  -type f -printf "%f\t%p\t1;\"\tF\n" | \
         sort -f)) > ./tags


