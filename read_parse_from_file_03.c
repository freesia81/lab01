/*
 * ReadFileData.c
 *
 *  Created on: 2018. 8. 7.
 *      Author: ccomasora
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * INFO3.TXT 파일 구성

   HEADER1(8자리)#HEADER2(8자리)#HEADER3(8자리)#DATACNT(2자리)
   FIELD1(5자리),FIELD2(5자리),FIELD3(4자리)
   FIELD1(5자리),FIELD2(5자리),FIELD3(4자리)
   ...... (데이터는 N개)
 */

typedef struct {
	char field1[6];
	char field2[6];
	char field3[5];
} DATA;

typedef struct {
	char header1[9];
	char header2[9];
	char header3[9];
	int data_cnt;
	DATA data[100];
} INFO;


int main()
{

	FILE *fp_in;
	char buf_in1[255];
	char buf_in2[255];

	INFO info_list[100];
	int info_cnt = 0;
	int i, j;

	fp_in = fopen("../INPUT/INFO3.TXT", "r");
	if ( fp_in == NULL )
	{
		perror("file open error 1: ");
		exit(1);
	}

	memset(info_list, 0x00, sizeof(info_list));
	info_cnt = 0;
	i = 0;

	while ( fgets(buf_in1, sizeof(buf_in1), fp_in) != NULL )
	{
		char *pheader1 = strtok(buf_in1, "#\r\n");
		char *pheader2 = strtok(NULL, "#\r\n");
		char *pheader3 = strtok(NULL, "#\r\n");
		char *pheader4 = strtok(NULL, "#\r\n");

		strncpy( info_list[info_cnt].header1, pheader1, strlen(pheader1) );
		strncpy( info_list[info_cnt].header2, pheader2, strlen(pheader2) );
		strncpy( info_list[info_cnt].header3, pheader3, strlen(pheader3) );

		info_list[info_cnt].data_cnt = atoi(pheader4);

		for(i=0; i < info_list[info_cnt].data_cnt; i++)
		{
			if ( fgets( buf_in2, sizeof(buf_in2), fp_in) != NULL )
			{
				char *pfield1 = strtok(buf_in2, ",\r\n");
				char *pfield2 = strtok(NULL, ",\r\n");
				char *pfield3 = strtok(NULL, ",\r\n");

				strncpy( info_list[info_cnt].data[i].field1, pfield1, strlen(pfield1) );
				strncpy( info_list[info_cnt].data[i].field2, pfield2, strlen(pfield2) );
				strncpy( info_list[info_cnt].data[i].field3, pfield3, strlen(pfield3) );
			}
		}

		info_cnt++;
		memset(buf_in1, 0x00, sizeof(buf_in1));
		memset(buf_in2, 0x00, sizeof(buf_in2));
	}

	fclose(fp_in);

	// 입력값 확인해보기
	printf("==================================================\n");
	for(i=0; i<info_cnt; i++)
	{
		printf("%s %s %s\n", info_list[i].header1, info_list[i].header2, info_list[i].header3);

		for(j=0; j<info_list[i].data_cnt; j++)
			printf("%s %s %s\n", info_list[i].data[j].field1, info_list[i].data[j].field2, info_list[i].data[j].field3);
	}
	printf("==================================================\n");

	return 0;
}
