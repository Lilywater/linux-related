/*
 * =====================================================================================
 *
 *       Filename:  serv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/26/2012 06:17:52 PM
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
 #define  QUEUE_LINE  12
 #define  SOURCE_PORT 8003
 
 #define  SOURCE_IP_ADDRESS "127.0.0.1"
 
 void process_info(int s)
 {
         int recv_num;
         int send_num;
         char recv_buf[50];
         char send_buf[50];
         int count = 0;
         while(count++ <30){
                 printf("begin recv count: %d\n",count);
                 recv_num = recv(s,recv_buf,sizeof(recv_buf),0);
                 if(recv_num <0){
                         perror("recv");
                         exit(1);
                 } else {
                         recv_buf[recv_num] = '\0';
                         printf("recv sucessful:%s\n",recv_buf);
                 }
                 sprintf(send_buf,"recv %d numbers bytes\n",recv_num);
                 printf("begin send count %d\n",count);
                 send_num = send(s,send_buf,sizeof(send_buf),0);
                 if (send_num < 0){
                         perror("sned");
                         exit(1);
                 } else {
                         printf("send sucess\n");
                 }
         }
 }
 int main()
 {
         int sock_fd,conn_fd;
         int client_len;
         pid_t pid;
         struct sockaddr_in addr_serv,addr_client;
         sock_fd = socket(AF_INET,SOCK_STREAM,0);
         if(sock_fd < 0){
                 perror("socket");
                 exit(1);
         } else {
                 printf("sock sucessful\n");
         }
         //初始化服务器端地址
         memset(&addr_serv,0,sizeof(addr_serv));
         addr_serv.sin_family = AF_INET;
         addr_serv.sin_port = htons(SOURCE_PORT);
         addr_serv.sin_addr.s_addr =inet_addr(SOURCE_IP_ADDRESS);
         client_len = sizeof(struct sockaddr_in);
         if(bind(sock_fd,(struct sockaddr *)&addr_serv,sizeof(struct sockaddr_in))<0){
                 perror("bind");
                 exit(1);
         } else {
                 printf("bind sucess\n");
         }
         if (listen(sock_fd,QUEUE_LINE) < 0){
                 perror("listen");
                 exit(1);
         } else {
                 printf("listen sucessful\n");
         }
       //  while(1){
                  printf("begin accept:\n");
                  conn_fd = accept(sock_fd,(struct sockaddr *)&addr_client,&client_len);

                  if(conn_fd < 0){
                         perror("accept");
                         exit(1);
                  }
                  printf("accept a new client,ip:%s\n",inet_ntoa(addr_client.sin_addr));
         /*         pid = fork();
                  if(0 == pid){         //子进程
                         close(sock_fd);//在子进程中关闭服务器的侦听
                         process_info(conn_fd);//处理信息
                  } else {
                         close(conn_fd);//在父进程中关闭客户端的连接
                  }*/
                 close(sock_fd);//在子进程中关闭服务器的侦听
                 process_info(conn_fd);//
               //  close(conn_fd);
        // }
 
 }


