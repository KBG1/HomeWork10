/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node { //별칭 Node, node구조체 포인터 변수 left,right, 정수형 변수 key를 가지는 구조체 node 선언
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20 //스택 최대 사이즈 20
Node* stack[MAX_STACK_SIZE]; //Node구조체 stack, 크기 20짜리 선언
int top = -1; //top을 -1로 설정

Node* pop(); //Node구조체에 대한 pop함수 선언
void push(Node* aNode); //aNode를 변수로 하는 push함수 선언

/* for queue */
#define MAX_QUEUE_SIZE	20 //최대 큐 사이즈 20설정
Node* queue[MAX_QUEUE_SIZE]; // 20크기만큼의 큐 구조체 선언
int front = -1; //front와 rear를 각각 -1로 초기화
int rear = -1;

Node* deQueue(); //deQueue함수 선언
void enQueue(Node* aNode); //aNode를 변수로 하는 enQueue함수 선언


int initializeBST(Node** h); //Node구조체 이중포인터변수 h를 변수로하는 정수형 함수 initializeBST함수 선언

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */ //Node 구조체 포인터변수 ptr을 변수로하는 중위재귀함수 선언
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */ //Node 구조체 포인터변수 ptr을 변수로하는 중위반복함수 선언
void levelOrder(Node* ptr);	          /* level order traversal */ //Node 구조체 포인터변수 ptr을 변수로하는 levelOrder함수 선언
int insert(Node* head, int key);      /* insert a node to the tree */ //Node 구조체 포인터변수 head, 정수형 변수 key 변수로하는 insert함수 선언
int deleteNode(Node* head, int key);  /* delete the node for the key */ //Node 구조체 포인터변수 head, 정수형 변수 key 변수로하는 deleteNode함수 선언
int freeBST(Node* head); /* free all memories allocated to the tree */ //Node 구조체 포인터변수 head를 변수로하는 freeBST함수 선언

/* you may add your own defined functions if necessary */


void printStack(); //printStack 함수 선언



int main()
{
	char command; //명령어 입력받을 커맨드
	int key; //스택, 큐안에 있는  key값과 비교하기위한 입력받을 키 값
	Node* head = NULL; //head값 초기화

	do{
		printf("\n\n");
		printf("--------------Kim Beom Gyu-----------------2019062022-----------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      printStack                   = p \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //입력받은 명령어 command에 저장

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
		
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //포인터변수 h에 값이 있을때만
		freeBST(*h); //freeBST함수로 h초기화

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //Node구조체 크기만큼 포인터변수 h에 동적 메모리 할당
	(*h)->left = NULL;	/* root */ //*h의 left를 NULL로 초기화
	(*h)->right = *h; //*h의 right은 *h값을
	(*h)->key = -9999; //*h의 key에는 -9999할당

	top = -1; //top 을 -1로

	front = rear = -1; // stack과 마찬가지로 큐의 front와 rear도 -1로 초기화

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) { //ptr에 값이 있으면
		recursiveInorder(ptr->left); //ptr의 left에 대해 재귀중위 함수 실행
		printf(" [%d] ", ptr->key); //ptr의 key값 출력
		recursiveInorder(ptr->right); //ptr의 right에 대해서도 재귀중위 함수 실행
	}
}

void iterativeInorder(Node* node)
{
	for(;;) //무한 루프
	{
		for(; node; node = node->left) //초기값 없고, node의 값까지, 한번 반복 후 node의 left값을 node로 대입하는 반복분
			push(node); //node에 대해 push함수 실행
		node = pop(); //pop함수 실행후 node값에 대입

		if(!node) break; //노드에 값이 없으면 break(이걸로 무한루프 탈출)
		printf(" [%d] ", node->key); //node의 key값 출력

		node = node->right; //node의 right값을 node에 대입
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	int front = rear = -1;

	if(!ptr) return; /* empty tree */ //ptr에 값이 없으면 반환

	enQueue(ptr); //ptr에 대해 enQueue함수 실행

	for(;;) //무한루프 2
	
	{
		ptr = deQueue(); //deQueue함수 실행후 ptr에 대입
		if(ptr) { //ptr에 값이 있으면
			printf(" [%d] ", ptr->key); //ptr의 key값 출력

			if(ptr->left) //ptr의 left에 값이있으면
				enQueue(ptr->left); //enQueue함수 실행
			if(ptr->right) //마찬가지로 left에 값이 있으면
				enQueue(ptr->right); //enQueue함수 실행
		}
		else
			break; //아니면 무한루프 탈출

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //newNode에 Node구조체 크기만큼 동적 메모리 할당
	newNode->key = key; //key값을 newNode의 key값에
	newNode->left = NULL; //newNode의 left와 right에는 NULL대입
	newNode->right = NULL;

	if (head->left == NULL) { //head의 left가 NULL이면
		head->left = newNode; //거기에 newNode의 값 대입
		return 1; 
	}

	/* head->left is the root */
	Node* ptr = head->left; //head의 left값을 ptr에 대입

	Node* parentNode = NULL; //부모노드 초기화
	while(ptr != NULL) { //ptr에 값이 있을때 계속 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr의 key와 key와 값이 같으면 return 1

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr을 부모노드에 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key값이 key값보다 작으면
			ptr = ptr->right; //ptr의 right 값을 ptr에 대입
		else //크면
			ptr = ptr->left; //ptr의 left값을 ptr에 대입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //부모노드의 key값이 key값보다 크면
		parentNode->left = newNode; //newNode값을 부모노드의 left에
	else //작으면
		parentNode->right = newNode; //newNode값을 부모노드의 right에
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이면
		printf("\n Nothing to delete!!\n" );//오류출력
		return -1;
	}

	if (head->left == NULL) { //head의 left가 NULL이여도 오류출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //head의 left을 Nomd구조체 root에 할당



	Node* parent = NULL; //부모노드 초기화
	Node* ptr = root; //ptr에 root값 대입

	while((ptr != NULL)&&(ptr->key != key)) { //ptr에 값이있고, ptr의 key값이 key값과 다를 때 반복
		if(ptr->key != key) { //ptr의 key값이 key값과 다르면
 
			parent = ptr;	/* save the parent */ //parent에 ptr값 대입

			if(ptr->key > key) //ptr의 key값이 key값보다 크면
				ptr = ptr->left; //ptr의 left값을 ptr로
			else//작으면
				ptr = ptr->right; //ptr의 right을 ptr로
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //ptr에 값이 없으면
	{
		printf("No node for key [%d]\n ", key); //key에대한 노드가 없다 오류출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //ptr의 left에 값이없고 right에도 값이 없으면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */ //또, parent에는 값이 있을 시
			if(parent->left == ptr) //parent의 left의 값이 ptr과 같으면
				parent->left = NULL; //parent의 left초기화
			else//다르면
				parent-> right = NULL;//right를 초기화
		} else { //parent에도 값 없으면
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL; //head의 left 초기화

		}

		free(ptr); //ptr에 대한 메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //만약 ptr의 left,right중 하나라도 NULL이라면
	{
		Node* child; //child 구조체변수 선언
		if (ptr->left != NULL) //ptr의 left에 값이 있으면
			child = ptr->left; //ptr의 left값을 child에 할당
		else //없으면
			child = ptr->right; //ptr의 right값 할당

		if(parent != NULL) //부모노드에 값이 있으면
		{
			if(parent->left == ptr) //ptr값과 parent의 left가 같으면
				parent->left = child; //child값을 parent의 left에
			else//다르면
				parent->right = child;//parent의 right값에 child값 할당
		} else { //부모노드 NULL이면
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //child값을 root에다가 넣음
		}

		free(ptr); //ptr에 할당된 메모리 반환
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //candidate변수 선언
	parent = ptr; //ptr값을 parent에


	candidate = ptr->right; //ptr의 right갑승ㄹ candidate에

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) //candidate의 left가 NULL이 아닐때 까지 반복
	{
		parent = candidate; //candidate값을 parent에
		candidate = candidate->left; //candidate의 left값을 candidate로
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //candidate값과 부모의 right 값이 같으면
		parent->right = candidate->right; //candidate의 right값을 부모의 right에 대입
	else //다르면
		parent->left = candidate->right; //candidate의 right값을 부모의 left에 대입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //candidate의 key값을 ptr key값에 넣음

	free(candidate); //candidate에 대한 메모리 반환
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) { //ptr에 값이 있다면
		freeNode(ptr->left); //ptr의 left와 right에 대해 freeNode함수 실행하고
		freeNode(ptr->right);
		free(ptr); //ptr에 할당된 메모리를 반환
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //head의 left가 head와 같으면
	{
		free(head); //head에 할당된 메모리 반환
		return 1;
	}

	Node* p = head->left; //head의 left값을 p에 옮기고

	freeNode(p); //p에 대해 freeNode함수 실행

	free(head); //head에 대해서 메모리 반환함수 실행
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL; //top이 0보다 작으면 반환값 없음
	return stack[top--]; //stack[top]출력후에 top -1 실행
	}

void push(Node* aNode)
{
	stack[++top] = aNode; //top값에 1더하고, stack[++top] 값에 aNode값 대입함
}


void printStack()
{
	int i = 0; //정수형 변수 i선언 및 초기화
	printf("--- stack ---\n"); 
	while(i <= top) //i가 top보다 같거나 작을 때 까지
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); //스택번호와 값 출력
	}
}


Node* deQueue()
{
	if (front == rear) { //front와 rear값이 같으면 큐가 빈것이므로
		// printf("\n....Now Queue is empty!!\n" );
		return NULL; //반환할거 없음
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front값에 front에 1더하고 20으로 나눈 값의 나머지 대입
	return queue[front]; //queue[위에서 계산해서 나온 값] 반환

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear+1을 20으로 나눈 나머지를 rear에 대입
	if (front == rear) { //front, rear가 같으면
		// printf("\n....Now Queue is full!!\n");
		return; //반환 x
	}

	queue[rear] = aNode; //aNode값을 queue[rear]에..
}





