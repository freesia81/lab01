/*
 * read_parse_from_file.c
 *
 *  Created on: 2018. 8. 7.
 *      Author: ccomasora
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * INFO파일 구성

   HEADER1(8자리)#HEADER2(8자리)#HEADER3(8자리)
   FIELD1(5자리),FIELD2(5자리),FIELD3(4자리)#FIELD1(5자리),FIELD2(5자리),FIELD3(4자리)#...... (데이터는 N개)
   _____________________________________ _____________________________________ ______
   data[0]                               data[1]                               ......
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
	char *pfield = NULL;

	INFO info_list[100];
	int info_cnt = 0;
	int i, j;
	bool first_flag = true;

	fp_in = fopen("../INPUT/INFO.TXT", "r");
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

		strncpy( info_list[info_cnt].header1, pheader1, strlen(pheader1) );
		strncpy( info_list[info_cnt].header2, pheader2, strlen(pheader2) );
		strncpy( info_list[info_cnt].header3, pheader3, strlen(pheader3) );

		if ( fgets( buf_in2, sizeof(buf_in2), fp_in) != NULL )
		{
#if 0
			//방법1. #을 기준으로 거래데이터 1건씩  잘라낸 후, 각 필드를 파싱함

			while(1)
			{
				if ( first_flag == true )
				{
					pfield = strtok(buf_in2, "#\r\n");
					first_flag = false;
				}
				else
				{
					pfield = strtok(NULL, "#\r\n");
				}

				if ( pfield == NULL )
					break;

				// 주의사항: 데이터 포맷에 정의된 크기만큼 하드코딩으로 잘라서 복사해줘야 함!!!
				strncpy( info_list[info_cnt].data[i].field1, pfield,      sizeof(info_list[info_cnt].data[i].field1)-1 );
				strncpy( info_list[info_cnt].data[i].field2, pfield + 6,  sizeof(info_list[info_cnt].data[i].field2)-1 );
				strncpy( info_list[info_cnt].data[i].field3, pfield + 12, sizeof(info_list[info_cnt].data[i].field3)-1 );
				info_list[info_cnt].data_cnt = ++i;
			}
#else
			// 방법2. #과 ,를 기준으로 각 필드에 인덱스를 부여하여 파싱함
			int idx = 0, seq = 0;
			while(1)
			{
				if ( first_flag == true )
				{
					pfield = strtok(buf_in2, ",#\r\n");
					first_flag = false;
				}
				else
				{
					pfield = strtok(NULL, ",#\r\n");
				}

				if ( pfield == NULL )
					break;

				/* 하드코딩 숫자 3은 filed개수만큼 수정해야 함 */
				idx = seq % 3;
				switch( idx )
				{
					case 0:
						strncpy( info_list[info_cnt].data[i].field1, pfield, strlen(pfield) );
						break;
					case 1:
						strncpy( info_list[info_cnt].data[i].field2, pfield, strlen(pfield) );
						break;
					case 2:
						strncpy( info_list[info_cnt].data[i].field3, pfield, strlen(pfield) );
						info_list[info_cnt].data_cnt = ++i;
						break;
				}
				seq++;
			}
#endif

		}

		info_cnt++;
		memset(buf_in1, 0x00, sizeof(buf_in1));
		memset(buf_in2, 0x00, sizeof(buf_in2));
		i = 0;
		first_flag = true;
	}


	// 입력값 확인해보기
	printf("==================================================\n");
	for(i=0; i<info_cnt; i++)
	{
		printf("%s %s %s\n", info_list[i].header1, info_list[i].header2, info_list[i].header3);

		for(j=0; j<info_list[i].data_cnt; j++)
			printf("%s %s %s\n", info_list[i].data[j].field1, info_list[i].data[j].field2, info_list[i].data[j].field3);
	}
	printf("==================================================\n");


	fclose(fp_in);

	return 0;
}
