/*
 * Ficheiro com recursos para Hashtables.
 */

#define HASH_SIZE 307
#include "ST.h"

typedef struct hash_element **hash_table;

typedef struct hash_element {

    char *id;
    ST_Data data;

}hash_element;

unsigned int hash(char *str);

hash_table hash_new();

int hash_destroy(hash_table hash_table);

void hash_insert(char *id, ST_Data data, hash_table hash_table);

int hash_remove(char *id, hash_table hash_table);
