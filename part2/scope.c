// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "matrixElement.c"
 

typedef struct Scope
{
    char* name;
    Type returnType;
    Bool isFunction;
    struct Scope* upperScope;
    matrixElement* matrix;

} Scope;


Scope* createScope(char* name, Type returnType, Scope* upperScope, Bool isFunction)
{
    Scope* newScope = (Scope*)malloc(sizeof(Scope));
    if(newScope == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }

    matrixElement* matrixHead = NULL;

    newScope->name= strdup(name);
    newScope->matrix = matrixHead;
    newScope->returnType=returnType;
    newScope->isFunction = isFunction;

    newScope->upperScope=upperScope;

    return newScope;
}


Scope* prependScope(char* name, Type returnType, Scope* upperScope, Bool isFunction )
{
    printf("PUSH %s : %d\n",name,returnType);
    Scope* scope = createScope(name,returnType,upperScope,isFunction);
    upperScope = scope;
    return upperScope;
}
 
Scope* popScope(Scope* head)
{
    if(strcmp(head->name,"GLOBAL")==0)
        {
            printf("FINISH\n");
            exit(0);
        }
    else
        {
            printf("POP %s\n",head->name);
            return head->upperScope;
        }
}


Bool isFuncDeclaredInScope(char* funcName, Scope* currentScope)
{
	while(currentScope)
	{
		if(isFuncInMatrix(funcName,currentScope->matrix)== TRUE)
				return TRUE;
		else
			currentScope=currentScope->upperScope;	

	}
	return FALSE;
	
}


Bool isVariableDeclaredInScope(char* varName, Scope* currentScope)
{
	while(currentScope)
	{
		if(isVariableInMatrix(varName,currentScope->matrix)== TRUE)
				return TRUE;
		else
			currentScope=currentScope->upperScope;

	}
	return FALSE;

}


Type getVarTypeScope(char* varName, Scope* currentScope)
{
    Type type=UNTYPED;
    while(currentScope)
    {
        type = getVarTypeMatrix(varName,currentScope->matrix);
        if(type!=UNTYPED)
            return type;
        else
            currentScope=currentScope->upperScope;

    }
    return type;
}

Type getFuncTypeScope(char* varName, Scope* currentScope)
{
    Type type=UNTYPED;
    while(currentScope)
    {
        type = getFuncTypeMatrix(varName,currentScope->matrix);
        if(type!=UNTYPED)
            return type;
        else
            currentScope=currentScope->upperScope;

    }
    return type;
}


void printScope(Scope* head)
{
    while(head){
        printf("Scope : %s, Type : %d, Func : %d\n",head->name,head->returnType, head->isFunction);
        if(head->matrix)
            printMatrix(head->matrix);
        head= head->upperScope;
    }
}