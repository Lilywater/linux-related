/*
 * =====================================================================================
 *
 *       Filename:  cli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/26/2012 06:18:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

 #include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 #include<errno.h>
 
 #include<sys/types.h>
 #include<sys/socket.h>
 #include<unistd.h>//close()
 #include<netinet/in.h>//struct sockaddr_in
 #include<arpa/inet.h>//inet_ntoa
 
 #define DEST_PORT 8003
 #define DEST_IP_ADDRESS "127.0.0.1"
 
 /*客户端的处理过程*/
 void process_info(int s)
 {
         int send_num;
         int recv_num;
         char send_buf[]="tigerjibo";
         char recv_buf[50];
         int count = 0;
//        while(count++ < 30){
           while(1){
                 printf("begin send count %d\n,count",count);
                 send_num = send(s,send_buf,sizeof(send_buf),0);
                 if (send_num < 0){
                         perror("send");
                         exit(1);
                 } else {
                         printf("send sucess:%s\n",send_buf);
                 }
                 printf("begin recv coudnt %d:\n",count);
                 recv_num = recv(s,recv_buf,sizeof(recv_buf),0);
                 if(recv_num < 0){
                         perror("recv");
                         exit(1);
                 } else {
                         recv_buf[recv_num]='\0';
                         printf("recv sucess:%s\n",recv_buf);
                 }
        //         sleep(10);
         }
 }
 int main(int argc,char *argv[])
 {
         int sock_fd;
         struct sockaddr_in addr_serv, cliaddr;//服务器端地址
         socklen_t len = (socklen_t)sizeof(cliaddr);  
         sock_fd = socket(AF_INET,SOCK_STREAM,0);
         if(sock_fd < 0){
                 perror("sock");
                 exit(1);
         } else {
                 printf("sock sucessful:\n");
         }
         memset(&addr_serv,0,sizeof(addr_serv));
         addr_serv.sin_family = AF_INET;
         addr_serv.sin_port =  htons(DEST_PORT);
         addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
        if( connect(sock_fd,(struct sockaddr *)&addr_serv,sizeof(struct sockaddr)) < 0){
                 perror("connect");
                 printf("connect (%d)\n",errno);
                 exit(1);
        } else {
                 printf("connect sucessful\n");
        }
       
       getsockname(sock_fd, (struct sockaddr *) &cliaddr, &len);
        printf("accept a new client,ip:%s and port is %d\n",inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
         process_info(sock_fd);
        // close(sock_fd);
         // shutdown(sock_fd,0);
 }


