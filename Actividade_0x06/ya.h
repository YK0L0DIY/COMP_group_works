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

        ids id_list;
        type

    }u;
};

typedef ids_ *ids;
struct ids_ {

    enum {
        ID_SINGLE,
        ID_LIST
    } kind;

    union {

        char *id;
        ids id_list;

    }u;
};

typedef t_lit_ *t_lit;
struct t_lit_ {

    enum {LIT_INTLIT, LIT_FLOATLIT, LIT_STRLIT, LIT_BOOLLIT} kind;

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
