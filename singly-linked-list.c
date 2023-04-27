#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //listNode 구조체 선언
	int key;
	struct Node* link;
} listNode;

typedef struct Head { //headNode 구조체 선언
	struct Node* first;
}headNode;

headNode* initialize(headNode* h); //headNode를 초기화하는 함수
int freeList(headNode* h); //리스트의 메모리를 해제하는 함수

int insertFirst(headNode* h, int key); //리스트의 첫번째노드에 노드를 삽입하는 함수
int insertNode(headNode* h, int key); //리스트에 노드를 삽입하는 함수
int insertLast(headNode* h, int key); //리스트의 마지막노드에 노드를 삽입하는 함수

int deleteFirst(headNode* h); //리스트의 첫번째노드에 노드를 삭제하는 함수
int deleteNode(headNode* h, int key); //리스트에 노드를 삭제하는 함수
int deleteLast(headNode* h); //리스트의 마지막노드에 노드를 삭제하는 함수
int invertList(headNode* h); //리스트를 역순으로 재배치하는 함수

void printList(headNode* h); //리스트를 출력하는 함수

int main()
{
	printf("[----- [박에스더]  [2022041054] -----]\n"); 
	char command; //사용자에게 입력받을 메뉴 변수 선언
	int key; //사용자에게 입력받을 변수 key 선언
	headNode* headnode=NULL; //headNode구조체 headNode을 선언 후 NULL로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자에게 메뉴를 입력받는다

		switch(command) { //commad의 값에 따라 실행
		case 'z': case 'Z': //command가 z or Z일때
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': //command가 p or P일때
			printList(headnode);
			break;
		case 'i': case 'I': //command가 i or I일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //command가 d or D일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			deleteNode(headnode, key);
			break; 
		case 'n': case 'N': //command가 n or N일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //command가 e or E일때
			deleteLast(headnode);
			break;
		case 'f': case 'F': //command가 f or F일때
			printf("Your Key = ");
			scanf("%d", &key); //사용자에게 key값을 입력받는다
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //command가 t or T일때
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //command가 r or R일때
			invertList(headnode);
			break; 
		case 'q': case 'Q': //command가 q or Q일때
			freeList(headnode);
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1; //함수 종료
}

headNode* initialize(headNode* h) { //headNode를 초기화하는 함수

	//headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(h != NULL)
		freeList(h);

	//headNode에 대한 메모리를 할당하여 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){ //리스트의 메모리를 해제하는 함수
	listNode* p = h->first; //listNode구조체 *p 선언 후 headNode의 first 저장

	listNode* prev = NULL; //listNode구조체 prev 선언 후 NULL저장
	while(p != NULL) { //반복문을 사용하여 연결된 listNode들을 메모리 해제
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h); //headNode메모리 해제
	return 0;
}


int insertNode(headNode* h, int key) { //노드를 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 node를 선언 후 동적메모리 할당
	node->key = key; //node의 멤버변수 key에 매개변수 key저장
	node->link = NULL; //node의 멤버구조체 link에 NULL저장

	if (h->first == NULL) //headNode의 멤버구조체 first가 NULL이면
	{
		h->first = node; //headNode의 멤버구조체 first에 node저장
		return 0; //함수 종료
	}

	listNode* n = h->first; //listNode구조체 n을 선언 후 headNode의 멤버구조체 first 저장
	listNode* trail = h->first; //listNode구조체 trail을 선언 후 headNode의 멤버구조체 first 저장

	while(n != NULL) { //n이NULL일때 까지 반복
		if(n->key >= key) {//첫 노드의 키가 매개변수 키보다 값이 클때 
			if(n == h->first) { //n이 첫노드와 같을 때
				h->first = node; //삽입할 노드를 headNode로 바꾼다
				node->link = n; //노드의 link도 headNode로 바꾼다
			} else { //key가 중간이나 마지막일때
				node->link = n; //node의 link에 n저장
				trail->link = node; //trail의 link에 node저장
			}
			return 0; //함수 종료
		}

		trail = n; //trail에 n저장
		n = n->link; //n에 n의 다음 노드를 저장
	}

	trail->link = node; //trail이 가리키는 노드가 마지막 노드이기 때문에 trail의 link에 node를 저장
	return 0; //함수 종료
}

int insertLast(headNode* h, int key) { //노드의 마지막에 노드를 추가하는 함수 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 node를 선언 후 동적메모리 할당
	node->key = key; //node의 멤버변수 key에 매개변수 key저장
	node->link = NULL; //node의 멤버구조체 link에 NULL저장

	if (h->first == NULL) //첫번째 노드가 NULL일때
	{
		h->first = node; //첫번째 노드에 삽입할 node 저장
		return 0; //함수 종료
	}

	listNode* n = h->first; //listNode구조체 n를 선언 후 첫번째 노드 저장
	while(n->link != NULL) { //n의 link가 NULL일때
		n = n->link; //n에 n의 다음 노드 저장
	}
	n->link = node; //n의 다음 노드에 삽입할 node 저장
	return 0;
}

int insertFirst(headNode* h, int key) { //노드의 처음에 노드를 추가하는 함수 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode구조체 node를 선언 후 동적메모리 할당
	node->key = key; //node의 멤버변수 key에 매개변수 key저장

	listNode* n=h->first;
	h->first=node;
	node->link=n;


	return 0; //함수 종료
}

int deleteNode(headNode* h, int key) { //노드를 삭제하는 함수

	if (h->first == NULL) //첫번째 노드가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제 할 노드가 없다
		return 0; //함수종료
	}

	listNode* n = h->first; //listNode구조체 n을 선언 후 첫번째 노즈 저장
	listNode* trail = NULL; //listNode구조체 trail를 선언 후 NULL 저장

	while(n != NULL) { //n이 NULL일때까지 반복
		if(n->key == key) { //노드의 key가 삭제할 key와 같을때
			if(n == h->first) { //n이 첫번째 노드일 경우
				h->first = n->link; //첫번째 노드에 n의 link 저장
			} else { //삭제해야할 노드가 첫번째노드가 아닌경우
				trail->link = n->link;//trail의 link에 n의 link저장
			}
			free(n); //n의 메모리 해제
			return 0; //함수 종료
		}

		trail = n; //trail에 n저장
		n = n->link; //n에 n의 link 저장
	}

	printf("cannot find the node for key = %d\n", key); // 찾지 못 한경우 
	return 0; //함수 종료
}

int deleteLast(headNode* h) { //노드의 마지막을 삭제하는 함수

	if (h->first == NULL) //첫번째 노드가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제할 노드가 없습니다
		return 0; //함수 종료
	}

	listNode* n = h->first; //listNode구조체 n을 선언 후에 첫번째 노드 저장
	listNode* trail = NULL; //listNode구조체 trail을 선언 후에 NULL 저장

	if(n->link == NULL) { //노드가 하나일때 
		h->first = NULL; //첫번째 노드에 NULL 저장
		free(n); //n의 메모리 해제
		return 0; // 함수 종료
	}

	while(n->link != NULL) { //n의 link가 NULL 일때까지 반복
		trail = n; //trail에 n저장
		n = n->link; //n에 n의 link저장
	}

	trail->link = NULL; //trail의 link에 NULL저장
	free(n); //n의 메모리 해제

	return 0; //함수 종료
}

int deleteFirst(headNode* h) { //첫번째 노드를 삭제하는 함수

	if (h->first == NULL) //첫번째 노드가 NULL일때
	{
		printf("nothing to delete.\n"); //삭제 할 노드가 없습니다.
		return 0; //함수 종료
	}
	listNode* n = h->first; //listNode구조체 n을 선언 후 첫번째 노드 저장

	h->first = n->link; //첫번째 노드의 link에 n의 link 저장
	free(n); //n의 메모리 해제

	return 0; //함수 종료
}


int invertList(headNode* h) { //list를 역순으로 재배치하는 함수


	if(h->first == NULL) { //h의 first가 NULL일때 
		printf("nothing to invert...\n"); //재배치할 list가 없다
		return 0; //함수 종료
	}
	listNode *n = h->first; //listNode 객체 n선언 후 첫번째 노드 저장
	listNode *trail = NULL; //listNode 객체 trail선언 후 NULL저장
	listNode *middle = NULL; //listNode 객체 middle선언 후 NULL저장

	while(n != NULL){ //n이 NULL일때까지 반복
		trail = middle; //trail에 middle저장
		middle = n;  //trail에 n저장
		n = n->link; //n에 n의 다음 노드저장
		middle->link = trail; //middle의 다음 노드에 trail저장
	}

	h->first = middle; //h의 첫번째 노드에 miiddle 저장

	return 0;
}


void printList(headNode* h) { //list를 출력하는 함수
	int i = 0; //변수 i선언 후 0으로 초기화
	listNode* p; //listNode구조체 *p선언

	printf("\n---PRINT\n"); 

	if(h == NULL) { //h가 NULL이면
		printf("Nothing to print....\n");
		return; //함수 종료
	}

	p = h->first; //p에 h의 frist 저장

	while(p != NULL) { //p가 NULL이 될때까지 
		printf("[ [%d]=%d ] ", i, p->key); //list 출력
		p = p->link; //p에 p의 link를 저장한다
		i++; //i++
	}

	printf("  items = %d\n", i); //list의 개수를 출력
}