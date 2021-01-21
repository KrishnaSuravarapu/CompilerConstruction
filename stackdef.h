// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include "stack.h"

bool syn = false;
parsetree *recentlypopped;
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


stack *match(stack *stac, set* tokset, stringlist **ParseTable)
{
    char* new=tokset->token;
    char *top;
    int t = getindex(new, TERMINALS) - 1;
    
    while (strcmp(getstacktop(stac), "e") == 0)
    {
        stac = pop(stac);
    }
    top = getstacktop(stac);
    int nt = getindex(top, NONTERMINALS) - 1;
    while (nt != -1 && strcmp(getstacktop(stac), "syn") != 0)
    {
        //printf("stack top is %s",getstacktop(stac));
        //printstack(stac);

        if (strcmp(ParseTable[nt][t].str[0], "syn") != 0)
        {
            // printf("stoppedhere1");
            int ruleno;
            recentlypopped = stac->parse;
            //printf("here to be popped is rule no . %d\n",getruleno(Rules,NONTERMINALS.str[nt],ParseTable[nt][t]));
            ruleno=getruleno(Rules,NONTERMINALS.str[nt],ParseTable[nt][t]);
            stac = popwithrule(stac,ruleno);

            stac = push(stac, ParseTable[nt][t], recentlypopped);
        }
        else if (strcmp(ParseTable[nt][t].str[0], "syn") == 0)
        {
            //printf("In Syn bruh\n\n");
            // printf("stoppedhere2");
            syn = true;
            return stac;
        }
        else
        {
            //printf("error encountered\n");
            return stac;
        }
        while (strcmp(getstacktop(stac), "e") == 0)
        {
            //printf("is here mate");
            // printf("stoppedhere3");
            //printstack(stac);
            stac = pop(stac);
        }
        if (isempty(stac))
        {
             //printf("stoppedhere4\n");
            return stac;
        }
        top = getstacktop(stac);
        nt = getindex(top, NONTERMINALS) - 1;
    }

    while (strcmp(getstacktop(stac), "e") == 0)
    {
        // printstack(stac);
        stac = pop(stac);
    }

    if (strcmp(getstacktop(stac), new) == 0 && !(isempty(stac)))
    {
        // printstack(stac);
        strcpy(stac->parse->value,tokset->lexeme);
        stac->parse->linenum=*line2ptr;
        //printf("Terminal is %s line no. is %d \n",stac->str,stac->parse->linenum);
       //printf("lexeme is %s \n",tokset->lexeme);
        stac = pop(stac);
        return stac;
    }
    else if (strcmp(getstacktop(stac), new) != 0 && getindex(getstacktop(stac), TERMINALS) != 0)
    {
       // printf("ERROR RECOVERY TERMINALS POPPED\n");
        stac->parse->linenum=*line2ptr;
        //printf("11111   Terminal is %s line no. is %d \n",stac->str,stac->parse->linenum);
        stac = pop(stac);
        return stac;
    }
    else{
       stac = pop(stac);
        return stac;
    }
}


parsetree* getparsetree(char* FP)
{
    
    parsetree *parsetreel;
    stack *stack1;
    line2ptr=malloc(sizeof(int));
    *line2ptr=0;
    // *lineptr=0;
    int linenum;
    stack1 = pushdollar(stack1);
    parsetreel = initialise("<program>");
    stack1 = pushstartsymbol(stack1, "<program>");
    stack1->parse = parsetreel;
    ParseTable = parseTable();
    FILE *fp = fopen(FP, "r");
    set * news;
    news=NULL;
    news = getonetoken(fp);
    while (!feof(fp))
    {
        if(news!=NULL){
        if (syn == false)
        {
           //printf("\nINPUT :- %s\n", news->lexeme);
            //printstack(stack1);
            //printf("hi\n");
            stack1 = match(stack1, news, ParseTable);
            //printf("line number is %d\n\n",*line2ptr);
        }
        if (syn == true)
        {
            //printf("line number is %d\n\n",*lineptr);
            //printf("\nhi1\n");
            int synindex = getindex(getstacktop(stack1), NONTERMINALS) - 1;
            //printf("hi2\n");
            //printf("check here is %s for index %d \n", new, synindex);

            //printf("[ERROR RECOVERY] stack before popping\n");
            //printstack(stack1);
            stack1 = pop(stack1);
            //printf("[ERROR RECOVERY] stack after popping\n");
            //printstack(stack1);
            //printf("\n [ERROR RECOVERY] now terminal to be matched is %s\n", new);
            syn = false;
            //printf("hi1");
            stack1 = match(stack1, news, ParseTable);
            //printf("Syn came for this nt %s \n",getstacktop(stack1));
        }
        
        }
        news=getonetoken(fp);
    }
    //printstack(stack1);
    if (feof(fp))
    {
        //this is to be matched coz some might give rule a->e if ip symbol is $//
        //printf("came here\n");
        char *inpdoll;
        inpdoll = malloc(sizeof(char) * 2);
        strcpy(inpdoll, "$");
        set* doll;
        doll=malloc(sizeof(set));
        doll->token=malloc(sizeof(char)*5);
        strcpy(doll->token,inpdoll);
        //printf("came here at last\n");
        stack1 = match(stack1, doll, ParseTable);
    }
    if (isempty(stack1) && feof(fp))
    {
        printf("successful parsing\n");
    }
    
    fclose(fp);
    return parsetreel;
}