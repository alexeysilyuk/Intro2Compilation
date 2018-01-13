#include <string.h>


// Stack
char st[10][10];
int top = 0;
char i_l[2] = "0";
char temp[2] = "t";
char Label[5];
int label[20];
int labels[5];
int Inum = 0, Itop = 0;
char next[5];
int currentLine = -1;
char quadBuffer[50];
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
    strcpy(temp, "t");
    strcat(temp, i_l);
    i_l[0]++; //fix this
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
    while(top>=0) {
        printf("%s\n", st[top]); 
        top--;
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
    //printf("upper INUM : %d\n",labels[Inum]);
    return Label;
}

void if_cond(){
    char temp_text[100] = "ifZ ";
    strcat(temp_text,st[top--]);
    strcat(temp_text," GOTO ");
    strcat(temp_text,freshLabel());
    strcat(temp_text," ;");
    codeLineHead->gotoL = Itop;
    genLine(temp_text);
}

void else_cond(){
    char temp_text[100] = "";
    char itoa[2];
    sprintf(itoa, "L%d", label[Itop--]);
    strcat(temp_text,itoa);
    strcat(temp_text," :");
    genLine(temp_text);
    //printf("GOTOL %d\n",codeLineHead->gotoL);
    codeLineHead->gotoL = Itop;
}

void printFreshLable(){
    printf("%s\n",freshLabel());
}

void endBlock(){
    char temp_text[100] = "";
    strcat(temp_text,freshLabel());
    strcat(temp_text," :");
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


    while(codeLine)
    {
        int ret;
        //No goto
        if(codeLine->gotoL == -1){
            ret = printf("%-4lu %s\n", lineNumber, codeLine->code);
        }
            //goto
        else{
            ret = printf("%-4lu %s %d\n", lineNumber, codeLine->code, codeLine->gotoL);
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
    strcat(temp_text,freshLabel());
    strcat(temp_text,":");
    genLine(temp_text);
    strcpy(temp_text,"");
    strcat(temp_text,"ifZ ");
    strcat(temp_text,st[top--]);
    strcat(temp_text," GOTO __");
    strcat(temp_text," ;");
    genLine(temp_text);

}

void while_end_block(){

    char temp_text[100] = "", buffer[50]="";
    strcat(temp_text,"GOTO ");
    strcat(temp_text,"L");
    sprintf(buffer,"%d",labels[Inum]);
    labels[Inum] = labels[Inum-1];
    //label[Itop] = Inum--;
    strcat(temp_text,buffer);
    genLine(temp_text);
}

void do_while_block()
{

    char temp_text[100]="";
    strcat(temp_text,freshLabel());
    strcat(temp_text,":");
    genLine(temp_text);
}

void do_while_cond()
{
    char temp_text[100]="", buffer[50]="";
    strcat(temp_text,"ifNZ ");
    strcat(temp_text,st[top--]);
    strcat(temp_text," GOTO ");
    strcat(temp_text,"L");
    sprintf(buffer,"%d",Itop--);
    strcat(temp_text, buffer);
    strcat(temp_text," ;");
    genLine(temp_text);
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
    char temp_text[100]="";
    strcat(temp_text,"ifZ ");
    strcat(temp_text,st[top--]);
    strcat(temp_text," GOTO forNEXT");
    strcat(temp_text," ;");
    genLine(temp_text);
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
    strcat(buffer,":\n\t Begin func :");
    genLine(buffer);
    strcpy(codeLineTail->funcName,funcName);

    //codeLineTail->gotoL=-1;
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

void funcCall(char* funcName)
{
    char buffer[50] = "";
    sprintf(buffer, "LCall %s", funcName);
    push(buffer);
}
