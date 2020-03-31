#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "hash.h"

/*
	node:
		has the content of the node and the reference for the next node.
*/
typedef struct node {
	hash_table scope;
	struct node *next;
	struct node *prev;
} node;

/*
	node_new:
		Allocates space for a new node and returns the address of the allocated space.
*/
static node *node_new(hash_table hash_table, node *next) {

	node *node = malloc(sizeof(struct node));

	if (node != NULL) {

		node -> element = hash_table;
		node -> next = next;
		node -> prev = NULL;
	}

	return node;
}

/*
	list:
		the list is represented by the head node, only has the pointer to the head node.
*/
struct list {
	node *head;
};

/*
	list_new:
		Allocates space for a new list and returns the address of the allocated space.
*/
struct list *list_new(void) {

	list *list = malloc(sizeof(list));
	if (list != NULL){
		list -> head = NULL;
	}

	return list;
}

/*
	list_empty:
		If a list has at least a head it is not empty.
*/
bool list_empty(struct list *list) {

	return (list -> head == NULL);
}

/*
	list_insert:
		Creates a new node with the value given and inserts it into the list.
*/
bool list_insert(struct list *list, hash_table hash_table) {

	node *node = node_new(hash_table, list -> head);

	if (node == NULL) {
		free(node);
		return false;
	}

	list -> head -> prev = node;
	list -> head = node;

	return true;
}

/*
	list_remove:
		Given a certain value, removes it from the list. Connects the previous node to next one so the list doesn't "break".
*/
void list_remove(struct list *list, hash_table hash_table) {

    struct node *node = list -> head;
    struct node *prevNode = list -> head;
    int counter = 0;

    while (node -> next != NULL && node->scope != hash_table) {

        node = node -> next;

        if(counter > 0)
            prevNode = prevNode -> next;
        counter++;
    }

    if(counter == 0) {

        list -> head = node -> next;
        node -> next -> prev = NULL;

    } else {

        prevNode -> next = node -> next;
        node -> next -> prev = prevNode;
    }
    free(node);
}

/*
	list_find:
		Searches the values passed on the list. If not found returns -1.
*/
int list_find(struct list *list, int value) {

	node *node = list -> head;
	int index = 0;

	while(node != NULL && node -> element != value) {

		node = node -> next;
		index++;
	}

	return (node == NULL ? -1 : index);
}

/*
	list_print:
		Prints the element of the node, passes to next and does the same. Repeats until it finds one that is NULL.
*/
void list_print(struct list *list) {

	node *node = list -> head;

	while (node != NULL) {
		printf("%d ", node -> element);
		node = node -> next;
	}
}

/*
	list_destroy:
		Free every node of the list and after the list.
*/
void list_destroy(struct list *list) {

	node *node = list -> head;
	struct node *temp;

	while (node != NULL) {
		temp = node;
		node = node -> next;
		free(temp);
	}
	free(list);
}
