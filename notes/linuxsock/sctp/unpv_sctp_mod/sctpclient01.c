#include	"unp.h"

int
main(int argc, char **argv)
{
	int sock_fd;
	struct sockaddr_in servaddr;
	struct sctp_event_subscribe evnts;
	int echo_to_all=0;
       struct sctp_initmsg initmsg = {0};

	if(argc < 2)
		err_quit("Missing host argument - use '%s host [echo]'\n",
		       argv[0]);
	if(argc > 2) {
		printf("Echoing messages to all streams\n");
		echo_to_all = 1;
	}
//        sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
        sock_fd = Socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

       initmsg.sinit_num_ostreams = 3;

       setsockopt( sock_fd, IPPROTO_SCTP, SCTP_INITMSG, &initmsg,sizeof(initmsg));
       printf("setsockopt succeeded...\n");


  	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	Setsockopt(sock_fd,IPPROTO_SCTP, SCTP_EVENTS,
		   &evnts, sizeof(evnts));

/*     connect( sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
       printf("connect succeeded...\n");


      //check status
     struct sctp_status status = {0};
     socklen_t  opt_len = (socklen_t) sizeof(struct sctp_status);
       getsockopt(sock_fd, IPPROTO_SCTP, SCTP_STATUS, &status, &opt_len);
       printf("assoc id = %d\n", status.sstat_assoc_id );
  printf("state = %d\n", status.sstat_state );
  printf("instrms = %d\n", status.sstat_instrms );
  printf("outstrms = %d\n", status.sstat_outstrms );
*/




	if(echo_to_all == 0)
		sctpstr_cli(stdin,sock_fd,(SA *)&servaddr,sizeof(servaddr));
	else
		sctpstr_cli_echoall(stdin,sock_fd,(SA *)&servaddr,sizeof(servaddr));
	Close(sock_fd);
	return(0);
}
