#ifndef CALC_TYPES_H_
#define CALC_TYPES_H_

typedef struct calc_t_exp_ *calc_t_exp;
typedef struct calc_t_seq_ *calc_t_seq;

void calc_seq_print(calc_t_seq s);
calc_t_exp calc_exp_new_num(int num);
calc_t_exp calc_exp_new_id(char *id);
calc_t_exp calc_exp_new_binop(char op[], calc_t_exp arg1, calc_t_exp arg2);
calc_t_exp calc_exp_new_unop(char op[], calc_t_exp arg);
calc_t_exp calc_exp_new_assign(char *id, calc_t_exp rvalue);

calc_t_seq calc_seq_new_empty();
calc_t_seq calc_seq_new_exp(calc_t_exp e, calc_t_seq s);

#endif
