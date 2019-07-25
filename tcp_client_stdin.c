#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 9000
#define IPADDR "127.0.0.1"
#define BUF_SIZE 1024

int get_file_size(FILE *fp)
{
	int nRet;
	fseek(fp, 0, SEEK_END);
	nRet = ftell(fp);
	rewind(fp);

	return nRet;
}


int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in servAddr;

	FILE *fp_in = NULL;

	if ( (sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
	{
		perror("socket error: ");
		exit(1);
	}

	memset( &servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IPADDR);
	servAddr.sin_port = htons(PORT);

	if ( connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 )
	{
		perror("connect error: ");
		exit(1);
	}


	fp_in = fopen("./BIGFILE/ABCDFILE.TXT", "rb");
	if(!fp_in)
	{
		perror("fopen error: ");
		return -1;
	}


	int size = get_file_size(fp_in);

	// write: name#size
	char writeBuf[256];
	memset(writeBuf, 0x00, sizeof(writeBuf));	
	sprintf(writeBuf, "%s#%05d", "ABCDFILE.TXT", size);
	if ( write(sock, writeBuf, strlen(writeBuf)) != strlen(writeBuf) )
	{
		perror("send error: ");
		exit(1);
	}

	// read: ACK
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

	// write: file
	while(1)
	{
		memset(writeBuf, 0x00, sizeof(writeBuf));
		if ( fgets(writeBuf, sizeof(writeBuf), fp_in) != NULL)
		{
			write(sock, writeBuf, strlen(writeBuf));
		}
		else
			break;
	}
	
	// read: EOF
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


	close(sock);
	exit(0);
}
