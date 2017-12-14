#include "htable.c"



var* vTable;
funcs* fTable;

funcs* test(node* tree,funcs* globalScope){

    int space=0;
    if(strcmp("FUNCTION_DECLARATION",tree->token)==0)
    {
        // add parameters list adding to matrix table
        funcs* newfunc = createFunc(tree->left->left->token,tree->left->type,fTable->name);
        fTable = addFunc(newfunc,fTable);
    }

    if(strcmp("}",tree->token)==0)
    {

        popFuncScope(fTable);
    }

    /*if(strcmp("BLOCK",tree->token)==0)
        globalScope = prependScope("(BLOCK",UNTYPED,globalScope,FALSE);


    if(strcmp("DECLARATION",tree->token)==0)
    {
        node *subTree = tree;
        funcs* newfunc = newfunc(tree->left->left->token,tree->left->type);
        fTable = addFunc(newfunc,fTable);

        addVarsToMatrix(subTree,globalScope,subTree->type);
    }


*/


    if (tree->left)
        test(tree->left,globalScope);
    if (tree->right)
        test(tree->right,globalScope);


return fTable;
}


void run(node* tree){
    funcs* globalF= createFunc("GLOBAL",UNTYPED,"NULL");
    fTable = addFunc(globalF,fTable);

    test(tree,fTable);


    printFTable(fTable);
}


