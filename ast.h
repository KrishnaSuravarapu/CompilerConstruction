// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"astdef.h"
#include"parsetreedef.h"
enum{
    INTEGER,REAL,BOOLEAN,ERROR
}TYPE;
astree* createastnode(char* label);
void* astreenodegen(parsetree* node);
void putintosymboltable(idsymboltable* symboltab,parsetree* parsetreenode);
idsymboltable* initialisesymtab(idsymboltable* nestedparent);
symidentry* getinfoofsymbol(idsymboltable* symboltab,char* id);
void printsymboltable(idsymboltable* symboltab);
void populatesymboltable(parsetree* parsenode);
symfuncentry** initialisefunctable();
void putintofunctable(symfuncentry** functiontable,parsetree* parsenode);
void printfunctiontable(symfuncentry** functiontable);
symfuncentry* getinfooffunction(symfuncentry** functiontable,char* id);
void printast(astree* head);
void printqueue2(astree **que, int *newlen);
astree **putchildtoqueue2(astree **que, int *newlen);
void populatefunctiontable(parsetree *parsenode);
void printcustomsymboltable(idsymboltable *symboltab);
