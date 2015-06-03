/*
 * =====================================================================================
 *
 *       Filename:  t.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/26/2012 06:24:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#define MDE 6
#include <stdio.h>
main()
{
 char *pn =0x222;
int cc =0;
 cc = cc + MDE;
 printf("prepare to read violation address\n");  
printf("hello, world, %s",pn);
}
