#include "ya.h"
#include <stdlib.h>
#include <string.h>

//Functions

//t_decls

t_decls t_decls_new(t_decl decl, t_decls decls) {

    t_decls to_return = (t_decls) malloc(sizeof(*t_decls));

    to_return->u.decl = decl;
    to_return->u.decls = decls;

    if (decls) {

        to_return->kind = DECLS_LIST;

    } else {

        to_return->kind = DECLS_SINGLE;

    }

    return to_return;
}

//t_argdefs

t_argdefs t_argdefs_new(t_argdef argdef, t_argdefs argdefs) {

    t_argdefs to_return = (t_argdefs) malloc(sizeof(*t_argdefs));

    to_return->u.argdef = argdef;
    to_return->u.argdefs = argdefs;

    if(argdefs) {
        to_return->kind = ARGDEFS_LIST;
    } else {
        to_return->kind = ARGDEFS_SINGLE;
    }

    return to_return;
}

//t_argdef

t_argdef t_argdef_new(char *id, t_type type) {

    t_argdef to_return = (t_argdef) malloc(sizeof(*t_argdef));

    strcpy(to_return->id,id);
    to_return->type = type;

    return to_return;
}

//t_args

t_args t_args_new(t_exp exp, t_args args) {

    t_args to_return = (t_args) malloc(sizeof(*t_args));

    to_return->u.exp = exp;
    to_return->u.args = args;

    if(args) {
        to_return->kind = ARGS_LIST;

    }else{
        to_return->kind = ARGS_SINGLE;
    }

    return to_return;
}

//t_ids

t_ids t_ids_new(char *id, t_ids id_list) {

    t_ids to_return = (t_ids) malloc(sizeof(*t_ids));

    strcpy(to_return->u.id, id);
    to_return->u.id_list;

    if(id_list) {

        to_return->kind = ID_LIST;

    } else {

        to_return->kind = ID_SINGLE;
    }

    return to_return;
}

//t_stms

t_stms t_stms_new(t_stm stm, t_stms stms) {

    t_stms to_return = (t_stms) malloc(sizeof(t_stms));

    to_return->u.stm = stm;
    to_return->u.stms = stms;

    if(stms) {

        to_return->kind = STMS_SINGLE;

    } else {
        to_return->kind = STMS_LIST;

    }

    return to_return;
}

//t_stm

t_stm t_stm_new_decl(t_decl decl) {

    t_stm  to_return = (t_stm) malloc(sizeof(*t_stm));

    to_return->kind = STM_DECL;
    to_return->u.stm_decl.decl = decl;

    return to_return;
}

t_stm t_stm_new_exp(t_exp exp) {

    t_stm  to_return = (t_stm) malloc(sizeof(*t_stm));

    to_return->kind = STM_EXP;
    to_return->u.stm_exp.exp = exp;

    return to_return;
}

t_stm t_stm_new_return(t_exp exp) {

    t_stm  to_return = (t_stm) malloc(sizeof(*t_stm));

    to_return->kind = STM_RETURN;
    to_return->u.stm_decl.decl = decl;

    return to_return;
}

t_stm t_stm_new_if_else(t_exp exp, t_stms then_stms, t_stms else_stms) {

    t_stm  to_return = (t_stm) malloc(sizeof(*t_stm));

    to_return->u.stm_if_else.exp = exp;
    to_return->u.stm_if_else.then_stms = then_stms;
    to_return->u.stm_if_else.else_stms = else_stms;

    if(else_stms) {

        to_return->kind = STM_IF_THEN_ELSE;

    } else {

        to_return->kind = STM_IF_THEN;
    }

    return to_return;
}

t_stm t_stm_new_while(t_exp exp, t_stms while_stms) {

    t_stm  to_return = (t_stm) malloc(sizeof(*t_stm));

    to_return->kind = STM_WHILE;

    to_return->u.stm_while.exp = exp;
    to_return->u.stm_while.while_stms = while_stms;

    return to_return;
}

t_stm t_stm_new_next() {

    t_stm  to_return = (t_stm) malloc(sizeof(*t_stm));

    to_return->kind = STM_NEXT;

    return to_return;
}

//t_type

t_type t_type_new_type(int kind, char *type) {
    t_type to_return = (t_type) malloc(sizeof(*t_type));

    to_return->kind = kind;
    strcpy(to_return->u.type, type);

    return to_return;
}

t_type t_type_new_id(char *id) {
    t_type to_return = (t_type) malloc(sizeof(*t_type));

    to_return->kind = TYPE_ID;
    strcpy(to_return->u.id, id);

    return to_return;
}

t_type t_type_new_array(t_type type, int intlit) {
    t_type to_return = (t_type) malloc(sizeof(*t_type));

    to_return->kind = TYPE_ARRAY;
    to_return->u.array.type = type;
    to_return->u.array.intlit = intlit;

    return to_return;
}

//t_lit

t_lit t_lit_new_intlit(int intlit) {
    t_lit to_return = (t_lit) malloc(sizeof(*t_lit));

    to_return->kind = LIT_INTLIT;
    to_return->u.intlit = intlit;

    return to_return;
}

t_lit t_lit_new_floatlit(double floatlit) {
    t_lit to_return = (t_lit) malloc(sizeof(*t_lit));

    to_return->kind = LIT_FLOATLIT;
    to_return->u.floatlit = floatlit;

    return to_return;
}

t_lit t_lit_new_strlit(char *srtlit) {
    t_lit to_return = (t_lit) malloc(sizeof(*t_lit));

    to_return->kind = LIT_STRLIT;
    strcpy(to_return->u.strlit.strlit);

    return to_return;
}

t_lit t_lit_new_boollit(int boollit) {
    t_lit to_return = (t_lit) malloc(sizeof(*t_lit));

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
    t_exp to_return = (t_exp) malloc(sizeof(*t_exp));

    to_return->kind = EXP_LIT;
    to_return->lit = lit;

    return to_return;
}

t_exp t_exp_new_id(char *id) {

    t_exp to_return = (t_exp) malloc(sizeof(*t_exp));

    to_return->kind = EXP_ID;
    strcpy(to_return->id, id);

    return to_return;
}

t_exp t_exp_new_array(t_exp exp, int intlit) {
    t_exp to_return = (t_exp) malloc(sizeof(*t_exp));

    to_return->kind = EXP_ARRAY;
    to_return->u.array.exp = exp;
    to_return->u.array.intlit = intlit;

    return to_return;
}

t_exp t_exp_new_function(char *id, t_args args) {
    t_exp to_return = (t_exp) malloc(sizeof(*t_exp));

    to_return->kind = EXP_FUNC;
    to_return->u.func.args = args;
    strcpy(to_return->u.func.id, id);

    return to_return;
}