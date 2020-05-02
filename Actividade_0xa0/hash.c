/*
 * Implementação dos métodos de recursos_hash.h.
 *
 * Copiadas as implementações usadas por um dos membros do grupo (l39873, Eduardo Medeiros) no trabalho E.
 *
 */
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/*
    hashCode:
    Hash function DJB2 adapted to ints.
    Source: http://www.cse.yorku.ca/~oz/hash.html
*/
unsigned int hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

hash_table hash_new() {

    hash_table to_return = (hash_table) malloc(sizeof(hash_element) * HASH_SIZE);

    for (int i = 0; i < HASH_SIZE; i++) {
        to_return[i] = NULL;
    }

    return to_return;
}

int hash_destroy(hash_table hash_table) {

    for (int i = 0; i < HASH_SIZE; i++) {

        if(hash_table[i]) {

            free(hash_table[i]);
        }
    }

    return 0;
}

void hash_insert(char *id, ST_Data data, hash_table hash_table) {

    hash_element *new_element = (hash_element*) malloc(sizeof(hash_element));

    new_element->id = strdup(id);
    new_element->data = data;

    int index = hash(id);

    hash_table[index] = new_element;

}

int hash_remove(char *id, hash_table hash_table) {

    int index = hash(id);

    free(hash_table[index]);

    return 1;
}
