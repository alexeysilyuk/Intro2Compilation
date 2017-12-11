#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scope.c"

//typedef enum type {UNTYPED=-1,BOOLEAN_TYPE=0, CHAR_TYPE=1, INT_TYPE=2, STRING_TYPE=3, CHARP_TYPE=4, INTP_TYPE=5, BIN_TYPE=6,OCT_TYPE=7,HEX_TYPE=8 } Type;


typedef struct node {
	char* token;
	struct node* left;
	struct node* right;
	int printHeader;
	Type type;
} node;


void printTree(node* tree, int space);
Scope* createScopes(node *tree,Scope * globalScope);

Scope* globalScope ;

void runSemantic(node* tree){
	//printTree(tree,0);
	globalScope= createScope("GLOBAL",UNTYPED,NULL,FALSE);
	globalScope= createScopes(tree,globalScope);


}


Scope* createScopes(node *tree,Scope * globalScope){

	int space=0;
	if(strcmp("FUNCTION_DECLARATION",tree->token)==0)
		globalScope = prependScope(tree->left->left->token,tree->left->type,globalScope,TRUE);
				
	if(strcmp("BLOCK",tree->token)==0)
		globalScope = prependScope("(BLOCK",UNTYPED,globalScope,FALSE);


	if(strcmp("DECLARATION",tree->token)==0)	
		{
			prependMatrixElement(globalScope->matrix,"Line statement",tree->left->type,"-",FALSE,NULL);
		}


	if(strcmp("}",tree->token)==0)
		popScope(globalScope);


	if (tree->left) 
		createScopes(tree->left,globalScope);
	if (tree->right)
		createScopes(tree->right,globalScope);
			
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
