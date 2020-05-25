/*
	Header file for a Linked List.
*/
#ifndef LIST_H_
#define LIST_H_


#include <stdbool.h>
#include "hash.h"
#include "ST.h"



/*
	node:
		has the content of the node and the reference for the next node.
*/
typedef struct node {
    hash_table element;
    struct node *next;
} node;

/*
    list:
        the list is represented by the head node, only has the pointer to the head node.
*/
struct list {
    node *head;
};

struct list *list_new();
bool list_empty(struct list *list);
bool list_insert(struct list *list);
void list_remove(struct list *list, hash_table hash_table);
int list_find(struct list *list, hash_table hash_table);
ST_Data list_find_id(struct list *list, char *id);
void list_print(struct list *list);
void list_destroy(struct list *list);

#endif
