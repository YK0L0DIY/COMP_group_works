#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
	node_new:
		Allocates space for a new node and returns the address of the allocated space.
*/
static node *node_new(node *next) {

    node *node = malloc(sizeof(struct node));

    hash_table new_hash = hash_new();

    if (node != NULL) {

        node->element = new_hash;
        node->next = next;
    }

    return node;
}

/*
	list_new:
		Allocates space for a new list and returns the address of the allocated space.
*/
struct list *list_new(void) {

    struct list *list = malloc(sizeof(*list));
    if (list != NULL) {
        list->head = NULL;
    }

    return list;
}

/*
	list_empty:
		If a list has at least a head it is not empty.
*/
bool list_empty(struct list *list) {

    return (list->head == NULL);
}

/*
	list_insert:
		Creates a new node with the value given and inserts it into the list.
*/
bool list_insert(struct list *list) {

    node *node = node_new(list->head);

    if (node == NULL) {
        free(node);
        return false;
    }

    list->head = node;

    return true;
}

/*
	list_remove:
		Given a certain value, removes it from the list. Connects the previous node to next one so the list doesn't "break".
*/
void list_remove(struct list *list) {

//    struct node *node = list -> head;
//    struct node *prevNode = list -> head;
//    int counter = 0;
//
//    while (node -> next != NULL && node->element != hash_table) {
//
//        node = node -> next;
//
//        if(counter > 0)
//            prevNode = prevNode -> next;
//        counter++;
//    }
//
//    if(counter == 0) {
//
//        list -> head = node -> next;
//
//    } else {
//        prevNode -> next = node -> next;
//    }
//    free(node);

    struct node *head = list->head;
    struct node *temp = NULL;

    if (head->next != NULL) {

        temp = head->next;

        free(head->element);
        free(head);

        list->head = temp;

    }
}

/*
	list_find:
		Searches the values passed on the list. If not found returns -1.
*/
int list_find(struct list *list, hash_table hash_table) {

    node *node = list->head;
    int index = 0;

    while (node != NULL && node->element != hash_table) {

        node = node->next;
        index++;
    }

    return (node == NULL ? -1 : index);
}

ST_Data list_find_id(struct list *list, char *id) {

    node *node = list->head;
    int index = hash(id);

    while (node != NULL) {

        if(node->element[index] != NULL && (strcmp(node->element[index]->id, id) == 0)) {
            break;
        } else {
            node = node->next;
        }
    }

    if (node == NULL || node->element[index] == NULL) {
        return NULL;
    } else {
        return node->element[index]->data;
    }
}

/*
	list_print:
		Prints the element of the node, passes to next and does the same. Repeats until it finds one that is NULL.
*/
void list_print(struct list *list) {

    node *node = list->head;

    while (node != NULL) {

        for (int i = 0; i < HASH_SIZE; i++) {
            printf("%s ", node->element[i]->id);
        }
        node = node->next;
    }
}

/*
	list_destroy:
		Free every node of the list and after the list.
*/
void list_destroy(struct list *list) {

    node *node = list->head;
    struct node *temp;

    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
    free(list);
}
