#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_CNT	10
#define MAX_FILE_LEN	512

int getAllSearchFilePathInSubDir(char outFilePath[MAX_FILE_CNT][MAX_FILE_LEN], int *outFileCnt, char *inSubDir, char *inSearchFile)
{
	struct dirent *dentry;
	struct stat fstat;
	DIR *dp;
	char tmpPath[MAX_FILE_LEN] = {0, };
	
	if ((dp = opendir(inSubDir)) == NULL) 
	{
		perror("opendir error: ");
		return -1;
	}
	
	while ((dentry = readdir(dp)) != NULL) 
	{
		if (strcmp(dentry->d_name, ".") == 0 || strcmp(dentry->d_name, "..") == 0)
			continue;
		
		memset(tmpPath, 0x00, sizeof(tmpPath));
		sprintf(tmpPath, "%s/%s", inSubDir, dentry->d_name);
		
		if (stat(tmpPath, &fstat) == -1) 
		{
			perror("stat error: ");
			continue;
		}
		
		if (S_ISDIR(fstat.st_mode)) 
		{
			//printf("DIR:  %s\n", tmpPath);
			getAllSearchFilePathInSubDir(outFilePath, outFileCnt, tmpPath, inSearchFile);
		}
		else if (S_ISREG(fstat.st_mode)) 
		{
			//printf("FILE: %s\n", tmpPath);
			if (strcmp(dentry->d_name, inSearchFile) == 0)
			{
				strncpy(outFilePath[(*outFileCnt)++], tmpPath, strlen(tmpPath));
			}
		}
		else 
		{
			//printf("OTHER: %s\n", tmpPath); 
		}	
	}

	closedir(dp);
	return 0;
	
}

int main(int argc, char *argv[]) 
{
	char outAllFilePath[MAX_FILE_CNT][MAX_FILE_LEN] = {0, };
	int outFileCnt = 0;
	
	getAllSearchFilePathInSubDir(outAllFilePath, &outFileCnt, "BIGFILE", "ABCDFILE.TXT");
	for(int i=0; i<outFileCnt; i++)
			printf("%s\n", outAllFilePath[i]);
	
	// 파일경로를 디렉토리 단위로 쪼개기
	char subFilePath[50][MAX_FILE_LEN] = {0, };
	int subFileCnt = 0;

	char temp[MAX_FILE_LEN];
	char *ptr = NULL;

	for(int i=0; i < outFileCnt; i++)
	{
		memset(temp, 0x00, sizeof(temp));
		strncpy(temp, outAllFilePath[i], strlen(outAllFilePath[i]));

		while( 1 )
		{
			if ( (ptr = strrchr(temp, '/')) == NULL)
			{
				printf("/ is not exist\n");
				break;
			}

			*ptr = 0x00;
			sprintf(subFilePath[subFileCnt++], "%s/%s", temp, "org.txt");
		}
	}

	printf("%d\n", subFileCnt);
	for(int i=0; i<subFileCnt; i++)
		printf("%s\n", subFilePath[i]);

	return 0;
}
