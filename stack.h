// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "lexerDef.h"
#include "parsetree.h"
#include "parser.h"
typedef struct stacki
{
    char *str;
    char* val;
    parsetree* parse;
    struct stacki *next;
}stack;
stack *push(stack *stack, stringlist strlist,parsetree* parent);
stack* pop(stack *stac);
bool isempty(stack* stac);
char *getstacktop(stack* stac);
stack* pushdollar(stack *stac);
stack* pushstartsymbol(stack * stac,char* startsymbol);
stack* popwithrule(stack *stac,int ruleno);
void printstack(stack* stac);
stack *match(stack *stac, set* tokset, stringlist **parseTable);