#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ya.h"
#include "ST.h"
#include "list.h"
#include "semantic_analyser.h"

#define NOT "not"


enum {
    EXP_INCOMPATIBLE_TYPES,
    EXP_ID_NOT_FOUND,
    EXP_NOT_EXISTS,
    ARGS_NOT_ENOUGH_ARGS,
    ARGS_TOO_MUCH_ARGS,
    ARGS_INCOMPATIBLE_TYPES,
    DECL_INVALID_ASSIGN,
    DECL_DEFINE_ALREADY_EXISTS,
    ID_EXISTS,
    STMS_NOT_EXISTS,
    IF_NOT_BOOL_EXP,
    IF_ELSE_NOT_BOOL_EXP,
    WHILE_NOT_BOOL_EXP,
    FUNC_NOT_FOUND
};

//TODO void ERROR(); com enum de erros e switch dos mesmos para print
void ERROR(int error) {
    switch (error) {
        case EXP_INCOMPATIBLE_TYPES:
            printf("Expresion with incompatibles types\n");
            break;

        case EXP_ID_NOT_FOUND:
            printf("Expresion id not found\n");
            break;

        case EXP_NOT_EXISTS:
            printf("Expresion not exists\n");
            break;

        case ARGS_NOT_ENOUGH_ARGS:
            printf("Not enough args\n");
            break;

        case ARGS_TOO_MUCH_ARGS:
            printf("Too much args\n");
            break;

        case ARGS_INCOMPATIBLE_TYPES:
            printf("Argument types incompatible.\n");
            break;

        case DECL_INVALID_ASSIGN:
            printf("Invalid assignment\n");
            break;

        case DECL_DEFINE_ALREADY_EXISTS:
            printf("Type already exists\n");
            break;

        case ID_EXISTS:
            printf("ID already exists\n");
            break;

        case STMS_NOT_EXISTS:
            printf("Invalid statement type\n");
            break;

        case IF_NOT_BOOL_EXP:
            printf("Not expresion must be boolean\n");
            break;

        case IF_ELSE_NOT_BOOL_EXP:
            printf("Not expresion must be boolean\n");
            break;

        case WHILE_NOT_BOOL_EXP:
            printf("Not expresion must be boolean\n");
            break;

        case FUNC_NOT_FOUND:
            printf("Function not declared\n");
            break;
    }
}

t_type check_types(int op, t_type type1, t_type type2) {

    switch (op) {

        case EXP_BINOP:

            if (type1->kind == TYPE_T_INT && type2->kind == TYPE_T_INT) {

                return type1;

            } else if (type1->kind == TYPE_T_FLOAT && type2->kind == TYPE_T_INT) {

                return type1;

            } else if (type1->kind == TYPE_T_INT && type2->kind == TYPE_T_FLOAT) {

                return type2;

            } else if (type1->kind == TYPE_T_BOOL && type2->kind == TYPE_T_BOOL) {

                return type1;

            } else {
                ERROR(EXP_INCOMPATIBLE_TYPES);
            }

            break;

        case EXP_UNOP:

            //if true op was "not"
            if (type1 != NULL && type1->kind == TYPE_T_BOOL) {

                return type1;

            } else if (type2 != NULL && (type1->kind == TYPE_T_INT || type1->kind == TYPE_T_FLOAT)) {

                return type2;

            } else {
                ERROR(EXP_INCOMPATIBLE_TYPES);
            }
            break;

        case EXP_ARRAY:

            if (type1->kind == TYPE_ID || type1->kind == TYPE_ARRAY) {

                if (type2->kind != TYPE_T_INT) {
                    //TODO ERROR(); EXP_ARRAY_INVALID_SIZE
                }
            } else {
                //TODO ERROR(); EXP_INVALID_ASSIGN
            }

            return type1;
            break;
    }
}

void check_args_type(t_args args, t_argdefs argdefs) {

    t_type type1 = t_exp_ant(args->u.exp);
    t_type type2 = argdefs->u.argdef->type;

    if (type1->kind != type2->kind) {
        ERROR(ARGS_INCOMPATIBLE_TYPES);
        //TODO ERROR ON TYPES;

    }

    if (args->kind == ARGS_SINGLE && argdefs->kind == ARGDEFS_LIST) {
        ERROR(ARGS_NOT_ENOUGH_ARGS);
        //TODO ERRO  NOT ENOUGH ARGS
    } else if (args->kind == ARGS_LIST && argdefs->kind == ARGDEFS_SINGLE) {
        ERROR(ARGS_TOO_MUCH_ARGS);
        //TODO ERRO  TOO MUCH ARGS

    } else if (args->kind != ARGS_SINGLE && argdefs->kind != ARGDEFS_SINGLE) {

        check_args_type(args->u.args, argdefs->u.argdefs);

    }
}

void t_argdef_ant(t_argdef argdef) {

    ST_Data temp_id = new_ST_Data();

    temp_id->kind = ST_VAR;
    temp_id->u.var.kind = VARarg;
    temp_id->u.var.yatype = argdef->type;

    ST_insert(argdef->id, temp_id);
}

void t_argdefs_ant(t_argdefs argdefs) {

    if (argdefs == NULL) {
        return;
    }

        switch (argdefs->kind) {
            case ARGDEFS_SINGLE:
                t_argdef_ant(argdefs->u.argdef);
                break;
            case ARGDEFS_LIST:
                t_argdef_ant(argdefs->u.argdef);
                t_argdefs_ant(argdefs->u.argdefs);
                break;
        }
}

void t_decl_ant(t_decl decl) {

    ST_Data temp_id;

    //TODO ACABAR
    switch (decl->kind) {

        case DECL_INIT:

            t_ids_ant(decl->u.init.id_list, decl->u.init.type);

            break;

        case DECL_ASSIGN:

            t_ids_ant(decl->u.assign.id_list, decl->u.assign.type);

            if (decl->u.assign.type->kind != t_exp_ant(decl->u.assign.exp)->kind) {
                ERROR(DECL_INVALID_ASSIGN);
                //TODO ERROR(); DECL_INVALID_ASSIGN

            }
            break;

        case DECL_FUNC:

            temp_id = ST_lookup(decl->u.func.id);

            if (temp_id == NULL) {

                temp_id = new_ST_Data();

                temp_id->u.func.yatype = decl->u.func.type;
                temp_id->u.func.arg = decl->u.func.argdefs;
                temp_id->kind = ST_FUNC;
                ST_insert(decl->u.func.id, temp_id);

                ST_new_scope();

                t_argdefs_ant(decl->u.func.argdefs);
                t_stms_ant(decl->u.func.stms);

                ST_discard();

            } else {

                //TODO ERROR(); DECL_FUNC_ALREADY_EXISTS

            }
            break;

        case DECL_DEFINE:

            temp_id = ST_lookup(decl->u.define.id);

            if (temp_id == NULL) {

                temp_id = new_ST_Data();

                temp_id->u.type = t_type_new_type(5);
                temp_id->kind = ST_TYPE;
                ST_insert(decl->u.define.id, temp_id);

            } else {
                ERROR(DECL_DEFINE_ALREADY_EXISTS);
                //TODO ERROR(); DECL_DEFINE_ALREADY_EXISTS
            }
            break;
    }
}

void t_decls_ant(t_decls decls) {

    switch (decls->kind) {

        case DECLS_SINGLE:

            t_decl_ant(decls->u.decl);
            break;

        case DECLS_LIST:

            t_decl_ant(decls->u.decl);
            t_decls_ant(decls->u.decls);
            break;
    }
}

void t_ids_ant(t_ids ids, t_type type) {

    ST_Data temp_id;

    switch (ids->kind) {

        case ID_SINGLE:

            //ASSIM N PERMITE REDEFINIR UMA VAR
            temp_id = ST_lookup(ids->u.id);

            if (temp_id == NULL) {

                temp_id = new_ST_Data();

                temp_id->u.var.yatype = type;
                temp_id->u.type = t_type_new_type(5);
                temp_id->kind = ST_VAR;
                ST_insert(ids->u.id, temp_id);

            } else {
                ERROR(ID_EXISTS);
                //TODO ERROR(); ID_EXISTS
            }
            break;

        case ID_LIST:

            temp_id = ST_lookup(ids->u.id);

            if (temp_id == NULL) {

                temp_id = new_ST_Data();

                temp_id->u.var.yatype = type;
                temp_id->kind = ST_VAR;
                ST_insert(ids->u.id, temp_id);

            } else {
                ERROR(ID_EXISTS);
                //TODO ERROR(); ID_EXISTS
            }

            t_ids_ant(ids->u.id_list, type);

            break;
    }
}

void t_stm_ant(t_stm stm) {

    switch (stm->kind) {

        case STM_DECL:

            t_decl_ant(stm->u.stm_decl.decl);
            break;

        case STM_EXP:

            t_exp_ant(stm->u.stm_exp.exp);
            break;

        case STM_IF_THEN:

            if (t_exp_ant(stm->u.stm_if_else.exp)->kind == TYPE_T_BOOL) {

                t_stms_ant(stm->u.stm_if_else.then_stms);

            } else {
                ERROR(IF_NOT_BOOL_EXP);
                //TODO ERROR(); IF_NOT_BOOL_EXP

            }

            break;

        case STM_IF_THEN_ELSE:

            if (t_exp_ant(stm->u.stm_if_else.exp)->kind == TYPE_T_BOOL) {

                t_stms_ant(stm->u.stm_if_else.then_stms);
                t_stms_ant(stm->u.stm_if_else.else_stms);

            } else {
                ERROR(IF_ELSE_NOT_BOOL_EXP);
                //TODO ERROR(); IF_ELSE_NOT_BOOL_EXP

            }
            break;

        case STM_WHILE:

            if (t_exp_ant(stm->u.stm_while.exp)->kind == TYPE_T_BOOL) {

                t_stms_ant(stm->u.stm_while.while_stms);

            } else {
                ERROR(WHILE_NOT_BOOL_EXP);
                //TODO ERROR(); WHILE_NOT_BOOL_EXP

            }
            break;

        default:
            ERROR(STMS_NOT_EXISTS);
            //TODO ERROR();
            break;
    }

}

void t_stms_ant(t_stms stms) {

    switch (stms->kind) {

        case STMS_SINGLE:

            t_stm_ant(stms->u.stm);
            break;

        case STMS_LIST:

            t_stm_ant(stms->u.stm);
            t_stms_ant(stms->u.stms);
            break;

        default:
            ERROR(STMS_NOT_EXISTS);
            //TODO ERROR();
            break;
    }
}

t_type t_lit_ant(t_lit lit) {

    t_type to_return;

    switch (lit->kind) {

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

    ST_Data temp_id;
    t_type type1, type2;

    switch (exp->kind) {

        case EXP_LIT:

            return t_lit_ant(exp->u.lit);
            break;

        case EXP_ID:

            temp_id = ST_lookup(exp->u.id);

            if (temp_id == NULL) {
                ERROR(EXP_ID_NOT_FOUND);
                //TODO ERROR(); EXP_ID_NOT_FOUND
                break;

            }

            return temp_id->u.type;
            break;

        case EXP_ARRAY:

            type1 = t_exp_ant(exp->u.array.exp);
            type2 = t_exp_ant(exp->u.array.index);

            return check_types(EXP_ARRAY, type1, type2);
            break;

        case EXP_BINOP:

            type1 = t_exp_ant(exp->u.binop.arg1);
            type2 = t_exp_ant(exp->u.binop.arg2);

            return check_types(EXP_BINOP, type1, type2);

            break;

        case EXP_UNOP:

            type1 = t_exp_ant(exp->u.unop.arg);

            if (strcmp(NOT, exp->u.unop.op) == 0) {

                return check_types(EXP_UNOP, type1, NULL);

            } else {

                return check_types(EXP_UNOP, NULL, type2);

            }

            break;

        case EXP_ASSIGN:

            type1 = t_exp_ant(exp->u.assign.id);
            type2 = t_exp_ant(exp->u.assign.value);

            if (type1->kind != TYPE_ID) {
                //#TODO ERROR(); EXP_ASSIGN_INVALID_ID
            } else {
                temp_id = ST_lookup((exp->u.assign.id)->u.id);
            }

            if (temp_id == NULL) {
                //TODO ERROR(); EXP_ASSIGN_INVALID_ID

            } else {

                if (temp_id->kind != ST_VAR) {

                    //TODO ERROR(); EXP_ASSIGN_NOT_A_VAR

                } else {

                    type1 = temp_id->u.var.yatype;

                    if ((type1->kind == TYPE_ARRAY) && (type2->kind == TYPE_ARRAY)) {

                        if (type1->u.array.type->kind != type2->u.array.type->kind) {

                            //TODO ERROR(); EXP_ASSIGN_INCOMPATIBLE_ARRAY_TYPE

                        }

                    } else if (type1->kind == TYPE_ARRAY) {

                        if (type2->kind != type1->u.array.type->kind) {

                            //TODO ERROR(); EXP_ASSIGN_NCOMPATIBLE_TYPE_WITH_ARRAY
                        }
                    } else if (type2->kind == TYPE_ARRAY) {

                        if (type2->u.array.type->kind != type1->kind) {

                            //TODO ERROR(); EXP_ASSIGN_NCOMPATIBLE_TYPE_WITH_ARRAY
                        }

                    } else if (type1->kind != type2->kind) {

                        //TODO ERROR(); EXP_ASSIGN_INCOMAPTIBLE_TYPES

                    }
                }
            }

            return type1;
            break;

        case EXP_FUNC:

            temp_id = ST_lookup(exp->u.id);

            if (temp_id == NULL) {
                break;
            }

            if (temp_id->kind == ST_FUNC) {

                if (exp->u.func.args != NULL) {

                    check_args_type(exp->u.func.args, temp_id->u.func.arg);

                    return temp_id->u.func.yatype;
                }

            } else {
                ERROR(FUNC_NOT_FOUND);
                //TODO ERRO FUNC_NOT_FOUND
            }
            break;

        default:
            ERROR(EXP_NOT_EXISTS);
            // TODO ERROR
            break;
    }
    return NULL;
}