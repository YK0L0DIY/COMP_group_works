/*
	Header file for a Linked List.
*/

#include <stdbool.h>
#include "hash.h"

typedef struct list list;
struct list *list_new();
bool list_empty(struct list *list);
bool list_insert(struct list *list, hash_table hash_table);
void list_remove(struct list *list, hash_table hash_table);
int list_find(struct list *list, hash_table hash_table);
void list_print(struct list *list);
void list_destroy(struct list *list);
