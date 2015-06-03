
/*
 * =====================================================================================
 *
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/16/2012 02:01:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#define SERV_PORT 9877
#define INADDR_ANY "127.0.0.1"
#include <sys/socket.h>	
 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<errno.h>


 #include<sys/types.h>
 #include<sys/socket.h>
 #include<unistd.h>//close()
 #include<netinet/in.h>//struct sockaddr_in
 #include<arpa/inet.h>//inet_ntoa
#define SA  struct sockaddr 
#define MAXLINE 100
void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
int	n; //
socklen_t len; //,  clilen
char	mesg[MAXLINE];
struct sockaddr_in caddr; //IPv4
for ( ; ; ) {
len = clilen;
/*  */
n = recvfrom(sockfd, mesg, MAXLINE, 0, (SA*)&caddr, &len);
 printf("get %d bytes a new client,ip:%s and port is %d\n",n,inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
//printf("receive from %d bytes the the peer \n",n);
/*  */
//sendto(sockfd, mesg, n, 0, pcliaddr, len);
sendto(sockfd, mesg, n, 0,(SA *) &caddr, len);
printf("send %d bytes the the peer \n",n);
}
}
int main(int argc, char **argv)
{
int	sockfd; //
struct sockaddr_in servaddr, cliaddr; //IPv4
sockfd = socket(AF_INET, SOCK_DGRAM, 0); //UDP
bzero(&servaddr, sizeof(servaddr)); //
servaddr.sin_family = AF_INET; //IPv4
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//
servaddr.sin_port = htons(SERV_PORT); //9877 
/*,*/
bind(sockfd, (SA *) &servaddr, sizeof(servaddr)); 
/* */
dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
}


