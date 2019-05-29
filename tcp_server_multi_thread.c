#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAXPENDING 5
#define BUF_SIZE 256
#define MAX_CLNT 100

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;


void * HandleTCPClient(void *arg);


int main(int argc, char *argv[])
{
	int servSock;
	int clntSock;
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	unsigned short servPort;
	unsigned int clntLen;
	pthread_t t_id;

	if ( argc != 2 )
	{
		printf("Usage: %s <Server Port>\n", argv[0]);
		exit(1);
	}


	pthread_mutex_init(&mutx, NULL);


	if ( (servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
	{
		perror("socket error: ");
		exit(1);
	}

	/* Construct local address structure */
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servPort = atoi(argv[1]);
	servAddr.sin_port = htons(servPort);


	if ( bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 )
	{
		perror("bind error: ");
		exit(1);
	}


	if ( listen(servSock, MAXPENDING) < 0 )
	{
		perror("listen error: ");
		exit(1);
	}


	while(1)
	{
		clntLen = sizeof(clntAddr);

		if ( (clntSock = accept(servSock, (struct sockaddr *)&clntAddr, (socklen_t *)&clntLen)) < 0 )
		{
			perror("accept error: ");
			exit(1);
		}


		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++] = clntSock;

		printf("Connected client ");
		for(int i=0; i<clnt_cnt; i++)
			printf("[%d] ", clnt_socks[i]);
		printf("\n");

		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id, NULL, HandleTCPClient, (void *)&clntSock);
		pthread_detach(t_id);
		printf("Connected client IP: %s\n", inet_ntoa(clntAddr.sin_addr));

	}

	/* NOT REACHED */
	close(servSock);
	return 0;
}



void * HandleTCPClient(void *arg)
{
	int i;
	char buf[BUF_SIZE];
	int len;
	int clntSock = *((int *)arg);

	while( (len = read(clntSock, buf, sizeof(buf))) != 0 )
	{
		pthread_mutex_lock(&mutx);
		for ( i=0; i<clnt_cnt; i++ )
		{
			if ( write(clnt_socks[i], buf, len) != len )
			{
				perror("write error: ");
				return NULL;
			}
		}
		pthread_mutex_unlock(&mutx);
	}

	// Remove disconnected client
	pthread_mutex_lock(&mutx);
	for ( i=0; i<clnt_cnt; i++ )
	{
		if ( clntSock == clnt_socks[i] )
		{
			while( i < clnt_cnt-1)
			{
				clnt_socks[i] = clnt_socks[i+1];
				i++;
			}
			break;
		}
	}
	clnt_cnt--;

	printf("Remained client ");
	for(int i=0; i<clnt_cnt; i++)
		printf("[%d] ", clnt_socks[i]);
	printf("\n");

	pthread_mutex_unlock(&mutx);


	close(clntSock);

	return NULL;
}

