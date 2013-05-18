#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<strings.h>
main(int c, char *v[])
{
  int sd_ser;
	int len_ser;
	struct sockaddr_in server_st;
	char wrbuf[128],rdbuf[128];
	sd_ser=socket(PF_INET,SOCK_STREAM,0);
	if(sd_ser<0)
	{
		perror("socket");
		return;
	}
	printf("server sd=%d\n",sd_ser);
	server_st.sin_family=PF_INET;
	server_st.sin_port=htons(atoi(v[1]));
	server_st.sin_addr.s_addr=inet_addr(v[2]);
	len_ser=sizeof(server_st);
	if(connect(sd_ser,(struct sockaddr *)&server_st,len_ser)<0)
	{
		perror("connect");
		return;
	}
	printf("connect success\n");
	while(1)
	{
		if(fork())
		{
			printf("to server: ");
			scanf(" %[^\n]",wrbuf);
			write(sd_ser,wrbuf,strlen(wrbuf));
		}
		else
		{
			bzero(rdbuf,128);
			read(sd_ser,rdbuf,sizeof(rdbuf));
			printf("\nfrom server: %s\n",rdbuf);
		}	
	}
}
