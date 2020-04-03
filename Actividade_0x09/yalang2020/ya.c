//Functions
t_decls t_decls_new(t_decl decl, t_decls decls) {

    t_decls to_return = (t_decls*) malloc(sizeof(struct t_decls_));

    to_return->u.decl = decl;
    to_return->u.decls = decls;

    if (decls) {

        to_return->kind = DECLS_LIST;

    } else {

        to_return->kind = DECLS_SINGLE;

    }

    return to_return;
}