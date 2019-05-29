#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

struct node {
	int num;
	char str[10];
	TAILQ_ENTRY(node) nodes;     /* 꼬리 큐 */
};

TAILQ_HEAD(node_head_t, node) node_head;

pthread_mutex_t mutex_queue = PTHREAD_MUTEX_INITIALIZER;

void InitQueue(void)
{
	TAILQ_INIT(&node_head);
}

bool IsEmptyQueue(void)
{
	bool is_empty;

	pthread_mutex_lock(&mutex_queue);
	is_empty = TAILQ_EMPTY(&node_head);
	pthread_mutex_unlock(&mutex_queue);

	return is_empty;
}

struct node * RemoveQueue(void)
{
	struct node *np;

	pthread_mutex_lock(&mutex_queue);
	np = TAILQ_FIRST(&node_head);
	TAILQ_REMOVE(&node_head, np, nodes);
	pthread_mutex_unlock(&mutex_queue);

	return np;
}

void AddQueue(int num, char *str)
{
	struct node *elem;

	pthread_mutex_lock(&mutex_queue);
	elem = malloc(sizeof(struct node));
	if (elem)
	{
		elem->num = num;
		memcpy(elem->str, str, sizeof(elem->str));

		TAILQ_INSERT_TAIL(&node_head, elem, nodes);
	}
	pthread_mutex_unlock(&mutex_queue);
}


int main()
{
	InitQueue();                      /* 큐 초기화 */

	char buf[10][10] = {"AAA", "BBB", "CCC", "DDD", "EEE"};

	// 큐 추가
	for(int i=0; i<5; i++)
		AddQueue(i, buf[i]);

	// 큐 삭제
	while( !IsEmptyQueue())
	{
		struct node *np = RemoveQueue();
		printf("%d: %s\n", np->num, np->str);

		free(np);
	}

	return 0;
}
