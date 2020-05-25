#ifndef YA_H_
#define YA_H_

//Structs
typedef struct t_decls_ *t_decls;

typedef struct t_decl_ *t_decl;

typedef struct t_argdefs_ *t_argdefs;

typedef struct t_argdef_ *t_argdef;

typedef struct t_args_ *t_args;

typedef struct t_ids_ *t_ids;

typedef struct t_stms_ *t_stms;

typedef struct t_stm_ *t_stm;

typedef struct t_type_ *t_type;

typedef struct t_lit_ *t_lit;

typedef struct t_exp_ *t_exp;

//Structs
struct t_decls_ {

    enum {
        DECLS_SINGLE,
        DECLS_LIST
    } kind;

    struct {
        t_decl decl;
        t_decls decls;
    } u;
};

struct t_decl_ {

    enum {
        DECL_INIT,
        DECL_ASSIGN,
        DECL_FUNC,
        DECL_DEFINE
    } kind;

    union {

        struct {
            t_ids id_list;
            t_type type;
        } init;

        struct {
            t_ids id_list;
            t_type type;
            t_exp exp;
        } assign;

        struct {
            char *id;
            t_argdefs argdefs;
            t_type type;
            t_stms stms;
        } func;

        struct {
            char *id;
            t_type type;
        } define;

    } u;
};

struct t_argdefs_ {

    enum {
        ARGDEFS_SINGLE,
        ARGDEFS_LIST
    } kind;

    struct {

        t_argdef argdef;
        t_argdefs argdefs;
    } u;
};

struct t_argdef_ {

    char *id;
    t_type type;
};

struct t_args_ {

    enum {
        ARGS_SINGLE,
        ARGS_LIST
    } kind;

    struct {

        t_exp exp;
        t_args args;
    } u;
};

struct t_ids_ {

    enum {
        ID_SINGLE,
        ID_LIST
    } kind;

    struct {

        char *id;
        t_ids id_list;

    } u;
};

struct t_stms_ {

    enum {
        STMS_SINGLE,
        STMS_LIST
    } kind;

    struct {

        t_stm stm;
        t_stms stms;
    } u;
};

struct t_stm_ {

    enum {
        STM_DECL,
        STM_EXP,
        STM_RETURN,
        STM_IF_THEN,
        STM_IF_THEN_ELSE,
        STM_WHILE,
        STM_NEXT
    } kind;

    union {

        struct {
            t_decl decl;
        } stm_decl;

        struct {
            t_exp exp;
        } stm_exp;

        struct {
            t_exp exp;
            t_stms then_stms;
            t_stms else_stms;
        } stm_if_else;

        struct {
            t_exp exp;
            t_stms while_stms;
        } stm_while;
    } u;
};

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
        struct {
            t_type type;
            int intlit;
        } array;

    } u;

};

struct t_lit_ {

    enum {
        LIT_INTLIT,
        LIT_FLOATLIT,
        LIT_STRLIT,
        LIT_BOOLLIT
    } kind;

    union {
        int intlit;
        double floatlit;
        char *strlit;
        int boollit;
    } u;
};

struct t_exp_ {

    enum {
        EXP_LIT,
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
            t_exp index;
        } array;

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
            t_exp id;
            t_exp value;
        } assign;

        //EXP_FUNC
        struct {
            char *id;
            t_args args;
        } func;
    } u;
};

//Functions

//t_decls

t_decls t_decls_new(t_decl decl, t_decls decls);

//t_decl

t_decl t_decl_new_init(t_ids id_list, t_type type);

t_decl t_decl_new_assign(t_ids id_list, t_type type, t_exp exp);

t_decl t_decl_new_func(char *id, t_argdefs argdefs, t_type type, t_stms stms);

t_decl t_decl_new_define(char *id, t_type type);

//t_argdefs

t_argdefs t_argdefs_new(t_argdef argdef, t_argdefs argdefs);

//t_argdef

t_argdef t_argdef_new(char *id, t_type type);

//t_args

t_args t_args_new(t_exp exp, t_args args);

//t_ids

t_ids t_ids_new(char *id, t_ids id_list);

//t_stms

t_stms t_stms_new(t_stm stm, t_stms stms);

//t_stm

t_stm t_stm_new_decl(t_decl decl);

t_stm t_stm_new_exp(t_exp exp);

t_stm t_stm_new_return(t_exp exp);

t_stm t_stm_new_if_else(t_exp exp, t_stms then_stms, t_stms else_stms);

t_stm t_stm_new_while(t_exp exp, t_stms while_stms);

t_stm t_stm_new_next();

//t_type

t_type t_type_new_type(int kind);

t_type t_type_new_id(char *id);

t_type t_type_new_array(t_type type, int intlit);

//t_lit

t_lit t_lit_new_intlit(int intlit);

t_lit t_lit_new_floatlit(double floatlit);

t_lit t_lit_new_strlit(char *srtlit);

t_lit t_lit_new_boollit(int boollit);

//t_exp

t_exp t_exp_new_binop(char op[], t_exp arg1, t_exp arg2);

t_exp t_exp_new_unop(char op[], t_exp arg1);

t_exp t_exp_new_assign(t_exp exp, t_exp value);

t_exp t_exp_new_lit(t_lit lit);

t_exp t_exp_new_id(char *id);

t_exp t_exp_new_array(t_exp exp, t_exp index);

t_exp t_exp_new_function(char *id, t_args args);

#endif