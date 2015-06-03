#include	"unp.h"

int 
sctp_get_no_strms(int sock_fd,struct sockaddr *to, socklen_t tolen)
{
//	int retsz;
      socklen_t retsz;
	struct sctp_status status={0};
	retsz = (socklen_t) sizeof(struct sctp_status);	
	bzero(&status,sizeof(status));

	int associd = sctp_address_to_associd(sock_fd,to,tolen);
	status.sstat_assoc_id = sctp_address_to_associd(sock_fd,to,tolen);
	Getsockopt(sock_fd,IPPROTO_SCTP, SCTP_STATUS,
//	Getsockopt(sock_fd,SOL_SCTP, SCTP_STATUS,
		   &status, &retsz);
        printf("the assco id is %d and the out steam is %d, in stream %d\n",associd,
       status.sstat_outstrms,status.sstat_instrms);
	return(status.sstat_outstrms);
}
