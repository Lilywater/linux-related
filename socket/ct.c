/*
 * =====================================================================================
 *
 *       Filename:  ct.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/27/2012 05:50:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <stdio.h>
typedef unsigned char uint8_t;       
typedef unsigned short uint16_t;       
void main()

{
   uint8_t cc=0;
 //   uint16_t unicode = "€";  
   printf("a test to unicode is %x", '€');
//   char path[10]= "strace -o ctlog ./cn";
//   execl("/usr/bin/strace", "/usr/bin/strace", "-o", "tlog" ,"./t",NULL);
//   printf("a test to exec");
}

