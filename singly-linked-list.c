#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { //struct Node 선언
	int key;
	struct Node* link; //포인터 link 선언
} listNode;

typedef struct Head {//struct Head 선언
	struct Node* first; //포인터 first 선언
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //headNode에 메모리를 할당하여 초기화하는 함수 선언
int freeList(headNode* h); //할당된 메모리를 해제하는 함수 선언

int insertFirst(headNode* h, int key); //list 처음에 key에 대한 노드하나를 추가하는 함수 선언
int insertNode(headNode* h, int key); //리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 함수 선언
int insertLast(headNode* h, int key); //list에 key에 대한 노드하나를 추가하는 함수 선언

int deleteFirst(headNode* h); //list의 첫 노드 삭제 함수 선언
int deleteNode(headNode* h, int key); //list에서 key에 대한 노드 삭제하는 함수 선언
int deleteLast(headNode* h); //list의 마지막 노드 삭제하는 함수 선언
int invertList(headNode* h); //list의 링크를 역순으로 재 배치하는 함수 선언

void printList(headNode* h); //list 출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL; //headnode에 대한 포인터 headnode 선언 및 초기화

	do{
		printf("----------[변재윤][2022041046]------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': //입력 받은 문자가 z 또는 Z일때
        case 'Z':
			headnode = initialize(headnode); //headnode에 initialize 함수의 리턴 값 대입
			break;
		case 'p': //입력 받은 문자가 p 또는 P일때
        case 'P':
			printList(headnode); //printList 함수 호출
			break;
		case 'i'://입력 받은 문자가 i 또는 I일때
        case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //inserNode 함수 호출
			break;
		case 'd': //입력 받은 문자가 d 또는 D일때
        case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);// deleteNode 함수 호출
			break;
		case 'n': //입력 받은 문자가 n 또는 N일때
        case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);//insertLast 함수 호출
			break;
		case 'e': //입력 받은 문자가 e 또는 E일때
        case 'E':
			deleteLast(headnode); //deleteLast함수 호출
			break;
		case 'f': //입력 받은 문자가 f 또는 F일때
        case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);//insertFirst 함수 호출
			break;
		case 't': //입력 받은 문자가 t 또는 T일때
        case 'T':
			deleteFirst(headnode); //deleteFirst 함수 호출
			break;
		case 'r': //입력 받은 문자가 r 또는 R일때
        case 'R':
			invertList(headnode); //invertList 함수 호출
			break;
		case 'q': //입력 받은 문자가 q 또는 Q일때
        case 'Q':
			freeList(headnode); //freeList 함수 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q 또는 Q가 입력되지 않는 동안 반

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL) //만약 h가 NULL이 아니라면
		freeList(h); // 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); //headNode의 크기만큼 temp에 저장
	temp->first = NULL; //temp의 first에 NULL 저장
	return temp; //temp 반환
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //listNode 포인터 p 선언 후 h를 통해 first 연결하여 p에 저장

	listNode* prev = NULL; //listNode 포인터 prev 선언 후 NULL로 초기화
	while(p != NULL) {//p가 NULL이 아닐 때까지
		prev = p; //prev에 p 저장
		p = p->link; // p의 link를 p에 저장
		free(prev); //메모리 해제
	}
	free(h);//메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode의 포인터 node에 listnode 크기의 메모리를 할당
	node->key = key; // node의 key에 key 저장
	node->link = NULL; //node의 link에 NULL값 저장

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node를 저장
		return 0;
	}

	listNode* n = h->first; //포인터 n에 h의 first를 저장
	listNode* trail = h->first; //포인터 trail 에 h의 first를 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n이 != NULL일 때까지
		if(n->key >= key) {//만약 n의 key가 입력받은 key보다 크다면
            /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //만약 n이 first일 경우
				h->first = node; //n이 first라면
				node->link = n; //n을 node의 link에 저장
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; //n을 node의 link에 저장
				trail->link = node; //trail의 link에 node를 저장
			}
			return 0;
		}

		trail = n; //trail에 n을 저장
		n = n->link; //n에 n의 link를 저장
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; //trail의 link에 node 저장
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //포인터node에 listnode 크기 만큼의 메모리 할당
	node->key = key; //node의 key에 입력받은 key값 저장
	node->link = NULL; //node의 link에 NULL값 저장

	if (h->first == NULL) //만약 h의 first가 NULL이라면
    {
	
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //listnode n에 h의 first 저장
	while(n->link != NULL) { //n의 link!=NULL일 때까지
		n = n->link; //n에 n의 link 저장
	}
	n->link = node; //n의 link에 node 저장
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node에 listNode 크기만큼의 메모리 할당
	node->key = key;  //node의 key에 입력받은 key 저장

	node->link = h->first; //node의 link에 h의 시작주소 저장
	h->first = node; //first에 node 저장

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //포인터 n에 h의 first 저장
	listNode* trail = NULL; //포인터 trail 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n!=NULL일 때까지
		if(n->key == key) { //만약 n의 key가 입력된 key와 같다면
			//n의 key가 입력된 key와 같을때
			if(n == h->first) { //만약 n가 h의 first라면
				h->first = n->link; //n의 link를 h의 frist에 저장
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //n의 link를 trail의 link에 저장
			}
			free(n); //메모리 해제
			return 0;
		}

		trail = n; //trail에 n 저장
		n = n->link; //n에 n의 link를 저장 
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //n에 h의 frist 저장
	listNode* trail = NULL; //trail 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { //만약 n의  link가 NULL이라면
		h->first = NULL; //h의 first를 NULL로 초기화
		free(n); // 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {  //n->link != NULL일 때까지
		trail = n; //trail에 n 저장
		n = n->link; //n에 n의 link 저장
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; //trail의 link  NULL로 초기화
	free(n); //메모리 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //만약 h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //n에 h의 first를 저장

	h->first = n->link; //h의 first에 n의 link 저장
	free(n); //메모리 해제

	return 0;
}


/*
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {//만약 h의 first가 NULL이라면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //포인터 n에 h의 first 저장
	listNode *trail = NULL; //포인터 trail NULL로 초기화
	listNode *middle = NULL; //포인터 middle NULL로 초기화

	while(n != NULL){ //n!=NULL일 때까지
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n 저장
		n = n->link; //n에 n의 link 저장
		middle->link = trail; //middle의 link에 trail 저장 
	}

	h->first = middle; //h의 first에 middle 저장

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //만약 h가 NULL이라면 
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p에 h의 first 저장

	while(p != NULL) { //p가 NULL이 아닐 때까지
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; //p에 p의 link 저장
		i++; //i 증가
	}

	printf("  items = %d\n", i);
}
