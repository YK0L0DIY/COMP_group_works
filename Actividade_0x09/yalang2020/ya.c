#include "ya.h"
#include <stdlib.h>
#include <string.h>

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
            int intlit;
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

//t_decls

t_decls t_decls_new(t_decl decl, t_decls decls) {

    t_decls to_return = (t_decls) malloc(sizeof(*to_return));

    to_return->u.decl = decl;
    to_return->u.decls = decls;

    if (decls) {

        to_return->kind = DECLS_LIST;

    } else {

        to_return->kind = DECLS_SINGLE;

    }

    return to_return;
}

//t_decl

t_decl t_decl_new_init(t_ids id_list, t_type type) {
    t_decl to_return = (t_decl) malloc(sizeof(*to_return));

    to_return->kind = DECL_INIT;
    to_return->u.init.id_list = id_list;
    to_return->u.init.type = type;

    return to_return;
}

t_decl t_decl_new_assign(t_ids id_list, t_type type, t_exp exp) {
    t_decl to_return = (t_decl) malloc(sizeof(*to_return));

    to_return->kind = DECL_ASSIGN;
    to_return->u.assign.id_list = id_list;
    to_return->u.assign.type = type;
    to_return->u.assign.exp = exp;

    return to_return;
}

t_decl t_decl_new_func(char *id, t_argdefs argdefs, t_type type, t_stms stms) {
    t_decl to_return = (t_decl) malloc(sizeof(*to_return));

    to_return->kind = DECL_FUNC;
    strcpy(to_return->u.func.id, id);
    to_return->u.func.type = type;
    to_return->u.func.argdefs = argdefs;
    to_return->u.func.stms = stms;

    return to_return;
}

t_decl t_decl_new_define(char *id, t_type type) {
    t_decl to_return = (t_decl) malloc(sizeof(*to_return));

    to_return->kind = DECL_DEFINE;
    strcpy(to_return->u.define.id, id);
    to_return->u.define.type = type;

    return to_return;
}

//t_argdefs

t_argdefs t_argdefs_new(t_argdef argdef, t_argdefs argdefs) {

    t_argdefs to_return = (t_argdefs) malloc(sizeof(*to_return));

    to_return->u.argdef = argdef;
    to_return->u.argdefs = argdefs;

    if (argdefs) {
        to_return->kind = ARGDEFS_LIST;
    } else {
        to_return->kind = ARGDEFS_SINGLE;
    }

    return to_return;
}

//t_argdef

t_argdef t_argdef_new(char *id, t_type type) {

    t_argdef to_return = (t_argdef) malloc(sizeof(*to_return));

    strcpy(to_return->id, id);
    to_return->type = type;

    return to_return;
}

//t_args

t_args t_args_new(t_exp exp, t_args args) {

    t_args to_return = (t_args) malloc(sizeof(*to_return));

    to_return->u.exp = exp;
    to_return->u.args = args;

    if (args) {
        to_return->kind = ARGS_LIST;

    } else {
        to_return->kind = ARGS_SINGLE;
    }

    return to_return;
}

//t_ids

t_ids t_ids_new(char *id, t_ids id_list) {

    t_ids to_return = (t_ids) malloc(sizeof(*to_return));

    strcpy(to_return->u.id, id);
    to_return->u.id_list = id_list;

    if (id_list) {

        to_return->kind = ID_LIST;

    } else {

        to_return->kind = ID_SINGLE;
    }

    return to_return;
}

//t_stms

t_stms t_stms_new(t_stm stm, t_stms stms) {

    t_stms to_return = (t_stms) malloc(sizeof(*to_return));

    to_return->u.stm = stm;
    to_return->u.stms = stms;

    if (stms) {

        to_return->kind = STMS_SINGLE;

    } else {
        to_return->kind = STMS_LIST;

    }

    return to_return;
}

//t_stm

t_stm t_stm_new_decl(t_decl decl) {

    t_stm to_return = (t_stm) malloc(sizeof(*to_return));

    to_return->kind = STM_DECL;
    to_return->u.stm_decl.decl = decl;

    return to_return;
}

t_stm t_stm_new_exp(t_exp exp) {

    t_stm to_return = (t_stm) malloc(sizeof(*to_return));

    to_return->kind = STM_EXP;
    to_return->u.stm_exp.exp = exp;

    return to_return;
}

t_stm t_stm_new_return(t_exp exp) {

    t_stm to_return = (t_stm) malloc(sizeof(*to_return));

    to_return->kind = STM_RETURN;
    to_return->u.stm_exp.exp = exp;

    return to_return;
}

t_stm t_stm_new_if_else(t_exp exp, t_stms then_stms, t_stms else_stms) {

    t_stm to_return = (t_stm) malloc(sizeof(*to_return));

    to_return->u.stm_if_else.exp = exp;
    to_return->u.stm_if_else.then_stms = then_stms;
    to_return->u.stm_if_else.else_stms = else_stms;

    if (else_stms) {

        to_return->kind = STM_IF_THEN_ELSE;

    } else {

        to_return->kind = STM_IF_THEN;
    }

    return to_return;
}

t_stm t_stm_new_while(t_exp exp, t_stms while_stms) {

    t_stm to_return = (t_stm) malloc(sizeof(*to_return));

    to_return->kind = STM_WHILE;

    to_return->u.stm_while.exp = exp;
    to_return->u.stm_while.while_stms = while_stms;

    return to_return;
}

t_stm t_stm_new_next() {

    t_stm to_return = (t_stm) malloc(sizeof(*to_return));

    to_return->kind = STM_NEXT;

    return to_return;
}

//t_type

t_type t_type_new_type(int kind) {
    t_type to_return = (t_type) malloc(sizeof(*to_return));

    to_return->kind = kind;

    return to_return;
}

t_type t_type_new_id(char *id) {
    t_type to_return = (t_type) malloc(sizeof(*to_return));

    to_return->kind = TYPE_ID;
    strcpy(to_return->u.id, id);

    return to_return;
}

t_type t_type_new_array(t_type type, int intlit) {
    t_type to_return = (t_type) malloc(sizeof(*to_return));

    to_return->kind = TYPE_ARRAY;
    to_return->u.array.type = type;
    to_return->u.array.intlit = intlit;

    return to_return;
}

//t_lit

t_lit t_lit_new_intlit(int intlit) {
    t_lit to_return = (t_lit) malloc(sizeof(*to_return));

    to_return->kind = LIT_INTLIT;
    to_return->u.intlit = intlit;

    return to_return;
}

t_lit t_lit_new_floatlit(double floatlit) {
    t_lit to_return = (t_lit) malloc(sizeof(*to_return));

    to_return->kind = LIT_FLOATLIT;
    to_return->u.floatlit = floatlit;

    return to_return;
}

t_lit t_lit_new_strlit(char *strlit) {
    t_lit to_return = (t_lit) malloc(sizeof(*to_return));

    to_return->kind = LIT_STRLIT;
    strcpy(to_return->u.strlit, strlit);

    return to_return;
}

t_lit t_lit_new_boollit(int boollit) {
    t_lit to_return = (t_lit) malloc(sizeof(*to_return));

    to_return->kind = LIT_BOOLLIT;
    to_return->u.boollit = boollit;

    return to_return;
}

//t_exp

t_exp t_exp_new_binop(char op[], t_exp arg1, t_exp arg2) {

    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_BINOP;
    strcpy(to_return->u.binop.op, op);
    to_return->u.binop.arg1 = arg1;
    to_return->u.binop.arg2 = arg2;

    return to_return;
}

t_exp t_exp_new_unop(char op[], t_exp arg1) {

    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_UNOP;
    strcpy(to_return->u.unop.op, op);
    to_return->u.unop.arg = arg1;

    return to_return;
}

t_exp t_exp_new_assign(t_exp exp, t_exp value) {

    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_ASSIGN;
    to_return->u.assign.id = exp;
    to_return->u.assign.value = value;

    return to_return;
}

t_exp t_exp_new_lit(t_lit lit) {
    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_LIT;
    to_return->u.lit = lit;

    return to_return;
}

t_exp t_exp_new_id(char *id) {

    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_ID;
    strcpy(to_return->u.id, id);

    return to_return;
}

t_exp t_exp_new_array(t_exp exp, int intlit) {
    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_ARRAY;
    to_return->u.array.exp = exp;
    to_return->u.array.intlit = intlit;

    return to_return;
}

t_exp t_exp_new_function(char *id, t_args args) {
    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_FUNC;
    to_return->u.func.args = args;
    strcpy(to_return->u.func.id, id);

    return to_return;
}