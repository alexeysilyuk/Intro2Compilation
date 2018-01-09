#include <string.h>

// Stack
char st[10][10];
int top = 0;
char i_l[2] = "0";
char temp[2] = "t";

int label[20];
int Inum = 0, Itop = 0;

//void if_f();
//void declaration_f(node* t);
void push(char* yytext);
void codeGen();
char* freshLabel();


void push(char* yytext) {
    strcpy(st[++top], yytext);
}


void codeGen() {
    if (st[top-2] && st[top-1] && st[top]) {
    printf("%s =  %s %s %s\n", freshLabel(), st[top-2], st[top-1], st[top]);
    top -= 2;
    strcpy(st[top], temp);
    }
}

char* freshLabel() {
    strcpy(temp, "t");
    strcat(temp, i_l);
    i_l[0]++;
    return temp;
}

void printStack()  {
    while(top>=0) {
        printf("%s\n", st[top]); 
        top--;
    } 
}

char* varAssign() {
if (st[top-2] && st[top-1] && st[top]) {
    char *var = strdup(st[top-1]);
    printf("%s %s %s\n", st[top-2], st[top], st[top-1]);
    top -= 2;
    return var;
    }
    
    return "";
}