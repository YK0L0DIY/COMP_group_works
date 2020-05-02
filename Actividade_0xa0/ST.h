struct st_data_ {
    enum {ST_VAR, ST_FUNC, ST_TYPE} kind;

    union {
    struct {
        _Type yatype; /* _Type pode ser o tipo definido na análise sintáctica */
        enum {VARloc, VARarg} kind;
        /* . . . mais tarde, precisaremos de mais info */
    } var;
    struct {
        _Type yatype; /* tipo de retorno */
        _ArgTypes arg; /* "lista" de tipos dos argumentos, por ordem */
        /* . . . mais tarde, precisaremos de mais info */
    } func;

    _Type type; /* para este caso só precisamos do tipo destino */
 } u;
};

typedef struct st_data_ *ST_Data;

/*############## ST_Data interface ##############*/

/* Insere um novo nome (ID) na ST */
int ST_insert(char *id, ST_Data data);

/* Devolve os dados de um ID (ou NULL, se não existe) */
ST_Data ST_lookup(char *id);

/* Devolve os dados de um ID (apenas no scope actual) */
ST_Data ST_lookup_local(char *id);

/* Cria um novo âmbito (scope ou environment) local - à entrada
na função */
int ST_new_scope();

/* Descarta o último scope - à saída da função */
int ST_discard();
