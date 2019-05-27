#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in servAddr;
	unsigned short servPort;
	char *servIP;

	if ( argc != 3 )
	{
		printf("Usage: %s <Server IP> <Port> \n", argv[0]);
		exit(1);
	}

	servIP = argv[1];
	servPort = atoi(argv[2]);

	// 서버 주소 설정
	memset( &servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servIP);
	servAddr.sin_port = htons(servPort);

	// 소켓 생성 및 연결
	if ( (sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
	{
		perror("socket error: ");
		exit(1);
	}

	if ( connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 )
	{
		perror("connect error: ");
		exit(1);
	}

	// 데이터 전송
	char writeBuf[256];
	memset(writeBuf, 0x00, sizeof(writeBuf));	
	sprintf(writeBuf, "%s", "ABCDFILE.TXT");
	if ( write(sock, writeBuf, strlen(writeBuf)) != strlen(writeBuf) )
	{
		perror("send error: ");
		exit(1);
	}

	// 데이터 수신
	char readBuf[256];
	int  readLen = 0;
	memset(readBuf, 0x00, sizeof(readBuf));
	if ( (readLen = read(sock, readBuf, sizeof(readBuf))) < 0 )
	{
		perror("read error: ");
		exit(1);
	}
	else if ( readLen == 0 )
	{
		perror("sock is closed..\n");
		close(sock);
		exit(0);
	}
	
	readBuf[readLen] = '\0';
	printf("%s\n", readBuf);
	
	// 연결 종료
	close(sock);
	exit(0);
}
