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
    printf("prepend func %s\n",name);
    Scope* scope = createScope(name,returnType,upperScope,isFunction);
    upperScope = scope;
    return upperScope;
}
 

