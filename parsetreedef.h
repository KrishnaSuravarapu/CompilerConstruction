// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
typedef struct parsetree{
astree* astaddr;
char node[30];
struct parsetree ** child;
struct parsetree * parent;
char value[30];
int linenum;
int rulenum;
int no_of_childs;
}parsetree;

parsetree* getparsetree();