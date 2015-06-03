/*
 * =====================================================================================
 *
 *       Filename:  scc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2013 10:57:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define RECVBUFSIZE     4096
#define PPID            1234
#define MAXLINE    60
int main()
{
       int SctpScocket, in, flags;
       socklen_t opt_len;
       char * szAddress;
       int iPort;
       char * szMsg;
       int iMsgSize;
       char a[1024];

    
       struct sockaddr_in servaddr = {0};
       struct sctp_status status = {0};
       struct sctp_sndrcvinfo sndrcvinfo = {0};
       struct sctp_event_subscribe events = {0};
       struct sctp_initmsg initmsg = {0};
       char * szRecvBuffer[RECVBUFSIZE + 1] = {0};
       socklen_t from_len = (socklen_t) sizeof(struct sockaddr_in);
       char sendline[MAXLINE];

       //get the arguments
       szAddress = "127.0.0.1";
       iPort = 5001;
      
       printf("Starting SCTP client connection to %s:%u\n", szAddress, iPort);

     
       SctpScocket = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
       printf("socket created...\n");

       //set the association options
       initmsg.sinit_num_ostreams = 3;
       setsockopt( SctpScocket, IPPROTO_SCTP, SCTP_INITMSG, &initmsg,sizeof(initmsg));
       printf("setsockopt succeeded...\n");

       bzero( (void *)&servaddr, sizeof(servaddr) );
       servaddr.sin_family = AF_INET;
       servaddr.sin_port = htons(iPort);
       servaddr.sin_addr.s_addr = inet_addr( szAddress );

      
       connect( SctpScocket, (struct sockaddr *)&servaddr, sizeof(servaddr));
       printf("connect succeeded...\n");

       //check status
       opt_len = (socklen_t) sizeof(struct sctp_status);
       getsockopt(SctpScocket, IPPROTO_SCTP, SCTP_STATUS, &status, &opt_len);
       printf("assoc id = %d\n", status.sstat_assoc_id );  
  printf("state = %d\n", status.sstat_state );  
  printf("instrms = %d\n", status.sstat_instrms );  
  printf("outstrms = %d\n", status.sstat_outstrms ); 

       printf("Sending Role  to server: ");
       while(fgets(sendline, MAXLINE,stdin) != NULL )
       {
      //  iMsgSize = strlen(sendline);
       //fgets(sendline, MAXLINE,stdin);
       printf(" ige to send: ");
     //  sctp_sendmsg(SctpScocket, (const void *)a, iMsgSize, NULL, 0,htonl(PPID), 0, 0 , 0, 0);
       sctp_sendmsg(SctpScocket, sendline, strlen(sendline)+1, NULL, 0,htonl(PPID), 0, 0 , 0, 0);


       //read response from test server
       in = sctp_recvmsg(SctpScocket, (void*)szRecvBuffer, RECVBUFSIZE,(struct sockaddr *)&servaddr, &from_len, &sndrcvinfo, &flags);
       if (in > 0 && in < RECVBUFSIZE - 1)
       {
               szRecvBuffer[in] = 0;
               printf("Received from server: %s\n",
                        (char *)szRecvBuffer);
        }
      } 
       printf("exiting...\n");

       close(SctpScocket);
       return 0;
}









