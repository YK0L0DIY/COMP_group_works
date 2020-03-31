/*
 * Implementação dos métodos de recursos_hash.h.
 *
 * Copiadas as implementações usadas por um dos membros do grupo (l39873, Eduardo Medeiros) no trabalho E.
 *
 */

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


/*
    getClosestPrime:
        Given a certain number, returns the next bigger prime number.

        args:
            number - the number given to get the closest prime.

        return:
            The closest bigger prime to number.
*/
int getClosestPrime(int number) {

    number++;

    for (int i = 2; i < number; i++) {

        if (number % i == 0) {

            number++;
            i = 2;

        } else {

            continue;
        }
    }

    return number;
}

int destroy_hash(hash_table hash_table) {

    for (int i = 0; i < sizeof(*hash_table); i++) {
        free(hash_table[i]);
    }

    return 0;
}

void insert_hash(char *id, SD_Data data, hash_table hash_table) {

    hash_element *new_element = malloc(sizeof(hash_element));

    new_element->id = strdup(id);
    new_element->data = data;

    int index = hash(id);

    hash_table[index] = new_element;

}

int remove_hash(char *id, hash_table hash_table) {

    int index = hash(id);

    free(hash_table[index]);

    return 1;
}
