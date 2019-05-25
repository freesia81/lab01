#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char	*argv[]) {
	
	char fName[100]	= {0, };
	
	// 콘솔입력
	scanf("%s", fName);
	
	// 입력파일
	char strInFilePath[100]	= {0, };
	sprintf(strInFilePath, "./BIGFILE/%s", fName);

	FILE *fp_in;
	if ( (fp_in = fopen(strInFilePath, "r")) ==	NULL )
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
		perror("output file open error: ");
		exit(1);
	}
	
	// 2줄씩 읽어서	비교
	char strBase[1000] = {0, };
	char strNext[1000] = {0, };
	int	 nLineCnt = 0;
	int	 bFirstFlag = 0;
	
	while(1)
	{
		if (bFirstFlag == 0)
		{
			fgets(strBase, sizeof(strBase),	fp_in);
			if ( strBase[strlen(strBase)-1] == '\n' )
				strBase[strlen(strBase)-1] = '\0';

			nLineCnt = 1;
			bFirstFlag = 1;
			continue;			
		}

		char *ptr = NULL;
		if ( (ptr = fgets(strNext, sizeof(strNext), fp_in)) != NULL)
		{
			if ( strNext[strlen(strNext)-1] == '\n' )
				strNext[strlen(strNext)-1] = '\0';

			if ( strcmp(strBase, strNext) == 0 )
			{
				nLineCnt++;
				continue;
			}
		}	

		if (nLineCnt == 1)
			fprintf(fp_out, "%s\n", strBase);
		else
			fprintf(fp_out, "%d#%s\n", nLineCnt, strBase);

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
