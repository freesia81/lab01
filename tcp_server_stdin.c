#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PORT 9000
#define IPADDR "127.0.0.1"
#define BUF_SIZE 1024

void *t_func(void *arg)
{
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;

	s_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(PORT);

	if( bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0 )
	{
		perror("bind error: ");
		return NULL;
	}

	if( listen(s_socket, 5) < 0 )
	{
		perror("listen error: ");
		return NULL;
	}

	// Accept a client socket
	while(1)
	{
		len = sizeof(c_addr);
		if ( (c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len)) < 0 )
		{
			perror("accept error: ");
			close(s_socket);
			return NULL;
		}

		while(1)
		{
			// read: <===== name#size
			char tmp1[128] = {0, };
			char tmp2[128] = {0, };
			char fileName[128] = {0, };
			int fileSize = 0;

			char recvBuf[BUF_SIZE] = {0, };
			int recvLen;
			if( (recvLen = read(c_socket, recvBuf, sizeof(recvBuf))) <= 0 )
			{
				printf("connection is closed\n");
				break;
			}

			strcpy(tmp1, strtok(recvBuf, "#"));
			strcpy(tmp2, strtok(NULL, "#"));
			sprintf(fileName, "./OUTPUT/%s", tmp1);
			fileSize = atoi(tmp2);

			printf("%s, %d\n", fileName, fileSize);

			// write: ACK =====>
			char sendBuf[BUF_SIZE] = {0, };
			strcpy(sendBuf, "ACK");
			if( write(c_socket, sendBuf, strlen(sendBuf)) != strlen(sendBuf) )
			{
				printf("ACK send fail\n");
				break;
			}

			FILE *fp_out = NULL;
			if( (fp_out = fopen(fileName, "wb")) == NULL )
			{
				perror("fopen error: ");
				break;
			}

			// read: <===== file
			memset(recvBuf, 0x00, sizeof(recvBuf));
			int totSize = 0;
			while( (recvLen = c_socket, recvBuf, sizeof(recvBuf)) != 0 )
			{
				fwrite(recvBuf, 1, recvLen, fp_out);
				totSize += recvLen;

				if ( totSize == fileSize )
				{
					printf("complete!!\n");
					break;
				}
			}
			fclose(fp_out);

			// write: END =====>
			memset(sendBuf, 0x00, sizeof(sendBuf));
			strcpy(sendBuf, "END");
			if( write(c_socket, sendBuf, strlen(sendBuf)) != strlen(sendBuf) )
			{
				printf("END send fail\n");
				break;
			}
		}

		close(c_socket);
	}
}


int main(int argc, char *argv[]) 
{
	mkdir("./OUTPUT", 0777);

	pthread_t thread1;
	int thr_id;

	if( (thr_id = pthread_create(&thread1, NULL, t_func, NULL)) != 0 )
	{
		perror("pthread create error! ");
		return -1;
	}

	while(1)
	{
		char cmd[128] = {0, };

		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd)-1] = '\0';

		if (strcmp(cmd, "REPORT") == 0)
		{
			printf("REPORT FINISH\n");
		}
		else if (strcmp(cmd, "QUIT") == 0)
		{
			return 0;
		}
		else
		{
			printf("Others: %s\n", cmd);
		}
	}
	
	pthread_join(thread1, NULL);
	return 0;

}
