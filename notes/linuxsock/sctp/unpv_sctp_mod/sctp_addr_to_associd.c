#include	"unp.h"

sctp_assoc_t
sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen)
{
//	struct sctp_paddrparams sp;
/*	struct sctp_paddrinfo sp;
	int siz = sizeof(struct sctp_paddrinfo);
	bzero(&sp,siz);
	memcpy(&sp.spinfo_address,sa,salen);
	sctp_opt_info(sock_fd,0, SCTP_PEER_ADDR_PARAMS, &sp, &siz);
	return(sp.spinfo_assoc_id);*/

           struct sctp_paddrinfo sp;
       int sz;
    sz = sizeof(struct sctp_paddrinfo);
    bzero(&sp, sz);
    //   socklen_t salen = (socklen_t)sizeof(struct sockaddr_in);
    memcpy(&sp.spinfo_address, sa, salen);
    if (sctp_opt_info(sock_fd, 0, SCTP_GET_PEER_ADDR_INFO, &sp, &sz) == -1) 
        perror("get assoc from sctp_opt_info\n");

	return(sp.spinfo_assoc_id);

}
