/*
 * util_popen.c
 *
 *  Created on: 2018. 7. 19.
 *      Author: ccomasora
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
	FILE *fp = NULL;
	char buf[200] = {0, };

	fp = popen("pwd", "r");
	if ( fp == NULL )
	{
		perror("popen error 1: ");
		exit(1);
	}

	while( fgets(buf, sizeof(buf), fp) != NULL )
	{
		printf("pwd: %s\n", buf);
	}

	pclose(fp);

	return 0;
}

