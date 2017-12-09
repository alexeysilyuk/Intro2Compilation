#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum type {UNTYPED=-1,BOOLEAN_TYPE=0, CHAR_TYPE=1, INT_TYPE=2, STRING_TYPE=3, CHARP_TYPE=4, INTP_TYPE=5, BIN_TYPE=6,OCT_TYPE=7,HEX_TYPE=8 } Type;


typedef enum bool{FALSE,TRUE} Bool;
typedef struct matrixElement
{
    char* name;
    Type type;
    char* value;
    Bool isFunc;
    Type* paramList;
    struct matrixElement* next;
} matrixElement;


matrixElement* createMatrixElement(char* name, Type type, char* value,Bool isFunc,Type* paramList, matrixElement* next)
{
    matrixElement* new_node = (matrixElement*)malloc(sizeof(matrixElement));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
	new_node->name = strdup(name);
    new_node->type = type;
	new_node->value = strdup(value);
	new_node->isFunc = isFunc;
	new_node->paramList = paramList;
    
    new_node->next = next;
 
    return new_node;
}


matrixElement* prependMatrixElement(matrixElement* head,char* name, Type type, char* value,Bool isFunc, Type* paramList)
{
    matrixElement* new_node = createMatrixElement(name,type,value,isFunc,paramList,head);
    head = new_node;
    return head;
}

void printMatrix(matrixElement* head){
	matrixElement *current = head;
	while(current!=NULL){
		printf("name : %s, type : %d, value : %s\n",current->name,current->type, current->value);
        current= current->next;
    }
}





