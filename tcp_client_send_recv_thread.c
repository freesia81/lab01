#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_SIZE 256
#define NAME_SIZE 20

void *send_msg(void *arg);
void *recv_msg(void *arg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];


int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in servAddr;
	unsigned short servPort;
	char *servIP;

	pthread_t snd_tid, rcv_tid;
	void *thread_return;

	if ( argc != 4 )
	{
		printf("Usage: %s <Server IP> <Port> <name>\n", argv[0]);
		exit(1);
	}

	servIP = argv[1];
	servPort = atoi(argv[2]);
	sprintf(name, "[%s]", argv[3]);


	if ( (sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
	{
		perror("socket error: ");
		exit(1);
	}

	/* Construct the server address structure */
	memset( &servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servIP);
	servAddr.sin_port = htons(servPort);


	/* Establish the connection to the echo server */
	if ( connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 )
	{
		perror("connect error: ");
		exit(1);
	}


	pthread_create(&snd_tid, NULL, send_msg, (void *)&sock);
	pthread_create(&rcv_tid, NULL, recv_msg, (void *)&sock);
	pthread_join(snd_tid, &thread_return);
	pthread_join(rcv_tid, &thread_return);

	close(sock);
	return 0;
}

void *send_msg(void *arg)
{
	int sock = *((int *)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];

	while( fgets(msg, BUF_SIZE, stdin) != NULL )
	{
		if ( strcmp(msg, "q\n") == 0 || strcmp(msg, "Q\n") == 0 )
		{
			close(sock);
			exit(1);
		}

		sprintf(name_msg, "%s %s", name, msg);

		if ( write(sock, name_msg, strlen(name_msg)) != strlen(name_msg) )
		{
			perror("write error: ");
			exit(1);
		}
	}

	return NULL;
}

void *recv_msg(void *arg)
{
	int sock = *((int *)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;

	while( 1 )
	{
		if ( (str_len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1)) <= 0 )
		{
			perror("read error: ");
			exit(1);
		}

		name_msg[str_len] = '\0';
		fputs(name_msg, stdout);
	}

	return NULL;
}


