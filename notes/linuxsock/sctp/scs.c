/*
 * =====================================================================================
 *
 *       Filename:  scs.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/19/2013 10:56:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define RECVBUFSIZE             4096
#define PPID                    1234

int main() {
       int SctpScocket, n, flags;
       socklen_t from_len;
       socklen_t salen;

       struct sockaddr_in addr = {0};
       struct sctp_sndrcvinfo sinfo = {0};
       struct sctp_event_subscribe event = {0};
       char pRecvBuffer[RECVBUFSIZE + 1] = {0};

       char * szAddress;
       int iPort;
       char * szMsg;
       int iMsgSize;

       //get the arguments
       szAddress = "127.0.0.1";
       iPort = 5001;
       szMsg = "Hello Client";
       iMsgSize = strlen(szMsg);
       if (iMsgSize > 1024)
       {
               printf("Message is too big for this test\n");
               return 0;
       }

       //here we may fail if sctp is not supported
       SctpScocket = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
       printf("socket created...\n");

event.sctp_data_io_event = 1; 
event.sctp_association_event = 1; 
       //make sure we receive MSG_NOTIFICATION
       setsockopt(SctpScocket, IPPROTO_SCTP, SCTP_EVENTS, &event,sizeof(struct sctp_event_subscribe));
       printf("setsockopt succeeded...\n");

       addr.sin_family = AF_INET;
       addr.sin_port = htons(iPort);
       addr.sin_addr.s_addr = inet_addr(szAddress);

       //bind to specific server address and port
       bind(SctpScocket, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
       printf("bind succeeded...\n");

       //wait for connections
       listen(SctpScocket, 1);
       printf("listen succeeded...\n");

        int count = 0,i;
        char a[20][10],d[20][10];
        char send_data[1024];
       socklen_t opt_len;
       struct sctp_status status = {0};

        strcpy(a[0],"Abraham");
        strcpy(a[1],"Buck");
        strcpy(a[2],"Casper");
        strcpy(a[3],"Dammy");
        strcpy(d[0],"1");
        strcpy(d[1],"2");
        strcpy(d[2],"3");
        strcpy(d[3],"4");

      
       while(1)
       {
               //each time erase the stuff
               flags = 0;
               memset((void *)&addr, 0, sizeof(struct sockaddr_in));
               from_len = (socklen_t)sizeof(struct sockaddr_in);
               memset((void *)&sinfo, 0, sizeof(struct sctp_sndrcvinfo));

               n = sctp_recvmsg(SctpScocket, (void*)pRecvBuffer, RECVBUFSIZE,(struct sockaddr *)&addr, &from_len, &sinfo, &flags);
               if (-1 == n)
               {
                       printf("Error with sctp_recvmsg: -1... waiting\n");
                       printf("errno: %d\n", errno);
                       perror("Description: ");
                       sleep(1);
                       continue;
               }



    if(flags & MSG_NOTIFICATION)
    {
        union sctp_notification *notification =(void *) pRecvBuffer; 
        switch(notification->sn_header.sn_type) { 
         case SCTP_SHUTDOWN_EVENT: { 
            struct sctp_shutdown_event *shut; 
            shut = (struct sctp_shutdown_event *) pRecvBuffer; 
            printf("Shutdown on assoc id %d\n", 
                    shut->sse_assoc_id); 
            break; 
        }
        case SCTP_ASSOC_CHANGE: { 
            struct sctp_assoc_change *assoc; 
            assoc = (struct sctp_assoc_change *) pRecvBuffer; 
            printf("Init on assoc id %d\n", 
                    assoc->sac_assoc_id); 
            break; 
         }
         default: 
            printf("Unhandled event type %d\n", 
                   notification->sn_header.sn_type);
        }
        printf("Notification received!\n");
        printf("From %s:%u\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
      }
      else
       {
         printf("Received from assoc id  %d\n", sinfo.sinfo_assoc_id); 
         printf("Received from %s:%u on stream %d, PPID %d.: %s\n",
                               inet_ntoa(addr.sin_addr),
                               ntohs(addr.sin_port),
                               sinfo.sinfo_stream,
                               ntohl(sinfo.sinfo_ppid),
                               pRecvBuffer
                       );
       struct sctp_paddrinfo sp;
       int sz;
    sz = sizeof(struct sctp_paddrinfo);
    bzero(&sp, sz);
   
    salen = (socklen_t)sizeof(struct sockaddr_in);
    memcpy(&sp.spinfo_address, &addr, salen);
    if (sctp_opt_info(SctpScocket, 0, SCTP_GET_PEER_ADDR_INFO, &sp, &sz) == -1)
        perror("get assoc from sctp_opt_info\n");
                   
              printf("Get assoc id from  address is %d",sp.spinfo_assoc_id );

             int p = 0;
                     for(i=0;i<4;i++)
                     {
                        if(strcmp(pRecvBuffer,d[i]) == 0)
                        {
                             strcpy(send_data,a[i]);p=1;
                        }
                     }
                     if(p == 0)
                      strcpy(send_data,"No one on that role.");

               }
    /*   opt_len = (socklen_t) sizeof(struct sctp_status);
       if(getsockopt(SctpScocket, IPPROTO_SCTP, SCTP_STATUS, &status, &opt_len)< 0)
        { 
         perror("getsockopt error");
         return;}
       printf("assoc id = %d\n", status.sstat_assoc_id );  
  printf("state = %d\n", status.sstat_state );  
  printf("instrms = %d\n", status.sstat_instrms );  
  printf("outstrms = %d\n", status.sstat_outstrms ); 
 */

               //send message to client
               printf("Sending to client: %s\n", send_data);
               sctp_sendmsg(SctpScocket, (const void *)send_data, strlen(send_data), (struct sockaddr *)&addr, from_len, htonl(PPID), 0, 0 /*stream 0*/, 0, 0);

               //close server when exit is received
               if (0 == strcmp(pRecvBuffer, "exit"))
               {
                       break;
               }
       }//while

       printf("exiting...\n");

       close(SctpScocket);
       return (0);
}
 

