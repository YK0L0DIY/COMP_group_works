#include <stdio.h>
#include "code_generator.h"
#include "ya.h"

//DECLS
void codegen_decls(t_decls decls){

    switch(decls->kind){
        case DECLS_LIST:

            //TODO TRATAR O RESULTADO DO PRIMEIRO CODEGEN
            codegen_decl(decls->u.decl);
            codegen_decls(decls->u.decls);
            break;

        case DECLS_SINGLE:

            codegen_decl(decls->u.decl);
            break;
    }

}

//DECLS AND SUB-GENERATORS
void codegen_decl_init(){
    
}
void codegen_decl_assign(){
    
}
void codegen_decl_func(){
    
}
void codegen_decl_define(){
    
}
void codegen_decl(){

}


//ARGDEFS AND SUB-GENERATORS
void codegen_argdef(t_argdef argdef) {
    
}

void codegen_argdefs(t_argdefs argdefs) {

    switch (argdefs->kind){
        case ARGDEFS_LIST:

            //TODO TRATAR O RESULTADO DO PRIMEIRO CODEGEN
            codegen_argdef(argdefs->u.argdef);
            codegen_argdefs(argdefs->u.argdefs);
            break;

        case ARGDEFS_SINGLE:
        
            codegen_argdef(argdefs->u.argdef);
            break;
        default:
            break;
    }
}


//ARGS
void codegen_args(t_args args){

    switch (args->kind){
        case ARGS_LIST:
            
            //TODO TRATAR O RESULTADO DO PRIMEIRO CODEGEN
            codegen_exp(args->u.exp);
            codegen_args(args->u.args);
            break;

        case ARGS_SINGLE:

            codegen_exp(args->u.exp);
            break;
        
        default:
            break;
        }
}

//IDS
void codegen_ids(t_ids ids) {

    switch (ids->kind){
        case ID_LIST:
            //TODO guardar na stack ou no $t0
            codegen_ids(ids->u.id_list);
            break;
        case ID_SINGLE:
            //TODO guardar na stack ou no $t0
            break;
        default:
            break;
    }
}


//STMS
void codegen_stms(t_stms stms){

    switch (stms->kind){

        case STMS_LIST:

            //TODO TRATAR O RESULTADO DO PRIMEIRO CODEGEN
            codegen_stm(stms->u.stm);
            codegen_stms(stms->u.stms);
            break;

        case STMS_SINGLE:

            codegen_stm(stms->u.stm);
            break;
        
        default:
            break;
    }
}

//STM AND SUB_GENERATORS
void codegen_stm_decl(){

}
void codegen_stm_exp(){

}
void codegen_stm_return(){

}
void codegen_stm_if_then(){

}
void codegen_stm_if_then_else(){

}
void codegen_stm_while(){

}
void codegen_stm_next(){

}
void codegen_stm(){

}

//LIT AND SUB-GENERATORS
void codegen_lit_intlit(){

}
void codegen_lit_floatlit(){

}
void codegen_lit_strlit(){

}
void codegen_lit_boollit(){

}
void codegen_lit(){

}

//EXP AND SUB-GENERATORS
void codegen_exp_lit(){

}
void codegen_exp_id(){
    
}
void codegen_exp_array(){
    
}
void codegen_exp_binop(){
    
}
void codegen_exp_unop(){
    
}
void codegen_exp_assign(){
    
}
void codegen_exp_func(){
    
}

void codegen_exp(){

}