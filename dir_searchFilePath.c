#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_CNT	10
#define MAX_FILE_LEN	1000

int searchFilePathInSubDir(char *outFileFullPath, char *inSubDir, char *inSearchFile)
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
			//printf("DIR: %s\n", tmpPath);
			if (searchFilePathInSubDir(outFileFullPath, tmpPath, inSearchFile) == 0)
			{
				closedir(dp);
				return 0;
			}
		}
		else if (S_ISREG(fstat.st_mode)) 
		{
			//printf("FILE: %s\n", tmpPath);
			if (strcmp(dentry->d_name, inSearchFile) == 0)
			{
				printf("Search Success - %s\n", tmpPath);
				strncpy(outFileFullPath, tmpPath, strlen(tmpPath));
				closedir(dp);
				return 0;
			}
		}
		else 
		{
			//printf("OTHER: %s\n", tmpPath); 
		}	
	}

	closedir(dp);
	return -1;
	
}

int main(int argc, char *argv[]) 
{
	char searchFileFullPath[MAX_FILE_LEN] = {0, };
	
	searchFilePathInSubDir(searchFileFullPath, "BIGFILE", "ABCDFILE.txt");
	
	return 0;
}
