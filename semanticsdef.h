// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
int expr_type(astree* ,idsymboltable*);
int arth_type(astree* ,idsymboltable*);
bool semantics(astree* );
bool checkModule_def(astree* );
bool checkStmts(astree*);
bool checkID(astree* ,idsymboltable* );
bool check_var_id(astree*,idsymboltable*);