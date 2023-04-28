#include <stdio.h>
#include <stdlib.h>

//* Objective: change pointers and merge both sorted list//
static int countsAllocated = 0;
//***********Open input.txt Powerpoint
struct Node
{
	int value;
	struct Node* next;
};

void printList(struct Node* head)
{
	struct Node* tmp = head; //temp node
	while (tmp != NULL)
	{
		printf("%d ", tmp->value); // value=
		tmp = tmp->next; //traverse
	}
	printf("\n"); //space
}

struct Node* allocateNode(int value)
{
	struct Node* node = (struct Node *) malloc(sizeof(struct Node));
	node->value = value;
	node->next = NULL;
	countsAllocated++;
	return node;
}

struct Node* mergeLists(struct Node* pNumbers1, struct Node* pNumbers2)
{
	struct Node* head = NULL; // pointer to the start of the merged list
	struct Node** ppCurrent = &head; // pointer to a pointer to the current node in the merged list

	while (pNumbers1 != NULL && pNumbers2 != NULL) {
		if (pNumbers1->value < pNumbers2->value) {
			*ppCurrent = pNumbers1;
			pNumbers1 = pNumbers1->next;
		} else {
			*ppCurrent = pNumbers2;
			pNumbers2 = pNumbers2->next;
		}
		ppCurrent = &((*ppCurrent)->next);
	}

	// append the remaining nodes from the non-empty list
	if (pNumbers1 != NULL) {
		*ppCurrent = pNumbers1;
	} else {
		*ppCurrent = pNumbers2;
	}

	return head;
	
}

void insert(struct Node** pHead, int value)
{
	struct Node* newNode = allocateNode(value);
	newNode->next = *pHead;
	*pHead = newNode;
}

void* freeList(struct Node** pHead)
{
	struct Node* tmp = *pHead;
	while (tmp != NULL)
	{	
		*pHead = tmp->next;
		free (tmp);
		tmp = *pHead;
		countsAllocated--;
	}

	return *pHead;
}

int main(void)
{
	int i, numInputs;
	char* str;
	float average;
	int value;
	int index;
	int* numArray = NULL;
	int countOfNums1;
	int countOfNums2;
	struct Node* head1 = NULL;
	struct Node* head2 = NULL;
	struct Node* head3 = NULL;

	FILE* inFile = fopen("input (1).txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		head1 = NULL;
		head2 = NULL;
		head3 = NULL;
		fscanf(inFile, " %d %d\n", &countOfNums1, &countOfNums2);
		for (i = 0; i < countOfNums1; i++)
		{
			fscanf(inFile," %d", &value);
			insert(&head1, value);
		}
		for (i = 0; i < countOfNums2; i++)
		{
			fscanf(inFile, " %d", &value);
			insert(&head2, value);
		}

		printf("List 1:\n");
		printList(head1);
		printf("List 2:\n");
		printList(head2);

		printf("Memory Allocated before merge : %d\n", countsAllocated);
		head3 = mergeLists(head1, head2);
		printf("List 3:\n");
		printList(head3);

		freeList(&head3);
		printf("Memory Allocated after free : %d\n", countsAllocated);

	}

	fclose(inFile);
}