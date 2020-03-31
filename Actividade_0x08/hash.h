/*
 * Ficheiro com recursos para Hashtables.
 */

#define HASH_SIZE 307

typedef struct hash_element *hash_table[HASH_SIZE];

typedef struct hash_element {

    char *id;
    ST_Data data;

}hash_element;

int getClosestPrime(int number);

unsigned int hash(char *str);

void insert_hash(char *id, SD_Data data, hash_table hash_table);

int remove_hash(char *id, hash_table hash_table);
