// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include<stdio.h>
#include<stdlib.h>
//#include"astdef.h"
char* newtemp();
char* genname();
void astpostordertraverse(astree* astnode);
void printintermediatecode(astree* astnode);
void printfunctionlabel(astree* astnode);
char* genint();
char* genreal();
char* genbool();