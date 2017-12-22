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
void declaration(node* tree, Scope* scope,Type type);
Type checkType(node* tree);
void complexExprTyping(node* tree, int space, Scope* scope);
void findVarsInParamList(node* tree, Scope* scope, matrixElement* matrix);
int funcCallParamsCount(node* tree);
Bool isAmountOfParamsCompare(Scope* scope, char* funcName, int paramsAmount,Type* compareParamsList);
void checkMainCorrectness(Scope*);
void funcCallParamsListTyping(node* tree,Scope* globalScope);
void function_call(node* tree, Scope * scope);
void parseReturnStatementType(node* tree,Scope* scope,Type* type);
Type getIDName(node* tree,Scope* scope);
void initialization(node* tree,  Scope* scope, Type type, decl_init_flag flag);
void checkXORStatement(node* tree,Scope* scope);
void booleanExprTyping(node* tree, Scope* scope);
void ifBlockParsing(node* tree, Scope* scope);
void whileBlockParsing(node* tree, Scope* scope);
void doWhileBlockParsing(node* tree, Scope* scope);
void forBlockParsing(node* tree, Scope* scope);
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
    globalScope->isScopeClosed=TRUE;
	//updateNodesNype(tree);

	createScopes(tree,globalScope);
    checkMainCorrectness(globalScope);
    printf("\n\t\t------ GLOBAL ------\n");
	//printScope(globalScope);


    //printf("GLOBAL : %s\n",globalScope->name);
    printMatrix(globalScope->matrix);
}


void createScopes(node *tree,Scope * globalScope){

	if(strcmp("USER_FUNCTION",tree->token)==0)
		{
			// add parameters list adding to matrix table
            if(strcmp("main", tree->left->token)==0) {
                if (isMainDeclared == FALSE) {
                    isMainDeclared = TRUE;
                }
                else {
                    printf("%s\n", error_text[MAIN_REDECLARATION]);
                    exit(MAIN_REDECLARATION);
                }
            }

            if(isFuncDeclaredInCurrentScope(tree->left->token,globalScope)==TRUE)
            {
                printf("Function %s is already declared in this scope\n",tree->left->token);
                exit(ERROR);
            }

            globalScope->matrix = prependMatrixElement(globalScope->matrix,tree->left->token,tree->left->type,"-",TRUE,0);
            globalScope = prependScope(tree->left->token,tree->left->type,globalScope,TRUE);
		}




    if(strcmp("DECLARATION",tree->token)==0)
    {
        node *subTree = tree;

        declaration(subTree,globalScope,subTree->type);
    }

    if(strcmp("DECL_INIT",tree->token)==0){
        node *subTree = tree;
        initialization(subTree,globalScope,UNTYPED,Initialization);
    }


    if(strcmp(tree->token,"return")==0){
        Type* returnType = (Type*)malloc(sizeof(Type));
        parseReturnStatementType(tree,globalScope,returnType);

        Type funcDeclaredType;
        if(strcmp(globalScope->name,"BLOCK")==0)
            funcDeclaredType = globalScope->returnType;
        else
        {
            funcDeclaredType= getFuncTypeMatrix(globalScope->name, globalScope->upperScope->matrix);
            globalScope->isScopeClosed = TRUE;
        }


        if(funcDeclaredType != *returnType){
            printf("Function \'%s\' return type different from function type %d | %d\n",globalScope->name,funcDeclaredType,*returnType);
            exit(ERROR);
        }
        if(*returnType==STRING_TYPE)
        {
            printf("Function \'%s\' return type can't be STRING\n",globalScope->name);
            exit(ERROR);
        }
        //globalScope->isScopeClosed == TRUE;

    }

    if(strcmp("return-void",tree->token)==0){
        printf("return void for %s\n",globalScope->name);
        globalScope->isScopeClosed = TRUE;
        if(globalScope->returnType!=VOID_TYPE)
        {
            printf("\'return ;\' can be used only for VOID functions\n");
            exit(ERROR);
        }

    }
    if(strcmp("params_types_list",tree->token)==0)
    {
        int params = binarytree_count(tree,"TYPE");
        globalScope->upperScope->matrix->paramsAmount = params;
        findVarsInParamList(tree->right,globalScope,globalScope->upperScope->matrix);

    }


	if(strcmp("BLOCK",tree->token)==0)
    {
        globalScope = prependScope("BLOCK",globalScope->returnType,globalScope,FALSE);

    }


    if(strcmp("(IF",tree->token)==0)
    {

        ifBlockParsing(tree,globalScope);
    }

    if(strcmp("(WHILE",tree->token)==0)
    {
        whileBlockParsing(tree,globalScope);
    }

    if(strcmp("(DO_WHILE",tree->token)==0) {
        doWhileBlockParsing(tree,globalScope);
    }

    if(strcmp("(FOR",tree->token)==0)
        forBlockParsing(tree,globalScope);

    if(strcmp("function_call",tree->token)==0)
    {
        function_call(tree,globalScope);
    }

    if(strcmp("FUNC_PARAM",tree->token)==0){
        funcCallParamsListTyping(tree,globalScope);
    }

    if(strcmp("ARRAY_SIZE",tree->token)==0)
    {
        if(tree->left)
        {
            complexExprTyping(tree->left,0,globalScope);
            tree->type = checkType(tree->left);
            if(tree->type != INT_TYPE){
                printf("%s : array size may be only INT type\n",symantic_error);
                exit(ERROR);
            }

        }
    }


	if(strcmp("}",tree->token)==0)
		{

            if(globalScope->isFunction)
            {
                if(globalScope->isScopeClosed == TRUE)
                {
                    printf("pop %s\n",globalScope->name);
                    popScope(globalScope);
                }
                else
                {
                    printf("Scope %s not closed!\n",globalScope->name);
                    exit(ERROR);
                }

            }
            else
                popScope(globalScope);
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
				printf("%s | %d\n", tree->token,tree->type);
			
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


void printFullTree(node* tree, int space) {
    int i;

        for (i= 0; i< space; i++)
        { printf("   "); }
        printf("%s | %d\n", tree->token,tree->type);

        space++;

        if (tree->left)
        {   printTree(tree->left, space);  }
        if (tree->right)
        {   printTree(tree->right, space);}


}


void declaration(node* tree,  Scope* scope, Type type) {

    if(strcmp("function_call",tree->token)==0)
    {
        function_call(tree,scope);

    }

    if(strcmp(tree->token,"ID")==0)
    {

        if(isVariableDeclaredInScope(tree->left->token,scope)==FALSE)
        {
            //printf("var %s added with type %d\n",tree->left->token,type);
            scope->matrix = prependMatrixElement(scope->matrix,tree->left->token,type,"-",FALSE,0);
        }

        else {
            printf("Variable %s is already exists\n", tree->left->token);
            exit(ERROR);
        }
    }

    if(strcmp("DECL_INIT",tree->token)==0){

        tree->type = type;
        initialization(tree,scope,type,Declaration);
    }

    if(strcmp("ID-ARRAY[size]",tree->token)==0 && type != STRING_TYPE)
    {
        printf("[] may be used only for STRING type\n");
        exit(ERROR);
    }

    if (tree->left)
				   declaration(tree->left,scope,type);
    if (tree->right)
				  declaration(tree->right,scope,type);

	}


void complexExprTyping(node* tree, int space, Scope* scope) {

    if (tree->right)
        complexExprTyping(tree->right, space,scope);

    if (tree->left)
        complexExprTyping(tree->left, space,scope);


    if(strcmp("|ID|",tree->token)==0)
    {

        if(tree->left)
        {
            if(tree->left->type==INT_TYPE || tree->left->type == STRING_TYPE)
            {
                tree->type = INT_TYPE;
                tree->left->type = INT_TYPE;
            }

            else
                printf("|%s| must be STRING or INTEGER type\n",tree->left->token);
        }
    }

    if(strcmp("function_call",tree->token)==0)
    {
        function_call(tree,scope);
        return;
    }

    if(strcmp("&",tree->token)==0)
    {
        tree->type = BITWISE_AND;
    }

    if(strcmp("^",tree->token)==0)
    {
        tree->type = BITWISE_XOR;
    }

    
    if(strcmp("EXPR_ID[]",tree->token)==0){
        tree->type = getIDName(tree,scope);
        //
    }


    if(tree->type == ID_TYPE) {

        Type type;

        if (isVariableDeclaredInScope(tree->token, scope) == TRUE) {
            type = getVarTypeScope(tree->token, scope);
            tree->type = type;
        }
        else if (isFuncDeclaredInScope(tree->token, scope) == TRUE) {
            Type type = getFuncTypeScope(tree->token, scope);
            tree->type = type;
        }
        else {

            printf("%s : %s %s\n", symantic_error, tree->token, error_text[UNDECLARED]);
            exit(UNDECLARED);
        }

    }

    tree->type = checkType(tree);

}




Type checkType(node* tree){

    if(tree->left&&tree->right)
    {
        if(tree->left->type == tree->right->type)
            return tree->left->type;


        if(tree->left->type== INT_TYPE && tree->right->type == INT_TYPE )
            return INT_TYPE;

        if (tree->left->type== BOOLEAN_TYPE && tree->right->type == BOOLEAN_TYPE)
            return BOOLEAN_TYPE;

        if(tree->left->type== BITWISE_XOR && tree->right->type == INTP_TYPE)
            return INT_TYPE;

        if(tree->left->type== BITWISE_XOR && tree->right->type == CHARP_TYPE)
            return CHAR_TYPE;

        if(tree->left->type== BITWISE_AND && tree->right->type == CHAR_TYPE)
            return CHARP_TYPE;

        if(tree->left->type== BITWISE_AND && tree->right->type == INT_TYPE)
            return INTP_TYPE;

        if(tree->left->type== BITWISE_AND && tree->right->type == STRING_TYPE)
            return CHARP_TYPE;

        if(tree->left->type== CHAR_TYPE && tree->right->type == NULL_TYPE)
            return CHAR_TYPE;

        if(tree->left->type== INTP_TYPE && tree->right->type == NULL_TYPE)
            return INTP_TYPE;

        if(tree->left->type == INTP_TYPE && tree->right->type==INT_TYPE)
            return INTP_TYPE;

        if(tree->left->type == INT_TYPE && tree->right->type==INTP_TYPE)
            return INTP_TYPE;

        if(tree->left->type == CHARP_TYPE && tree->right->type==INT_TYPE)
            return CHARP_TYPE;

        if(tree->left->type == INT_TYPE && tree->right->type== CHARP_TYPE)
            return CHARP_TYPE;

        if(tree->left->type == STRING_TYPE && tree->right->type == INT_TYPE && strcmp(tree->token,"EXPR_ID[]")==0)
            return CHAR_TYPE;


        printf("%s : %s! %d|%d\n",symantic_error,error_text[INCOMPATIBLE_TYPES],tree->left->type,tree->right->type);
        exit(INCOMPATIBLE_TYPES);


    }

    if(tree->left)
        return tree->left->type;

    if(!tree->left && tree->right)
        return tree->right->type;


    return tree->type;

}

void addParamToParamList(matrixElement* upperMatrix, char* scopeName, char* name, Type type){

        matrixElement* tempMatrix = upperMatrix;
        while(tempMatrix){
            if(strcmp(scopeName,tempMatrix->name)==0 && tempMatrix->isFunc==TRUE){
                upperMatrix->paramsTypes[upperMatrix->paramTypeIndex] = type;
                upperMatrix->paramTypeIndex++;
                //printf("%s : %d\n",name,upperMatrix->paramsTypes[upperMatrix->paramTypeIndex-1]);
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





void checkMainCorrectness(Scope *scope){
    if(isMainDeclared==FALSE){
        printf("Program must have \'main\' function!\n");
        exit(ERROR);
    }
    while(scope->matrix){
        if(strcmp("main", scope->matrix->name)==0 && scope->matrix->isFunc==TRUE){
            if(globalScope->matrix->paramsAmount!=0)
            {
                printf("Main function can not have parameters!\n");
                exit(ERROR);
            }
        }
        scope->matrix = scope->matrix->next;
    }
}

void funcCallParamsListTyping(node* tree,Scope* scope){

    if(strcmp("complex_expression",tree->token)==0)
    {
        complexExprTyping(tree,0,scope);
    }

    if(tree->left)
        funcCallParamsListTyping(tree->left,scope);
    if(tree->right)
        funcCallParamsListTyping(tree->right,scope);



}

void function_call(node* tree, Scope* scope){

    if (isFuncDeclaredInScope(tree->left->token, scope) == TRUE) {

        Type type = getFuncTypeScope(tree->left->token, scope);
        tree->type = type;

        Type* typesArray = (Type*)malloc(10* sizeof(Type));
        int params = funcCallCountParams(tree->left,typesArray,0);

        if(isAmountOfParamsCompare(scope,tree->left->token,params,typesArray) == FALSE){
            printf("function %s have incorrect amount of parameters!\n",tree->left->token);
            exit(ERROR);
        }

    }
    else
    {

        if(tree->left->left)
            printf("%s : function \'%s\' %s\n", symantic_error, tree->left->left->token,error_text[UNDECLARED]);
        else
            printf("%s : function \'%s\' %s\n", symantic_error, tree->left->token,error_text[UNDECLARED]);

        exit(UNDECLARED);
    }
}

void parseReturnStatementType(node* tree,Scope* scope,Type* type){

    if(tree->type == ID_TYPE) {
        Type type;

        if (isVariableDeclaredInScope(tree->token, scope) == TRUE) {
            type = getVarTypeScope(tree->token, scope);
            tree->type = type;
        }
        else if (isFuncDeclaredInScope(tree->token, scope) == TRUE) {
            Type type = getFuncTypeScope(tree->token, scope);
            tree->type = type;
        }
        else {
            printf("%s : %s %s\n", symantic_error, tree->token, error_text[UNDECLARED]);
            exit(UNDECLARED);
        }

    }



    if(tree->left)
        parseReturnStatementType(tree->left,scope,type);
    if(tree->right)
        parseReturnStatementType(tree->right,scope,type);

    tree->type = checkType(tree);
    *type = tree->type;


}

Type getIDName(node* tree,Scope* scope){

        if(tree->type == ID_TYPE) {


            if (isVariableDeclaredInScope(tree->token, scope) == TRUE) {

                return getVarTypeScope(tree->token, scope);
            }
                else if (isFuncDeclaredInScope(tree->token,scope)==TRUE)
            {

                return getFuncTypeScope(tree->token,scope);
            }

            else {

                printf("%s : %s %s\n", symantic_error, tree->token, error_text[UNDECLARED]);
                exit(UNDECLARED);
            }

        }

        if(tree->left)
            getIDName(tree->left,scope);
       /* if(tree->right)
            getIDName(tree->right,scope);
*/


    }

void initialization(node* tree,  Scope* scope, Type type, decl_init_flag flag) {

    if (flag == Initialization) {
        type = getIDName(tree->left, scope);
    }

    tree->type = type;

    complexExprTyping(tree->right, 0, scope);


    if((type==CHARP_TYPE || type == INTP_TYPE) && tree->right->type == NULL_TYPE)
        return;
    else if((type==STRING_TYPE || type ==CHAR_TYPE) && tree->right->type == CHAR_TYPE)
        return;
    else if (type != tree->right->type) {
        printf("Can't assign result with type %d to variable with %d type\n", tree->right->type, type);
        exit(ERROR);
    }

//    if(tree->left)



}

void ifBlockParsing(node* tree, Scope* scope){
    if(tree->left->right)
    {
        booleanExprTyping(tree->left->right,scope);
    }



}

void booleanExprTyping(node* tree, Scope* scope){
    complexExprTyping(tree,0,scope);
    if(strcmp("complex_expression",tree->token)==0)
    {

        complexExprTyping(tree,0,scope);
        if(tree->left)
            tree->type = tree->left->type;
        if(tree->right)
            tree->type = tree->right->type;
    }

    if(strcmp(tree->token,">")==0 ||
            strcmp(tree->token,">=")==0 ||
            strcmp(tree->token,"<")==0 ||
            strcmp(tree->token,"<=")==0)
    {
        if(tree->left->type != INT_TYPE || tree->right->type!=INT_TYPE)
        {
            printf("%s|%d - %s:%d\n",tree->left->token,tree->left->type,tree->right->token,tree->right->type);
            printf("Operands in boolean expression must be INTEGER\n");
            exit(ERROR);
        }
        else
            tree->type = BOOLEAN_TYPE;
    }

    if(strcmp("&&",tree->token)==0 || strcmp("||",tree->token)==0)
    {
        complexExprTyping(tree->left,0,scope);
        complexExprTyping(tree->right,0,scope);

    }

    if(strcmp("==",tree->token)==0 || strcmp("!=",tree->token)==0)
    {

        if(tree->left->type == INT_TYPE && tree->right->type==INT_TYPE ||
           tree->left->type == BOOLEAN_TYPE && tree->right->type==BOOLEAN_TYPE ||
           tree->left->type == CHARP_TYPE && tree->right->type==CHARP_TYPE ||
           tree->left->type == CHAR_TYPE && tree->right->type==CHAR_TYPE ||
           tree->left->type == INTP_TYPE && tree->right->type==INTP_TYPE)
        {
           tree->type = BOOLEAN_TYPE;
        }
        else
        {
            printf("Operands types on comparison expression must be equal\n");
            exit(ERROR);
        }


    }

    if(strcmp("!",tree->token)==0)
    {
        complexExprTyping(tree->right,0,scope);
        tree->type= tree->right->type;

        if(tree->right->type != BOOLEAN_TYPE)
            printf("\'!\' Operator must receive only boolean right operand!\n");
    }

    if(tree->left)
        booleanExprTyping(tree->left,scope);

    if(tree->right)
        booleanExprTyping(tree->right,scope);



}

void whileBlockParsing(node* tree, Scope* scope){
    if(tree->left)
    {
        booleanExprTyping(tree->left,scope);
    }
}

void doWhileBlockParsing(node* tree, Scope* scope){
    if(tree->right)
    {
        booleanExprTyping(tree->right,scope);
    }
}

void forBlockParsing(node* tree, Scope* scope){
    if(strcmp("FOR_COND",tree->token)==0){
        if(tree->right)
        {
            booleanExprTyping(tree->right,scope);
        }
    }

    if(tree->left)
        forBlockParsing(tree->left,scope);

    if(tree->right)
        forBlockParsing(tree->right,scope);
}