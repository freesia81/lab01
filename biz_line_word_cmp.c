#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// 문자열 처리
void process_str(char *outStr, char *inStr)
{
	char tmp[1000] = {0, };
	char ch1, ch2;
	int nWordCnt = 0;
	
	printf("inStr: %s, len: %d\n", inStr, strlen(inStr));
	 
	for(int i=0; i<strlen(inStr)+1; i++)
	{
		if ( i == 0)
		{
			ch1 = inStr[i];
			nWordCnt++;
			continue;
		}
		
		ch2 = inStr[i];
		
		if ( isupper(ch1) && isupper(ch2) && ch1 == ch2 )
		{
			nWordCnt++;
			continue;
		}
		
		if ( nWordCnt == 1 )
			sprintf(&tmp[strlen(tmp)], "%c", ch1);
		else if ( nWordCnt == 2 )
			sprintf(&tmp[strlen(tmp)], "%c%c", ch1, ch1);
		else
			sprintf(&tmp[strlen(tmp)], "%d%c", nWordCnt, ch1);
			
		ch1 = ch2;
		nWordCnt = 1;
	}
	
	strncpy(outStr, tmp, strlen(tmp));
	printf("outStr: %s, len: %d\n", outStr, strlen(outStr));
	
	return;
}



int	main(int argc, char	*argv[]) {
	
	char fName[100]	= {0, };
	
	// 콘솔입력
	scanf("%s",	fName);
	
	// 입력파일
	char strInFilePath[100]	= {0, };
	sprintf(strInFilePath, "./BIGFILE/%s", fName);

	FILE *fp_in;
	if ( (fp_in	= fopen(strInFilePath, "r")) ==	NULL )
	{
		perror("input file open	error: ");
		exit(1);
	}	
	
	// 출력	파일
	char strOutFilePath[100] = {0, };
	sprintf(strOutFilePath,	"%s", fName);
	
	FILE *fp_out;
	if ( (fp_out = fopen(strOutFilePath, "w")) == NULL )
	{
		perror("output file	open error:	");
		exit(1);
	}
	
	// 2줄씩 읽어서	비교
	char strBase[1000] = {0, };
	char strNext[1000] = {0, };
	char buf_in[1000] = {0, };
	char buf_out[1000] = {0, };
	int	nLineCnt = 0;
	int	bFirstFlag = 0;
	char *ptr;
	
	while(1)
	{
		// 첫줄 읽기
		if (bFirstFlag == 0)
		{
			fgets(buf_in, sizeof(buf_in),	fp_in);
			strcpy(strBase, strtok(buf_in, "\r\n"));
			
			nLineCnt = 1;
			bFirstFlag = 1;
			continue;			
		}
		
		// 두번째부터 끝까지 읽기
		memset(buf_in, 0x00, sizeof(buf_in));
		if ( (ptr = fgets(buf_in, sizeof(buf_in), fp_in)) != NULL)
		{
			memset(strNext, 0x00, sizeof(strNext));
			strcpy(strNext, strtok(buf_in, "\r\n"));
			
			if ( strcmp(strBase, strNext) == 0 )
			{
				nLineCnt++;
				continue;
			}
		}	
		
		// 중복문자 처리	
		memset(buf_out, 0x00, sizeof(buf_out));
		process_str(buf_out, strBase);
		
		// 결과 기록
		if (nLineCnt == 1)
			fprintf(fp_out, "%s\n", buf_out);
		else
			fprintf(fp_out, "%d#%s\n", nLineCnt, buf_out);
			
		// 문자열 읽기 종료 or 계속 조건
		if ( ptr == NULL )
			break;
		else
		{
			strcpy(strBase, strNext);
			nLineCnt = 1;
		}		
	}

	fclose(fp_in);
	fclose(fp_out);	
	
	return 0;
}
