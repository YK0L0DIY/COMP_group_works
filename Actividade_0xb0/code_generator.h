#include "ya.h"

void codegen_decls(t_decls decls);
void codegen_decl_init(t_decl init);
void codegen_decl_assign(t_decl assign);
void codegen_decl_func(t_decl func);
void codegen_decl_define(t_decl define);
void codegen_decl(t_decl decl);

//ARGDEFS AND SUB-GENERATORS
void codegen_argdef(t_argdef argdef);
void codegen_argdefs(t_argdefs argdefs);


//ARGS
void codegen_args(t_args args);

//IDS
void codegen_ids(t_ids ids);


//STMS
void codegen_stms(t_stms stms);

//STM AND SUB_GENERATORS
void codegen_stm_decl(t_stm decl);
void codegen_stm_exp(t_stm exp);
void codegen_stm_return(t_stm ret);
void codegen_stm_if_then(t_stm it);
void codegen_stm_if_then_else(t_stm ite);
void codegen_stm_while(t_stm whl);
void codegen_stm_next(t_stm nxt);
void codegen_stm(t_stm stm);

//LIT AND SUB-GENERATORS
void codegen_lit_intlit(t_lit intlit);
void codegen_lit_floatlit(t_lit floatlit);
void codegen_lit_strlit(t_lit strlit);
void codegen_lit_boollit(t_lit boollit);
void codegen_lit(t_lit lit);

//EXP AND SUB-GENERATORS
void codegen_exp_lit(t_exp lit);
void codegen_exp_id(t_exp id);
void codegen_exp_array(t_exp array);
void codegen_exp_binop(t_exp binop);
void codegen_exp_unop(t_exp unop);
void codegen_exp_assign(t_exp assign);
void codegen_exp_func(t_exp func);
void codegen_exp(t_exp exp);