#include <stdio.h>   
#include <string.h>   
#include <malloc.h>   
#include <memory.h>   
#include <wchar.h>  
#include <netinet/in.h>
#ifdef WIN32   
#define uint8_t  unsigned __int8   
#define uint16_t unsigned __int16   
#define uint32_t unsigned __int32   
#define uint64_t unsigned __int64   
  
#define int8_t  __int8   
#define int16_t __int16   
#define int32_t __int32   
  
#endif   
/*typedef unsigned char uint8_t;       
typedef unsigned short uint16_t;      
typedef unsigned long uint32_t;      */
int unicode_to_utf8(uint16_t *in, int insize, uint8_t **out)  
{  
    int i = 0;  
    int outsize = 0;  
    int charscount = 0;  
    uint8_t *result = NULL;  
    uint8_t *tmp = NULL;  
  
    charscount = insize / sizeof(uint16_t);  
    result = (uint8_t *)malloc(charscount * 3 + 1);  
    memset(result, 0, charscount * 3 + 1);  
    tmp = result;  
  
    for (i = 0; i < charscount; i++)  
    {  
        uint16_t unicode = in[i];  
          
        if (unicode >= 0x0000 && unicode <= 0x007f)  
        {  
            *tmp = (uint8_t)unicode;  
            tmp += 1;  
            outsize += 1;  
        }  
        else if (unicode >= 0x0080 && unicode <= 0x07ff)  
        {  
            *tmp = 0xc0 | (unicode >> 6);  
            tmp += 1;  
            *tmp = 0x80 | (unicode & (0xff >> 2));  
            tmp += 1;  
            outsize += 2;  
        }  
        else if (unicode >= 0x0800 && unicode <= 0xffff)  
        {  
            *tmp = 0xe0 | (unicode >> 12);  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 6 & 0x00ff);  
            tmp += 1;  
            *tmp = 0x80 | (unicode & (0xff >> 2));  
            tmp += 1;  
            outsize += 3;  
        }  
  
    }  
  
    *tmp = '\0';  
    *out = result;  
    return 0;  
}  
 int unicode_to_utf8_C(uint32_t in, long long int  *out)  

{  
    int i = 0;  
    int outsize = 0;  
    int charscount = 1;  
    uint8_t *result = NULL;  
    uint8_t *tmp = NULL;  
    tmp = (uint8_t *)out; 
   // charscount = insize / sizeof(uint16_t);  
/*    result = (uint8_t *)malloc(charscount * 3 + 1);  
    memset(result, 0, charscount * 3 + 1);  
    tmp = result;  
  */
      
        uint32_t unicode = in;  
          
        if (unicode >= 0x0000 && unicode <= 0x007f)  
        {  
            *tmp = (uint8_t)unicode;  
            tmp += 1;  
            outsize += 1;  
        }  
        else if (unicode >= 0x0080 && unicode <= 0x07ff)  
        {  
            *tmp = 0xc0 | (unicode >> 6);  
            tmp += 1;  
            *tmp = 0x80 | (unicode & (0xff >> 2));  
            tmp += 1;  
            outsize += 2;  
        }  
        else if (unicode >= 0x0800 && unicode <= 0xffff)  
        {  
            *tmp = 0xe0 | (unicode >> 12);  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 6 & 0x00ff);  
            tmp += 1;  
            *tmp = 0x80 | (unicode & (0xff >> 2));  
            tmp += 1;  
            outsize += 3;  
        }  
  
     
  else if (unicode >= 0x10000 && unicode <= 0x1fffff)  
        {  
            *tmp = 0xf0 | (unicode >> 18);  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 12 & (0xff >>2));  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 6 & (0xff>>2));  
            tmp += 1;  
            *tmp = 0x80 | (unicode  & (0xff >> 2));  
            tmp += 1;  
            outsize += 4;  
        }  
        else if (unicode >= 0x200000 && unicode <= 0x3ffffff)  
        {  
            *tmp = 0xf8 | (unicode >> 24);  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 18 & (0xff >>2));  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 12 & (0xff >>2));  
            tmp += 1;  
            *tmp = 0x80 | (unicode >> 6 & (0xff>>2));  
            tmp += 1;  
            *tmp = 0x80 | (unicode  & (0xff >> 2));  
            tmp += 1;  
            outsize += 4;  
        }  


      else if (unicode >= 0x4000000 && unicode <= 0x7fffffff)
        {
            *tmp = 0xfc | (unicode >> 24);
            tmp += 1;
            *tmp = 0x80 | (unicode >> 18 & (0xff >>2));
            tmp += 1;
            *tmp = 0x80 | (unicode >> 12 & (0xff >>2));
            tmp += 1;
            *tmp = 0x80 | (unicode >> 6 & (0xff>>2));
            tmp += 1;
            *tmp = 0x80 | (unicode  & (0xff >> 2));
            tmp += 1;
            outsize += 5;
        }      

  
    *tmp = '\0';  
  //  *out = result;  
    return 0;  
} 
int utf8_to_unicode(uint8_t *in, uint16_t **out, int *outsize)  
{  
    uint8_t *p = in;  
    uint16_t *result = NULL;  
    int resultsize = 0;  
    uint8_t *tmp = NULL;  
  
    result = (uint16_t *)malloc(strlen(in) * 2 + 2); /* should be enough */  
    memset(result, 0, strlen(in) * 2 + 2);  
    tmp = (uint8_t *)result;  
  
    while(*p)  
    {  
        if (*p >= 0x00 && *p <= 0x7f)  
        {  
            *tmp = *p;  
            tmp++;  
            *tmp = '\0';  
            resultsize += 2;  
        }  
        else if ((*p & (0xff << 5))== 0xc0)  
        {  
            uint16_t t = 0;  
            uint8_t t1 = 0;  
            uint8_t t2 = 0;  
  
            t1 = *p & (0xff >> 3);  
            p++;  
            t2 = *p & (0xff >> 2);  
  
            *tmp = t2 | ((t1 & (0xff >> 6)) << 6);//t1 >> 2;   
            tmp++;  
  
            *tmp = t1 >> 2;//t2 | ((t1 & (0xff >> 6)) << 6);   
            tmp++;  
  
            resultsize += 2;  
        }  
        else if ((*p & (0xff << 4))== 0xe0)  
        {  
            uint16_t t = 0;  
            uint8_t t1 = 0;  
            uint8_t t2 = 0;  
            uint8_t t3 = 0;  
  
            t1 = *p & (0xff >> 3);  
            p++;  
            t2 = *p & (0xff >> 2);  
            p++;  
            t3 = *p & (0xff >> 2);  
  
            //Little Endian   
            *tmp = ((t2 & (0xff >> 6)) << 6) | t3;//(t1 << 4) | (t2 >> 2);   
            tmp++;  
  
            *tmp = (t1 << 4) | (t2 >> 2);//((t2 & (0xff >> 6)) << 6) | t3;   
            tmp++;  
            resultsize += 2;  
        }  
  
        p++;  
    }  
  
    *tmp = '\0';  
    tmp++;  
    *tmp = '\0';  
    resultsize += 2;  
  
    *out = result;  
    *outsize = resultsize;   
    return 0;  
}  
  

void dump_utf8(uint8_t *utf8)  
{  
    uint8_t *p = utf8;  
    int i = 0;
    char strarr[20];
    while(*p)  
    {  
      //  printf("%02X", *p);  
        sprintf(&strarr[i],"%02X", *p);  
        p++;  
        i+=2;
    } 
      for (i=0; i< 10; i++)
        printf("str ele is %c\n", strarr[i]);  
       printf("the str is %s", strarr);  
   // putchar('\n');  
}  
  
void dump_unicode(uint16_t *utf16, int size)  
{  
    uint8_t *p = (uint8_t *)utf16;  
    int i = 0;  
  
    for (i = 0; i < size; i++)  
    {  
        printf("%02X", *p);  
        p++;  
    }  
    putchar('\n');  
}  
  
int main()  
{  
 //   uint16_t unicode[] = L"€";  
//    uint16_t unicodec = (uint16_t)'€';  
 //   uint16_t unicode[32] = {unicodec};  
    uint16_t unicode[] = {0x20AC,0xA2};  
    uint8_t *utf8 = NULL;  
  
    int unisize = 0;  
    uint16_t *uni = NULL;  
   // uint32_t varray = 0; 
   long long int varray = 0; 
    //uint32_t uchar = {0x20AC};   
   // uint32_t uchar = 0x20AC;   
    uint32_t uchar = 0x24B62;
    printf("original unicode: \n");  
    dump_unicode(unicode, sizeof(unicode));  
     

   unicode_to_utf8_C(uchar,&varray);
    dump_utf8((uint8_t *)(&varray));  
        printf(" conver to int is %08X\n",varray );  
        printf("htonl conver to int is %08X\n",htonl(varray) );  
        printf("size of long long int is %d",sizeof(long long int) );  
  //  printf("converted to utf8: \n");  
 //   unicode_to_utf8(unicode, sizeof(unicode), &utf8);  
  //  dump_utf8(utf8);  
  
/*    printf("converted to unicode: \n");  
    utf8_to_unicode(utf8, &uni, &unisize);  
    dump_unicode(uni, unisize);  
  */
    free(utf8);  
    free(uni);  
  
    return 0;  
}  

