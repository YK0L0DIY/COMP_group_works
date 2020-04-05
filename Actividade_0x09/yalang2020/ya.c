#include "ya.h"
#include <stdlib.h>

//Functions
t_decls t_decls_new(t_decl decl, t_decls decls) {

    t_decls to_return = (t_decls *) malloc(sizeof(struct t_decls_));

    to_return->u.decl = decl;
    to_return->u.decls = decls;

    if (decls) {

        to_return->kind = DECLS_LIST;

    } else {

        to_return->kind = DECLS_SINGLE;

    }

    return to_return;
}

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