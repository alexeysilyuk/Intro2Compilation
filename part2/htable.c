#include "semantic.c"



typedef struct var
{
    char* name;
    Type type;
    char* scopeName;
    struct var* next;
} var;

typedef struct funcs
{
    char* name;
    Type type;
    char* upperScopeName;
    Type* params;
    struct funcs* next;
} funcs;


var* createVar(char* name, Type type, char* scopeName){
    var* newvar = (var*)malloc(sizeof(var));
    newvar->name = strdup(name);
    newvar->type = type;
    newvar->scopeName = strdup(scopeName);
    newvar->next = NULL;
    return newvar;
}

funcs* createFunc(char* name, Type type, char* upperScopeName){

    funcs* newFunc = (funcs*)malloc(sizeof(funcs));
    if(newFunc == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }

    newFunc->name = strdup(name);
    newFunc->type = type;
    newFunc->upperScopeName = strdup(upperScopeName);
    newFunc->next = NULL;
    newFunc->params = NULL;
    return newFunc;
}


var* findVar(char* var, char* scope){
   /* while(head)
    {
        if(strcmp(head->name,var)==0 && strcmp(head->scopeName,scope)==0){
            return head;
        }
        head = head->next;
    }
    return head;*/
}


funcs* findFunc(char* scope, char* uppedScope, funcs* head){
    while(head)
    {
        if(strcmp(head->name,scope)==0 && strcmp(head->upperScopeName,uppedScope)==0){
            return head;
        }
        head = head->next;
    }
    return head;
}

funcs* addFunc(funcs* newFunc, funcs * head){

//    funcs* scope = createFunc(newFunc->name,newFunc->type,newFunc->upperScopeName);
    newFunc->next = head;
    head = newFunc;
    return head;
}

var* addVar(var* newVar, var * head){

//    funcs* scope = createFunc(newFunc->name,newFunc->type,newFunc->upperScopeName);
    newVar->next = head;
    head = newVar;
    return head;
}

void printFTable(funcs* head)
{
    while(head){
        printf("Name : %s, Type : %d, Upper : %s\n",head->name,head->type, head->upperScopeName);

        head= head->next;
    }
}

funcs* popFuncScope(funcs* head){

        if(strcmp(head->upperScopeName,"NULL")==0)
        {
            printf("FINISH\n");
            exit(0);
        }
        else
        {
            printf("POP %s\n",head->name);
            head->name = strdup(head->upperScopeName);
        }
return head;
}