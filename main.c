#include <stdio.h>
#include <stdlib.h>

/*
The data type for the doubly linked list will be of type “int”.
*/
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

/*
DoublyLinkedList struct simply contains a pointer to the head of a list and a
count variable to allow for multiple lists in one program without messing up
count.
*/
typedef struct DoublyLinkedList {
  unsigned int count;
  struct Node *head;
} DoublyLinkedList;

/*
Function prototypes from requirements
*/
Node *createNode(DoublyLinkedList *list, int data);
DoublyLinkedList *createList();
Node *getFirst(DoublyLinkedList *list);
Node *getLast(DoublyLinkedList *list);
unsigned int getNumElements(DoublyLinkedList *list);
Node *getIndex(DoublyLinkedList *list, unsigned int index);
int removeIndex(DoublyLinkedList *list, unsigned int index);
DoublyLinkedList *append(DoublyLinkedList *first, DoublyLinkedList *second);
int searchValue(DoublyLinkedList *list, int value);

/*
Other misc functions I added to make testing easier and more clear
*/

void print(Node *node);
void printAll(DoublyLinkedList *list);
void freeList(DoublyLinkedList *list);

/*
Function Definitions
*/

/* prints a node's data */
void print(Node *node) {
  fprintf(stdout, "[%d]", node->data);
}

/* traverses the list from head to tail, printing data (used in tests) */
void printAll(DoublyLinkedList *list) {
  Node *move = list->head;
  while (move != NULL) {
    print(move);
    move = move->next;
  }
  fprintf(stdout, " : count = %d\n", getNumElements(list));
}

/* traverses a doubly linked list freeing all nodes, and then the list itself */
void freeList(DoublyLinkedList *list) {
  Node *move = list->head;
  Node *cleanup = move;
  /* move through all nodes */
  while (cleanup != NULL) {
    move = cleanup->next;
    free(cleanup);
    cleanup = move;
  }
  free(cleanup);
  free(move);
  free(list);
}

/* create (a node) */
Node *createNode(DoublyLinkedList *list, int data) {
  Node *newNode;
  if ((newNode = (Node*)malloc(sizeof(Node))) == NULL) {
    fprintf(stderr, "Could not allocate memory for a new Node.\n");
  }
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;
  /* if this is the first node in the list, make it head, else add to end */
  if (list->count == 0) {
    list->head = newNode;
  } else {
    Node *move = list->head;
    while (move->next != NULL) {
      move = move->next;
    }
    move->next = newNode;
    newNode->prev = move;
  }
  list->count++;
	return newNode;
}

/* create (a list) */
DoublyLinkedList *createList() {
	DoublyLinkedList *list;
  if ((list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList))) == NULL) {
    fprintf(stderr, "Could not allocate memory for a new DoublyLinkedList.\n");
  }
	list->head = NULL;
  list->count = 0;
	return list;
}

/* get first (node in a given list) */
Node *getFirst(DoublyLinkedList *list) {
  return list->head;
}

/* get last (node in a given list) */
Node *getLast(DoublyLinkedList *list) {
  Node *move = list->head;
  /* move to the last node in a list */
  while (move->next != NULL) {
    move = move->next;
  }
  return move;
}

/* get number of elements */
unsigned int getNumElements(DoublyLinkedList *list) {
  return list->count;
}

/* get element at given index */
Node *getIndex(DoublyLinkedList *list, unsigned int index) {
  /* if the specified index is not an element in the list print an error */
  if (index > list->count - 1) {
    fprintf(stderr, "Error: invalid index\n");
    return NULL;
  }
  Node *move = list->head;
  /* move to the index element */
  for (int i = 0; i < index; i++) {
    move = move->next;
  }
  return move;
}

/* remove element at given index */
int removeIndex(DoublyLinkedList *list, unsigned int index) {
  /* if the list is empty print an error */
  if (list->head == NULL) {
    fprintf(stderr, "Error: list doesn't have a head.\n");
    return 0;
  }
  /* if the index does not exist in the list throw an error */
  if (index > list->count - 1) {
    fprintf(stderr, "Error: index is invalid in this list.\n");
    return 0;
  }
  /* if the index is the last node */
  if (index == list->count - 1) {
    Node *move = list->head;
    for (int i = 0; i < index; i++) {
      move = move->next;
    }
    move->prev->next = NULL;
    list->count--;
    return 1;
  }
  /* if the index is the head */
  if (index == 0) {
    list->head = list->head->next;
    list->count--;
    return 1;
  }
  Node *move = list->head;
  /* if none of the other conditions were met, remove at index */
  for (int i = 0; i < index; i++) {
    move = move->next;
  }
  move->prev->next = move->next;
  move->next->prev = move->prev;
  list->count--;
  free(move);
  return 1;
}

/* append one list to another */
/* NOTE: appends second list elements to first, leaving list2 empty */
DoublyLinkedList *append(DoublyLinkedList *list, DoublyLinkedList *list2) {
  Node *endOfFirst = list->head;
  /* move to end */
  while (endOfFirst->next != NULL) {
    endOfFirst = endOfFirst->next;
  }
  endOfFirst->next = list2->head;
  list2->head->prev = endOfFirst;
  list->count = (list->count + list2->count);
  return list;
}

/* search for given value in list and return index */
int searchValue(DoublyLinkedList *list, int value) {
  int index = 0;
  /* check if list has a head (isn't empty) */
  if (list->head == NULL) {
    return -1;
  }
  Node *move = list->head;
  /* traverse list until value found */
  while (move != NULL) {
    if (move->data == value) {
      return index;
    }
    move = move->next;
    index++;
  }
  return -1;
}


/*
Tests for program functions.
*/
int main(int argc , char *argv[]) {

  /* create lists, print each list */
  DoublyLinkedList *first = createList();
  createNode(first, 999);
  createNode(first, 888);
  createNode(first, 777);
  printAll(first);
  DoublyLinkedList *second = createList();
  createNode(second, 13123);
  createNode(second, 53452);
  createNode(second, 12313);
  printAll(second);

  /* append second list to first list, print resulting list */
  append(first, second);
  printAll(first);

  /* removeIndex 2 from first list, print resulting list */
  removeIndex(first, 2);
  printAll(first);

  /* search for value 53452, print index if found of print if not found */
  int res;
  if ((res = searchValue(first, 53452)) >= 0) {
    fprintf(stdout, "found 53452, index: %u\n", res);
  } else {
    fprintf(stdout, "couldn't find 53452\n");
  }

  /* search for value 1234 (not there), print index if found of print if not found */
  if ((res = searchValue(first, 1234)) >= 0) {
    fprintf(stdout, "found 1234, index: %u\n", res);
  } else {
    fprintf(stdout, "couldn't find 1234\n");
  }

  /* get and print node at index 3 */
  fprintf(stdout, "Index 3: %d\n", getIndex(first, 3)->data);

  /* get and print first node */
  fprintf(stdout, "First: %d\n", getFirst(first)->data);

  /* get and print last node */
  fprintf(stdout, "Last: %d\n", getLast(first)->data);

  /* free first list struct and all of its node structs (nodes appended from 'second' also!) */
  freeList(first);

  /* free second list struct which has no nodes at this point. */
  free(second);

  return 0;
}
