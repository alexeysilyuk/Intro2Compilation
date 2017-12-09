#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char* token;
	struct node* left;
	struct node* right;
	int printHeader;
} node;

void printTree (node* tree, int space);






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
