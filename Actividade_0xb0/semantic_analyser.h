#ifndef SEMANTIC_ANALYSER_H_
#define SEMANTIC_ANALYSER_H_

#include "ya.h"

t_type check_types(int op, t_type type1, t_type type2);

void t_decls_ant(t_decls decls);
void t_decl_ant(t_decl decl);

void t_argdefs_ant(t_argdefs argdefs);
void t_argdef_ant(t_argdef argdef);     //TODO n sei se é preciso

void t_args_ant(t_args args);

void t_ids_ant(t_ids ids, t_type type);

void t_stms_ant(t_stms stms);
void t_stm_ant(t_stm stm);

void t_type_ant(t_type type);

t_type t_lit_ant(t_lit lit);

t_type t_exp_ant(t_exp exp);

#endif