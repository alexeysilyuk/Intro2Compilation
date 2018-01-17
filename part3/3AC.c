#include <string.h>


// Stack
char st[100][10];
int top = 0;
int i_l;
char temp[2] = "t";
char Label[5];
char TLable[5];
int TTop=0;
int label[20];
int labels[5];
int Inum = 0, Itop = 0;
char next[5];
int currentLine = -1;
char quadBuffer[50];
char TFstack[10][5];
char boolbuffer[7]="";
int TFindex=0;
int ifCondExprs=1;
int initT;
int funcBytes;

//void if_f();
//void declaration_f(node* t);
void push(char* yytext);
void codeGen();
char* freshLabel();
char* freshVar();


typedef struct _CodeLineEntry
{
    char *code;
    int gotoL;
    char funcName[30];
    struct _CodeLineEntry *next;
}  CodeLineEntry;

typedef struct _BackpatchList
{
    CodeLineEntry *entry;

    struct _BackpatchList *next;

}  BackpatchList;

CodeLineEntry *codeLineHead = NULL, *codeLineTail = NULL;
//BackpatchList* addToList(BackpatchList* list, CodeLineEntry* entry);


CodeLineEntry *genLine(char *code){
    fflush(stdout);
    //Create the element
    CodeLineEntry* newCodeLine = malloc(sizeof(CodeLineEntry));
    newCodeLine->code = strdup(code);
    newCodeLine->next = NULL;
    newCodeLine->gotoL = -1;
    //refresh the header/tail
    if(codeLineHead == NULL){
        codeLineHead = newCodeLine;
        codeLineTail = newCodeLine;
    }
    else{
        codeLineTail->next = newCodeLine;
        codeLineTail = newCodeLine;
    }
    currentLine++;
    //return a pointer to the new element
    return newCodeLine;
}



void push(char* yytext) {
    strcpy(st[++top], yytext);
}

char* freshVar() {
    sprintf(temp, "t%d",i_l);
    i_l++; //fix this
    funcBytes+=4;
    return temp;
}

void codeGen() {
    if (st[top-2] && st[top-1] && st[top]) {
        char buffer[100]="", freshv[5]="";

        strcpy(freshv,freshVar());
        strcat(buffer,freshv);
        strcat(buffer," = ");
        strcat(buffer,st[top-2]);
        strcat(buffer,st[top-1]);
        strcat(buffer,st[top]);
        top -= 2;
        strcpy(st[top],freshv);
        genLine(buffer);
    }
}



void printStack()  {
    int temp = top;
    while(temp>=0) {
        printf("%s\n", st[temp]);
        temp--;
    }
}

void varAssign() {
if (st[top-1] && st[top]) {
    char temp_text[100]="";
    //printf("%s, %s, %s\n\n",st[top-2],st[top-1],st[top]);
    strcat(temp_text,st[top-1]);
    strcat(temp_text," = ");
    strcat(temp_text,st[top]);
    genLine(temp_text);
    top -= 3;
    funcBytes+=4;
    }
}

char* freshLabel(){
    strcpy(Label,"");
    Inum++;
    char tempLabel[20] = "L";
    char itoa[2];
    sprintf(itoa, "%d", Inum);
    strcat(tempLabel,itoa);
    strcat(Label,tempLabel);
    label[++Itop]= Inum;
    labels[Inum] = Inum;

    return Label;
}
char* freshTLabel(){
    char itoa[6];
    strcpy(TLable,"");
    sprintf(itoa, "T%d", TTop++);
    strcat(TLable,itoa);
    return TLable;
}


void if_cond(){
if(top>=0) {
    char temp_text[100] = "ifZ ";
    strcat(temp_text, st[top--]);
    strcat(temp_text, " GOTO ");
    strcat(temp_text, "ElseLabel or BlockEnd");
    codeLineHead->gotoL = Itop;
    genLine(temp_text);
}
}

void else_cond(){
    char temp_text[100] = "";
    strcat(temp_text,"ElseLabel:");
    genLine(temp_text);
    codeLineHead->gotoL = Itop;
}

void printFreshLable(){
    printf("%s\n",freshLabel());
}

void endBlock(){
    char temp_text[100] = "";
    strcat(temp_text,freshLabel());
    strcat(temp_text," : BlockEnd");
    genLine(temp_text);
}

void gotoNext(){
    char temp_text[100] = "";
    strcat(temp_text,"\t\tGOTO _NEXT_");
    strcat(temp_text,next);
    strcat(temp_text," ;");
    genLine(temp_text);

}

int nextquad(){
    return currentLine + 1;
}


int printCode()
{
    CodeLineEntry *codeLine = codeLineHead;

    if(codeLine == NULL)
    {
         return 1;
    }

    unsigned long lineNumber = 0;
    FILE* file;
    file=fopen("output.3ac","a");
    while(codeLine)
    {
        int ret;
        //No goto
        if(codeLine->gotoL == -1){
            ret = printf("%-4lu %s\n", lineNumber, codeLine->code);
            fprintf(file,"%-4lu %s\n", lineNumber, codeLine->code);
        }
            //goto
        else{
            ret = printf("%-4lu %s\n", lineNumber, codeLine->code/*, codeLine->gotoL*/);
            fprintf(file,"%-4lu %s\n", lineNumber, codeLine->code);
        }
        if(ret <= 0)
        {
            printf("ERROR\n");
            return 1;
        }
        codeLine = codeLine->next;
        ++lineNumber;
    }

    return 0;
}


void while_cond(){

    char temp_text[100]="";
        strcat(temp_text, freshLabel());
        strcat(temp_text, ":");
        genLine(temp_text);
        strcpy(temp_text, "");
        strcat(temp_text, "ifZ ");
        strcat(temp_text, st[top--]);
        strcat(temp_text, " GOTO WHILE END");
        genLine(temp_text);


}

void while_end_block(){

    char temp_text[100] = "", buffer[50]="";
    strcat(temp_text,"GOTO ");
    strcat(temp_text,"L");
    sprintf(buffer,"%d",labels[Inum-1]);
    labels[Inum] = labels[Inum-1];
    label[Itop] = Inum--;
    strcat(temp_text,buffer);
    genLine(temp_text);
    strcpy(temp_text,"WHILE END:");
    genLine(temp_text);

}

void do_while_block()
{

    char temp_text[100]="",lbl[5]="";
    strcpy(lbl,freshLabel());
    //strcpy(label[Itop++],lbl);
    strcat(temp_text,lbl);
    strcat(temp_text,":");
    genLine(temp_text);
    push(lbl);
}

void do_while_cond()
{

    if(Itop>0) {

        char temp_text[100] = "", buffer[50]="";
        sprintf(temp_text,"ifNz %s GOTO ",st[top--]);
        strcat(temp_text,"L");
        sprintf(buffer,"%d",labels[Inum]);
        labels[Inum] = labels[Inum];
        label[Itop] = Inum--;
        strcat(temp_text,buffer);
        genLine(temp_text);
        
    }
}

void for_block_start()
{
    char temp_text[100]="";
    strcat(temp_text,freshLabel());
    strcat(temp_text,":");
    genLine(temp_text);
}

void for_expr_cond()
{
    if(top>0) {
        char temp_text[100] = "";
        strcat(temp_text, "ifZ ");
        strcat(temp_text, st[top--]);
        strcat(temp_text, " GOTO forNEXT");
        strcat(temp_text, " ;");
        genLine(temp_text);
    }
}

void createFreshLabel() {
    char temp_text[100] = "";
    strcpy(temp_text, "");
    strcat(temp_text, freshLabel());
    strcat(temp_text, ":");
    genLine(temp_text);
}

/*
BackpatchList* addToList(BackpatchList* list, CodeLineEntry* entry){

    fflush(stdout);
    if(entry == NULL){
        return list;
    }
    else if(list == NULL){
        BackpatchList* newEntry = malloc(sizeof(BackpatchList));
        newEntry->entry = entry;
        newEntry->next = NULL;
        return newEntry;
    }
    else{
        BackpatchList* newEntry = malloc(sizeof(BackpatchList)), *temp = list;
        newEntry->entry = entry;
        newEntry->next=NULL;
        while(list->next){
            list = list->next;
        }
        list->next = newEntry;
        return temp;
    }
}

*/

void func(char * funcName){

    char buffer[50]="",bytes[5]="";
    strcat(buffer,funcName);
    genLine(buffer);
    strcpy(buffer,"");
    strcat(buffer,"\t Begin func :");
    genLine(buffer);
    strcpy(codeLineTail->funcName,funcName);

}

void updateFuncBytes(char* funcName){
    char buffer[50]="";
    CodeLineEntry* tempLine = codeLineHead;
    while(tempLine) {
        if (strcmp(tempLine->funcName, funcName) == 0) {
            sprintf(buffer, "%d bytes", funcBytes);
            strcat(tempLine->code, buffer);
            funcBytes=0;

            break;
        }
        tempLine=tempLine->next;
    }

}

void funcReturn(){
    char buffer[50]="";
    strcat(buffer,"\tReturn ");
    strcat(buffer,st[top]);
    top--;
    genLine(buffer);
}

void funcCall(char* funcName)
{
    char buffer[50] = "";
    sprintf(buffer, "LCall %s", funcName);
    top--;
    push(buffer);

}

void voidFuncReturn(){
    char buffer[50]="";
    strcat(buffer,"\tReturn;");
    genLine(buffer);
}


int funcCallparams(node *root)
{
    if(root)
    {
        if(strcmp("FUNC_PARAM",root->token)==0)
        {
            return 1+funcCallparams(root->right);
        }
        else
            return funcCallparams(root->right);
    }
}

void pushFcallParam(char* var)
{
    char buffer[30]="";
    sprintf(buffer,"PushParam %s",var);
    genLine(buffer);
}

int funcCallParams(node* tree){
    int params = funcCallparams(tree);
    int i;
    for(i=0;i<params;i++)
        if(top>0){
        pushFcallParam(st[top--]);
    }

return params;
}
void popFuncCallParams(int params){
        char buffer[30] ="";
        sprintf(buffer,"Pop Params %d",params*4);
        genLine(buffer);

}



void shortCircuitAnd(){
    char temp_text[100]="",temp[5]="";
    printStack();
    if(top>=0) {
        strcat(temp_text, "ifZ ");
        strcat(temp_text, st[top]);
        strcat(temp_text, " GOTO ");
        sprintf(temp, "falseLable");
        strcat(temp_text, temp);
        genLine(temp_text);
        //printf("%s %s\n",TFstack[TFindex],st[top]);

    }
}
void shortCircuitOr(){
    char temp_text[100]="",temp[5]="";
    printStack();
    if(top>=0) {
        strcat(temp_text, "ifNz ");
        strcat(temp_text, st[top]);
        strcat(temp_text, " GOTO ");
        sprintf(temp, "trueLable");
        strcat(temp_text, temp);
        genLine(temp_text);
        //printf("%s %s\n",TFstack[TFindex],st[top]);

    }
}

void ANDcond(){
    char buffer[30]="",var[5]="";
    if(top>1)
    {
        strcpy(var,freshVar());
        sprintf(buffer,"%s = %s && %s",var,st[top--],st[top--]);
        genLine(buffer);
        push(var);
    }
}




void ORcond(){
    char buffer[30]="",var[5]="";
    if(top>1)
    {
        strcpy(var,freshVar());
        sprintf(buffer,"%s = %s || %s",var,st[top--],st[top--]);
        genLine(buffer);
        push(var);
    }
}
void idArrayDeclarator(char* varname){
    //printf("---idArrayDeclarator---\n");
    //printStack();
    //printf("---idArrayDeclarator END---\n");
}
void idArrayInitializator(char* varname){

    char freshV[30]="",buffer[50]="";
    if(top>0) {

        strcpy(freshV, freshVar());

        sprintf(buffer, "%s = %s*4", freshV, st[top--]);
        genLine(buffer);

        push(freshV);
        strcpy(freshV, freshVar());
        sprintf(buffer, "%s = %s+%s", freshV, st[top--], st[top--]);

        genLine(buffer);

        push(freshV);

        strcpy(freshV, freshVar());
        sprintf(buffer, "%s = *(%s)", freshV,st[top--]);
        genLine(buffer);
        push(freshV);
        //push(buffer);
        //push(buffer);

        //printStack();

        }

    //printf("%s = *(%s)\n",varname,st[top--]);

}

void unaryAssignment(char* op, char* var){
    top--;
    char buffer[50]="";
    sprintf(buffer,"%s%s",op,var);
    push(buffer);
}

void funcEndBlock(char* funcName){
    char temp_text[100] = "";
    sprintf(temp_text,"END FUNC %s",funcName);
    genLine(temp_text);
}


void printTree2(node* tree, int space) {
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





void createTLables(node* tree)
{
    char buffer[30]="";

    int initt= initT,i;
    //printf("top t: %d\nexprs in this IF expr - %d\n",i_l,ifCondExprs);
    for(i=0;i<ifCondExprs-1;i++){
        //printf("T%d\n",initt);
        initt++;
    }
    //if(strcmp()==0)
    //freshTLabel();
    //strcpy(TFstack[TFindex++],topT);
    //sprintf(buffer,"ifZ %s GOTO",topT);
    //genLine(buffer);
    //genLine(buffer);
    //sprintf(buffer,"ifNz %s ->%s=1",topT,TLable);
    //genLine(buffer);

}