// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include"parser.h"
 
#define SIZE 100
 
bool GrammarFile(grammar* gtable,char* fname){
    char buffer[SIZE]={'\0'};
    FILE *fp=fopen(fname,"r");
    if(fp==NULL){
        perror("Error in opening the file.\n");
        return false;
    }
    while(!feof(fp)){
        fgets(buffer,SIZE,fp);
        int n=strlen(buffer)-1;
        while(buffer[n]=='\n'||buffer[n]==' '||buffer[n]=='\t')buffer[n--]='\0';
        populateGrammar(gtable,buffer);
    }
    return true;
}
 
bool populateGrammar(grammar* GrammarTable,char* rule){
    int firstnotadded=1;
    int index;
    for(int i=0;i<strlen(rule);i++){
        while(rule[i]==' '){
            i++;
        }
        if(firstnotadded){
            int start=i;
            while(rule[i]!='>'){
                i++;
            }
            char nonterminal[NTS]={"\0"};
            strncpy(nonterminal,rule+start,i-start+1);
            index=getindex(nonterminal,NONTERMINALS)-1;
            if(index+1==0){
                if(addToSet(nonterminal,&NONTERMINALS)==1){
                    GrammarTable->entry=realloc(GrammarTable->entry,sizeof(grammarentry)*(GrammarTable->ntc+1));
                    index=GrammarTable->ntc;
                    strcpy(GrammarTable->entry[index].nonterminal,nonterminal);
                    GrammarTable->entry[index].rulecount=0;
                    GrammarTable->entry[index].rule=malloc(sizeof(stringlist));
                    GrammarTable->entry[index].rule[0].count=0;
                    GrammarTable->ntc++;
                }
            }
            else{
                    GrammarTable->entry[index].rule=realloc(GrammarTable->entry[index].rule,sizeof(stringlist)*(GrammarTable->entry[index].rulecount+1));
                    GrammarTable->entry[index].rule[GrammarTable->entry[index].rulecount].count=0;
            }
            firstnotadded=0;
            continue;
        }
        if(rule[i]=='<'){
            int start=i;
            while(rule[i]!='>'&&rule[i]!='\0'){
                i++;
            }
            char nonterminal[NTS];
            memset(nonterminal,0,NTS);
            strncpy(nonterminal,rule+start,i-start+1);
            int i=0;
            while(i<NTS){
                if(nonterminal[i]=='>'){
                    nonterminal[i+1]=0;
                    break;
                }
                i++;
            }
            //printf("Nonterminal is %s\n",nonterminal);
            // addToSet(nonterminal,&NONTERMINALS);
            
            addString(nonterminal,&GrammarTable->entry[index].rule[GrammarTable->entry[index].rulecount]);
        }
        else{
            int start=i;
            while(rule[i]!=' '&&rule[i]!='<'&&rule[i]!='\0'){
                i++;
            }
            char terminal[NTS];
            memset(terminal,0,NTS);
            strncpy(terminal,rule+start,i-start);
            if(strcmp(terminal,"z")<=0 && strcmp(terminal,"A")>=0 )
            {
            for(int i=0;i<NTS;i++){
                if(terminal[i]==0){
                    break;
                }
                else if(terminal[i]>='A' && terminal[i]<='z')
                {
                    continue;
                }
                else{
                    terminal[i]=0;
                }
            }
            addToSet(terminal,&TERMINALS);
            }
            i--;
            if(terminal[0]<='z' && terminal[0]>='A' ){
            //printf("terminal is %s\n",terminal);
            
            addString(terminal,&GrammarTable->entry[index].rule[GrammarTable->entry[index].rulecount]);
            }
            
        }
    }
    GrammarTable->entry[index].rulecount++;
    return true;
}
void printGrammar(grammar GrammarTable){
    int n=0;
    for(int i=0;i<GrammarTable.ntc;i++){
        for(int j=0;j<GrammarTable.entry[i].rulecount;j++){
            printf("%d. %s->",++n,GrammarTable.entry[i].nonterminal);
            //printf("RHS count is %d",GrammarTable.entry[i].rule[j].count);
            printStringList(GrammarTable.entry[i].rule[j]);
        }
    }
}
int getruleno(rule* Rule,char* s1,stringlist s2){
    int i;
    int k;
    int j;
    //printf("char to be matched is %s\n",s1);
    for(i=0;i<NR;i++){
        if(strcmp(Rule[i].rule.str[0],s1)==0){
            break;
        }
    }
    //printf("To check from %d and length is %d\n",i,s2.count);
    //printStringList(s2);
    //printf("\n\n\n");
    for(j=i;j<NR;j++){
        
        if(Rule[j].rule.count-1==s2.count){
            //printStringList(Rule[j].rule);
            //printf("checking for rule %d\n",j);
            for(k=0;k<s2.count;k++){
                if(strcmp(Rule[j].rule.str[k+1],s2.str[k])==0){
                    //printf("\n\n%s is to be matched with %s \n\n",Rule[j].rule.str[k+1],s2.str[k]);
                    continue;
                }
                else{
                    break;
                }
            }
            if(k==s2.count){
                //printf("yell yeah successful\n");
                return j+1;
            }
        }
    }
    return -1;
}
 
 
bool first(grammar gtable,grammarentry gentry,firstandfollowentry* table){
    int index=getindex(gentry.nonterminal,NONTERMINALS)-1;
    if(index+1==0){
        printf("Invalid grammar rule for %s!!\n",gentry.nonterminal);
        return false;
    }
    if(table[index].first==true){
        // printf("First set already computed\n");
        return true;
    }
    strcpy(table[index].nonterminal,gentry.nonterminal);
    table[index].firstset.count=0;
    table[index].followset.count=0;
    table[index].rulecount=gentry.rulecount;
    table[index].rulefirst=malloc(sizeof(stringlist)*gentry.rulecount);
    for(int i=0;i<gentry.rulecount;i++){
        table[index].rulefirst[i].count=0;
        int nextindex=0;
        int hase=0;
        int j=0;
        do{
            hase=0;
            // printf("Computing for %s for rule %d , %d th time.\n",table[index].nonterminal,i,j+1);
            if(gentry.rule[i].str[j][0]=='<'){
                nextindex=getindex(gentry.rule[i].str[j],NONTERMINALS)-1;
                if(!table[nextindex].first){
                    // printf("Asked to compute for %s for rule %d during %d th time.\n",gtable.entry[nextindex].nonterminal,i,j+1);
                    if(!first(gtable,gtable.entry[nextindex],table)){
                        printf("Error in the computing of %s.\n",table[nextindex].nonterminal);
                    }
                }
                hase=getindex("e",table[nextindex].firstset);
                for(int k=0;k<table[nextindex].firstset.count;k++){
                    if(strcmp(table[nextindex].firstset.str[k],"e")!=0)
                        addToSet(table[nextindex].firstset.str[k],&table[index].rulefirst[i]);
                }
            }
            else{
                addToSet(gentry.rule[i].str[j],&table[index].rulefirst[i]);
                // printf("\tterminal Added to set\n");
                j++;
                break;
            }
            j++;
        }while(hase!=0 && j<gentry.rule[i].count);
        for(int k=0;k<table[index].rulefirst[i].count;k++){
            addToSet(table[index].rulefirst[i].str[k],&table[index].firstset);
        }
    }
    // printStringList(table[index].firstset);
    // printf("Computing finished for %s\n",NONTERMINALS.str[index] );
    table[index].first=true;
    return true;
}
 
bool follow(grammar gtable,char* nonterminal,firstandfollowentry* table){
    int index=getindex(nonterminal,NONTERMINALS)-1;
    // printf("Computing for %s\n",nonterminal);
    if(table[index].follow){
        // printf("Already Computed\n");
        return true;
    }
    table[index].followset.count==0;
    table[index].followset.str=malloc(sizeof(char)*NTS);
    for(int k=0;k<gtable.ntc;k++){
        int rulecount=gtable.entry[k].rulecount;
        grammarentry gentry=gtable.entry[k];
        for (int i = 0; i < rulecount; ++i)
        {
            int a;
            for (a = 0;  a< gentry.rule[i].count; ++a){
                if(strcmp(nonterminal,gentry.rule[i].str[a])==0){
                    int index2=a;
                    int j=1,hase=0;
                    do{
                        // printf(" str-%d  ",j);
                        hase=0;
                        if(index2!=-1){
                            if(index2+j<gentry.rule[i].count){
                                if(gentry.rule[i].str[index2+j][0]=='<'){
                                    int index3=getindex(gentry.rule[i].str[index2+j],NONTERMINALS)-1;
                                    // printf("Adding the firstset of %s",gentry.rule[i].str[index2+j]);
                                    // printStringList(table[index3].firstset);
                                    for (int i2=0; i2 < table[index3].firstset.count; ++i2){
                                        if(table[index3].firstset.str[i2][0]=='e'){
                                            // printf("%s has e\n",NONTERMINALS.str[index3]);
                                            hase=1;
                                        }
                                        else{
                                           addToSet(table[index3].firstset.str[i2],&table[index].followset);
                                        }
                                    }
                                    // printf("Set added\n");
                                }
                                else{
                                    // printf("Here in the terminal addition\n");
                                    addToSet(gentry.rule[i].str[index2+j],&table[index].followset);
                                    break;
                                }
                            }
                            else{
                                int index3=getindex(gentry.nonterminal,NONTERMINALS)-1;
                                if(index==index3)break;
                                if(!follow(gtable,gentry.nonterminal,table)){
                                    // printf("Error in calculating the follow\n");
                                    return false;
                                }
                                addStringSet(table[index3].followset,&table[index].followset);
                                break;
                            }
                        }
                        j++;
                    }while(hase);
                    // printf("\n");
                }
            } 
        }
    }
    // printf(" Before %d ",table[index].followset.count);
    if(table[index].followset.count==0)addToSet("$",&table[index].followset);
    table[index].follow=true;
    // printStringList(table[index].followset);
    // printf("%d %s computation complete\n",table[index].followset.count,nonterminal);
    return true;
}
 
 
bool computeFirstAndFollow(grammar gtable,firstandfollowentry* table){
    int ntc=gtable.ntc;
    for(int i=0;i<ntc;i++){
        if(!first(gtable,gtable.entry[i],table)){
            printf("Error while computing first of %s\n",gtable.entry[i].nonterminal);
            return false;
        }
    }
    for(int i=0;i<ntc;i++){
        if(!follow(gtable,NONTERMINALS.str[i],table)){
            printf("Error while computing follow of %s",NONTERMINALS.str[i]);
            return false;
        }
    }
    return true;
}
 
 
void printFirstAndFollow(firstandfollowentry* table){
    int ntc=NONTERMINALS.count;
    for(int i=0;i<ntc;i++){
        printf("%s\n\t",NONTERMINALS.str[i]);
        printStringList(table[i].firstset);
        printf("\t");
        printStringList(table[i].followset);
    }
}
// void computeParseTable(firstandfollowentry*,grammar,parseentry**);
 
 
int getindex(char*str,stringlist strlist){
    for(int i=0;i<strlist.count;i++){
        if(strcmp(str,strlist.str[i])==0){
            return i+1;
        }
    }
    return 0;
}
 
bool addStringSet(stringlist src,stringlist* des){
    if(des==NULL){
        printf("Error! Invalid destination.\n");
        return false;
    }
    for (int i = 0; i < src.count; ++i)
    {
        addToSet(src.str[i],des);
    }
    return true;
}
bool addStringList(stringlist src,stringlist* des){
    if(des==NULL){
        printf("Error! Invalid destination.\n");
        return false;
    }
    for (int i = 0; i < src.count; ++i)
    {
        addString(src.str[i],des);
    }
    return true;
}
 
int addToSet(char* str,stringlist* strlist){
    if(getindex(str,strlist[0])){
        return -1;
    }
    if(addString(str,strlist))return 1;
    return 0;
}
bool addString(char* str,stringlist* strlist){
    if ((strlist->count==0))
    {
        strlist->str=malloc(sizeof(char**));
        strlist->str[0]=malloc(sizeof(char)*NTS);
        strcpy(strlist->str[0],str);
        strlist->count++;
        return true;
    }
    else{
        strlist->str=realloc(strlist->str,sizeof(char**)*(strlist->count+1));
        strlist->str[strlist->count]=malloc(sizeof(char)*NTS);
        strcpy(strlist->str[strlist->count],str);
        strlist->count++;
        return true;
    }
    return false;
    
}
void printStringList(stringlist strlist){
    //printf("count is %d\n",strlist.count);
    if(strlist.count<=0){
        printf("The given stringlist is empty.\n");
        return;
    }
    printf("{");
    int i=0;
    for(i=0;i<strlist.count-1;i++){
        printf("%s ,",strlist.str[i]);
    }
    printf("%s",strlist.str[i]);
    printf("}\n");
}

void printRules(){
	for(int i=0;i<NR;i++){
		printf("%d. ",Rules[i].id);
		printStringList(Rules[i].rule);
	}
	return;	
}
 
bool initializeStringlist(stringlist* list){
    list->str=malloc(sizeof(char)*NTS);
    list->count=0;
    return true;
}
 
stringlist** parseTable()
{
    GrammarTable.entry=malloc(sizeof(grammarentry));
    GrammarTable.ntc=0;
    GrammarFile(&GrammarTable,"grammar.txt");
    int ntc=GrammarTable.ntc,tc=TERMINALS.count;
    
    firstandfollowentry ftable[ntc];
    FirstAndFollowTable=ftable;
    for(int i=0;i<ntc;i++){
        FirstAndFollowTable[i].first=false;
        FirstAndFollowTable[i].follow=false; 
    }
    ParseTable=malloc(sizeof(stringlist*)*ntc);
    for (int i=0;i<ntc;i++){
        ParseTable[i]=malloc(sizeof(stringlist)*tc);
    }
    
    computeFirstAndFollow(GrammarTable,FirstAndFollowTable);
    
    // printFirstAndFollow(FirstAndFollowTable);
    // for(int i=0;i<ntc;i++){
    //     printf("%s\n",NONTERMINALS.str[i] );
    //     for(int j=0;j<GrammarTable.entry[i].rulecount;j++){
    //         printf("\t");
    //         printStringList(FirstAndFollowTable[i].rulefirst[j]);
    //     }
    // }
    stringlist terminals;
    initializeStringlist(&terminals);
    addStringSet(TERMINALS,&terminals);
    //printStringList(terminals);
    //printf("\n\n\n");
    //printStringList(NONTERMINALS);
    //printf("\n\n\n");
    int i=getindex("e",TERMINALS)-1;
    //printf("index is %d no of Terminals is %d and No of Non Terminals is %d\n",i,TERMINALS.count,NONTERMINALS.count);
    strcpy(terminals.str[i],"$");
    Rules=malloc(sizeof(rule));
    int n=1;
    
    for(int i=0;i<ntc;i++){
        for (int j = 0; j < tc; ++j)
        {
            initializeStringlist(&ParseTable[i][j]);
        }
    }
    for(int i=0;i<ntc;i++){
        int hase=0,index;
        for (int j = 0; j < GrammarTable.entry[i].rulecount; ++j)
         {
            hase=0;
            Rules=realloc(Rules,sizeof(rule)*n);
            Rules[n-1].id=n;
            initializeStringlist(&Rules[n-1].rule);
            addString(NONTERMINALS.str[i],&Rules[n-1].rule);
            addStringList(GrammarTable.entry[i].rule[j],&Rules[n-1].rule);
            n++;
            for(int k=0;k<FirstAndFollowTable[i].rulefirst[j].count;k++){
                index=getindex(FirstAndFollowTable[i].rulefirst[j].str[k],TERMINALS)-1;
                if(strcmp("e",TERMINALS.str[index])==0){
                    hase=1;
                    continue;
                }
                if(index!=-1){
                addStringList(GrammarTable.entry[i].rule[j],&ParseTable[i][index]);
                }
            }
        }
            
            if(hase){
                for(int k=0;k<FirstAndFollowTable[i].followset.count;k++){
                    index=getindex(FirstAndFollowTable[i].followset.str[k],terminals)-1;
                    if(index!=-1){
                    addToSet("e",&ParseTable[i][index]);
                    }
                }
            }
            else{
                
                for(int k=0;k<FirstAndFollowTable[i].followset.count;k++){
                    index=getindex(FirstAndFollowTable[i].followset.str[k],terminals)-1;
                    if(ParseTable[i][index].count==0&&index!=-1)
                    addToSet("syn",&ParseTable[i][index]);
                } 
        }

    }
    NR=n-1;
    
    for(int i=0;i<ntc;i++){
        //printf("%d %s\n",i+1, NONTERMINALS.str[i]);
        for (int j = 0; j < tc; ++j)
        {
            if(ParseTable[i][j].count==0){
                addToSet("error",&ParseTable[i][j]);
                continue;
            }
          // printf("\t%s.",terminals.str[j]);
           //printStringList(ParseTable[i][j]);
        }
    }
    strcpy(TERMINALS.str[0],"$");
    //printGrammar(GrammarTable);
    //printFirstAndFollow(FirstAndFollowTable);
    //printRules();
    return ParseTable;
}