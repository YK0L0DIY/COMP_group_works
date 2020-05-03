#include "semantic_analyser.h"

#define NOT "not"

t_type check_types(int op, t_type type1, t_type type2) {

    switch (op) {

        case EXP_BINOP:

            if(type1->kind == TYPE_T_INT && type2->kind == TYPE_T_INT) {

                return type1;

            } else if(type1->kind == TYPE_T_FLOAT && type2->kind == TYPE_T_INT) {

                return type1;

            } else if(type1->kind == TYPE_T_INT && type2->kind == TYPE_T_FLOAT) {

                return type2;

            } else if(type1->kind == TYPE_T_BOOL && type2->kind == TYPE_T_BOOL) {

                return type1;

            } else {
                //TODO ERRO
            }

            break;

        case EXP_UNOP:

            //if true op was "not"
            if(type1 != NULL && type1->kind == TYPE_T_BOOL) {

                return type1;

            } else if(type2 != NULL && (type1->kind == TYPE_T_INT || type1->kind == TYPE_T_FLOAT)) {

                return type2;

            } else {
                //TODO ERRO
            }
            break;

        case EXP_ASSIGN:

            if(type1->kind == TYPE_T_ID) {

                if(type2->kind != TYPE_T_VOID &&
                    type2->kind != TYPE_T_ID &&
                    type2->kind != TYPE_T_ARRAY) {

                    return type2;
                }

            } else if (type1->kind == TYPE_ARRAY) {

            }

            break;

    }
}


t_type t_lit_ant(t_lit lit) {

    t_type to_return;

    switch(lit->kind) {

        case LIT_INTLIT:

            to_return = t_type_new_type(0);
            break;

        case LIT_FLOATLIT:

            to_return = t_type_new_type(1);
            break;

        case LIT_STRLIT:

            to_return = t_type_new_type(2);
            break;

        case LIT_BOOLLIT:

            to_return = t_type_new_type(3);
            break;
    }
}

t_type t_exp_ant(t_exp exp) {

    t_type type1, type2;

    switch(exp->kind) {

        case EXP_LIT:

            return t_lit_ant(exp->u.lit);
            break;

        case EXP_ID:
            //lookup do id, se n tiver cria?
            break;

        case EXP_ARRAY:
            break;

        case EXP_BINOP:

            type1 = t_exp_ant(exp->u.binop.arg1);
            type2 = t_exp_ant(exp->u.binop.arg2);

            return check_types(EXP_BINOP, t1, t2);

            break;

        case EXP_UNOP:

            type1 = t_exp_ant(exp->u.unop.arg);

            if(strcmp(NOT, exp->u.unop.op) == 0) {

                return check_types(EXP_UNOP, type1, NULL);

            } else {

                return check_types(EXP_UNOP, NULL, type2);

            }

            break;

        case EXP_ASSIGN:

            type1 = t_exp_ant(exp->u.assign.id);
            type2 = t_exp_ant(exp->u.assign.value);

            return check_types(EXP_ASSIGN, type1, type2);
            break;

        case EXP_FUNC:
            break;

        default:
            //ERROR
            break;

    }

}