//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstNode
{
	int item;
	struct _bstNode *left;
	struct _bstNode *right;
} BSTNode; // You should not change the definition of BSTNode

typedef struct _stackNode
{
	BSTNode *data;
	struct _stackNode *next;
} StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
} Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root)
{
	// 	현재 노드(current)를 루트로 설정하고, 마지막으로 방문한 노드(lastVisited)를 NULL로 초기화합니다.
	// current가 NULL이 아니거나 스택이 비어있지 않은 동안 다음을 반복합니다:
	// a. current가 NULL이 아니면:
	// current를 스택에 푸시합니다.
	// current를 왼쪽 자식으로 이동합니다.
	// b. current가 NULL이면:
	// 스택의 top에 있는 노드를 확인합니다(peek).
	// 만약 이 노드에 오른쪽 자식이 있고, 그 오른쪽 자식이 마지막으로 방문한 노드가 아니라면:
	// current를 오른쪽 자식으로 설정합니다.
	// 그렇지 않다면 (왼쪽, 오른쪽 자식을 모두 방문했거나 자식이 없는 경우):
	// 노드의 값을 출력합니다.
	// 노드를 스택에서 팝하고 lastVisited로 설정합니다.
	// 이 방법이 후위 순회를 올바르게 수행하는 이유는 다음과 같습니다:
	// 왼쪽 서브트리를 전부 탐색한 후에야 오른쪽 서브트리로 이동합니다.
	// 오른쪽 서브트리를 전부 탐색한 후에야 현재 노드를 출력합니다.
	// lastVisited 변수를 사용하여 오른쪽 자식 노드의 처리 여부를 추적합니다.

	if (root == NULL)
		return;

	Stack s = {NULL};
	BSTNode *current = root;
	BSTNode *lastVisited = NULL;

	while (current != NULL || !isEmpty(&s))
	{
		if (current != NULL)
		{
			push(&s, current);
			current = current->left;
		}
		else
		{
			BSTNode *peekNode = peek(&s);

			if (peekNode->right != NULL && lastVisited != peekNode->right)
			{
				current = peekNode->right;
			}
			else
			{
				printf("%d ", peekNode->item);
				lastVisited = pop(&s);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value > (*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode *pop(Stack *s)
{
	StackNode *temp, *t;
	BSTNode *ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode *peek(Stack *s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
