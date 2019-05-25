// 현재시간에서 알람조건 발생 전까지 1초 주기로 반복하여 모니터링 수행

#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

/*
// 1초 = 1000000 마이크로초
struct timeval {
	time_t			tv_sec; 	// 초
	suseconds_t	tv_usec;	// 마이크로초
};
*/

int main()
{
	struct timeval tvStart;
	struct timeval tvEnd;
	struct timeval tvGap;
	
	gettimeofday(&tvStart, NULL);
	
	while(1)
	{
		gettimeofday(&tvEnd, NULL);
		timersub(&tvEnd, &tvStart, &tvGap);
				
		if (tvGap.tv_sec == 1)
		{
			printf("1second alarm\n");
			gettimeofday(&tvStart, NULL);
		}			
	}

	//printf("Gap time  [%d.%d] \n", tvGap.tv_sec, tvGap.tv_usec);		// Gap time  [10.572]
	//printf("usec/1000 [%d]ms\n", (int)(tvGap.tv_usec/1000));				// usec/1000 [0]ms
	
	return 0;
	
}
