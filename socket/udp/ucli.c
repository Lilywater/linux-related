/*
 * =====================================================================================
 *
 *       Filename:  userv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/16/2012 02:02:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */



 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<errno.h>


 #include<sys/types.h>
 #include<sys/socket.h>
 #include<unistd.h>//close()
 #include<netinet/in.h>//struct sockaddr_in
 #include<arpa/inet.h>//inet_ntoa

#define MAXLINE 100
#define SERV_PORT 9877
#define SA  struct sockaddr 

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
int	 n; socklen_t	 len;
char	 sendline[MAXLINE], recvline[MAXLINE + 1];
struct sockaddr_in	reply_addr; //?? (??)????
//struct sockaddr	*preply_addr; //?? (??)????
//preply_addr = Malloc(servlen); //??????
while (fgets(sendline, MAXLINE, fp) != NULL) {
sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
len = servlen; 
n = recvfrom(sockfd, recvline, MAXLINE, 0, (SA *)&reply_addr, &len);
//if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {

//getsockname(sockfd, (SA *) &reply_addr, &len);
 printf("get %d bytes a new client,ip:%s and port is %d\n",n,inet_ntoa(reply_addr.sin_addr), ntohs(reply_addr.sin_port));
//printf("reply from %s (ignored)\n", sock_ntop(preply_addr, len) ); 
//continue; 
//}
recvline[n] = 0;	/* null terminate */
fputs(recvline, stdout);
}
}

int main(int argc, char **argv)
{
int	sockfd;
unsigned int	 len;
struct sockaddr_in	cliaddr, servaddr;
if (argc != 2)// err_quit("usage: udpcli <IPaddress>");
{
printf("usage: udpcli <IPaddress>\n");
exit(1);
}
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//bzero(&servaddr, sizeof(servaddr));
memset(&servaddr, 0,sizeof(servaddr)); 
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(SERV_PORT);
inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
/*connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
len = sizeof(cliaddr);
getsockname(sockfd, (SA *) &cliaddr, &len);
 printf("accept a new client,ip:%s and port is %d\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
exit(0);*/
dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));
}
