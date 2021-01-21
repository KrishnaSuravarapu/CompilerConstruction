// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include"stack.h"

stack *push(stack *stac, stringlist strlist,parsetree* parent)
{
    //printf("parsetree parent is %s\n",parent->node);
    //printf("to be pushed :");
    //printStringList(strlist);
    //printf("\n\n\n");
    stack *new;
    new = malloc(sizeof(stack));
    new->str = malloc(sizeof(char) * 50);
    new->next = NULL;
    new->parse=NULL;
    strcpy(new->str, strlist.str[0]);
    new->parse=initialise(new->str);
    new->parse->parent=parent;
    if(parent!=NULL){
    parent->no_of_childs=strlist.count;
    parent->child=malloc(sizeof(parsetree*)*parent->no_of_childs);
    parent->child[0]=new->parse;
    }
    int i = 1;
    stack *change;
    change = new;
    while (i < strlist.count)
    {
        change->next = malloc(sizeof(stack));
        change = change->next;
        change->str = malloc(sizeof(char) * 50);
        change->next = NULL;
        change->parse=NULL;
        strcpy(change->str, strlist.str[i]);
        change->parse=initialise(change->str);
        change->parse->parent=parent;
        if(parent!=NULL){
        parent->child[i]=change->parse;
        }
        i++;
    }
   
    change->next = stac;
    return new;
}

stack* pop(stack *stac)
{
    stac->parse->rulenum=-1;
    stac = stac->next;
    return stac;
}

stack* popwithrule(stack *stac,int ruleno)
{
    stac->parse->rulenum=ruleno;
    stac = stac->next;
    return stac;
}

bool isempty(stack* stac)
{
    if(strcmp(stac->str,"$")==0){
        return true;
    }
    return false;
}

char *getstacktop(stack* stac)
{
    char *top;
    top = malloc(sizeof(char) * 50);
    strcpy(top, stac->str);
    return top;
}
stack* pushdollar(stack* stac){
    stringlist doll;
    doll.count=1;
    doll.str=malloc(sizeof(char*)*1);
    doll.str[0]=malloc(sizeof(char)*2);
    strcpy(doll.str[0],"$");
    stac=push(stac,doll,NULL);
    return stac;
}

stack* pushstartsymbol(stack * stac,char* startsymbol){
    stringlist doll;
    doll.count=1;
    doll.str=malloc(sizeof(char*)*1);
    doll.str[0]=malloc(sizeof(char)*50);
    strcpy(doll.str[0],startsymbol);
    stac=push(stac,doll,NULL);
    return stac;

}
void printstack(stack* stac){
    stack* copy;
    copy=stac;
    printf("\n\nstackstart  ----");
    while(!(isempty(copy))){
        printf("%s   ",copy->str);
        copy=copy->next;
    }
    printf("--------stackend\n\n");
}