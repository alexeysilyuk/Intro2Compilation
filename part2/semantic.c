#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scope.c"

typedef struct node {
	char* token;
	struct node* left;
	struct node* right;
	int printHeader;
	Type type;
} node;


void printTree(node* tree, int space);
Scope* createScopes(node *tree,Scope * globalScope);
void updateNodesNype(node* tree);
Bool isFuncDeclaredInScope(char* funcName, Scope* currentScope);
void addVarsToMatrix(node* tree, Scope* scope,Type type);
Type checkType(node* tree);
void complexExprTyping(node* tree, int space, Scope* scope);
void findVarsInParamList(node* tree, Scope* scope);
//void printParamList(paramElem* head);

Scope* globalScope ;




unsigned int binarytree_count_recursive(const node *root)
{
    unsigned int count = 0;
    if (root->left != NULL) {
        if(strcmp("TYPE",root->token)==0)
            return 1;
        else
            count += binarytree_count_recursive(root->left);
    }
    if (root->right != NULL) {
        count += binarytree_count_recursive(root->right);
    }
    return count;
}

unsigned int binarytree_count(node* tree)
{
    unsigned int count = 0;
    if (tree != NULL) {
        count = binarytree_count_recursive(tree);
    }
    return count;
}


void runSemantic(node* tree){
	//printTree(tree,0);
	globalScope= createScope("GLOBAL",UNTYPED,NULL,FALSE);

	//updateNodesNype(tree);
	globalScope= createScopes(tree,globalScope);
    printf("\n\t\t------ GLOBAL ------\n");
	printMatrix(globalScope->matrix);
}


Scope* createScopes(node *tree,Scope * globalScope){

	int space=0;
	if(strcmp("FUNCTION_DECLARATION",tree->token)==0)
		{
			// add parameters list adding to matrix table

            globalScope->matrix = prependMatrixElement(globalScope->matrix,tree->left->left->token,tree->left->type,"-",TRUE,0);
            globalScope = prependScope(tree->left->left->token,tree->left->type,globalScope,TRUE);


            //printMatrix(globalScope->matrix);

		}

    if(strcmp("params_types_list",tree->token)==0)
    {
        int params = binarytree_count(tree);
        globalScope->upperScope->matrix->paramsAmount = params;
        findVarsInParamList(tree->right,globalScope);
    }


	if(strcmp("BLOCK",tree->token)==0)
		globalScope = prependScope("(BLOCK",UNTYPED,globalScope,FALSE);


	if(strcmp("DECLARATION",tree->token)==0)
		{
			node *subTree = tree;
			addVarsToMatrix(subTree,globalScope,subTree->type);
		}


//	if(strcmp("function_call",tree->token)==0)
//		{
//			if(isFuncDeclaredInScope(tree->left->token,globalScope)==TRUE)
//				printf("%s is declared\n",tree->left->token);
//			else
//				printf("%s is NOT declared\n",tree->left->token);
//		}

    if(strcmp("COMPLEX_EXPR",tree->token)==0)
    {
        complexExprTyping(tree,0,globalScope);
    }


	if(strcmp("}",tree->token)==0)
		{
			printScope(globalScope);
			popScope(globalScope);
		}

			
	if (tree->left) 
		createScopes(tree->left,globalScope);
	if (tree->right)
		createScopes(tree->right,globalScope);
		
	//printMatrix(globalScope->matrix);
	return globalScope;
}

void printTree(node* tree, int space) {
	int i;

		if(tree->printHeader==1)
		{	

			for (i= 0; i< space; i++) 
				{ printf("   "); }
				printf("%s\n", tree->token);
			
			space++;
			
			if (tree->left) 
				{   printTree(tree->left, space);  }
			if (tree->right)
				{   printTree(tree->right, space);}
			
			
		}
		else{
			if (tree->left) {   printTree(tree->left, space); }
			if (tree->right){   printTree(tree->right, space); }

		}
	}



void addVarsToMatrix(node* tree,  Scope* scope, Type type) {


    if(strcmp(tree->token,"ID")==0)
    {
        if(isVariableDeclaredInScope(tree->left->token,scope)==FALSE)
            scope->matrix = prependMatrixElement(scope->matrix,tree->left->token,type,"-",FALSE,0);
        /*else
            printf("Variable %s is already exists\n",tree->left->token);*/
			}

    if (tree->left)
				   addVarsToMatrix(tree->left,scope,type);
    if (tree->right)
				  addVarsToMatrix(tree->right,scope,type);

	}


void complexExprTyping(node* tree, int space, Scope* scope) {

    if (tree->right)
        complexExprTyping(tree->right, space,scope);

    if (tree->left)
        complexExprTyping(tree->left, space,scope);

    if(strcmp("function_call",tree->token)==0)
    {

        if (isFuncDeclaredInScope(tree->left->token, scope) == TRUE) {
            Type type = getFuncTypeScope(tree->left->token, scope);
            tree->type = type;
        }
        else
        {
            printf("%s : function \'%s\' %s\n", symantic_error, tree->left->left->token,error_text[UNDECLARED]);
            exit(UNDECLARED);
        }
    }


    if(tree->type == ID_TYPE) {
        Type type;

        if (isVariableDeclaredInScope(tree->token, scope) == TRUE) {
            type = getVarTypeScope(tree->token, scope);
            tree->type = type;
        }
        if (isFuncDeclaredInScope(tree->token, scope) == TRUE) {
            Type type = getFuncTypeScope(tree->token, scope);
            tree->type = type;
        }
        else {
            printf("%s : %s %s\n", symantic_error, tree->token,error_text[UNDECLARED]);
            exit(UNDECLARED);
        }
    }

    tree->type = checkType(tree);
    //printf("%s:%d\n", tree->token,tree->type);

}





Type checkType(node* tree){

    if(tree->left&&tree->right)
    {
        if(tree->left->type== INT_TYPE && tree->right->type == INT_TYPE && tree->type == INT_TYPE)
            return INT_TYPE;
        if (tree->left->type== BOOLEAN_TYPE && tree->right->type == BOOLEAN_TYPE && tree->type == BOOLEAN_TYPE)
            return BOOLEAN_TYPE;

        else
        {
            printf("%s : %s!\n",symantic_error,error_text[INCOMPATIBLE_TYPES]);
            exit(INCOMPATIBLE_TYPES);
        }
    }

    if(tree->left)
        return tree->left->type;


    return tree->type;

}


void findVarsInParamList(node* tree, Scope* scope){
    if(strcmp("TYPE",tree->token)==0) {
        if(tree->left && tree->right)
            //printf("%s : %s : %d\n",scope->name,tree->right->token,tree->left->type);
            if(isVariableDeclaredInScope(tree->right->token,scope)==FALSE)
                scope->matrix = prependMatrixElement(scope->matrix,tree->right->token,tree->left->type,"-",FALSE,0);

    }
    if(tree->left)
        findVarsInParamList(tree->left,scope);
        if(tree->right)
            findVarsInParamList(tree->right,scope);
}



