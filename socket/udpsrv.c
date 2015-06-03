/*
 * =====================================================================================
 *
 *       Filename:  udpsrv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/19/2014 03:56:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fh-swf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */
  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h>

  #define BUFLEN 512
  #define NPACK 10
  #define PORT 9930

  void diep(char *s)
  {
    perror(s);
    exit(1);
  }

  int main(void)
  {
    struct sockaddr_in si_me, si_other;
    int s, i, slen=sizeof(si_other),pass_sd;
    char buf[BUFLEN];
//    char buffer[BUFLEN];
    char buffer[5];  //testing if the buffer len is less thatn the received packet size, MSG_TRUNC will be reported
    unsigned char set = 0x03;
 struct msghdr msg; 
struct iovec pkt;
//struct Who pkt;
 int *ecnptr;
 unsigned char received_ecn;

 struct iovec iov[1];  
  int cmsg_size = sizeof(struct cmsghdr)+sizeof(received_ecn);
// char buf[CMSG_SPACE(sizeof(received_ecn))];
 unsigned int nRet =0;


memset(&msg, '\0', sizeof(msg));
 msg.msg_iov = iov; 
 msg.msg_iovlen = 1;
 iov[0].iov_base = buffer;
 iov[0].iov_len = sizeof(buffer);
/*iov[1].iov_base = buffer;
iov[1].iov_len =BUFLEN ;*/


 msg.msg_control = buf;
 msg.msg_controllen = sizeof(buf); 
 msg.msg_name =&si_other  ; //src addr
 msg.msg_namelen = sizeof(si_other); 

 struct cmsghdr *cmsg;
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
      diep("socket");

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

if(setsockopt(s, IPPROTO_IP, IP_RECVTOS, &set,sizeof(set))<0) 
{
    printf("cannot set recvtos\n");
} 
else
{
        printf("socket set to recvtos\n");
 } 

    if (bind(s, &si_me, sizeof(si_me))==-1)
        diep("bind");

    for (i=0; i<NPACK; i++) {
    /*  if (recvfrom(s, buf, BUFLEN, 0, &si_other, &slen)==-1)
        diep("recvfrom()");*/

      nRet = recvmsg(s, &msg, 0);
if (nRet > 0) {


        printf("name:%d, iov:%d, control:%d flags:%d\n",
                msg.msg_namelen,msg.msg_iovlen,
                msg.msg_controllen,msg.msg_flags);
        printf("Receveid packet size %d: %s\n",nRet,buffer);
      printf("Received packet from %s:%d\n\n\n", 
             inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port) );
//        printf("Daemon: Packet has been received with ttl %d\n", aodv_get_ttl(&msg));
        switch(msg.msg_flags)
        {
            case MSG_EOR:
                puts("MSG_EOR");
                break;
            case MSG_TRUNC:
                puts("MSG_TRUNC");
                break;
            case MSG_CTRUNC:
                puts("MSG_CTRUNC");
                break;
            case MSG_OOB:
                puts("MSG_OOB");
                break;
            case MSG_ERRQUEUE:
                puts("MSG_ERRQUEUE");
                break;
            case MSG_DONTWAIT:
                puts("MSG_DONTWAIT");
                break;
        }



for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL;
cmsg = CMSG_NXTHDR(&msg,cmsg)) {
         if ((cmsg->cmsg_level == IPPROTO_IP) && 
         (cmsg->cmsg_type == IP_TOS) && (cmsg->cmsg_len) ){
                ecnptr = (int *) CMSG_DATA(cmsg);
        received_ecn = *ecnptr;
       // int isecn =  ((received_ecn & INET_ECN_MASK) == INET_ECN_CE);
        int isecn = 0; 

                printf("TOS is %d, UDP data is %s and UDP length is %d \n",  received_ecn,buffer,nRet ); 

                 break;
    }
      
        
    }
    }
 
/*      if (recvfrom(s, buffer, BUFLEN, 0, &si_other, &slen)!=-1)
      printf("Received packet from %s:%d\nData: %s\n\n", 
             inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buffer);*/
    }

    close(s);
    return 0;
 }

