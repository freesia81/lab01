/*
 * util_tiem.c
 *
 *  Created on: 2018. 7. 20.
 *      Author: ccomasora
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
	char buf[15] = {0, };
	struct tm strTime;
	time_t lcoalTime = time(0);

	memset(&strTime, 0x00, sizeof(struct tm));
	localtime_r(&lcoalTime, &strTime);

	strftime(buf, 15, "%Y%m%d%H%M%S", &strTime);
	printf("%s\n", buf);

}
