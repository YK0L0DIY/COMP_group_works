#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "calctypes.h"

struct calc_t_exp_ {
    enum {EXP_NUM, EXP_ID, EXP_BINOP, EXP_UNOP, EXP_ASSIGN} kind;

    union {
        int num;
        char *id;

        struct{
            char op[3];
            calc_t_exp arg1;
            calc_t_exp arg2;
        } binop;

        struct{
            char op[3];
            calc_t_exp arg;
        } unop;

        struct{
            char *id;
            calc_t_exp value;
        } assign;
    } u;
};

struct calc_t_seq_ {
    enum {SEQ_EMPTY, SEQ_EXP} kind;
    union {
        struct {
            calc_t_exp e;
            calc_t_seq s;
        } exp;
    } u;
};

calc_t_exp calc_exp_new_num(int num){
    calc_t_exp ret = (calc_t_exp) malloc (sizeof (*ret));
    ret->kind = EXP_NUM;
    ret->u.num = num;
    return ret;
}
calc_t_exp calc_exp_new_id(char *id){
    calc_t_exp ret = (calc_t_exp) malloc (sizeof (*ret));
    ret->kind = EXP_ID;
    ret->u.id = id;
    return ret;
}
void calc_exp_print(calc_t_exp exp){
    switch (exp->kind) {
        case EXP_NUM:
            printf("[.exp [.num $%d$ ] ]\n", exp->u.num);
            break;

        case EXP_ID:
            printf("[.exp [.id $%s$ ] ]\n", exp->u.id);
            break;

        case EXP_BINOP:
            printf("[.exp [.binop [.$%s$ ] ", exp->u.binop.op);
            calc_exp_print(exp->u.binop.arg1);
            calc_exp_print(exp->u.binop.arg2);
            printf(" ] ]\n ");
            break;

        case EXP_UNOP:
            printf("[.exp [.unop [.$%s$ ] ", exp->u.unop.op);
            calc_exp_print(exp->u.unop.arg);
            printf(" ] ]\n ");
            break;

        case EXP_ASSIGN:
            printf("[.exp [.assign [.id $%s$ ] ", exp->u.assign.id);
            calc_exp_print(exp->u.assign.value);
            printf(" ] ]\n ");
            break;
    }
}

calc_t_seq calc_seq_new_empty(){
    calc_t_seq ret = (calc_t_seq) malloc (sizeof (*ret));
    ret->kind = SEQ_EMPTY;
    return ret;
}

calc_t_seq calc_seq_new_exp(calc_t_exp e, calc_t_seq s){
    calc_t_seq ret = (calc_t_seq) malloc (sizeof (*ret));

    ret->kind = SEQ_EXP;
    ret->u.exp.e = e;
    ret->u.exp.s = s;

    return ret;
}


void calc_seq_print(calc_t_seq s){
    switch (s->kind) {
        case SEQ_EMPTY:
            printf("[.\\emph{empty} ]\n");
            break;
        default:
            printf("[.seq \n");
            calc_exp_print(s->u.exp.e);
            calc_seq_print(s->u.exp.s);
            printf("] \n");
    }
}

calc_t_exp calc_exp_new_binop(char op[], calc_t_exp arg1, calc_t_exp arg2) {

  calc_t_exp to_return = (calc_t_exp) malloc(sizeof(*to_return));

  to_return->kind = EXP_BINOP;
  strcpy(to_return->u.binop.op, op);
  to_return->u.binop.arg1 = arg1;
  to_return->u.binop.arg2 = arg2;

  return to_return;
}

calc_t_exp calc_exp_new_unop(char op[], calc_t_exp arg1) {

  calc_t_exp to_return = (calc_t_exp) malloc(sizeof(*to_return));

  to_return->kind = EXP_UNOP;
  strcpy(to_return->u.unop.op, op);
  to_return->u.unop.arg = arg1;

  return to_return;
}

calc_t_exp calc_exp_new_assign(char *id, calc_t_exp value) {

  calc_t_exp to_return = (calc_t_exp) malloc(sizeof(*to_return));

  to_return->kind = EXP_ASSIGN;
  to_return->u.assign.id = id;
  to_return->u.assign.value = value;

  return to_return;
}
