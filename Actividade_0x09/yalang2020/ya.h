#ifndef YA_H_
#define YA_H_

//Structs
typedef struct t_decls_ *t_decls;

typedef struct t_decl_ *t_decl;

typedef struct t_argdefs_ *t_argdefs;

typedef struct t_argdef_ *t_argdef;

typedef struct t_args_ *t_args;

typedef struct t_ids_ *t_ids;

typedef struct t_stms_ *t_stms;

typedef struct t_stm_ *t_stm;

typedef struct t_type_ *t_type;

typedef struct t_lit_ *t_lit;

typedef struct t_exp_ *t_exp;

//Functions

//t_decls

t_decls t_decls_new(t_decl decl, t_decls decls);

//t_decl

t_decl t_decl_new_init(t_ids id_list, t_type type);

t_decl t_decl_new_assign(t_ids id_list, t_type type, t_exp exp);

t_decl t_decl_new_func(char *id, t_argdefs argdefs, t_type type, t_stms stms);

t_decl t_decl_new_define(char *id, t_type type);

//t_argdefs

t_argdefs t_argdefs_new(t_argdef argdef, t_argdefs argdefs);

//t_argdef

t_argdef t_argdef_new(char *id, t_type type);

//t_args

t_args t_args_new(t_exp exp, t_args args);

//t_ids

t_ids t_ids_new(char *id, t_ids id_list);

//t_stms

t_stms t_stms_new(t_stm stm, t_stms stms);

//t_stm

t_stm t_stm_new_decl(t_decl decl);

t_stm t_stm_new_exp(t_exp exp);

t_stm t_stm_new_return(t_exp exp);

t_stm t_stm_new_if_else(t_exp exp, t_stms then_stms, t_stms else_stms);

t_stm t_stm_new_while(t_exp exp, t_stms while_stms);

t_stm t_stm_new_next();

//t_type

t_type t_type_new_type(int kind);

t_type t_type_new_id(char *id);

t_type t_type_new_array(t_type type, int intlit);

//t_lit

t_lit t_lit_new_intlit(int intlit);

t_lit t_lit_new_floatlit(double floatlit);

t_lit t_lit_new_strlit(char *srtlit);

t_lit t_lit_new_boollit(int boollit);

//t_exp

t_exp t_exp_new_binop(char op[], t_exp arg1, t_exp arg2);

t_exp t_exp_new_unop(char op[], t_exp arg1);

t_exp t_exp_new_assign(t_exp exp, t_exp value);

t_exp t_exp_new_lit(t_lit lit);

t_exp t_exp_new_id(char *id);

t_exp t_exp_new_array(t_exp exp, int intlit);

t_exp t_exp_new_function(char *id, t_args args);

#endif