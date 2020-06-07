#include <stdio.h>
#include "code_generator.h"
#include "ya.h"

void save_on_stack(char *reg) {
    printf("sw %s, 0($sp)\n", reg);
    printf("addiu $sp, $sp, -4\n");
}

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
void codegen_decl_init(t_decl init){

    //Analyzes the ids.
    codegen_ids(init->u.init.id_list);

    //saves the result from the previous codegen on the stack.
    save_on_stack("$t0");
    
}
void codegen_decl_assign(t_decl assign){

    //Analyzes the ids.
    codegen_ids(assign->u.assign.id_list);

    //saves the result from the previous codegen on the stack.
    save_on_stack("$t0");

    //Analyzes the expresseion.
    codegen_exp(assign->u.assign.exp);

    //saves the result from the previous codegen on the stack.
    save_on_stack("$t0");
    
}
void codegen_decl_func(t_decl func){

    printf("%s:\n", func->u.func.id);
    printf("move $fp, $sp\n");
    save_on_stack("$ra");

    codegen_stms(func->u.func.stms);

    printf("%s_exit:\n", func->u.func.id);
    printf("lw $ra, 4($sp)\n");
    printf("addiu $sp, $sp, %d\n", func->u.func.size);
    printf("lw $fp, 0($sp)\n");
    printf("jr $ra\n");
    
}
void codegen_decl_define(t_decl define){
    
}
void codegen_decl(t_decl decl){

    switch(decl->kind){

        case DECL_INIT:

            codegen_decl_init(decl);
            break;

        case DECL_ASSIGN:

            codegen_decl_assign(decl);
            break;

        case DECL_FUNC:

            codegen_decl_func(decl);
            break;

        case DECL_DEFINE:

            codegen_decl_define(decl);
            break;
    }
}


//ARGDEFS AND SUB-GENERATORS
void codegen_argdef(t_argdef argdef) {

    //LOOKUP DO VALOR? OU APENAS RESERVAR ESPAÇO?
    
}

//ARGDEFS
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
            //TODO guardar na stack ou no $t0 ??
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
void codegen_stm_decl(t_stm decl){

    codegen_decl(decl->u.stm_decl.decl);
}
void codegen_stm_exp(t_stm exp){

    codegen_decl(exp->u.stm_exp.exp);

}
void codegen_stm_return(t_stm ret){

}
void codegen_stm_if_then(t_stm it){

}
void codegen_stm_if_then_else(t_stm ite){

}
void codegen_stm_while(t_stm whl){

}
void codegen_stm_next(t_stm nxt){

}
void codegen_stm(t_stm stm){

    switch(stm->kind){
        case STM_DECL:
            codegen_stm_decl(stm);
            break;
        case STM_EXP:
            codegen_stm_exp(stm);
            break;
        case STM_RETURN:
            codegen_stm_return(stm);
            break;
        case STM_IF_THEN:
            codegen_stm_if_then(stm);
            break;
        case STM_IF_THEN_ELSE:
            codegen_stm_if_then_else(stm);
            break;
        case STM_WHILE:
            codegen_stm_while(stm);
            break;
        case STM_NEXT:
            codegen_stm_next(stm);
            break;
    }
}

//LIT AND SUB-GENERATORS
void codegen_lit_intlit(t_lit intlit){

}
void codegen_lit_floatlit(t_lit floatlit){

}
void codegen_lit_strlit(t_lit strlit){

}
void codegen_lit_boollit(t_lit boollit){

}
void codegen_lit(t_lit lit){

}

//EXP AND SUB-GENERATORS
void codegen_exp_lit(t_exp lit){}
void codegen_exp_id(t_exp id){}
void codegen_exp_array(t_exp array){}
void codegen_exp_binop(t_exp binop){}
void codegen_exp_unop(t_exp unop){}
void codegen_exp_assign(t_exp assign){}
void codegen_exp_func(t_exp func){}
void codegen_exp(t_exp exp){}