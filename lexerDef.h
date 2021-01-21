// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct tokenlex{
    char* token;
    char* lexeme;
    bool isemoty;
};
struct tableel{
	struct tokenlex* tokenlex;
	struct tableel *next;
};
int *line2ptr;
FILE* getStream(FILE* fp);
int hashFunction(char* S);
struct tokenlex* storekeywords(struct tableel*head , char* token , char*lexeme);
struct tokenlex* installID(struct tableel*head , struct tokenlex *token);
struct tableel* symboltable;
struct tokenlex* getNextToken(char* ch);
void initialize(struct tableel* symboltable);
void removecomments(FILE* fp2);
void removecomment(FILE* fp2);
void tokenise(FILE* fp);
typedef struct tokenlex set;
set* getonetoken(FILE* fp);

