#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "ya.h"

struct list *scope_list = NULL;

ST_Data new_ST_Data() {

    ST_Data to_return = (ST_Data) malloc(sizeof(*to_return));

    return to_return;

}

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

    if (scope_list->head != NULL && scope_list->head->element[index] != NULL &&
        (strcmp(scope_list->head->element[index]->id, id) == 0)) {

        return scope_list->head->element[index]->data;

    } else {
        return NULL;
    }
}

/* Cria um novo âmbito (scope ou environment) local - à entrada
na função */
int ST_new_scope() {

    if (scope_list == NULL) {
        scope_list = list_new();
    }

    list_insert(scope_list);

}

/* Descarta o último scope - à saída da função */
int ST_discard() {

    list_remove(scope_list);

}
