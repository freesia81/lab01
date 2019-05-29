#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct multi_data{
   char usr1[100];
   char usr2[100];
   int  num;
} MULTI_DATA;


int main(int argc, char *argv[])
{
	FILE *fp_in;
	char buf_in[255];

	fp_in = fopen("CHAIN2.TXT", "r");
	if ( fp_in == NULL )
	{
		perror("file open error 1: ");
		exit(1);
	}

	MULTI_DATA dataList[100];
	int dataCnt = 0;
	memset(dataList, 0x00, sizeof(dataList));

	char *ret_ptr;
	char *next_ptr;
	char *sub_ret_ptr;
	char *sub_next_ptr;
	while ( fgets(buf_in, sizeof(buf_in), fp_in) != NULL )
	{
		// µ•¿Ã≈Õ
		ret_ptr = strtok_r(buf_in, "#\r\n", &next_ptr);
		while(ret_ptr != NULL)
		{
			sub_ret_ptr = strtok_r(ret_ptr, ",\r\n", &sub_next_ptr);
			strcpy(dataList[dataCnt].usr1, sub_ret_ptr);

			sub_ret_ptr = strtok_r(NULL, ",\r\n", &sub_next_ptr);
			strcpy(dataList[dataCnt].usr2, sub_ret_ptr);

			sub_ret_ptr = strtok_r(NULL, ",\r\n", &sub_next_ptr);
			dataList[dataCnt].num = atoi(sub_ret_ptr);
			dataCnt++;

			ret_ptr = strtok_r(NULL, "#\r\n", &next_ptr);
		}
	}

	for(int i=0; i<dataCnt; i++)
	{
		printf("%s, %s, %d\n", dataList[i].usr1, dataList[i].usr2, dataList[i].num);
	}

	fclose(fp_in);

	return 0;
}


