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



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int isEmpty();
void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
        
		printf("성명: 신태양\n");
		printf("학번: 2017038096\n");
		printf("Command = ");
		scanf(" %c", &command);

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
			deleteNode(head->left, key);
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
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = NULL;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
  Node* ptr; 
  top = -1; 
  ptr = node; 
  while(1) { 
      while(ptr != NULL) { 
          push(ptr);
          ptr = ptr->left; 
          } 
          ptr = pop(); 
          if(ptr == NULL) break; 
          printf(" [%d] ", ptr->key); 
          ptr = ptr->right; 
       }
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
if (!ptr)
		return;
	
	enQueue(ptr);  

	while (1) {
		ptr = deQueue();
		if (ptr)
		{
			printf(" [%d] ", ptr->key);

			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else
			break; 
	}
}

int isEmpty(){
 if(top == -1) {
	 printf("Error : Stack is empty. \n");
	 return 1;
 }
 return 0;
}

void printStack() {
	if(!isEmpty()) {
		for(int i=0; i <= top; i++){
			printf(" [%d] ", stack[i]->key);
		}
		printf("\n");
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
Node *p,*child,*succ,*succ_p,*t;

 //key를 갖는 노드 t를 탐색, p는 t의 부모노드

 p = NULL;

 t = head;

 //key를 갖는 노드 t를 탐색한다.

 while(t != NULL && t->key != key){

  p = t;

  t = (key<t->key)? t->left:t->right;

 }

 //탐색이 종료된 시점에세 t가 NULL이면 트리안에 key가 없음

 if(t == NULL){//탐색트리에 없는 키

  printf("key is not in the tree");

  return -1;

 }

 //첫번째 경우:단말노드인 경우

 if(t->left == NULL && t->right == NULL){

         if(p != NULL){

                 //부모노드의 자식 필드를 NULL로 만든다.

                 if(p->left==t)

                         p->left=NULL;

                 else p->right=NULL;

         }



  else//만약 부모노드가 NULL이면 삭제되는 노드가 루트

   head = NULL;
   free(t);
}



 //두번째 경우 : 하나의 자식만을 가지는 경우

 else if((t->left==NULL) || (t->right == NULL)){

  child = (t->left!=NULL)? t->left:t->right;

  if(p != NULL){

          if(p->left ==t)//부모를 자식과 연결

                  p->left=child;

  else p->right = child;

  }

 else //만약 부모노드가 NULL이면 삭제되는 노드가 루트

         head=child;
 free(t);
 }

//세번째 경우: 두개의 자식을 가지는 경우

 else{

//오른쪽 서브 트리에서 후계자를 찾는다.

         succ_p = t;

         succ = t->right;

  //후계자를 찾아 계속 왼쪽으로 이동한다.

  while(succ->left != NULL){

   succ_p = succ;

   succ = succ->left;

  }

  //후속자와 부모와 자식을 연결
   int temp = succ->key;
      succ->key=t->key;
      t->key=temp;
      deleteNode(succ_p, key);
 }

 

 return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
 Node* node = NULL; 
 if(top == -1) { 
     return node; 
     } 
     node = stack[top]; 
     top--; 
     return node;
}

void push(Node* aNode)
{
if(top >= MAX_STACK_SIZE-1) { 
    return; 
    } 
    top++; 
    stack[top] = aNode;


}



Node* deQueue()
{
 Node* node = NULL; 
 if(front == rear) { 
     return node; 
} 
     front++; 
     node = queue[front]; 
     return node;

}

void enQueue(Node* aNode)
{
 if(rear == MAX_QUEUE_SIZE-1) { 
     return; 
} 
     
     rear++; 
     queue[rear] = aNode;

}





