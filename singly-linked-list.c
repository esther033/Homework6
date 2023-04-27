#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //listNode ����ü ����
	int key;
	struct Node* link;
} listNode;

typedef struct Head { //headNode ����ü ����
	struct Node* first;
}headNode;

headNode* initialize(headNode* h); //headNode�� �ʱ�ȭ�ϴ� �Լ�
int freeList(headNode* h); //����Ʈ�� �޸𸮸� �����ϴ� �Լ�

int insertFirst(headNode* h, int key); //����Ʈ�� ù��°��忡 ��带 �����ϴ� �Լ�
int insertNode(headNode* h, int key); //����Ʈ�� ��带 �����ϴ� �Լ�
int insertLast(headNode* h, int key); //����Ʈ�� ��������忡 ��带 �����ϴ� �Լ�

int deleteFirst(headNode* h); //����Ʈ�� ù��°��忡 ��带 �����ϴ� �Լ�
int deleteNode(headNode* h, int key); //����Ʈ�� ��带 �����ϴ� �Լ�
int deleteLast(headNode* h); //����Ʈ�� ��������忡 ��带 �����ϴ� �Լ�
int invertList(headNode* h); //����Ʈ�� �������� ���ġ�ϴ� �Լ�

void printList(headNode* h); //����Ʈ�� ����ϴ� �Լ�

int main()
{
	printf("[----- [�ڿ�����]  [2022041054] -----]\n"); 
	char command; //����ڿ��� �Է¹��� �޴� ���� ����
	int key; //����ڿ��� �Է¹��� ���� key ����
	headNode* headnode=NULL; //headNode����ü headNode�� ���� �� NULL�� �ʱ�ȭ

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
		scanf(" %c", &command); //����ڿ��� �޴��� �Է¹޴´�

		switch(command) { //commad�� ���� ���� ����
		case 'z': case 'Z': //command�� z or Z�϶�
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': //command�� p or P�϶�
			printList(headnode);
			break;
		case 'i': case 'I': //command�� i or I�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //command�� d or D�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			deleteNode(headnode, key);
			break; 
		case 'n': case 'N': //command�� n or N�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //command�� e or E�϶�
			deleteLast(headnode);
			break;
		case 'f': case 'F': //command�� f or F�϶�
			printf("Your Key = ");
			scanf("%d", &key); //����ڿ��� key���� �Է¹޴´�
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //command�� t or T�϶�
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //command�� r or R�϶�
			invertList(headnode);
			break; 
		case 'q': case 'Q': //command�� q or Q�϶�
			freeList(headnode);
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1; //�Լ� ����
}

headNode* initialize(headNode* h) { //headNode�� �ʱ�ȭ�ϴ� �Լ�

	//headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if(h != NULL)
		freeList(h);

	//headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){ //����Ʈ�� �޸𸮸� �����ϴ� �Լ�
	listNode* p = h->first; //listNode����ü *p ���� �� headNode�� first ����

	listNode* prev = NULL; //listNode����ü prev ���� �� NULL����
	while(p != NULL) { //�ݺ����� ����Ͽ� ����� listNode���� �޸� ����
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h); //headNode�޸� ����
	return 0;
}


int insertNode(headNode* h, int key) { //��带 �����ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode����ü node�� ���� �� �����޸� �Ҵ�
	node->key = key; //node�� ������� key�� �Ű����� key����
	node->link = NULL; //node�� �������ü link�� NULL����

	if (h->first == NULL) //headNode�� �������ü first�� NULL�̸�
	{
		h->first = node; //headNode�� �������ü first�� node����
		return 0; //�Լ� ����
	}

	listNode* n = h->first; //listNode����ü n�� ���� �� headNode�� �������ü first ����
	listNode* trail = h->first; //listNode����ü trail�� ���� �� headNode�� �������ü first ����

	while(n != NULL) { //n��NULL�϶� ���� �ݺ�
		if(n->key >= key) {//ù ����� Ű�� �Ű����� Ű���� ���� Ŭ�� 
			if(n == h->first) { //n�� ù���� ���� ��
				h->first = node; //������ ��带 headNode�� �ٲ۴�
				node->link = n; //����� link�� headNode�� �ٲ۴�
			} else { //key�� �߰��̳� �������϶�
				node->link = n; //node�� link�� n����
				trail->link = node; //trail�� link�� node����
			}
			return 0; //�Լ� ����
		}

		trail = n; //trail�� n����
		n = n->link; //n�� n�� ���� ��带 ����
	}

	trail->link = node; //trail�� ����Ű�� ��尡 ������ ����̱� ������ trail�� link�� node�� ����
	return 0; //�Լ� ����
}

int insertLast(headNode* h, int key) { //����� �������� ��带 �߰��ϴ� �Լ� 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode����ü node�� ���� �� �����޸� �Ҵ�
	node->key = key; //node�� ������� key�� �Ű����� key����
	node->link = NULL; //node�� �������ü link�� NULL����

	if (h->first == NULL) //ù��° ��尡 NULL�϶�
	{
		h->first = node; //ù��° ��忡 ������ node ����
		return 0; //�Լ� ����
	}

	listNode* n = h->first; //listNode����ü n�� ���� �� ù��° ��� ����
	while(n->link != NULL) { //n�� link�� NULL�϶�
		n = n->link; //n�� n�� ���� ��� ����
	}
	n->link = node; //n�� ���� ��忡 ������ node ����
	return 0;
}

int insertFirst(headNode* h, int key) { //����� ó���� ��带 �߰��ϴ� �Լ� 

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode����ü node�� ���� �� �����޸� �Ҵ�
	node->key = key; //node�� ������� key�� �Ű����� key����

	listNode* n=h->first;
	h->first=node;
	node->link=n;


	return 0; //�Լ� ����
}

int deleteNode(headNode* h, int key) { //��带 �����ϴ� �Լ�

	if (h->first == NULL) //ù��° ��尡 NULL�϶�
	{
		printf("nothing to delete.\n"); //���� �� ��尡 ����
		return 0; //�Լ�����
	}

	listNode* n = h->first; //listNode����ü n�� ���� �� ù��° ���� ����
	listNode* trail = NULL; //listNode����ü trail�� ���� �� NULL ����

	while(n != NULL) { //n�� NULL�϶����� �ݺ�
		if(n->key == key) { //����� key�� ������ key�� ������
			if(n == h->first) { //n�� ù��° ����� ���
				h->first = n->link; //ù��° ��忡 n�� link ����
			} else { //�����ؾ��� ��尡 ù��°��尡 �ƴѰ��
				trail->link = n->link;//trail�� link�� n�� link����
			}
			free(n); //n�� �޸� ����
			return 0; //�Լ� ����
		}

		trail = n; //trail�� n����
		n = n->link; //n�� n�� link ����
	}

	printf("cannot find the node for key = %d\n", key); // ã�� �� �Ѱ�� 
	return 0; //�Լ� ����
}

int deleteLast(headNode* h) { //����� �������� �����ϴ� �Լ�

	if (h->first == NULL) //ù��° ��尡 NULL�϶�
	{
		printf("nothing to delete.\n"); //������ ��尡 �����ϴ�
		return 0; //�Լ� ����
	}

	listNode* n = h->first; //listNode����ü n�� ���� �Ŀ� ù��° ��� ����
	listNode* trail = NULL; //listNode����ü trail�� ���� �Ŀ� NULL ����

	if(n->link == NULL) { //��尡 �ϳ��϶� 
		h->first = NULL; //ù��° ��忡 NULL ����
		free(n); //n�� �޸� ����
		return 0; // �Լ� ����
	}

	while(n->link != NULL) { //n�� link�� NULL �϶����� �ݺ�
		trail = n; //trail�� n����
		n = n->link; //n�� n�� link����
	}

	trail->link = NULL; //trail�� link�� NULL����
	free(n); //n�� �޸� ����

	return 0; //�Լ� ����
}

int deleteFirst(headNode* h) { //ù��° ��带 �����ϴ� �Լ�

	if (h->first == NULL) //ù��° ��尡 NULL�϶�
	{
		printf("nothing to delete.\n"); //���� �� ��尡 �����ϴ�.
		return 0; //�Լ� ����
	}
	listNode* n = h->first; //listNode����ü n�� ���� �� ù��° ��� ����

	h->first = n->link; //ù��° ����� link�� n�� link ����
	free(n); //n�� �޸� ����

	return 0; //�Լ� ����
}


int invertList(headNode* h) { //list�� �������� ���ġ�ϴ� �Լ�


	if(h->first == NULL) { //h�� first�� NULL�϶� 
		printf("nothing to invert...\n"); //���ġ�� list�� ����
		return 0; //�Լ� ����
	}
	listNode *n = h->first; //listNode ��ü n���� �� ù��° ��� ����
	listNode *trail = NULL; //listNode ��ü trail���� �� NULL����
	listNode *middle = NULL; //listNode ��ü middle���� �� NULL����

	while(n != NULL){ //n�� NULL�϶����� �ݺ�
		trail = middle; //trail�� middle����
		middle = n;  //trail�� n����
		n = n->link; //n�� n�� ���� �������
		middle->link = trail; //middle�� ���� ��忡 trail����
	}

	h->first = middle; //h�� ù��° ��忡 miiddle ����

	return 0;
}


void printList(headNode* h) { //list�� ����ϴ� �Լ�
	int i = 0; //���� i���� �� 0���� �ʱ�ȭ
	listNode* p; //listNode����ü *p����

	printf("\n---PRINT\n"); 

	if(h == NULL) { //h�� NULL�̸�
		printf("Nothing to print....\n");
		return; //�Լ� ����
	}

	p = h->first; //p�� h�� frist ����

	while(p != NULL) { //p�� NULL�� �ɶ����� 
		printf("[ [%d]=%d ] ", i, p->key); //list ���
		p = p->link; //p�� p�� link�� �����Ѵ�
		i++; //i++
	}

	printf("  items = %d\n", i); //list�� ������ ���
}