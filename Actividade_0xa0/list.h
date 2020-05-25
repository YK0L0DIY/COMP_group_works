/*
	Header file for a Linked List.
*/
#ifndef LIST_H_
#define LIST_H_


#include <stdbool.h>
#include "hash.h"
#include "ST.h"

struct list *list_new();
bool list_empty(struct list *list);
bool list_insert(struct list *list);
void list_remove(struct list *list, hash_table hash_table);
int list_find(struct list *list, hash_table hash_table);
ST_Data list_find_id(struct list *list, char *id);
void list_print(struct list *list);
void list_destroy(struct list *list);

#endif
