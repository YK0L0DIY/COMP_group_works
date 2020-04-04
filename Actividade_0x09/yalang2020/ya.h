//Structs
typedef t_decls_ *t_decls;
struct t_decls_ {

    enum {  DECLS_SINGLE,
            DECLS_LIST
    } kind;

    struct {
        t_decl decl;
        t_decls decls;
    } u;
};

typedef t_decl_ *t_decl;
struct t_decl_ {

    enum {
        DECL_INIT,
        DECL_ASSIGN,
        DECL_FUNC
    }kind;

    union {

        t_ids id_list;
        t_type type;
        t_exp exp;
        char *id;
        t_stms stms;
        t_argdefs argdefs;

    }u;
};

typedef t_argdefs_ *t_argdefs;
struct t_argdefs_ {

    enum {
        ARGDEFS_SINGLE,
        ARGDEFS_LIST
    } kind;

    union {

        t_argdef argdef;
        t_argdefs argdefs;
    }u;
};

typedef t_argdef_ *t_argdef;
struct t_argdef_ {

    char *id;
    t_type type;
};

typedef t_args_ *t_args;
struct t_args_ {

    enum {
        ARGS_SINGLE,
        ARGS_LIST
    } kind;

    union {

        t_exp exp;
        t_args args;
    }u;
};

typedef t_ids_ *t_ids;
struct t_ids_ {

    enum {
        ID_SINGLE,
        ID_LIST
    } kind;

    union {

        char *id;
        t_ids id_list;

    }u;
};

typedef t_stms_ *t_stms;
struct t_stms_ {

    enum {
        STMS_SINGLE,
        STMS_LIST
    } kind;

    union {

        t_stm stm;
        t_stms stms;
    }u;
};

typedef t_stm_ *t_stm;
struct t_stm_ {

    enum {
        STM_DECL,
        STM_EXP,
        STM_RETURN,
        STM_IF_THEN,
        STM_IF_THEN_ELSE,
        STM_WHILE
    } kind;

    union {

        t_decl decl;

        t_exp exp;

        t_stms stms;
        t_stms else_stms;

    }u;
};

typedef t_type_ *t_type;
struct t_type_ {

    enum {
        TYPE_T_INT,
        TYPE_T_FLOAT,
        TYPE_T_STRING,
        TYPE_T_BOOL,
        TYPE_T_VOID,
        TYPE_ID,
        TYPE_ARRAY
    } kind;

    union {

        char *type;
        char *id;
        t_type type;
        int intlit;

    }u;

};

typedef t_lit_ *t_lit;
struct t_lit_ {

    enum {
        LIT_INTLIT,
        LIT_FLOATLIT,
        LIT_STRLIT,
        LIT_BOOLLIT
    } kind;

    union {
        int intlit;
        double floalit;
        char *strlit;
        int boollit;
    }u;
};

typedef t_exp_ *t_exp;
struct t_exp_ {

    enum {  EXP_LIT,
            EXP_ID,
            EXP_ARRAY,
            EXP_BINOP,
            EXP_UNOP,
            EXP_ASSIGN,
            EXP_FUNC
        } kind;

    union {

        //EXP_LIT
        t_lit lit;

        //EXP_ID
        char *id;

        //EXP_ARRAY
        struct {
            t_exp exp;
            int intlit;
        }array;

        //EXP_BINOP
        struct {
            char op[3];
            t_exp arg1;
            t_exp arg2;
        } binop;

        //EXP_UNOP
        struct {
            char op[3];
            t_exp arg;
        } unop;

        //EXP_ASSIGN
        struct {
            char *id;
            t_exp value;
        } assign;

        //EXP_FUNC
        struct {
            char *id;
            t_args args;
        }func;
    }u;
};

//Functions
t_decls t_decls_new(t_decl decl, t_decls decls);
