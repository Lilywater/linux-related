#adding some := and , in log message for template usage
#sed '/,$/ {N; s/,\n\([[:space:]]*\)}/\n\1}/; }' cc
#sed ' :a; N; s/,\n\([[:space:]]*\)}/\n\1}/g;ba'
#sed 's/<< omit >>/omit/g' cl
BEGIN { FS="" }
{
  ig = 0;
  coma =1;
    for(i = 1; i <= NF; i++) {
    if ($i  == "{") {
       coma =0;
     }
    if($i != " ")
     {
       ig =1  
     }     
    if(ig==1 && $i == " ")
     {
       printf(":=")
       ig=0
     }     
   printf($i)
  }
    if(coma)
    {printf(",")}
    printf("\n")
}

