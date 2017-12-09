#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum type {UNTYPED=-1,BOOLEAN_TYPE=0, CHAR_TYPE=1, INT_TYPE=2, STRING_TYPE=3, CHARP_TYPE=4, INTP_TYPE=5, BIN_TYPE=6,OCT_TYPE=7,HEX_TYPE=8 } Type;

typedef struct node {
	char* token;
	struct node* left;
	struct node* right;
	int printHeader;
	Type type;
} node;


void printTree(node* tree, int space) {
	int i;


		if(strcmp(tree->token,"(BLOCK")==0 || strcmp("FUNCTION_DECLARATION",tree->token)==0)
				printf("NEWBLOCK-");

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
