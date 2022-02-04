// C program to find inverse of Burrows
// Wheeler transform
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store info of a node of
// linked list
struct node {
	int data;
	struct node* next;
};

// Compares the characters of bwt_arr[]
// and sorts them alphabetically
int cmpfunc(const void* a, const void* b)
{
	const char* ia = (const char*)a;
	const char* ib = (const char*)b;
	return strcmp(ia, ib);
}

// Creates the new node
struct node* getNode(int i)
{
	struct node* nn =
		(struct node*)malloc(sizeof(struct node));
	nn->data = i;
	nn->next = NULL;
	return nn;
}

// Does insertion at end in the linked list
void addAtLast(struct node** head, struct node* nn)
{
	if (*head == NULL) {
		*head = nn;
		return;
	}
	struct node* temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = nn;
}

// Computes l_shift[]
void* computeLShift(struct node** head, int index,
					int* l_shift)
{
	l_shift[index] = (*head)->data;
	(*head) = (*head)->next;
}

void invert(char bwt_arr[])
{
	int i,len_bwt = strlen(bwt_arr);
	char* sorted_bwt = (char*)malloc(len_bwt * sizeof(char));
	strcpy(sorted_bwt, bwt_arr);
	int* l_shift = (int*)malloc(len_bwt * sizeof(int));

	// Index at which original string appears
	// in the sorted rotations list
	int x = 4;

	// Sorts the characters of bwt_arr[] alphabetically
	qsort(sorted_bwt, len_bwt, sizeof(char), cmpfunc);

	// Array of pointers that act as head nodes
	// to linked lists created to compute l_shift[]
	struct node* arr[128] = { NULL };

	// Takes each distinct character of bwt_arr[] as head
	// of a linked list and appends to it the new node
	// whose data part contains index at which
	// character occurs in bwt_arr[]
	for (i = 0; i < len_bwt; i++) {
		struct node* nn = getNode(i);
		addAtLast(&arr[bwt_arr[i]], nn);
	}

	// Takes each distinct character of sorted_arr[] as head
	// of a linked list and finds l_shift[]
	for (i = 0; i < len_bwt; i++)
		computeLShift(&arr[sorted_bwt[i]], i, l_shift);

	printf("Burrows - Wheeler Transform: %s\n", bwt_arr);
	printf("Inverse of Burrows - Wheeler Transform: ");
	// Decodes the bwt
	for (i = 0; i < len_bwt; i++) {
		x = l_shift[x];
		printf("%c", bwt_arr[x]);
	}
}

// Driver program to test functions above
int main()
{
	char bwt_arr[] = "agttc&gattaa";
	invert(bwt_arr);
	return 0;
}

