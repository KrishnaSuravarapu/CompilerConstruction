// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include<stdbool.h>

typedef struct sym
{
    char name[30];
    int type;
    bool isarray;
    int dynamic;
    struct sym *indexid[2];
    int offset;
    struct sym *next;
    int startindex;
    int endindex;
    bool assigned;
    bool active;
    //char namechanged[30];
    
    // used in code generation//
    int *NUM;
    float *RNUM;
    bool *BOOLEAN;


} symidentry;

typedef struct symbolarray
{
    symidentry **head;
    struct symbolarray *nestedparent;
    int nestinglevel;
    int startline;
    int endline;
    char modulename[30];
} idsymboltable;

typedef struct sym2
{
    char name[30];
    symidentry **outputparam;
    symidentry **inputparam;
    int input_no;
    int output_no;
    idsymboltable* symtable;
    struct sym2 *next;

} symfuncentry;


typedef struct ast
{
    char label[30];
    struct ast *childhead;
    struct ast *sibling;
    struct ast *parent;
    char lexval[30];
    bool isarray;
    idsymboltable *symtab;
    int type;
    bool booleanvalue;
    char start[10];
    char end[10];
    char namechanged[30];
    ///////////////used in IR    

    symidentry* symboltabpointer;
    char next[20];
    char* True;
    char* False;
    char* inh;
    char* syn;
    char* addr;
    char labelname[20];
    char* intermediatecode;
    // char datatype[30];
    // char id[30];

} astree;

symfuncentry **functiontable;
idsymboltable *symbotable;
int astnode_count;