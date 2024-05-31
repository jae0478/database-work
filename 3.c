#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 1 2 3 4 5 6
int arr[200] = {0,};
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new TreeNode
TreeNode* newTreeNode(int value) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    if (!node) return NULL;
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create a new queue node
Node* newNode(TreeNode *node) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->treenode = node;
    new_node->next = NULL;
    return new_node;
}

// Function to add to queue
void enqueue(Node **head, TreeNode *node) {
    Node *new_node = newNode(node);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Function to remove from queue
TreeNode* dequeue(Node **head) {
    if (*head == NULL) return NULL;
    Node* temp = *head;
    TreeNode* result = temp->treenode;
    *head = temp->next;
    free(temp);
    return result;
}

// Function to create a tree from an array
TreeNode* createTree(int array[], int len) {
    if (array == NULL || len == 0) {
        return NULL;
    }

    Node *treeNodeQueue = NULL;
    int index = 1;
    
    TreeNode *treeNode = newTreeNode(array[0]);
    enqueue(&treeNodeQueue, treeNode);

    while (index < len) {
        TreeNode *current = dequeue(&treeNodeQueue);
        if (index < len && array[index] != -1) { // assuming -1 as NULL
            TreeNode *left = newTreeNode(array[index]);
            current->left = left;
            enqueue(&treeNodeQueue, left);
        }
        index++;
        if (index < len && array[index] != -1) { // assuming -1 as NULL
            TreeNode *right = newTreeNode(array[index]);
            current->right = right;
            enqueue(&treeNodeQueue, right);
        }
        index++;
    }
    return treeNode;
}

int* treeToArray(TreeNode *root, int *size) {
    if (root == NULL) {
        *size = 0;
        return NULL;
    }

    int capacity = 200;
    int *array = (int *)malloc(capacity * sizeof(int));
    Node *queue = NULL;
    enqueue(&queue, root);
    int count = 0;

    while (queue != NULL) {
        TreeNode *current = dequeue(&queue);
        if (current == NULL) {
            array[count++] = -1;
        } else {
            if (count == capacity) {
                capacity *= 2;
                array = (int *)realloc(array, capacity * sizeof(int));
            }
            array[count++] = current->val;
            enqueue(&queue, current->left);
            enqueue(&queue, current->right);
        }
    }

    // Trim the array to remove extra null entries at the end
    while (count > 0 && array[count - 1] == -1) {
        count--;
    }

    *size = count;
    return array;
}


TreeNode* solution (TreeNode * root) {
	// good luck
	return root;
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
	
	TreeNode* root = createTree(arr, cnt);
	
	
	///////////////////
	
	root = solution(root);
	
	// print tree as array
	
	int size = 0;
	int *array = treeToArray(root, &size);
	for (int i = 0; i < size; i++) {
			printf("%d ", array[i]);
	}
	printf("\n");
	free(array);

	return 0;
}
