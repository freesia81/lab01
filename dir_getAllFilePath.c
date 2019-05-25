#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_CNT	10
#define MAX_FILE_LEN	1000

int getAllFilePathInSubDir(char outFilePath[MAX_FILE_CNT][MAX_FILE_LEN], int *outFileCnt, char *inSubDir)
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
		if (dentry->d_ino == 0)
			continue;
		
		if (strcmp(dentry->d_name, ".") == 0 || strcmp(dentry->d_name, "..") == 0)
			continue;
		
		memset(tmpPath, 0x00, sizeof(tmpPath));
		sprintf(tmpPath, "%s/%s", inSubDir, dentry->d_name);
		
		if (stat(tmpPath, &fstat) == -1) 
		{
			perror("stat error: ");
			continue;
		}
		
		// 디렉토리 : 서브디렉토리 검색
		if (S_ISDIR(fstat.st_mode)) 
		{
			//printf("DIR: %s\n", tmpPath);
			getAllFilePathInSubDir(outFilePath, outFileCnt, tmpPath);
		}
		else if (S_ISREG(fstat.st_mode)) 
		{
			//printf("FILE: %s\n", tmpPath);
			strncpy(outFilePath[(*outFileCnt)++], tmpPath, strlen(tmpPath));
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
	int  outFileCnt = 0;
	
	getAllFilePathInSubDir(outAllFilePath, &outFileCnt, "BIGFILE");
	for(int i=0; i<outFileCnt; i++)
		printf("%s\n", outAllFilePath[i]);
	
	return 0;
}