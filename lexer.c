// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include"lexer.h"

void removecomments(FILE* fp2);
void removecomment(FILE* fp2){
removecomments(fp2);
fclose(fp2);
};

void tokenise(FILE *fp)
{
    state=malloc(sizeof(int));
    *state=0;

    struct tokenlex *toklex;
    symboltable = malloc(sizeof(struct tableel) * 30);
    for (int i = 0; i < 30; i++)
    {
        symboltable[i].tokenlex = NULL;
    }
    //printf("hi");

    initialize(symboltable);

    while (!feof(fp))
    {
        lineptr++;
        fp = getStream(fp);
        while ((toklex = getNextToken(line)) != NULL)
        {
            printf("Line is  %d < %s ,  %s >\n", lineptr, toklex->token, toklex->lexeme);
            //free(toklex);
        }
    }
    printf("\n Lexical Analysis Phases over\n");
    fclose(fp);
};
set* getonetoken(FILE* fp){
    state=malloc(sizeof(int));
    set *toklex;
    symboltable = malloc(sizeof(struct tableel) * 30);
    for (int i = 0; i < 30; i++)
    {
        symboltable[i].tokenlex = NULL;
    }
    //printf("hi");

    initialize(symboltable);
    // if(*state==40){
    //         printf("in this state bruh\n");
    //         set * cha;
    //         cha=getonetoken(fp);
    //         while(*state!=40){
    //             cha=getonetoken(fp);
    //         }
    //         return cha;
    //     }
    if((toklex = getNextToken(line)) != NULL){
        return toklex;
        
    }
    else if(!feof(fp)){
        //printf("state is %d \n",*state);
        int val;
        val=*(line2ptr)+1;
        *line2ptr=val;
        fp=getStream(fp);
        if((toklex = getNextToken(line)) != NULL){
        //printf("%s\n",toklex->lexeme);
        return toklex;
        }
        

        // else{
        return getonetoken(fp);
        //}
    }
    else{
        return NULL;
    }

}

FILE* getStream(FILE* fp){
    int i=0;
    char ch;
    if(fp==NULL){
        printf("cant open file");
        return NULL;
    }
    else{
        while((ch=getc(fp))!='\n'&&!(feof(fp))){
            line[i]=ch;
            i++;
        }
        line[i]='\0';
        *startpoint=0;
        return fp;
    }
}

struct tokenlex* getNextToken(char* c){
    struct tokenlex* ret;
    struct tokenlex* compret;
    ret=malloc(sizeof(struct tokenlex));
    char* token;
    token=malloc(sizeof(char)*20);
    char* lexeme;
    lexeme=malloc(sizeof(char)*20);
    ret->token=token;
    ret->lexeme=lexeme;
    int storelen,i,start;
    storelen=strlen(c);
    
    i=*startpoint;
    start=i;
    while(i<=storelen){
        switch(*state){
            case 0:
                if(c[i]=='\0'){
                    return NULL;
                }
                if(c[i]<='9'&&c[i]>='0'){
                    *state=1;
                    i++;
                    break;
                }
                if((c[i]<='z'&&c[i]>='a')||(c[i]<='Z'&&c[i]>='A')){
                    *state=12;
                    i++;
                    break;
                }
                if(c[i]=='\t'||c[i]=='\b'||c[i]=='\n'||c[i]==' '){
                    *state=14;
                    i++;
                    break;
                }
                if(c[i]=='['){
                    *state=16;
                    i++;
                    break;
                }
                if(c[i]==']'){
                    *state=17;
                    i++;
                    break;
                }
                if(c[i]=='('){
                    *state=18;
                    i++;
                    break;
                }
                if(c[i]==')'){
                    *state=19;
                    i++;
                    break;
                }
                if(c[i]=='='){
                    *state=20;
                    i++;
                    break;
                }
                if(c[i]=='!'){
                    *state=23;
                    i++;
                    break;
                }
                if(c[i]=='.'){
                    *state=26;
                    i++;
                    break;
                }
                if(c[i]=='>'){
                    *state=28;
                    i++;
                    break;
                }
                if(c[i]=='<'){
                    *state=32;
                    i++;
                    break;
                }
                if(c[i]==':'){
                    *state=36;
                    i++;
                    break;
                }
                if(c[i]=='*'){
                    *state=39;
                    i++;
                    break;
                }
                if(c[i]==','){
                    *state=44;
                    i++;
                    break;
                }
                if(c[i]==';'){
                    *state=45;
                    i++;
                    break;
                }
                if(c[i]=='/'){
                    *state=46;
                    i++;
                    break;
                }
                if(c[i]=='-'){
                    *state=47;
                    i++;
                    break;
                }
                if(c[i]=='+'){
                    *state=48;
                    i++;
                    break;
                }
                printf("Unable to tokenise '%c' in line no. %d\n",c[i-1],lineptr);
                //exit(0);
                i++;
                *startpoint=i;
                start=i;
                *state=0;
                break;

            case 1:
                //printf("\n in case1");
                if(c[i]<='9'&&c[i]>='0'){
                    *state=1;
                    i++;
                    break;
                }
                else if(c[i]=='.'){
                    *state=3;
                    i++;
                    break;
                }
                else{
                    *state=2;
                    break;

                }

                //exit(0);
            case 2:
                //printf("\n in case2");
                *startpoint=i;
                if(i-start<=20){
                    for(int k=start;k<i;k++){
                        lexeme[k-start]=c[k];
                    }
                    strcpy(token,"NUM");
                    *state=0;
                    return ret;
                    break;
                    }
                else{
                    printf("Unable to tokenise More than 20 characters  in line no. %d\n",lineptr);
                    *startpoint=i;
                    start=i;
                    *state=0;
                    break;
                }
            
            case 3:
                //printf("\n in case3");
                if((c[i]<='9'&&c[i]>='0')){
                    *state=5;
                    i++;
                    break;
                }
                else if(c[i]=='.'){
                    *state=4;
                    break;
                }
                printf("Unable to tokenise '%c' in line  no. %d\n",c[i-1],lineptr);
                *startpoint=i;
                start=i;
                *state=0;
                break;

                //exit(0);
                
            case 4:
                //printf("\n in case4");
                i-=1;
                *startpoint=i;
                for(int k=start;k<i;k++){
                    lexeme[k-start]=c[k];
                }
                strcpy(token,"NUM");
                *state=0;
                return ret;
                break;
            
            case 5:
                //printf("\n in case5");
                if(c[i]<='9'&&c[i]>='0'){
                    *state=5;
                    i++;
                    break;
                }
                else if(c[i]=='e' || c[i]=='E'){
                    *state=7;
                    i++;
                    break;
                }
                
                else{
                    *state=6;
                    break;
                }
                
            
            case 6:
                //printf("\n in case6");
                *startpoint=i;
                if(i-start<=20){
                for(int k=start;k<i;k++){
                    //printf("k is %d lexeme is %c\n",k,c[k]);
                    lexeme[k-start]=c[k];
                    //printf("k is %d lexeme is %c\n",k,lexeme[k]);
                }
                //printf("\nstart is %d i is %d lexeme is %s\n",start,i,lexeme);
                strcpy(token,"RNUM");
                *state=0;
                return ret;
                break;
                }
                else{
                printf("Unable to tokenise More than 20 characters  in line no. %d\n",lineptr);
                *startpoint=i;
                start=i;
                *state=0;
                break;
                }
                
            
            case 7:
                if(c[i]<='9'&&c[i]>='0'){
                    *state=10;
                    i++;
                    break;
                }
                else if(c[i]=='+'||c[i]=='-'){
                    *state=9;
                    i++;
                    break;
                }
                else{
                    *state=8;
                    break;
                }
               

            case 8:
                i-=1;
                *startpoint=i;
                for(int k=start;k<i;k++){
                    lexeme[k-start]=c[k];
                }
                strcpy(token,"RNUM");
                *state=0;
                return ret;
                break;
                

            case 9:
                if(c[i]<='9'&&c[i]>='0'){
                    *state=10;
                    i++;
                    break;
                }
                else{
                    *state=49;
                    i++;
                    break;
                }
                
            case 10:
                if(c[i]<='9'&&c[i]>='0'){
                    *state=10;
                    i++;
                    break;
                }
                else{
                    *state=11;
                    break;
                }
               
            case 11:
                *startpoint=i;
                for(int k=start;k<i;k++){
                    lexeme[k-start]=c[k];
                }
                strcpy(token,"RNUM");
                *state=0;
                return ret;
                break;
                

            case 12:
                //printf("\n in case12");
                if((c[i]<='z'&&c[i]>='a')||(c[i]<='Z'&&c[i]>='A')||c[i]=='_'||c[i]<='9'&&c[i]>='0'){
                    *state=12;
                    i++;
                    break;
                }
                else{
                    *state=13;
                    break;
                }
                
            case 13:
                *startpoint=i;
                if(i-start<=20){
                for(int k=start;k<i;k++){
                    lexeme[k-start]=c[k];
                }
                strcpy(token,"");

                //ret=storekeywords(symboltable,ret->token,ret->lexeme);
                //strcpy(ret->token,final);
                //printf("\n sahd returned %s and %s\n",ret->lexeme,ret->token);
                *state=0;
                return storekeywords(symboltable,ret->token,ret->lexeme);
                break;
                }
                else{
                printf("Unable to tokenise More than 20 characters in line no. %d\n",lineptr);
                *startpoint=i;
                start=i;
                *state=0;
                break;
                }
                
            
            case 49:
                i-=3;
                *startpoint=i;
                for(int k=start;k<i;k++){
                    lexeme[k-start]=c[k];
                }
                strcpy(token,"RNUM");
                *state=0;
                return ret;
                break;
               

            case 14:
                if(c[i]=='\t'||c[i]=='\b'||c[i]=='\n'||c[i]==' '){
                    *state=14;
                    i++;
                    break;
                }
                else{
                    *startpoint=i;
                    start=i;
                    *state=0;
                    break;
                }

            
            case 16:
                strcpy(token,"SQBO");
                strcpy(lexeme,"[");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 17:
                strcpy(token,"SQBC");
                strcpy(lexeme,"]");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 18:
                strcpy(token,"BO");
                strcpy(lexeme,"(");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 19:
                strcpy(token,"BC");
                strcpy(lexeme,")");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            case 44:
                strcpy(token,"COMMA");
                strcpy(lexeme,",");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 45:
                strcpy(token,"SEMICOL");
                strcpy(lexeme,";");
                *startpoint=i;
                *state=0;
                return ret;
                break;
                
            case 46:
                strcpy(token,"DIV");
                strcpy(lexeme,"/");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 47:
                strcpy(token,"MINUS");
                strcpy(lexeme,"-");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            case 48:
                strcpy(token,"PLUS");
                strcpy(lexeme,"+");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 20:
                if(c[i]=='='){
                    *state=21;
                    i++;
                    break;
                }
                printf("Unable to tokenise '%c' in line no. %d\n",c[i-1],lineptr);
                //i++;
                *startpoint=i;
                start=i;
                *state=0;
                break;

                
            case 21:
                strcpy(token,"EQ");
                strcpy(lexeme,"==");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 23:
                if(c[i]=='='){
                    *state=24;
                    i++;
                    break;
                }
                printf("Unable to tokenise '%c' in line no. %d\n",c[i-1],lineptr);
                //i++;
                *startpoint=i;
                start=i;
                *state=0;
                break;

                
            case 24:
                strcpy(token,"NE");
                strcpy(lexeme,"!=");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 26:
                if(c[i]=='.'){
                    *state=27;
                    i++;
                    break;
                }
                printf("Unable to tokenise '%c' in line no. %d\n",c[i-1],lineptr);
                *startpoint=i;
                start=i;
                *state=0;
                break;

                //exit(0);
                
            case 27:
                strcpy(token,"RANGEOP");
                strcpy(lexeme,"..");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 28:
                if(c[i]=='>'){
                    *state=30;
                    i++;
                    break;
                }
                else if(c[i]=='='){
                    *state=31;
                    i++;
                    break;
                }
                else{
                    *state=29;
                    break;
                }
            case 29:
                strcpy(token,"GT");
                strcpy(lexeme,">");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 30:
                if(c[i]=='>'){
                    *state=301;
                    i++;
                    break;
                }
                else
                {
                strcpy(token,"ENDDEF");
                strcpy(lexeme,">>");
                *startpoint=i;
                *state=0;
                return ret;
                break;
                }

            case 301:
                strcpy(token,"DRIVERENDDEF");
                strcpy(lexeme,">>>");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 31:
                strcpy(token,"GE");
                strcpy(lexeme,">=");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 32:
                if(c[i]=='<'){
                    *state=34;
                    i++;
                    break;
                }
                else if(c[i]=='='){
                    *state=35;
                    i++;
                    break;
                }
                else{
                    *state=33;
                    break;
                }

            case 33:
                strcpy(token,"LT");
                strcpy(lexeme,"<");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
            case 34:
                if(c[i]!='<'){
                strcpy(token,"DEF");
                strcpy(lexeme,"<<");
                *startpoint=i;
                *state=0;
                return ret;
                break;
                }
                else{
                    *state=341;
                    i++;
                    break;
                }
            
            case 341:
                strcpy(token,"DRIVERDEF");
                strcpy(lexeme,"<<<");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            
            case 35:
                strcpy(token,"LE");
                strcpy(lexeme,"<=");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 36:
                if(c[i]=='='){
                    *state=37;
                    i++;
                    break;
                }
                else{
                    *state=38;
                    break;
                }

            case 37:
                strcpy(token,"ASSIGNOP");
                strcpy(lexeme,":=");
                *startpoint=i;
                *state=0;
                return ret;
                break;

            case 38:
                strcpy(token,"COLON");
                strcpy(lexeme,":");
                *startpoint=i;
                *state=0;
                return ret;
                break;
    
            case 39:
                    if(c[i]=='*'){
                    *state=40;
                    i++;
                    break;
                }
                else{
                    *state=43;
                    break;
                }
            case 40:
                    if(c[i]=='*'){
                    *state=41;
                    i++;
                    break;
                }
                else{
                    *state=40;
                    i++;
                    break;
                }
            case 41:
                    if(c[i]=='*'){
                    *state=42;
                    i++;
                    break;
                }
                else{
                    *state=40;
                    i++;
                    break;
                }
            case 42:
                *state=0;
                break;
            
            
            case 43:
                strcpy(token,"MUL");
                strcpy(lexeme,"*");
                *startpoint=i;
                *state=0;
                return ret;
                break;
            
        }     
    }
    return NULL;
    
}

int hashFunction(char* S){

	long long int hash = 7;

	for (int i = 0; i < strlen(S); i++) 
		{
    		hash = hash*31 + 11*(S[i]-0);
		}
    hash=hash%30;
    if(hash<0){
        hash*=-1;
    }
	return hash;

}

struct tokenlex* installID(struct tableel* head , struct tokenlex *tokenlex){
    //printf("Yup3\n");
	int hashval;
	struct tableel* savehead;
	hashval=hashFunction(tokenlex->lexeme);
    savehead = &(head[hashval]);
    ///printf("\nhash value for lexeme is %d where lexeme is %s\n",hashval,tokenlex->lexeme);
	if((savehead->tokenlex)==NULL){
        ///printf("\n 1%s came here with\n",tokenlex->lexeme);
		savehead->tokenlex=tokenlex;
		savehead->next=NULL;
        if(strcmp(tokenlex->token,"")==0){
            ///printf("\n2 %s came here with\n",tokenlex->lexeme);
            (savehead->tokenlex)->token="ID";
            //strcpy(final,savehead->tokenlex->token);
            return savehead->tokenlex;
        }
        else{
            ///printf("\n3 %s came here with\n",tokenlex->lexeme);
        return savehead->tokenlex;
        }
	}
	else{
           ///printf("\n4 %s came here with\n",tokenlex->lexeme);
		while(savehead->next!=NULL && strcmp((savehead->tokenlex)->lexeme,tokenlex->lexeme)!=0){
			savehead=savehead->next;
		}
		if(strcmp((savehead->tokenlex)->lexeme,tokenlex->lexeme)==0){
			///printf("<<<<    %s  >>>>>\n",savehead->tokenlex->token);
            return savehead->tokenlex;

		}
		else{
		savehead->next=malloc(sizeof(struct tableel));
        savehead=savehead->next;
		savehead->tokenlex=tokenlex;
        savehead->next=NULL;
        if(strcmp((savehead->tokenlex)->token,"")==0){
            (savehead->tokenlex)->token="ID";
            return savehead->tokenlex;
        }
		return savehead->tokenlex;
		}

	}
}

struct tokenlex* storekeywords(struct tableel* head , char* token , char* lexeme){
	struct tokenlex* new,store;
	new=malloc(sizeof(struct tokenlex));
	new->token=malloc(sizeof(char)*20);
    strcpy(new->token,token);
	new->lexeme=malloc(sizeof(char)*20);
    strcpy(new->lexeme,lexeme);
	new=installID(head,new);
    return new;

}
void initialize(struct tableel* symboltable){
storekeywords(symboltable,"INTEGER","integer");
storekeywords(symboltable,"REAL","real");
storekeywords(symboltable,"BOOLEAN","boolean");
storekeywords(symboltable,"OF","of");
storekeywords(symboltable,"ARRAY","array");
storekeywords(symboltable,"START","start");
storekeywords(symboltable,"END","end");
storekeywords(symboltable,"DECLARE","declare");
storekeywords(symboltable,"MODULE","module");
storekeywords(symboltable,"DRIVER","driver");
storekeywords(symboltable,"PROGRAM","program");
storekeywords(symboltable,"RECORD","record");
storekeywords(symboltable,"TAGGED","tagged");
storekeywords(symboltable,"UNION","union");
storekeywords(symboltable,"GET_VALUE","get_value");
storekeywords(symboltable,"PRINT","print");
storekeywords(symboltable,"USE","use");
storekeywords(symboltable,"WITH","with");
storekeywords(symboltable,"PARAMETERS","parameters");
storekeywords(symboltable,"TRUE","true");
storekeywords(symboltable,"FALSE","false");
storekeywords(symboltable,"TAKES","takes");
storekeywords(symboltable,"INPUT","input");
storekeywords(symboltable,"RETURNS","returns");
storekeywords(symboltable,"AND","AND");
storekeywords(symboltable,"OR","OR");
storekeywords(symboltable,"FOR","for");
storekeywords(symboltable,"IN","in");
storekeywords(symboltable,"SWITCH","switch");
storekeywords(symboltable,"CASE","case");
storekeywords(symboltable,"BREAK","break");
storekeywords(symboltable,"DEFAULT","default");
storekeywords(symboltable,"WHILE","while");

}

void removecomments(FILE* fp){
    int flag=0;
    char* line;
    char ch;
    line=malloc(sizeof(char)*200);
    while(!feof(fp)){
       if(flag==1&&!feof(fp)){
           if((ch=fgetc(fp))=='*'){
               if((ch=fgetc(fp))=='*'){
                   flag=0;
                   continue;
               }
               else{
                   flag=1;
                   continue;
               }
           }

       }
       if(flag==0&&!feof(fp)){
           if((ch=fgetc(fp))=='*'){
               if((ch=fgetc(fp))=='*'){
                   flag=1;
                   continue;
               }
               else{
                   printf("*%c",ch);
                   continue;
               }
           }
           else{
                printf("%c",ch);
                continue;
           }

       }
}
printf("\b");
}
