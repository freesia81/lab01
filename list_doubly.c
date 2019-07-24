#include <stdio.h>
#include <malloc.h>

typedef struct _Node{
    int key;
    struct _Node *prev;
    struct _Node *next;
} Node;

Node *head, *tail;

void init_dlist(void)
{
    head = (Node*)malloc(sizeof(Node));
    tail = (Node*)malloc(sizeof(Node));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
}

void release_dlist(void)
{
	free(head);
	free(tail);
}

Node *find_node(int k)
{
    Node *curr;
    curr = head->next;
    while (curr->key != k && curr != tail)
    {
        curr = curr->next;
    }
    return curr;
}


void print_all_node(void)
{
	Node *curr;
	curr = head->next;

    while (curr != tail)
    {
        printf("%-4d", curr->key);
        curr = curr->next;
    }
    printf("\n\n");
}


Node *ordered_insert(int k)
{
    Node *curr;
    Node *new = NULL;

    curr = head->next;
    while (curr->key <= k && curr != tail)
    {
        curr = curr->next;
    }
    new = (Node*)malloc(sizeof(Node));
    new->key = k;
    curr->prev->next = new;
    new->prev = curr->prev;
    curr->prev = new;
    new->next = curr;
    return new;
}

Node *desc_ordered_insert(int k)
{
    Node *curr;
    Node *new = NULL;

    curr = head->next;
    while (curr->key >= k && curr != tail)
    {
        curr = curr->next;
    }
    new = (Node*)malloc(sizeof(Node));
    new->key = k;
    curr->prev->next = new;
    new->prev = curr->prev;
    curr->prev = new;
    new->next = curr;
    return new;
}

Node *insert_node(int k)
{
    Node *new;
    Node *curr = tail;

    new = (Node*)malloc(sizeof(Node));
    new->key = k;
    curr->prev->next = new;
    new->prev = curr->prev;
    curr->prev = new;
    new->next = curr;
    return new;
}

Node *insert_node_at_position(int k, Node *curr)
{
    Node *new;
    if (curr == head)
        return NULL;

    new = (Node*)malloc(sizeof(Node));
    new->key = k;
    curr->prev->next = new;
    new->prev = curr->prev;
    curr->prev = new;
    new->next = curr;
    return new;
}


int delete_node(int k)
{
    Node *curr;
    curr = find_node(k);
    if (curr != tail)
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
        return 1;
    }
    return 0;
}

void delete_all_node(void)
{
    Node *curr;
    Node *temp;
    curr = head->next;
    while (curr != tail)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    head->next = tail;
    tail->prev = head;
}



void main(void){

	// 0. 이중연결리스트 초기화
    init_dlist();

    // 1. 오름차순 정렬로 노드 추가
    ordered_insert(2);
    ordered_insert(1);
    ordered_insert(0);
    ordered_insert(-1);
    ordered_insert(-2);
    ordered_insert(2);

    printf("Initial Linked list is\n");
    print_all_node();

    // 모든 노드 삭제
    printf("Deleting all Node\n");
    delete_all_node();

    // 2. 내림차순 정렬로 노드 추가
    desc_ordered_insert(-1);
    desc_ordered_insert(-2);
    desc_ordered_insert(1);
    desc_ordered_insert(2);
    desc_ordered_insert(0);

    printf("Second Linked list is\n");
    print_all_node();

    // 3. 맨 뒤에 노드 추가
    insert_node(5);
    insert_node(4);

    printf("Insert Node at the end\n");
    print_all_node();

    // 4-1. 검색 성공하면 특정 위치 앞에 노드 추가
    Node *temp;
    temp = find_node(5);
    if(temp != tail)
    	insert_node_at_position(7, temp);
    printf("Insert 7 before 5 \n");
    print_all_node();

    // 4-2. 검색 성공하면 특정 위치 뒤에 노드 추가
    temp = find_node(5);
    if(temp != tail)
    {
    	temp = temp->next;
    	insert_node_at_position(8, temp);
    }
    printf("Insert 8 after 5 \n");
    print_all_node();

    // 4-3. 검색 실패하면 맨 뒤에 노드 추가
    temp = find_node(10);
    if(temp == tail)
    	insert_node(9);
    printf("Insert 9 at then end \n");
    print_all_node();

    // 5. 노드 검색
    temp = find_node(5);
    if(temp == tail)
    	printf("Finding 5 is failure\n");
    else
    	printf("Finding 5 is success\n");

    // 6. 특정노드 삭제
    delete_node(-2);
    printf("delete -2\n");
    print_all_node();

    // 7. 모든노드 삭제 후 이중연결리스트 해제
    printf("Deleting all Node\n");
    delete_all_node();
    release_dlist();

    return;
}

