#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<strings.h>
#include<string.h>
main()
{
	int sd_ser,sd_cli;
	int len_ser,len_cli;
	struct sockaddr_in server_st,client_st;
	char rdbuf[128],wrbuf[128];
	sd_ser=socket(PF_INET,SOCK_STREAM,0);
	printf("server sd=%d\n",sd_ser);
	server_st.sin_family=PF_INET;
	server_st.sin_port=htons(2000);
	server_st.sin_addr.s_addr=inet_addr("0.0.0.0");
	len_ser=sizeof(server_st);
	len_cli=sizeof(client_st);
	bind(sd_ser,(struct sockaddr *)&server_st,len_ser);
	listen(sd_ser,5);
	sd_cli=accept(sd_ser,(struct sockaddr *)&client_st,&len_cli);
	if(sd_cli<0)
	{
		perror("accept");
		return;
	}
	printf("client sd=%d\n",sd_cli);
	while(1)
	{
		if(fork())
		{
			bzero(rdbuf,128);
			read(sd_cli,rdbuf,128);
			printf("\nfrom client: %s\n",rdbuf);
		}
		else
		{
			printf("to client: ");
			scanf(" %[^\n]",wrbuf);
			write(sd_cli,wrbuf,strlen(wrbuf));
		}
	}
}
