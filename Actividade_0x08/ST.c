
#include "list.h"

list *scope_list = list_new();

/* Insere um novo nome (ID) na ST */
int ST_insert(char *id, ST_Data data) {

}

/* Devolve os dados de um ID (ou NULL, se não existe) */
ST_Data ST_lookup(char *id) {

}

/* Devolve os dados de um ID (apenas no scope actual) */
ST_Data ST_lookup_local(char *id) {

}

/* Cria um novo âmbito (scope ou environment) local - à entrada
na função */
int ST_new_scope() {

    list_insert(scope_list, hash_new());

}

/* Descarta o último scope - à saída da função */
int ST_discard() {

    list_remove(scope_list, scope_list->head);

}
