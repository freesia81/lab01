#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int thread_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 쓰레드 개수 증가
void increase_thread_count(void)
{
	pthread_mutex_lock(&mutex);
	thread_count++;
	printf("increase: %d\n", thread_count);
	pthread_mutex_unlock(&mutex);
}

// 쓰레드 개수 감소
void decrease_thread_count(void)
{
	pthread_mutex_lock(&mutex);
	thread_count--;
	printf("decrease: %d\n", thread_count);
	pthread_mutex_unlock(&mutex);
}

// 쓰레드 개수 획득
int get_thread_count(void)
{
	int result;

	pthread_mutex_lock(&mutex);
	result = thread_count;
	pthread_mutex_unlock(&mutex);

	return result;
}

// 쓰레드 함수
void *thread_function(void *args)
{
	pthread_detach(pthread_self());

	int i = *(int *)args;
	printf("[%d] thread\n", i);
	
	free( (int *)args );

	decrease_thread_count();

	return NULL;
}


int main(int argc, char *argv[])
{
	pthread_t thread;

	// 10개 쓰레드 생성 
	for ( int i=0; i<10; i++ )
	{
		increase_thread_count();

		int *pi = malloc(sizeof(int));
		*pi = i;
		pthread_create(&thread, NULL, thread_function, pi);
	}

	// 쓰레드 생성/소멸 시간 확보를 위해 대기 중..
	while( get_thread_count() > 0 )
	{
		usleep(10);
	}

	return 0;
}




