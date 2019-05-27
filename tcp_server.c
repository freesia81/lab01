#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
	int servSock;
	int clntSock;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	unsigned short servPort;
	unsigned int clntLen;
	
	// ���� �ּ� ����
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servPort = 9876;
	servAddr.sin_port = htons(servPort);

	// ���� ���� ���� �� ���ε�, ����  
	if ( (servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
	{
		perror("socket error: ");
		exit(1);
	}
	
	if ( bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 )
	{
		perror("bind error: ");
		exit(1);
	}

	if ( listen(servSock, 1) < 0 )
	{
		perror("listen error: ");
		exit(1);
	}	
	
	// Ŭ���̾�Ʈ�� ���� ����
	clntLen = sizeof(clntAddr);
	if ( (clntSock = accept(servSock, (struct sockaddr *)&clntAddr, (socklen_t *)&clntLen)) < 0 )
	{
		perror("accept error: ");
		exit(1);
	}
	
	// ������ ����
	char readBuf[256];
	memset(readBuf, 0x00, sizeof(readBuf));
	if ( read(clntSock, readBuf, sizeof(readBuf)) <= 0 )
	{
		perror("read error: ");
		exit(1);
	}
	printf("%s\n", readBuf);
		
	// ������ �۽�
	char writeBuf[256];
	memset(writeBuf, 0x00, sizeof(writeBuf));
	strcpy(writeBuf, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if ( write(clntSock, writeBuf, strlen(writeBuf)) != strlen(writeBuf) )
	{
		perror("write error: ");
		exit(1);
	}
	
	// ���� ����
	close(clntSock);
	close(servSock);
	
	return 0;
	
}