#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chain{
    char header[100];
    char data[10][100];
    int dataCnt;
} CHAIN;


int main(int argc, char *argv[])
{
	FILE *fp_in;
	char buf_in[255];

	fp_in = fopen("CHAIN.TXT", "r");
	if ( fp_in == NULL )
	{
		perror("file open error 1: ");
		exit(1);
	}


	CHAIN chainList[1000];
	int chainCnt = 0;
	memset(chainList, 0x00, sizeof(chainList));

	int i = 0;
	char *ret_ptr;
	while ( fgets(buf_in, sizeof(buf_in), fp_in) != NULL )
	{
		if (i%2 == 0)
		{
			// 헤더
			ret_ptr = strtok(buf_in, "\r\n");
			strcpy(chainList[chainCnt].header, ret_ptr);
		}
		else
		{
			// 데이터
			ret_ptr = strtok(buf_in, "#\r\n");
			while(ret_ptr != NULL)
			{
				strcpy(chainList[chainCnt].data[chainList[chainCnt].dataCnt], ret_ptr);
				chainList[chainCnt].dataCnt++;
				//printf("dataCnt: %d\n", chainList[chainCnt].dataCnt);
				ret_ptr = strtok(NULL, "#\r\n");
			}
			chainCnt++;
		}
		i++;
	}

	for(i=0; i<chainCnt; i++)
	{
		printf("%s\n", chainList[i].header);
		for(int j=0; j<chainList[i].dataCnt; j++)
			printf("%s\n", chainList[i].data[j]);
	}

	fclose(fp_in);

	return 0;
}


