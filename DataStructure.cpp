// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>

//常量定义
#define listType int
#define stackType int
#define queueType BTNode
#define maxSize 50

//抽象数据类型定义
typedef struct LNode {   //链表
	listType data;
	struct LNode* next;
}LNode, *List;


typedef struct BTNode{   //二叉树
	int data;
	struct BTNode *lchild, *rchild;
} BTNode;


typedef struct Stack {   //栈
	stackType data[maxSize];
	int top;
}Stack;


typedef struct Queue {   //队列
	queueType data[maxSize];
	int front;
	int rear;
}Queue;


typedef struct VertexType {
	int number;
	char info;
}VertexType;

typedef struct MGraphic{
	int edges[maxSize][maxSize];
	int vertexNum, edgeNum;
	VertexType vertexes[maxSize];
}MGraphic;   //图的邻接矩阵


typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextEdge;
	int value;
}ArcNode;

typedef struct VertexNode {
	char data;
	ArcNode* firstEdge;
}VertexNode;

typedef struct AGraphic {
	VertexNode adjList[maxSize];
	int vertexNum, edgeNum;
}AGraphic;   //图的邻接表



//函数声明
List InitList();
int AddList(List list, listType value);
void TraversalList(List list);
int GetListCount(List list);
int IsListEmpty(List list);
int IsAscending(List list);
int IsSymmetry(List list);
List MergeList(List l1, List l2);


Stack InitStack();
int Push(Stack* stack, stackType value);
int Pop(Stack* stack, stackType* value);
int IsStackEmpty(Stack* stack);
int GetStackCount(Stack* stack);

Queue InitQueue();
int EnQueue(Queue* queue, queueType* value);
int DeQueue(Queue* queue, queueType* value);
int IsQueueEmpty(Queue* queue);

BTNode* Create_BTree();
void Pre_Traversal(BTNode* bt);
void In_Traversal(BTNode* bt, List list);
void In_Traversal(BTNode* bt);
void Post_Traversal(BTNode* bt);
void Level_Traversal(BTNode* bt);
int IsBST(BTNode* bt);




//函数实现
List InitList() {
	List list;
	list = (List)malloc(sizeof(LNode));
	if (list == NULL) {
		puts("为链表申请内存空间失败！");
	}
	list->next = NULL;
	return list;
}

int AddList(List list, listType value) {
	LNode* node = (LNode*)malloc(sizeof(LNode));
	if (node == NULL) {
		return 0;
	}
	node->data = value;
	node->next = NULL;
	
	LNode* temp = list;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = node;

	return 1;
}

void TraversalList(List list) {
	LNode* temp = list->next;

	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

int GetListCount(List list) {
	LNode* temp = list;
	int iCount = 0;
	while (temp->next != NULL)
	{
		iCount++;
		temp = temp->next;
	}
	return iCount;
}

int IsListEmpty(List list) {
	return list->next == NULL;
}

int IsAscending(List list) {
	if (GetListCount(list) < 2) {
		return 0;
	}

	LNode* temp = list->next;
	int max;

	while (temp->next != NULL)
	{
		max = temp->data;
		temp = temp->next;
		if (temp->data < max) {
			return 0;
		}	
	}
	return 1;
}

int IsSymmetry(List list) {
	if (list->next == NULL) {
		return 0;
	}

	Stack stack = InitStack();
	LNode* temp = list->next;
	int value;
	while (temp != NULL)
	{
		Push(&stack, temp->data);
		temp = temp->next;
	}

	temp = list->next;

	while (IsStackEmpty(&stack) != 1)
	{
		Pop(&stack, &value);
		if (value != temp->data) {
			return 0;
		}
		temp = temp->next;
	}

	return 1;
}

List MergeList(List l1, List l2) {
	List result = InitList();

	LNode *t1 = l1->next, *t2 = l2->next;
	while (t1 != NULL){
		AddList(result, t1->data);
		t1 = t1->next;
	}
	while (t2 != NULL) {
		AddList(result, t2->data);
		t2 = t2->next;
	}

	return result;
}


Stack InitStack() {
	Stack stack;
	stack.top = -1;

	return stack;
}

int Push(Stack* stack, stackType value) {
	if (stack->top == maxSize - 1) {
		return 0;
	}
	stack->top++;
	stack->data[stack->top] = value;

	return 1;
}

int Pop(Stack* stack, stackType* value) {
	if (stack->top == -1) {
		return 0;
	}
	*value = stack->data[stack->top];
	stack->top--;

	return 1;
}

int IsStackEmpty(Stack* stack) {
	return stack->top == -1;
}

int GetStackCount(Stack* stack) {
	return (stack->top + 1);
}


Queue InitQueue() {
	Queue queue;
	queue.front = queue.rear = 0;

	return queue;
}

int EnQueue(Queue* queue, queueType* value) {
	if ((queue->rear + 1) % maxSize == queue->front){
		return 0;
	}
	queue->rear = (queue->rear + 1) % maxSize;
	queue->data[queue->rear] = *value;

	return 1;
}

int DeQueue(Queue* queue, queueType* value) {
	if (queue->front == queue->rear) {
		return 0;
	}
	queue->front = (queue->front + 1) % maxSize;
	*value = queue->data[queue->front];

	return 1;
}

int IsQueueEmpty(Queue* queue) {
	return queue->front == queue->rear;
}


BTNode* Create_BTree()
{
	int a;
	scanf_s("%d", &a);
	BTNode* node = NULL;
	if (a != 0)
	{
		node = (BTNode*)malloc(sizeof(BTNode));
		node->data = a;
		printf("Please input node %d's left child:", node->data);
		node->lchild = Create_BTree();
		printf("Please input node %d's right child:", node->data);
		node->rchild = Create_BTree();

	}
	return node;
}

void Pre_Traversal(BTNode* bt){
	if (bt != NULL)
	{
		printf("%d ", bt->data);
		Pre_Traversal(bt->lchild);
		Pre_Traversal(bt->rchild);
	}
}

void In_Traversal(BTNode* bt, List list) {
	if (bt != NULL)
	{
		
		In_Traversal(bt->lchild, list);
		AddList(list, bt->data);
		In_Traversal(bt->rchild, list);
	}
}

void In_Traversal(BTNode* bt) {
	if (bt != NULL) {
		In_Traversal(bt->lchild);
		printf("%d ", bt->data);
		In_Traversal(bt->rchild);
	}
}

void Post_Traversal(BTNode* bt) {
	if (bt != NULL) {
		In_Traversal(bt->lchild);
		In_Traversal(bt->rchild);
		printf("%d ", bt->data);
	}
}

void Level_Traversal(BTNode* bt) {
	BTNode* temp = bt;
	Queue queue = InitQueue();

	if (temp != NULL) {
		EnQueue(&queue, temp);
		while (IsQueueEmpty(&queue) != 1)
		{
			DeQueue(&queue, temp);
			printf("%d ", temp->data);

			if (temp->lchild != NULL) {
				EnQueue(&queue, temp->lchild);
			}
			if (temp->rchild != NULL) {
				EnQueue(&queue, temp->rchild);
			}
		}
	}
}

int IsBST(BTNode* bt) {
	List list = InitList();
	In_Traversal(bt, list);
	return IsAscending(list);
}


int main()
{
	

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
