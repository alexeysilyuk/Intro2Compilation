#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum type {ERROR=-2, UNTYPED=-1,BOOLEAN_TYPE=0, CHAR_TYPE=1, INT_TYPE=2, STRING_TYPE=3, CHARP_TYPE=4, INTP_TYPE=5, BIN_TYPE=6,OCT_TYPE=7,HEX_TYPE=8, VOID_TYPE=9, ID_TYPE=10, BITWISE_XOR=11,BITWISE_AND=12, NULL_TYPE=13 } Type;
typedef enum error_codes {UNDECLARED,USING_UNDECLARED_VARIABLE,INCOMPATIBLE_TYPES,USING_UNDECLARED_FUNCTION, MAIN_REDECLARATION} error_codes;
typedef enum decl_init_flag{Declaration, Initialization} decl_init_flag;
char* symantic_error = "Semantic Error";
char* error_text[] ={"Undeclared","Using undeclared variable",
              "Incompatible types", "Using undeclared function",
                     "Main function is already declared in program!"
};

typedef enum bool{FALSE,TRUE} Bool;

typedef struct paramElem{
    char* name;
    Type type;
    struct paramElem* next;

}paramElem;

typedef struct matrixElement
{
    char* name;
    Type type;
    char* value;
    Bool isFunc;
    int paramsAmount;
    int paramTypeIndex;
    Type* paramsTypes;
    paramElem* paramList;
    struct matrixElement* next;
} matrixElement;

Bool isMainDeclared;



Bool isFuncInMatrix(char* name, matrixElement* head);
void printParamsList(Type* typesList, int ammount);

matrixElement* createMatrixElement(char* name, Type type, char* value,Bool isFunc,int paramsAmount, matrixElement* next)
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
	new_node->paramsAmount = paramsAmount;
    new_node->paramsTypes = (Type*)malloc(10* sizeof(Type));
    new_node->paramList = NULL;
    new_node->paramTypeIndex=0;

    new_node->next = next;
    return new_node;
}


matrixElement* prependMatrixElement(matrixElement* head,char* name, Type type, char* value,Bool isFunc, int paramsAmount)
{
    //printf("\tName : %s, type : %d, value : %s\n",name,type, value);
    matrixElement* new_node = createMatrixElement(name,type,value,isFunc,paramsAmount,head);

    //printf("\tName : %s, type : %d, value : %s\n",new_node->name,new_node->type, new_node->value);
    head = new_node;
    return head;
}

void printMatrix(matrixElement* head){

	matrixElement *current = head;
	while(current!=NULL){
		printf("\t%s, type : %d, value : %s\n",current->name,current->type, current->value);
        if(current->isFunc) {
            printf("\t\t%s have %d params in declaration\n", current->name, current->paramsAmount);
            printParamsList(head->paramsTypes,head->paramsAmount);

        }
        current= current->next;
    }
}


Bool isFuncInMatrix(char* name, matrixElement* head){
    matrixElement *current = head;
    while(current)
        {
            if(strcmp(name,current->name)==0 && current->isFunc==TRUE)
                return TRUE;

            current = current->next;
        }
        return FALSE;
}

Bool isVariableInMatrix(char* name, matrixElement* head){
    matrixElement *current = head;
    while(current)
        {
            if(strcmp(name,current->name)==0 && current->isFunc==FALSE)
            {
                return TRUE;
            }

            current = current->next;
        }
        return FALSE;
}

Type getVarTypeMatrix(char* name, matrixElement* head){
    matrixElement *current = head;
    while(current)
    {
        if(strcmp(name,current->name)==0 && current->isFunc==FALSE)
            return current->type;
        else
            current = current->next;
    }
    return UNTYPED;
}

Type getFuncTypeMatrix(char* name, matrixElement* head){
    matrixElement *current = head;
    while(current)
    {
        if(strcmp(name,current->name)==0 && current->isFunc==TRUE)
            return current->type;
        else
            current = current->next;
    }
    return UNTYPED;
}

paramElem* prependParamElem(paramElem* newElem, paramElem* head){
    newElem->next = head;
    head = newElem;
    return head;
}

paramElem* createParamElem(char* name, Type type)
{
    paramElem* newElem = (paramElem*)malloc(sizeof(paramElem));
    if(!newElem){
        printf("Can't allocat memory for paramElem element");
        exit(1);
    }
    newElem->name = strdup(name);
    newElem->type = type;
    newElem->next = NULL;

    return newElem;

}

void printParamsList(Type* typesList, int ammount){

    if(typesList){
        int i;
        for(i=0;i<ammount;i++)
        {
            if(typesList[i])
                printf("\t\t\t%d\n",typesList[i]);
        }

    }

}

