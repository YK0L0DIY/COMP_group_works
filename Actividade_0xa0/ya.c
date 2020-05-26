#include "ya.h"
#include <stdlib.h>
#include <string.h>

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
    to_return->u.func.id = strdup(id);
    to_return->u.func.type = type;
    to_return->u.func.argdefs = argdefs;
    to_return->u.func.stms = stms;

    return to_return;
}

t_decl t_decl_new_define(char *id, t_type type) {
    t_decl to_return = (t_decl) malloc(sizeof(*to_return));

    to_return->kind = DECL_DEFINE;
    to_return->u.define.id = strdup(id);
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

    to_return->id = (id);
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

    to_return->u.id = strdup(id);
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
    to_return->u.id = (id);

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
    to_return->u.strlit = (strlit);

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
    to_return->u.binop.op = strdup(op);
    to_return->u.binop.arg1 = arg1;
    to_return->u.binop.arg2 = arg2;

    return to_return;
}

t_exp t_exp_new_unop(char op[], t_exp arg1) {

    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_UNOP;
    to_return->u.unop.op = strdup(op);
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
    to_return->u.id = strdup(id);

    return to_return;
}

t_exp t_exp_new_array(t_exp exp, t_exp index) {
    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_ARRAY;
    to_return->u.array.exp = exp;
    to_return->u.array.index = index;

    return to_return;
}

t_exp t_exp_new_function(char *id, t_args args) {
    t_exp to_return = (t_exp) malloc(sizeof(*to_return));

    to_return->kind = EXP_FUNC;
    to_return->u.func.args = args;
    to_return->u.func.id = strdup(id);

    return to_return;
}