#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUE 200

typedef enum { false, true } bool;
typedef struct TreeNode* Data;

int arr[200] = {0,};

typedef struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	int front, rear;
	Data items[MAX_QUEUE];
} Queue;

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
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1) % MAX_QUEUE;
}

void DeQueue(Queue *pqueue)
{
	if (IsEmpty(pqueue))
		exit(1); // 에러: 비어 있는 큐
	pqueue->front = (pqueue->front + 1) % MAX_QUEUE;
}

TreeNode* levelorder(int arr[], int size) {
	if (size <= 0)
		return NULL;
	
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->val = arr[0];
	root->left = NULL;
	root->right = NULL;
	
	Queue queue;
	InitQueue(&queue);
	EnQueue(&queue, root);
	
	int i = 1;
	while (i < size) {
		TreeNode* parentNode = Peek(&queue);
		DeQueue(&queue);
		
		if (arr[i] != -1) {
			TreeNode* left_child = (TreeNode*)malloc(sizeof(TreeNode));
			left_child->val = arr[i];
			left_child->left = NULL;
			left_child->right = NULL;
			parentNode->left = left_child;
			EnQueue(&queue, left_child);
		}
		else if (arr[i] == -1){
			TreeNode* Node_null = (TreeNode*)malloc(sizeof(TreeNode));
			Node_null->val = arr[i];
			Node_null->left = NULL;
			Node_null->right = NULL;
			parentNode->left = Node_null;
		}
		i++;
		
		if (i < size && arr[i] != -1) {
			TreeNode* right_child = (TreeNode*)malloc(sizeof(TreeNode));
			right_child->val = arr[i];
			right_child->left = NULL;
			right_child->right = NULL;
			parentNode->right = right_child;
			EnQueue(&queue, right_child);
		}
		else if(i< size && arr[i] == -1){
			TreeNode* Node_null = (TreeNode*)malloc(sizeof(TreeNode));
			Node_null->val = arr[i];
			Node_null->left = NULL;
			Node_null->right= NULL;
			parentNode->right = Node_null;
		}
		i++;
	}
	return root;
}

TreeNode* solution(TreeNode* root) {
	if (root == NULL || root->val == -1)
		return NULL;
	
	root->left = solution(root->left);
	root->right = solution(root->right);
	
	if ((root->left == NULL || root->left->val == -1) &&
	    (root->right == NULL || root->right->val == -1) && 
	    root->val == 0) {
		free(root->left);
		free(root->right);
		
		root->left = NULL;
		root->right = NULL;
		
		root->val = -1;
	}
	return root;
}

void printTree(TreeNode* root) {
	if (root == NULL)
		return;
	
	Queue queue;
	InitQueue(&queue);
	EnQueue(&queue, root);
	
	TreeNode* lastNode = NULL;
	TreeNode* lastRightNode = NULL;

	while (!IsEmpty(&queue)) {
		TreeNode* currentNode = Peek(&queue);
		DeQueue(&queue);

		if (currentNode != NULL) {
			lastNode = currentNode;
			if (currentNode->right != NULL) {
				lastRightNode = currentNode->right;
			}
			EnQueue(&queue, currentNode->left);
			EnQueue(&queue, currentNode->right);
		}
	}
	// 다시 큐를 초기화하고 마지막 오른쪽 노드를 제외한 노드들을 출력
	InitQueue(&queue);
	EnQueue(&queue, root);
	while (!IsEmpty(&queue)) {
		TreeNode* currentNode = Peek(&queue);
		DeQueue(&queue);
		if (currentNode != NULL) {
			if (currentNode != lastRightNode || currentNode->val != -1) {
				printf("%d ", currentNode->val);
			}
			EnQueue(&queue, currentNode->left);
			EnQueue(&queue, currentNode->right);
		}
	}
}

int main() {

	// 수정하지 마시오 //
	int i = 0, cnt = 0;
	char str[400] = {0,};
	char *s;
	scanf("%[^\n]", str);
	for (i = 2; i > 1; cnt += i > 0) {
		i = sscanf(str, "%d%*[ ]%[^\n]", &arr[cnt], str);
	}
	// 위 코드를 수행하면 arr에는 각 원소에 입력으로 받은 노드들이 저장됩니다.
	///////////////////
	
	TreeNode* root = levelorder(arr, cnt);
	root = solution(root);
	// 트리를 배열 형태로 출력
	printTree(root);
	return 0;
}
