#include "list.h"
#include "ya.h"

struct st_data_ {
    enum {ST_VAR, ST_FUNC, ST_TYPE} kind;

    union {
    struct {
        t_type yatype; /* _Type pode ser o tipo definido na análise sintáctica */
        enum {VARloc, VARarg} kind;
        /* . . . mais tarde, precisaremos de mais info */
    } var;
    struct {
        t_type yatype; /* tipo de retorno */
        t_argdefs arg; /* "lista" de tipos dos argumentos, por ordem */
        /* . . . mais tarde, precisaremos de mais info */
    } func;

    t_type type; /* para este caso só precisamos do tipo destino */
 } u;
};

list *scope_list = 0;

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

    if(scope_list == 0) {
        scope_list = list_new();
    }

    list_insert(scope_list, hash_new());

}

/* Descarta o último scope - à saída da função */
int ST_discard() {

    list_remove(scope_list, scope_list->head);

}
