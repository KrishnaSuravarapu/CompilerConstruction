// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define NTS 40
#define TMAX 60
#define NTMAX 60

typedef struct stringlist{
    char** str;
    int count;
}stringlist;


typedef struct rule{
    stringlist rule;
    int id;
}rule;


typedef struct grammarentry
{
    char nonterminal[NTS];
    stringlist* rule;
    int rulecount;
}grammarentry;

typedef struct grammar{
    grammarentry* entry;
    int ntc;
}grammar;


typedef struct firstandfollowentry{
    char nonterminal[NTS];
    stringlist firstset;
    stringlist followset;
    stringlist* rulefirst;
    int rulecount;
    bool first;
    bool follow;
}firstandfollowentry;

bool GrammarFile(grammar* ,char* );
bool populateGrammar(grammar*,char*);
void printGrammar(grammar);
 
bool computeFirstAndFollow(grammar,firstandfollowentry*);
bool first(grammar,grammarentry,firstandfollowentry*);
bool follow(grammar,char*,firstandfollowentry*);
void printFirstAndFollow(firstandfollowentry*);
 
stringlist** parseTable();
// void computeParseTable(firstandfollowentry*,grammar,parseentry**);
 
void printStringList(stringlist );
int getindex(char*,stringlist );
bool addStringList(stringlist ,stringlist* );
bool addStringSet(stringlist ,stringlist* );
bool addString(char* ,stringlist* );
int addToSet(char*,stringlist* );
bool initializeStringlist(stringlist*);
int getruleno(rule* Rule,char* s1,stringlist s2);

