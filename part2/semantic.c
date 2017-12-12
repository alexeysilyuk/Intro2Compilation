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
Bool isFuncDeclared(char* funcName, Scope* currentScope);
void addVarsToMatrix(node* tree, Scope* scope,Type type);
void error(char* msg);

Scope* globalScope ;

void runSemantic(node* tree){
	//printTree(tree,0);
	globalScope= createScope("GLOBAL",UNTYPED,NULL,FALSE);

	//updateNodesNype(tree);
	globalScope= createScopes(tree,globalScope);

	//printMatrix(globalScope->matrix);
}


Scope* createScopes(node *tree,Scope * globalScope){

	int space=0;
	if(strcmp("FUNCTION_DECLARATION",tree->token)==0)
		{
			// add parameters list adding to matrix table
			
			globalScope->matrix = prependMatrixElement(globalScope->matrix,tree->left->left->token,tree->left->type,"-",TRUE,NULL);
			globalScope = prependScope(tree->left->left->token,tree->left->type,globalScope,TRUE);
		}
				
	if(strcmp("BLOCK",tree->token)==0)
		globalScope = prependScope("(BLOCK",UNTYPED,globalScope,FALSE);


	if(strcmp("DECLARATION",tree->token)==0)	
		{
			node *subTree = tree;
			addVarsToMatrix(subTree,globalScope,subTree->type);
		}


	if(strcmp("function_call",tree->token)==0)	
		{
			if(isFuncDeclaredInScope(tree->left->token,globalScope)==TRUE)
				printf("%s is declared\n",tree->left->token);
			else
				printf("%s is NOT declared\n",tree->left->token);
		}
	if(strcmp("EXPRESSION",tree->token))
	{
		node* subTree=tree;
		printTree(subTree,0);
	}
	/*if(strcmp("BOOLEAN_EXPR_COMPLEX",tree->token)==0) || strcmp("|ID|",tree->left->token)==0 || strcmp("ID[]",tree->left->token)==0)	
		{
			if(isVariableDeclaredInScope(tree->left->token,globalScope)==TRUE)
				printf("%s is declared\n",tree->left->token);
			else
				printf("%s is NOT declared\n",tree->left->token);
		}
	*/

	if(strcmp("}",tree->token)==0)
		{
			printMatrix(globalScope->matrix);
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


/*
void updateNodesNype(node* tree)
{

		if(strcmp("DECLARATION",tree->token)==0)	
		{
		recursiveTyping(tree,tree->left->type);
		printf("%s : %d\n", tree->token,tree->type);
		printf("\tl -%s : %d\n", tree->left->left->token,tree->left->left->type);	
		printf("\tr -%s : %d\n", tree->left->right->token,tree->left->right->type);
		recursiveTyping(tree,tree->left->type);
		}
		
}
*/
void addVarsToMatrix(node* tree,  Scope* scope, Type type) {

			if(strcmp(tree->token,"ID")==0)
				{
				//printf("\tID:%s\n", tree->left->token);
				if(isVariableInMatrix(tree->left->token,scope->matrix)==FALSE)
					scope->matrix = prependMatrixElement(scope->matrix,tree->left->token,type,"-",FALSE,NULL);
				else
					printf("Variable %s is already exists\n",tree->left->token);

			}

	/*if(strcmp("=",tree->token)==0){
		char* variable = tree->left->token;


	}*/

			if (tree->left) 
				{   addVarsToMatrix(tree->left,scope,type);  }
			if (tree->right)
				{   addVarsToMatrix(tree->right,scope,type);}
			
			
	
	}

void error(char* msg){
	printf("\nERROR : %s! exiting...\n\n",msg);
	exit(1);
}