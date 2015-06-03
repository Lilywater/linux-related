
BEGIN { FS="" }  
{  
   strleng = length(lpstr) 
 # printf("the val of strleng is %d and str is %s---- \n",strleng,lpstr) 
  if ($NF  == "{")   
  {
   if(strleng)
    {
      lpstr = lpstr  ","  "\n" 
      printf(lpstr);
    }
    printf($0); 
    printf("\n"); 
    lpstr = ""
  }
  else 
  {
   if(strleng)
   { 
    add_comma = 0  
    for(i = 1; i <= NF; i++) {  
           if( $i $(i+1) == ":=") {  
              lpstr = lpstr ","  "\n" 
              printf(lpstr);  
              add_comma = 1  
             break 
          }
         
       } 
    if (!add_comma)
    {
      lpstr = lpstr   "\n" 
      printf(lpstr);
    }
   } 
    lpstr = $0  
   }
}
  

