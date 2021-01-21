// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ast.h"
// typedef struct parsetree{
// astree* astaddr;
// char node[30];
// struct parsetree ** child;
// struct parsetree * parent;
// char * value;
// int rulenum;
// int no_of_childs;
// }parsetree;
parsetree **finalprint;
int *printlen;
int parsenode_count;
parsetree *initialise(char *charstr)
{
    parsenode_count++;
    parsetree *parseel;
    parseel = malloc(sizeof(parsetree));
    parseel->child = NULL;
    parseel->astaddr = NULL;
    parseel->no_of_childs = 0;
    parseel->linenum=-1;
    strcpy(parseel->node, charstr);
    memset(parseel->value, 0, 30);
    return parseel;
}
void printqueue(parsetree **que, int *len)
{
    printf("------------------   ");
    for (int i = 0; i < *len; i++)
    {
        printf("%s   ", que[i]->node);
        //printf("Line num is %d",que[i]->linenum);
        //printf(" rule num %d   \n",que[i]->rulenum);
        
    }
    printf("    -------------------\n");
    //printf("\n");
}
parsetree **putchildtoqueue(parsetree **que, int *len)
{
    int count = 0;
    int indcount = 0;
    for (int i = 0; i < *len; i++)
    {
        count += que[i]->no_of_childs;
    }
    if (count == 0)
    {
        return NULL;
    }
    parsetree **newtree;
    newtree = malloc(sizeof(parsetree *) * count);
    for (int i = 0; i < *len; i++)
    {
        for (int j = 0; j < que[i]->no_of_childs; j++)
        {
            newtree[indcount + j] = que[i]->child[j];
        }
        indcount += que[i]->no_of_childs;
    }
    *len = count;
    return newtree;
}

void printparsetetree(parsetree *parse)
{
    printlen = malloc(sizeof(int));
    printf("%s \n", parse->node);
    finalprint = malloc(sizeof(parsetree *) * 1);
    finalprint[0] = parse;
    *printlen = 1;
    finalprint = putchildtoqueue(finalprint, printlen);
    while (finalprint != NULL)
    {
        printqueue(finalprint, printlen);
        finalprint = putchildtoqueue(finalprint, printlen);
    }
}

void generateast(parsetree **que, int *len)
{
    for (int j = 0; j < *len; j++)
    {
        //printf("node generated for %s\n",que[j]->node);
        astreenodegen(que[j]);
        populatefunctiontable(que[j]);
    }
    //printf("\n");
}

void populateast(parsetree *parse)
{
    functiontable = initialisefunctable();
    printlen = malloc(sizeof(int));
    //printf("%s   %d \n",parse->node,parse->rulenum);
    finalprint = malloc(sizeof(parsetree *) * 1);
    finalprint[0] = parse;
    *printlen = 1;
    generateast(finalprint,printlen);
    finalprint = putchildtoqueue(finalprint, printlen);
    while (finalprint != NULL)
    {
        generateast(finalprint, printlen);
        finalprint = putchildtoqueue(finalprint, printlen);
    }
    printf("done ast\n");
}

void intermediatetable(parsetree **que, int *len)
{
    for (int j = 0; j < *len; j++)
    {
        populatesymboltable(que[j]);
    }
}


void populatetables(parsetree *parse)
{
    
    printlen = malloc(sizeof(int));
    finalprint = malloc(sizeof(parsetree *) * 1);
    finalprint[0] = parse;
    *printlen = 1;
    finalprint = putchildtoqueue(finalprint, printlen);
    while (finalprint != NULL)
    {
        intermediatetable(finalprint, printlen);
        finalprint = putchildtoqueue(finalprint, printlen);
    }
    printf("done symbol tables\n");
}


void intermediatetableprint(parsetree **que, int *len)
{
    for (int j = 0; j < *len; j++)
    {
        if (strcmp(que[j]->node, "<moduleDef>") == 0)
        {
            printsymboltable(que[j]->child[1]->astaddr->symtab);
        }
        if (strcmp(que[j]->node, "<conditionalStmt>") == 0)
        {
            printsymboltable(que[j]->child[5]->astaddr->symtab);
        }
        if (strcmp(que[j]->node, "<iterativeStmt>") == 0 && strcmp(que[j]->child[0]->node, "FOR") == 0)
        {
            printsymboltable(que[j]->child[7]->astaddr->symtab);
        }
        if (strcmp(que[j]->node, "<iterativeStmt>") == 0 && strcmp(que[j]->child[0]->node, "WHILE") == 0)
        {
            printsymboltable(que[j]->child[5]->astaddr->symtab);
        }
    }
}

void printallsymboltables(parsetree *parse)
{
    printf("Printing Function table first \n\n");
    printfunctiontable(functiontable);
    printf("printing symbol tables\n");
    printlen = malloc(sizeof(int));
    printf("Variable_Name       Scope(Module Name)       Scope(line_numbers)     Width          isArray     Static_or_Dynamic       Range_lexemes       Type_of_element     Nesting_level \n");
    //printf("%s   %d \n",parse->node,parse->rulenum);
    finalprint = malloc(sizeof(parsetree *) * 1);
    finalprint[0] = parse;
    *printlen = 1;
    finalprint = putchildtoqueue(finalprint, printlen);
    while (finalprint != NULL)
    {
        intermediatetableprint(finalprint, printlen);
        finalprint = putchildtoqueue(finalprint, printlen);
    }
}
void initialisecount(){
    astnode_count=0;
    parsenode_count=0;
}
void printmemcount(){
   
    printf("No of parse nodes is : %d\n",parsenode_count);
    printf("Size of Parse Tree is : %ld Bytes\n",sizeof(parsetree)*parsenode_count);
    printf("\n\n");
    printf("No of AST nodes is : %d\n",astnode_count);
    printf("Size of Abstract Syntax Tree is : %ld Bytes\n",sizeof(astree)*astnode_count);
    printf("\n\n");
    long int new;
    long int parsemem;
    long int astmem;
    parsemem=sizeof(parsetree)*parsenode_count;
    astmem=sizeof(astree)*astnode_count;
    astmem=astmem/2;
    new=parsemem-astmem;
    double ratio;
    ratio=(double)new/parsemem;
    printf("Compression Ratio Achieved is %f",ratio);
    printf("\n\n");   

}
int gettotalsizeofsymtable(idsymboltable* table){
    symidentry* line;
    int size=0;
    for(int i=0;i<30;i++){
        line=table->head[i];
        //printf("assigned\n\n");
        if(line!=NULL){
            //printf("hi\n\n");
            while(line!=NULL){
                //printf("hi\n\n");
                if(line->isarray==0){
                    if(line->type==REAL)
                    size+=4;
                    if(line->type==INTEGER)
                    size+=2;
                    if(line->type==BOOLEAN)
                    size+=1;
                }
                if(line->isarray==true && line->dynamic==0){
                    if(line->type==REAL);
                    size+=4*(line->endindex-line->startindex);
                    if(line->type==INTEGER);
                    size+=2*(line->endindex-line->startindex);
                    if(line->type==BOOLEAN);
                    size+=1*(line->endindex-line->startindex);
                }
                
                line=line->next;
            }
            
        }
        else{
                //printf("line null\n\n");
               continue; 
            }
    }
    return size;
}
void printactivationrecord(){
    symfuncentry* line;
    //printf("hi\n");
    printf("\n\nPrinting Activation Records\n");
    printf("\n%-20s Size in Bytes\n","Function_Name");
    for(int i=0;i<30;i++){
        //printf("hi%d\n",i);
        line=functiontable[i];
        if(line!=NULL){
            //printf("Line not null\n");
            while(line!=NULL){
                //printf("%s line name\n\n",line->name);

                printf("%-20s  %d Bytes\n",line->name,gettotalsizeofsymtable(line->symtable));
                line=line->next;
            }
        }
    }
}

void intermediatetablearrayprint(parsetree **que, int *len)
{
    for (int j = 0; j < *len; j++)
    {
        if (strcmp(que[j]->node, "<moduleDef>") == 0)
        {
            printcustomsymboltable(que[j]->child[1]->astaddr->symtab);
        }
        if (strcmp(que[j]->node, "<conditionalStmt>") == 0)
        {
            printcustomsymboltable(que[j]->child[5]->astaddr->symtab);
        }
        if (strcmp(que[j]->node, "<iterativeStmt>") == 0 && strcmp(que[j]->child[0]->node, "FOR") == 0)
        {
            printcustomsymboltable(que[j]->child[7]->astaddr->symtab);
        }
        if (strcmp(que[j]->node, "<iterativeStmt>") == 0 && strcmp(que[j]->child[0]->node, "WHILE") == 0)
        {
            printcustomsymboltable(que[j]->child[5]->astaddr->symtab);
        }
    }
}

void customprint(parsetree* parsenode){
    //printf("hi\n");
    printlen = malloc(sizeof(int));
    printf("Variable_Name       Scope(Module Name)       Scope(line_numbers)     Width          isArray     Static_or_Dynamic       Range_lexemes       Type_of_element     Nesting_level \n");
    //printf("%s   %d \n",parse->node,parse->rulenum);
    finalprint = malloc(sizeof(parsetree *) * 1);
    finalprint[0] = parsenode;
    *printlen = 1;
    finalprint = putchildtoqueue(finalprint, printlen);
    while (finalprint != NULL)
    {
        intermediatetablearrayprint(finalprint, printlen);
        finalprint = putchildtoqueue(finalprint, printlen);
    }
}
