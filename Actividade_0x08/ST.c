
#include "list.h"

list *scope_list = list_new();

/* Insere um novo nome (ID) na ST */
int ST_insert(char *id, ST_Data data) {

    hash_insert(id, data, scope_list->head->element);

}

/* Devolve os dados de um ID (ou NULL, se não existe) */
ST_Data ST_lookup(char *id) {

    return list_find_id(scope_list, id);
}

/* Devolve os dados de um ID (apenas no scope actual) */
ST_Data ST_lookup_local(char *id) {

    int index = hash(id);

    return scope_list->head->element->data[index];

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
