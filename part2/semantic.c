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
void createScopes(node *tree,Scope * globalScope);
void updateNodesNype(node* tree);
Bool isFuncDeclaredInScope(char* funcName, Scope* currentScope);
void addVarsToMatrix(node* tree, Scope* scope,Type type);
Type checkType(node* tree);
void complexExprTyping(node* tree, int space, Scope* scope);
void findVarsInParamList(node* tree, Scope* scope, matrixElement* matrix);
int funcCallParamsCount(node* tree);
Bool isAmountOfParamsCompare(Scope* scope, char* funcName, int paramsAmount,Type* compareParamsList);
void checkMainCorrectness();
void funcCallParamsListTyping(node* tree,Scope* globalScope);
void function_call(node* tree);
//void printParamList(paramElem* head);

Scope* globalScope ;
paramElem* tempList;



paramElem* addVarsToParamList(const node *root)
{
    if (strcmp("TYPE", root->token) == 0) {
        paramElem *newElem = createParamElem(root->right->token, root->left->type);
        tempList = prependParamElem(newElem, tempList);
    }
    if (root->left)
        addVarsToParamList(root->left);

    if (root->right)
        addVarsToParamList(root->right);


}

unsigned int funcCallCountParams(const node *root,Type* typesArray, int i)
{

    if(root)
    {
        if(strcmp("FUNC_PARAM",root->token)==0)
        {
            typesArray[i++] = root->type;
            return 1+funcCallCountParams(root->right,typesArray,i);
        }
        else
            return funcCallCountParams(root->right,typesArray,i);
    }
}

unsigned int binarytree_count_recursive(const node *root, char* key)
{
    unsigned int count = 0;
    if (root->left != NULL) {
        if(strcmp(key,root->token)==0)
            return 1;

        else
            count += binarytree_count_recursive(root->left,key);
    }
    if (root->right != NULL) {
        count += binarytree_count_recursive(root->right,key);
    }
    return count;
}

unsigned int binarytree_count(node* tree, char* key)
{

    unsigned int count = 0;
    if (tree != NULL) {
        count = binarytree_count_recursive(tree,key);
    }
    return count;
}


void runSemantic(node* tree){
    isMainDeclared=FALSE;
	//printTree(tree,0);
	globalScope= createScope("GLOBAL",UNTYPED,NULL,FALSE);

	//updateNodesNype(tree);

	createScopes(tree,globalScope);
    checkMainCorrectness();
    printf("\n\t\t------ GLOBAL ------\n");
	//printScope(globalScope);


    //printf("GLOBAL : %s\n",globalScope->name);
    printMatrix(globalScope->matrix);
}


void createScopes(node *tree,Scope * globalScope){

	if(strcmp("FUNCTION_DECLARATION",tree->token)==0)
		{
			// add parameters list adding to matrix table
            if(strcmp("main", tree->left->left->token)==0) {
                if (isMainDeclared == FALSE) {
                    isMainDeclared = TRUE;
                }
                else {
                    printf("%s\n", error_text[MAIN_REDECLARATION]);
                    exit(MAIN_REDECLARATION);
                }
            }
            if(isFuncDeclaredInCurrentScope(tree->left->left->token,globalScope)==TRUE)
            {
                printf("Function %s is already declared in this scope\n",tree->left->left->token);
                exit(ERROR);
            }
            globalScope->matrix = prependMatrixElement(globalScope->matrix,tree->left->left->token,tree->left->type,"-",TRUE,0);
            globalScope = prependScope(tree->left->left->token,tree->left->type,globalScope,TRUE);

            //printMatrix(globalScope->matrix);

		}
    if(strcmp("DECLARATION",tree->token)==0)
    {
        node *subTree = tree;
        addVarsToMatrix(subTree,globalScope,subTree->type);
    }

    if(strcmp("params_types_list",tree->token)==0)
    {
        int params = binarytree_count(tree,"TYPE");
        globalScope->upperScope->matrix->paramsAmount = params;
        printf("%s have %d params\n",globalScope->name,params);
        findVarsInParamList(tree->right,globalScope,globalScope->upperScope->matrix);

    }


//	if(strcmp("BLOCK",tree->token)==0)
//		globalScope = prependScope("(BLOCK",UNTYPED,globalScope,FALSE);





    /*if(strcmp("function_call",tree->token)==0)
    {

        if (isFuncDeclaredInScope(tree->left->token, globalScope) == TRUE) {
            Type type = getFuncTypeScope(tree->left->token, globalScope);
            tree->type = type;

            Type* typesArray = (Type*)malloc(10* sizeof(Type));
            int params = funcCallCountParams(tree->left,typesArray,0);

            if(isAmountOfParamsCompare(globalScope,tree->left->token,params,typesArray) == FALSE){
                printf("function %s have incorrect amount of parameters!\n",tree->left->token);
                exit(ERROR);
            }
            //funcCallParamsCount(tree);
            //if(tree->right)
            //funcCallParamsCount(tree);


        }
        else
        {
            printf("%s : function \'%s\' %s\n", symantic_error, tree->left->left->token,error_text[UNDECLARED]);
            exit(UNDECLARED);
        }
    }
*/
    if(strcmp("FUNC_PARAM",tree->token)==0){
        funcCallParamsListTyping(tree,globalScope);
    }




	if(strcmp("}",tree->token)==0)
		{

			printScope(globalScope);
			popScope(globalScope);
            //printMatrix(globalScope->matrix);
		}

			
	if (tree->left) 
		createScopes(tree->left,globalScope);
	if (tree->right)
		createScopes(tree->right,globalScope);
		
	//printMatrix(globalScope->matrix);
	//return globalScope;
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

        else {
            printf("Variable %s is already exists\n", tree->left->token);
            exit(ERROR);
        }
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
        function_call(tree);
    }

    if(tree->type == ID_TYPE) {
        Type type;
        //printf("ID:%s\n",tree->token);
        if (isVariableDeclaredInScope(tree->token, scope) == TRUE) {
            type = getVarTypeScope(tree->token, scope);
            tree->type = type;
        }
        else if (isFuncDeclaredInScope(tree->token, scope) == TRUE) {
            Type type = getFuncTypeScope(tree->token, scope);
            tree->type = type;
        }
        else {
            printf("%s : %s %s\n", symantic_error, tree->token,error_text[UNDECLARED]);
            exit(UNDECLARED);
        }
    }

    tree->type = checkType(tree);


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

void addParamToParamList(matrixElement* upperMatrix, char* scopeName, char* name, Type type){

        matrixElement* tempMatrix = upperMatrix;
        while(tempMatrix){
            if(strcmp(scopeName,tempMatrix->name)==0 && tempMatrix->isFunc==TRUE){
                upperMatrix->paramsTypes[upperMatrix->paramTypeIndex] = type;
                upperMatrix->paramTypeIndex++;
                printf("%s : %d\n",name,upperMatrix->paramsTypes[upperMatrix->paramTypeIndex-1]);
                //addParamToParamList(upperMatrix, scope->name,tree->right->token, tree->left->type);
               // tempMatrix->paramList = prependParamElem(newElem,tempMatrix->paramList);
            }
            tempMatrix=tempMatrix->next;

        }

}


void findVarsInParamList(node* tree, Scope* scope, matrixElement* matrix){
    if(strcmp("TYPE",tree->token)==0) {
        if(tree->left && tree->right)
            //printf("%s : %s : %d\n",scope->name,tree->right->token,tree->left->type);
            if(isVariableDeclaredInScope(tree->right->token,scope)==FALSE)
            {
                scope->matrix = prependMatrixElement(scope->matrix,tree->right->token,tree->left->type,"-",FALSE,0);
                addParamToParamList(matrix, scope->name,tree->right->token, tree->left->type);
            }
    }
    if(tree->left)
        findVarsInParamList(tree->left,scope,matrix);
        if(tree->right)
            findVarsInParamList(tree->right,scope,matrix);
}

Bool isAmountOfParamsCompare(Scope* scope, char* funcName, int paramsAmount,Type* compareParamsList){
    Scope* temp = scope;
    Type* orignalParamsList;
    int params=-1;
    if(isFuncDeclaredInScope(funcName,temp)==FALSE)
        printf("Func %s not declared in scope %s\n",funcName,scope->name);

    while(temp){
        matrixElement *current = temp->matrix;

        while(current)
        {
            if(strcmp(funcName,current->name)==0 && current->isFunc==TRUE)
            {
                params = current->paramsAmount;
                orignalParamsList=current->paramsTypes;
            }

            current = current->next;
        }

        temp = temp->upperScope;
    }
    int i;

    if(params!=paramsAmount)
        return FALSE;

    for(i=0;i<params;i++){
        if(orignalParamsList[i]!=compareParamsList[i])
        {
            printf("expexted type: %d, received type: %d\n",orignalParamsList[i],compareParamsList[i]);
            exit(ERROR);
        }
    }
    return params==paramsAmount;
}





void checkMainCorrectness(){
    if(isMainDeclared==FALSE){
        printf("Program must have \'main\' function!\n");
        exit(ERROR);
    }
    while(globalScope->matrix){
        if(strcmp("main", globalScope->matrix->name)==0 && globalScope->matrix->isFunc==TRUE){
            if(globalScope->matrix->paramsAmount!=0)
            {
                printf("Main function can not have parameters!\n");
                exit(ERROR);
            }
        }
        globalScope->matrix = globalScope->matrix->next;
    }
}

void funcCallParamsListTyping(node* tree,Scope* globalScope){

    if(strcmp("complex_expression",tree->token)==0)
    {
        complexExprTyping(tree,0,globalScope);
    }

    if(tree->left)
        funcCallParamsListTyping(tree->left,globalScope);
    if(tree->right)
        funcCallParamsListTyping(tree->right,globalScope);



}

void function_call(node* tree){
    if (isFuncDeclaredInScope(tree->left->token, globalScope) == TRUE) {
        Type type = getFuncTypeScope(tree->left->token, globalScope);
        tree->type = type;

        Type* typesArray = (Type*)malloc(10* sizeof(Type));
        int params = funcCallCountParams(tree->left,typesArray,0);

        if(isAmountOfParamsCompare(globalScope,tree->left->token,params,typesArray) == FALSE){
            printf("function %s have incorrect amount of parameters!\n",tree->left->token);
            exit(ERROR);
        }

    }
    else
    {
        printf("%s : function \'%s\' %s\n", symantic_error, tree->left->left->token,error_text[UNDECLARED]);
        exit(UNDECLARED);
    }
}