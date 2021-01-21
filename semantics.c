// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include"semantics.h"
bool semantics(astree* ast){
	bool error=true;
	astree *module_dec=ast->childhead;
	astree* modules=module_dec->sibling->childhead;//reaching modules from othermodules
	//printf("In the semantics and checking ast\n");
	while(modules!=NULL){
		astree* module_def=modules->childhead->sibling->sibling->sibling;
		//printf("checking for %s\n",module_def->label);
		bool temp=checkModule_def(module_def);
		//printf("In the semantics and checked module_def\n");
		if(!temp){
			error=false;
		}
		modules=modules->sibling;
	}
	astree* driver=module_dec->sibling->sibling;
	astree* module_def=driver->childhead;
	//printf("checking for %s\n",module_def->label);
	bool temp=checkModule_def(module_def);
		//printf("In the semantics and checked module_def\n");
	if(!temp){
		error=false;
	}
	modules=module_dec->sibling->sibling->sibling->childhead;//reaching modules from othermodules
	do{
		astree* module_def=modules->childhead->sibling->sibling->sibling;
		bool temp=checkModule_def(module_def);
		if(!temp){
			error=false;
		}
		modules=modules->sibling;
	}while(modules!=NULL);
	return error;
}
bool checkModule_def(astree* module_def){
	astree* stmts=module_def->childhead;
	//printf("Checking semantics for statements\n");
	// if(strcmp(module_def->parent->label,"<module>")==0){
	// astree*inputlist=module_def->parent->childhead->sibling;
	// //printf("At %s\n\n",module_def->parent->childhead->sibling->sibling->label);
	// astree*outputlist;
	// if(module_def->parent->childhead->sibling->sibling->childhead!=NULL){
	// outputlist=module_def->parent->childhead->sibling->sibling->childhead;
	// checkID(outputlist->childhead,outputlist->childhead->symtab);
	// }
	// checkID(inputlist->childhead,inputlist->childhead->symtab);
	
	// }
	return checkStmts(stmts);
}
bool checkStmts(astree *stmts){
	idsymboltable* symtab=stmts->symtab;
	astree* stmt=stmts->childhead;
	if(stmt==NULL)return true;
	bool result=true;
	//printf("checking semantics for each statement in statements\n");
	while(stmt!=NULL){
		astree* stmt_type=stmt->childhead;
		//printf("\tSeeing which kind of stmt: %s\n",stmt_type->label);
		if(strcmp(stmt_type->label,"<declareStmt>")==0){
			astree* idlist=stmt_type->childhead->childhead;
			while(idlist){
				symidentry* entry=getinfoofsymbol(symtab,idlist->lexval);
				entry->active=true;
				idlist=idlist->sibling;
			}
			stmt=stmt->sibling;
			continue;
		}
		else if(strcmp(stmt_type->label,"<ioStmt>")==0){
			astree* io_stmt=stmt_type->childhead;
			if(strcmp(io_stmt->label,"GET_VALUE")==0){
				astree* id=io_stmt->sibling;
				if(!checkID(id,symtab))result=false;
			}
			else if(strcmp(io_stmt->label,"PRINT")==0){
				astree* var_type=io_stmt->sibling->childhead;
				if(strcmp(var_type->label,"<var_id_num>")==0){
					if(!check_var_id(var_type,symtab)){
						result=false;
					}
				}
			}
		}
		else if(strcmp(stmt_type->label,"<simpleStmt>")==0){
			if(strcmp(stmt_type->childhead->label,"<assignmentStmt>")==0){
				//printf("\t\t in Assignment Statement\n");
				astree* assgn_stmt=stmt_type->childhead;
				astree* id=assgn_stmt->childhead;
				astree* which=id->sibling;
				int type=id->type;
				if(!checkID(id,symtab))result=false;
				else if(strcmp("<expression>",which->label)==0){
					if(expr_type(which,symtab)!=type)result= false;
					//printf("\t\texpression type is %d\n",type);
				}				 
			}
			else if(strcmp(stmt_type->childhead->label,"<moduleReuseStmt>")==0){
				astree* mod_stmt=stmt_type->childhead;
				symfuncentry* func;
				astree* idlist;
					func=getinfooffunction(functiontable,mod_stmt->childhead->sibling->lexval);
					idlist=mod_stmt->childhead->childhead;
					if(func==NULL){
						printf("ERROR -- Invalid function %s\n",mod_stmt->childhead->lexval);
						result=false;
						stmt=stmt->sibling;
						continue;
					}
					int i=0;
					while(idlist!=NULL){
						if(checkID(idlist,symtab)){
							symidentry* id=getinfoofsymbol(symtab,idlist->lexval);
							if(i>=func->output_no){
								printf("ERROR -- Output parameters do not match\n");
								result=false;
								continue;
							}
							if(func->outputparam[i]->type!=id->type||func->outputparam[i]->isarray!=id->isarray){
								result=false;
								idlist=idlist->sibling;
								i++;
								continue;
							}
							id->assigned=true;
						}
						else{
							printf("ERROR -- Invalid output to the function %s\n",func->name);
							result=false;
						}
						i++;
						idlist=idlist->sibling;
					}
					if(i<func->output_no){
						printf("ERROR -- Output parameters for function %s are less than expected\n",func->name);
						result=false;
					}
					idlist=mod_stmt->childhead->sibling->sibling->childhead;
				// else{
				// 	//printf("\t\t\t%s\n",mod_stmt->childhead->lexval);
				// 	char newname[30];
				// 	if(strcmp(mod_stmt->childhead->label,"<optional>")==0){
				// 		strcpy(newname,mod_stmt->childhead->sibling->lexval);
				// 		idlist=mod_stmt->childhead->sibling->sibling->childhead;
				// 	}
				// 	else{
				// 		strcpy(newname,mod_stmt->childhead->lexval);
				// 		idlist=mod_stmt->childhead->sibling->childhead;
				// 	}
				// 	func=getinfooffunction(functiontable,newname);
					

				// 	if(func==NULL){
				// 		printf("ERROR -- Invalid function %s\n",newname);
				// 		result=false;
				// 		stmt=stmt->sibling;
				// 		continue;
				// 	}
				// }
				//printf("\t\t in Module Reuse Statement for module %s\n",mod_stmt->childhead->lexval);
				i=0;
				while(idlist!=NULL){
					if(checkID(idlist,symtab)){
						symidentry* id=getinfoofsymbol(symtab,idlist->lexval);
						//printf("\t\t\t%s:%d\n",id->name,id->type);
						if(i>=func->input_no){
							printf("ERROR -- Too many entries\n");
							result=false;
							break;
						}
						if(func->inputparam[i]->type!=id->type||func->inputparam[i]->isarray!=id->isarray){
							printf("ERROR -- Invalid input %s to the function %s\n",idlist->lexval,func->name);
							result=false;
						}
						//printf("\t\t\tchecked\n");
					}
					else{
						printf("ERROR -- Invalid input %s to the function %s\n",idlist->lexval,func->name);
						result=false;
					}
					i++;
					idlist=idlist->sibling;
				}
				if(i<func->input_no){
					printf("ERROR -- Input parameters for function %s are lesser than expected \n",func->name);
					result=false;
				}
			}
		}
		else if(strcmp(stmt_type->label,"<iterativeStmt>")){
			if(strcmp(stmt_type->childhead->label,"WHILE")){
				int type;
				astree* expr=stmt_type->childhead->sibling;
				if(strcmp("<arithmeticOrBooleanExpr>",expr->childhead->label)==0){
					astree* anyterm=expr->childhead;
					bool first=true;
					do{
						astree* arth_expr=anyterm->childhead;
						do{
							int temp=arth_type(arth_expr,symtab);
							//printf("\t\texpression type is %d\n",temp);
							if(first)type=temp;
							else{
								if(temp!=type)type=ERROR;
							}
							if(arth_expr->sibling==NULL)break;
							arth_expr=arth_expr->sibling->sibling;
						}while(arth_expr==NULL);
						anyterm=anyterm->sibling;
					}while(anyterm==NULL);
				}
				astree* stmts=expr->sibling;
				if(!checkStmts(stmts)){
					result=false;
				}
			}
			else{
				astree* id = stmt->childhead->sibling;
				astree* stmts=id->sibling->sibling;
				if(!checkID(id,symtab)||!checkStmts(stmts)){
					result=false;
				}
			}
		}
		else if(strcmp(stmt_type->label,"<switchStmt>")==0||strcmp(stmt_type->label,"<conditionalStmt>")==0){
			astree* cond_stmt=stmt_type;
			if(strcmp(stmt_type->label,"<switchStmt>")==0){
				cond_stmt=stmt_type->childhead;
			}
			if(checkID(cond_stmt->childhead,symtab)){
				if(cond_stmt->childhead->type!=INTEGER||cond_stmt->childhead->isarray){
					result=false;
				}else{
					astree* case_stmts=cond_stmt->childhead->sibling;
					astree* def_stmt=cond_stmt->sibling;
					idsymboltable* symtab=case_stmts->symtab;
					astree* stmts=cond_stmt->childhead->sibling;
					while(stmts!=NULL){
						stmts->symtab=symtab;
						if(!checkStmts(stmts))result=false;
						if(stmts->sibling==NULL)break;
						stmts=stmts->sibling->sibling;
					}
					if(def_stmt->childhead!=NULL){
						stmts=def_stmt->childhead;
						stmts->symtab=symtab;
						if(!checkStmts(stmts))result=false;							
					}
				}
			}
			else{
				printf("ERROR -- Invalid id %s in switch statement\n",cond_stmt->childhead->lexval);
				result=false;
			}
		}
		stmt=stmt->sibling;
	}
	//printf("Checking semantics for each statement complete\n");
	return result;
}
int arth_type(astree* arth_expr,idsymboltable* symtab){
	astree* term=arth_expr->childhead;
	int type=0;
	bool first=true;
	do{
		astree* factor=term->childhead;
		do{
			if(strcmp("<arithmeticExpr>",factor->childhead->label)==0){
				int type_temp=arth_type(factor->childhead,symtab);
				if(first)type=type_temp;
				else{
					if(type_temp!=type){
						type=ERROR;
					}
				}
			}
			else{
				int temp;
				temp=check_var_id(factor->childhead,symtab);
				if(temp){
					if(strcmp("ID",factor->childhead->childhead->label)==0){						
						symidentry* entry=getinfoofsymbol(symtab,factor->childhead->childhead->lexval);
						int type_temp=entry->type;
						if(first)type=type_temp;
						else{
							if(type!=type_temp){
								printf("ERROR -- Inconsistent types by %s\n",factor->childhead->childhead->lexval);
								type=ERROR;
							}
						}
					}
					else{
						int type_temp=factor->childhead->childhead->type;
						if(first)type=type_temp;
						else{
							if(type!=type_temp){
								printf("ERROR -- Inconsistent types by %s\n",factor->childhead->childhead->lexval);
								type=ERROR;
							}
						}
					}
				}
				else type=ERROR;
			}
			if(factor->sibling==NULL)break;
			factor=factor->sibling->sibling;
		}while(factor!=NULL);
		if(term->sibling==NULL)break;
		term=term->sibling->sibling;
	}while(term==NULL);
	return type;
}
int expr_type(astree* expr,idsymboltable* symtab){
	int type;
	if(strcmp("<arithmeticOrBooleanExpr>",expr->childhead->label)==0){
		astree* anyterm=expr->childhead;
		bool error=false;
		bool first=true;
		do{
			astree* arth_expr=anyterm->childhead;
			do{
				int temp=arth_type(arth_expr,symtab);
				if(first)type=temp;
				else{
					if(temp!=type)type=ERROR;
				}
				if(arth_expr->sibling==NULL)break;
				arth_expr=arth_expr->sibling->sibling;
			}while(arth_expr==NULL);
			anyterm=anyterm->sibling;
		}while(anyterm==NULL);
	}
	else if(strcmp("<U>",expr->childhead->label)==0){
		astree* new=expr->childhead->sibling->sibling;
		if(strcmp("<arithmeticExpr>",new->childhead->label)){
			type=arth_type(new->childhead,symtab);
		}
		else{
			if(check_var_id(new->childhead,symtab)){
				type=new->childhead->childhead->type;
			}
			else{
				type=ERROR;
			}
		}
	}
	return type;
}
bool checkID(astree* id,idsymboltable* symtab){
	//printf("Checking semantics for %s\n",id->lexval);
	symidentry *entry=getinfoofsymbol(symtab,id->lexval);
	if(entry==NULL){
		printf("ERROR --\t%s is not available in the scope\n",id->lexval);
		return false;
	}
	if(!(entry->active)){
		printf("ERROR --\t%s is not declared yet.\n",id->lexval);
		return false;
	}
	// if(!entry->assigned){
	// 	printf("\t%s is not assigned any value\n",id->lexval);
	// 	return false;
	// }
	if(entry->isarray)
	{
		if(strcmp("<index>",id->sibling->label)==0){
			astree* index=id->sibling;
			if(strcmp("ID",index->childhead->label)==0){
				symidentry *entry=getinfoofsymbol(symtab,index->childhead->lexval);
				if(entry==NULL){
					printf("ERROR --\tInvalid ID %s as index to Arrary %s\n",entry->name,id->lexval);
					return false;
				}
				else if(entry->isarray){
					printf("ERROR --\tArrary element %s written as an input for array %s",entry->name,id->lexval);
					return false;
				}
				else if(entry->type!=INTEGER){
					printf("ERROR --\tInvalid id %s as input for array %s",entry->name,id->lexval);
					return false;
				}
				else{
					return checkID(index->childhead,symtab);
				}
			}
			else if(entry->dynamic==0){
				astree* num=index->childhead;
				int index=atoi(num->lexval);
				if(index>entry->endindex||index<entry->startindex){
					return false;
				}
			}
		}
	}
	return true;
}
bool check_var_id(astree* var_id,idsymboltable* symtab){
	astree *id=var_id->childhead;
	astree *index=id->sibling;
	//printf("checking for semantics for var_id_num\n");
	if(strcmp("ID",id->label)==0){
		return checkID(id,symtab);
	}
	//printf("checking for semantics for var_id_num complete\n");
	return true;
}

// int main(){
// 	printf("Here\n\n");
//     parsetree* new;
//     new=getparsetree();
//     populateast(new);
//     // printast(ast);
//     populatetables(new);
//     printfunctiontable(functiontable);
//     if(semantics(ast)){
//     	printf("Semantic check complete.\n");
//     }
//     else{
//     	printf("Errors in Semantic check .\n");
//     }
// }
// typedef struct sym
// {
//     char name[30];
//     int type;
//     bool isarray;
//     int dynamic;
//     struct sym *indexid[2];
//     int offset;
//     struct sym *next;
//     // used in code generation//
//     int startindex;
//     int endindex;
//     bool assigned;
//     int *NUM;
//     float *RNUM;
//     bool *BOOLEAN;

// } symidentry;

// typedef struct sym2
// {
//     char name[30];
//     symidentry **outputparam;
//     symidentry **inputparam;
//     int input_no;
//     int output_no;
//     struct sym2 *next;

// } symfuncentry;

// typedef struct symbolarray
// {
//     symidentry **head;
//     struct symbolarray *nestedparent;
// } idsymboltable;


// typedef struct ast
// {
//     char label[30];
//     struct ast *childhead;
//     struct ast *sibling;
//     struct ast *parent;
//     char lexval[30];
//     bool isarray;
//     idsymboltable *symtab;
//     int type;
//     bool booleanvalue;
//     char start[30];
//     char end[30];
//     // char datatype[30];
//     // char id[30];

// } astree;
// semantics.c
// Displaying semantics.c.