#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUE 200

typedef enum { false, true }bool;
typedef int Data;

int arr[200] = {0,};
typedef struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	int front, rear;
	Data items[MAX_QUEUE];
}Queue;

void InitQueue(Queue *pqueue)
{
	pqueue->front = pqueue->rear = 0;
}

bool IsEmpty(Queue *pqueue){
	return pqueue->front == pqueue->rear;
}

bool IsFull(Queue *pqueue){
	return pqueue->front == (pqueue->rear + 1) % MAX_QUEUE;
}

Data Peek(Queue *pqueue){
	if (IsEmpty(pqueue))
		exit(1);
	return pqueue->items[pqueue->front];
}

void EnQueue(Queue *pqueue, Data item)
{
	if (IsFull(pqueue))
		exit(1);
	pqueue->rear = (pqueue->rear + 1) % MAX_QUEUE;
	pqueue->items[pqueue->rear] = item;
	if (pqueue->front == -1)
		pqueue->front = pqueue->rear;
}

void DeQueue(Queue *pqueue)
{
	if (IsEmpty(pqueue))
		exit(1); //error: empty stack
	pqueue->front = (pqueue->front + 1) % MAX_QUEUE;
}

TreeNode* levelorder(int arr[], int size){
	if (size <= 0)
		return NULL;
	
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->val = arr[];
	root->left = NULL;
	root->right = NULL;
	
	Queue queue;
	InitQueue(&queue);
	Enqueue(&queue, root);
	
	int i = 1;
	while(i < size){
		TreeNode* parentNode = Peek(queue);
		Dequeue(queue);
		
		if (arr[i] != -1){
			TreeNode* left_child = (TreeNode*)malloc(sizeof(TreeNode));
			left_child->val = arr[i];
			left_child->left = NULL;
			left_child->right = NULL;
			parentNode->left = left_child;
			Enqueue(queue, left_child);
		}
		else if (arr[i] == -1){
			TreeNode* Node_null = (TreeNode*)malloc(sizeof(TreeNode));
			Node_null->val = arr[i];
			Node_null->left = NULL;
			Node_null->right = NULL;
			parentNode->left = Node_null;
		}
		i++;
		
		if (i<size && arr[i] != -1){
			TreeNode* right_child = (TreeNode*)malloc(sizeof(TreeNode));
			right_child->val = arr[i];
			right_child->left = NULL;
			right_child->right= NULL;
			parentNode->right = right_child;
			Enqueue(queue, right_child);
		}
		else if(i< size && arr[i] == -1){
			TreeNode* Node_null = (TreeNode*)malloc(sizeof(TreeNode));
			Node_null->val = arr[i];
			Node_null->left = NULL;
			Node_null->right= NULL;
			parentNode->right = Node_null;
		}
	}
}
TreeNode* solution (TreeNode * root) {
	// good luck
	
	return root;
}

void printTree(TreeNode* root){
	if (root != NULL){
		printf("%d ", root->val);
		printTree(root->left_child);
		printTree(root->right_child);
	}
}

int main() {

	// DO NOT MODIFY //
	int i=0, cnt=0;
	char str[400] = {0,};
	char *s;
	scanf("%[^\n]", str);	
	for (i = 2; i > 1; cnt += i > 0) {
  	i = sscanf(str, "%d%*[ ]%[^\n]", &arr[cnt], str);
	}
	// 위 코드를 수행하면 arr 에는 각 원소에 입력으로 받은 노드들이 저장됩니다.
	///////////////////
	
	Levelorder(&root);
	root = solution(&root);
	// print tree as array
	printTree(&root);
	return 0;
}
