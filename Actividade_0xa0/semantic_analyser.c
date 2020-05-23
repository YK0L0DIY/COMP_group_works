#include "ST.h"
#include "semantic_analyser.h"

#define NOT "not"

//TODO void ERROR(); com enum de erros e switch dos mesmos para print

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

                //todo perguntar ao carvalho que ele sabe

            }

            break;

    }
}

void check_args_type(t_args args, t_argdefs argdefs) {

    t_type type1 = t_exp_ant(args->u.exp);
    t_type type2 = argdefs->u.argdef.type;

    if(type1->kind != type2->kind) {

        //TODO ERROR ON TYPES;

    }

    if(args->kind == ARGS_SINGLE && argdefs->kind == ARGDEFS_LIST) {
        //TODO ERRO  NOT ENOUGH ARGS
    } else if(args->kind == ARGS_LIST && argdefs->kind == ARGDEFS_SINGLE) {
        //TODO ERRO  TOO MUCH ARGS
    } else {
        check_args_type(args->u.args, argdefs->u.argdefs);
    }
}

void t_decls_ant(t_decls decls) {

    switch(decls->kind) {

        case DECLS_SINGLE:

            t_decl_ant(decls->u.decl);
            break;

        case DECLS_LIST:

            t_decls_ant(decls->u.decls);
            break;
    }
}

void t_decl_ant(t_decl decl) {

    //TODO ACABAR
    switch(decl->kind) {

        case DECL_INIT:

            t_ids_ant(decl->u.init.id_list);
            //TYPE?!

            break;

        case DECL_ASSIGN:

            t_ids_ant(decl->u.assign.id_list);

            if(decl->u.assign.type != t_exp_ant(decl->u.assign.exp)) {

                //TODO ERROR(); DECL_INVALID_ASSIGN

            }
            break;

        case DECL_FUNC:

            ST_Data temp_id = ST_lookup(decl->u.func.id);

            if(temp_id == NULL) {

                temp_id->type = decl->u.func.type;
                ST_insert(decl->u.func.id, temp_id);

            }

            if(decl->u.func.argdefs != NULL) {

                //TODO ?!
            }

            if(decl->u.func.stms != NULL) {

                t_stms_ant(decl->u.func.stms);
            }

            break;

        case DECL_DEFINE:

            ST_Data temp_id = ST_lookup(decl->u.define.id);

            if(temp_id == NULL) {

                temp_id->type = t_type_new_type(5);
                ST_insert(decl->u.define.id, temp_id);

            } else {

                //TODO ERROR(); DECL_DEFINE_ALREADY_EXISTS
            }
            break;
    }
}

void t_ids_ant(t_ids ids) {

    switch(ids->kind) {

        case ID_SINGLE:

            //ASSIM N PERMITE REDEFINIR UMA VAR
            ST_Data temp_id = ST_lookup(ids->u.id);

            if(id == NULL) {

                temp_id->type = t_type_new_type(5);
                ST_insert(ids->u.id, temp_id);

            } else {

                //TODO ERROR(); ID_EXISTS
            }
            break;

        case ID_LIST:

            t_ids_ant(ids->u.id_list);
            break;
    }
}

void t_stms_ant(t_smtms stms) {

    switch(stms->kind) {

        case STMS_SINGLE:

            t_stm_ant(stms->u.stm);
            break;

        case STMS_LIST:

            t_stm_ant(stms->u.stm);
            t_stms_ant(stms->u.stms);
            break;

        default:
            //TODO ERROR();
            break;
    }
}

void t_stm_ant(t_stm stm) {

    switch(stm->kind) {

        case STM_DECL:

            t_decl_ant(stm->u.stm_decl.decl);
            break;

        case STM_EXP:

            t_exp_ant(stml->u.stm_exp.exp);
            break;

        case STM_IF_THEN:

            if(t_exp_ant(stm->u.stm_if_else.exp)->kind == TYPE_T_BOOL) {

                t_stms_ant(stm->u.stm_if_else.then_stms);

            } else {

                //TODO ERROR(); IF_NOT_BOOL_EXP

            }

            break;

        case STM_IF_THEN_ELSE:

            if(t_exp_ant(stm->u.stm_if_else.exp)->kind == TYPE_T_BOOL) {

                t_stms_ant(stm->u.stm_if_else.then_stms);
                t_stms_ant(stm->u.stm_if_else.else_stms);

            }else {

                //TODO ERROR(); IF_ELSE_NOT_BOOL_EXP

            }
            break;

        case STM_WHILE:

            if(t_exp_ant(stm->u.stm_while.exp)->kind == TYPE_T_BOOL) {

                t_stms_ant(stm->u.stm_while.while_stms);

            } else {

                //TODO ERROR(); WHILE_NOT_BOOL_EXP

            }
            break;

        default:
            //TODO ERROR();
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

    return to_return;
}

t_type t_exp_ant(t_exp exp) {

    t_type type1, type2;

    switch(exp->kind) {

        case EXP_LIT:

            return t_lit_ant(exp->u.lit);
            break;

        case EXP_ID:

            ST_Data temp_id = ST_lookup(exp->u-id);

            if(id == NULL) {

                //TODO ERROR(); EXP_ID_NOT_FOUND

            }

            return temp_id->type;
            break;

        case EXP_ARRAY:
            //TODO i dunno how
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

            ST_Data temp_ST = ST_lookup(exp->u.id);

            if(temp_ST->kind == ST_FUNC) {

                if(exp->u.func.args != NULL) {

                    check_args_type(exp->u.func.args, temp_ST->u.func.args);

                    return temp_ST->u.func.yatype;
                }

            } else {
                //TODO ERRO FUNC NOT FOUND
            }
            break;

        default:
            //ERROR
            break;

    }

}