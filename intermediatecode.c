// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth
#include"ast.h"
#include"intermediatecode.h"
#include<string.h>
int labelcount=0;
int namecount=0;
int intcount=0;
int realcount=0;
int boolcount=0;
char* genint(){
    char* new;
    new=malloc(sizeof(char)*5);
    sprintf(new,"int_t%d",intcount);
    intcount++;
    return new;
}
char* genreal(){
    char* new;
    new=malloc(sizeof(char)*5);
    sprintf(new,"real_t%d",realcount);
    realcount++;
    return new;
}
char* genbool(){
    char* new;
    new=malloc(sizeof(char)*5);
    sprintf(new,"bool_t%d",boolcount);
    boolcount++;
    return new;
}
char* newtemp(){
    char* new;
    new=malloc(sizeof(char)*5);
    sprintf(new,"L%d",labelcount);
    labelcount++;
    return new;
}
char* genname(){
    char* new;
    new=malloc(sizeof(char)*5);
    sprintf(new,"t%d",namecount);
    namecount++;
    return new;
}

void astpostordertraverse(astree* astnode){
    astree* ast;
    ast=astnode->childhead;
    while(ast!=NULL){
    printfunctionlabel(ast);
    astpostordertraverse(ast);
    printintermediatecode(ast);
    ast=ast->sibling;
    }
    if(astnode==NULL){
        return;
    }
}

void printintermediatecode(astree* astnode){
    // we have to use a post order traversal mechanism
    if(strcmp(astnode->label,"<ioStmt>")==0 && strcmp(astnode->childhead->label,"PRINT")==0){
        //printf("printing %s\n",astnode->childhead->sibling->childhead->childhead->lexval);
        astnode->intermediatecode=malloc(sizeof(char)*strlen(astnode->childhead->sibling->childhead->childhead->lexval)+10);
        sprintf(astnode->intermediatecode,"print_");
        if(astnode->childhead->sibling->childhead->childhead->type==INTEGER){
            if(astnode->childhead->sibling->childhead->childhead->isarray==false || (astnode->childhead->sibling->childhead->childhead->isarray==true &&astnode->childhead->sibling->childhead->childhead->sibling->childhead==NULL)){
            strcat(astnode->intermediatecode,"int");
            sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->childhead->childhead->lexval);

            }
           else{
                   strcat(astnode->intermediatecode , "int");
                    sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->childhead->childhead->lexval);
                   sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode),"[%s]",astnode->childhead->sibling->childhead->childhead->sibling->childhead->lexval);

               }
           }
        if(astnode->childhead->sibling->childhead->childhead->type==REAL){
            if(astnode->childhead->sibling->childhead->childhead->isarray==false || (astnode->childhead->sibling->childhead->childhead->isarray==true &&astnode->childhead->sibling->childhead->childhead->sibling->childhead==NULL)){
            strcat(astnode->intermediatecode,"real");
            sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->childhead->childhead->lexval);
            }
           else{
                   strcat(astnode->intermediatecode , "real");
                    sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->childhead->childhead->lexval);
                   sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode),"[%s]",astnode->childhead->sibling->childhead->childhead->sibling->childhead->lexval);
               }
        }
        if(astnode->childhead->sibling->childhead->childhead->type==BOOLEAN){
            if(astnode->childhead->sibling->childhead->childhead->isarray==false || (astnode->childhead->sibling->childhead->childhead->isarray==true &&astnode->childhead->sibling->childhead->childhead->sibling->childhead==NULL)){
              strcat(astnode->intermediatecode,"bool");
            sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->childhead->childhead->lexval);
            }
           else{
                   strcat(astnode->intermediatecode , "bool");
                    sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->childhead->childhead->lexval);
                   sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode),"[%s]",astnode->childhead->sibling->childhead->childhead->sibling->childhead->lexval);
               }
        }
        printf("        %s\n\n",astnode->intermediatecode);
        //printf("address is %s\n",astnode->childhead->sibling->childhead->childhead->addr);
   
    }
    if(strcmp(astnode->label,"<ioStmt>")==0 && strcmp(astnode->childhead->label,"GET_VALUE")==0){
        //printf("printing %s\n",astnode->childhead->sibling->childhead->childhead->lexval);
        astnode->intermediatecode=malloc(sizeof(char)*strlen(astnode->childhead->sibling->lexval)+10);
        sprintf(astnode->intermediatecode,"getvalue");
        if(astnode->childhead->sibling->type==INTEGER){
                   strcat(astnode->intermediatecode , "_int");
            
           }
        if(astnode->childhead->sibling->type==REAL){
            strcat(astnode->intermediatecode , "_real");
           
        }
        if(astnode->childhead->sibling->type==BOOLEAN){
                   strcat(astnode->intermediatecode , "_bool");
            
        }
        sprintf(astnode->intermediatecode+strlen(astnode->intermediatecode)," %s",astnode->childhead->sibling->lexval);
        printf("        %s\n\n",astnode->intermediatecode);
        //printf("address is %s\n",astnode->childhead->sibling->childhead->childhead->addr);
   
    }

    if(strcmp(astnode->label,"NUM")==0 || strcmp(astnode->label,"RNUM")==0){
        if((strcmp(astnode->parent->label,"<index>")==0 && strcmp(astnode->parent->parent->label,"<range_arrays>")!=0) || strcmp(astnode->parent->label,"<var_id_num>")==0 || strcmp(astnode->parent->label,"<range>")==0 ){
        astnode->addr=malloc(sizeof(char)*strlen(astnode->lexval));
        astnode->intermediatecode=malloc(sizeof(char)*30);
        if(strcmp(astnode->label,"NUM")==0){
        //strcpy(astnode->addr,genname());
        strcpy(astnode->addr,genint());
        sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
        strncat(astnode->intermediatecode,",",1);
        strncat(astnode->intermediatecode,astnode->lexval,strlen(astnode->lexval));
        strncat(astnode->intermediatecode,"\n",1);
        printf("        assgnimm_int  %s\n",astnode->intermediatecode);
        }
        else{
            //strcpy(astnode->addr,genname());
             strcpy(astnode->addr,genreal());
              sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
        strncat(astnode->intermediatecode,"= ,",1);
        strncat(astnode->intermediatecode,astnode->lexval,strlen(astnode->lexval));
        strncat(astnode->intermediatecode,"\n",1);
        printf("MACHINE CODE CANNOT BE GENERATED \n\n");
        exit(0);
        printf("        assgnimm_real  %s\n",astnode->intermediatecode);

        }
        
       
        
        
        }
    }

    if(strcmp(astnode->label,"ID" )==0 && astnode->isarray==false){
        //if(strcmp(astnode->parent->label,"<ioStmt>") ==0 || strcmp(astnode->parent->label,"<var_id_num>") ==0  || (strcmp(astnode->parent->label,"<index>")==0 && strcmp(astnode->parent->label,"<range_arrays>")!=0) || strcmp(astnode->parent->label,"input_plist" )==0 || strcmp(astnode->parent->label,"output_plist" )==0)
        //printf("------------------------ for %s is %s\n\n",astnode->lexval,astnode->namechanged);
        astnode->addr=malloc(sizeof(char)*strlen(astnode->lexval));
        strcpy(astnode->addr,astnode->lexval);
    }

    
     if(strcmp(astnode->label,"ID" )==0 && astnode->isarray==true ){
        
        if(strcmp(astnode->parent->label,"<ioStmt>") ==0 || strcmp(astnode->parent->label,"<var_id_num>") ==0  || (strcmp(astnode->parent->label,"<index>")==0 && strcmp(astnode->parent->label,"<range_arrays>")!=0) || strcmp(astnode->parent->label,"input_plist")==0){
        astnode->addr=malloc(sizeof(char)*5);
        if(astnode->symboltabpointer->type==INTEGER ){
        //strcpy(astnode->addr,genname());
        strcpy(astnode->addr,genint());
        }
        if(astnode->symboltabpointer->type==REAL ){
        //strcpy(astnode->addr,genname());
        strcpy(astnode->addr,genreal());
        }
        if(astnode->symboltabpointer->type==BOOLEAN ){
        //strcpy(astnode->addr,genname());
        strcpy(astnode->addr,genbool());
        }
        //printf("1\n");
        astnode->intermediatecode=malloc(sizeof(char)*30);
        printintermediatecode(astnode->parent->childhead->sibling->childhead);
        strcpy(astnode->intermediatecode,astnode->addr);
        strncat(astnode->intermediatecode,",",1);
        strncat(astnode->intermediatecode,astnode->lexval,strlen(astnode->lexval));
        strncat(astnode->intermediatecode,"[",1);
        //printf("------------------------------------ %s\n",astnode->parent->childhead->sibling->childhead->addr);
        //printf("Here address is %s",astnode->parent->childhead->sibling->childhead->addr);
        strncat(astnode->intermediatecode,astnode->parent->childhead->sibling->childhead->addr,strlen(astnode->parent->childhead->sibling->childhead->addr));
        strncat(astnode->intermediatecode,"]",1);
        strncat(astnode->intermediatecode,"\n",1);
        if(astnode->symboltabpointer->type==INTEGER )
        printf("       assgn_int %s\n",astnode->intermediatecode);
        if(astnode->symboltabpointer->type==REAL )
        printf("       assgn_real %s\n",astnode->intermediatecode);
        if(astnode->symboltabpointer->type==BOOLEAN )
        printf("       assgn_bool %s\n",astnode->intermediatecode);
        //printf("\n\n");
        }
    }
    
    if(strcmp(astnode->label,"<assignmentStmt>")==0){
        astnode->intermediatecode=malloc(sizeof(char)*30);
        astnode->addr=malloc(sizeof(char)*strlen(astnode->childhead->lexval));
        
        if(astnode->childhead->sibling->sibling->type==INTEGER){
            sprintf(astnode->intermediatecode," assgn_int  ");
        }
        else if(astnode->childhead->sibling->sibling->type==REAL){
            sprintf(astnode->intermediatecode," assgn_real  ");
        }
        else if(astnode->childhead->sibling->sibling->type==BOOLEAN){
            sprintf(astnode->intermediatecode," assgn_bool  ");
        }
        else{
            sprintf(astnode->intermediatecode,"---------- Moving");
        }

        strncat(astnode->intermediatecode,astnode->childhead->lexval,strlen(astnode->childhead->lexval));
        
        if(strcmp(astnode->childhead->sibling->sibling->label,"<index>")==0){
            strncat(astnode->intermediatecode,"[",1);
            strncat(astnode->intermediatecode,astnode->childhead->sibling->sibling->addr,strlen(astnode->childhead->sibling->sibling->addr));
            strncat(astnode->intermediatecode,"]",1);
            strncat(astnode->intermediatecode,"  ,",2);
            strncat(astnode->intermediatecode,astnode->childhead->sibling->sibling->sibling->addr,strlen(astnode->childhead->sibling->sibling->sibling->addr));
            strncat(astnode->intermediatecode,"\n",1);
            printf("        %s\n",astnode->intermediatecode);
            //printf("-----------------------------array assignment\n");

        }
        else{
            strncat(astnode->intermediatecode,",",1);
            //printf("fine until here--------------------------------------------------111\n");
            strncat(astnode->intermediatecode,astnode->childhead->sibling->sibling->addr,strlen(astnode->childhead->sibling->sibling->addr));
            strncat(astnode->intermediatecode,"\n",1);
            printf("        %s\n",astnode->intermediatecode);
            //printf("------------------------not an array assignment\n");

        }
    }
    if(strcmp(astnode->label,"<expression>")==0){
        astnode->addr=malloc(sizeof(char)*30);
        strcpy(astnode->addr,astnode->childhead->addr);
        //printf("        %s\n\n",astnode->intermediatecode);
    }

    if(strcmp(astnode->label,"<U>")==0){
        astnode->addr=malloc(sizeof(char)*5);
        if(strcmp(astnode->childhead->sibling->childhead->label,"<var_id_num>")==0){
            if(strcmp(astnode->childhead->sibling->childhead->childhead->label,"NUM")==0){
                strcpy(astnode->addr,genint());
            }
            if(strcmp(astnode->childhead->sibling->childhead->childhead->label,"RNUM")==0){
                strcpy(astnode->addr,genreal());
            }
            if(strcmp(astnode->childhead->sibling->childhead->childhead->label,"ID")==0){
                if(astnode->childhead->sibling->childhead->childhead->symboltabpointer->type==INTEGER){
                strcpy(astnode->addr,genint());
                }
                if(astnode->childhead->sibling->childhead->childhead->symboltabpointer->type==REAL){
                strcpy(astnode->addr,genreal());

                }
                if(astnode->childhead->sibling->childhead->childhead->symboltabpointer->type==BOOLEAN){
                strcpy(astnode->addr,genbool());

                }
                
            }

        }
        astnode->intermediatecode=malloc(sizeof(char)*30);
        sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
        strncat(astnode->intermediatecode,"=",1);
        strcat(astnode->intermediatecode,astnode->childhead->lexval);
        // astnode->childhead->sibling->addr=malloc(sizeof(char)*5);
        // strcpy(astnode->childhead->sibling->addr,genname());
        strcat(astnode->intermediatecode,astnode->childhead->sibling->addr);
        printf("        %s\n\n",astnode->intermediatecode);
    }
    if(strcmp(astnode->label,"<new_NT>")==0){
        astnode->addr=malloc(sizeof(char)*30);
        strcpy(astnode->addr,astnode->childhead->addr);
    }
    if(strcmp(astnode->label,"<var_id_num>")==0){
        astnode->addr=malloc(sizeof(char)*30);
        strcpy(astnode->addr,astnode->childhead->addr);
     }
    // if(strcmp(astnode->label,"<factor>")==0){
    //     astnode->addr=malloc(sizeof(char)*30);
    //     astnode->inh=malloc(sizeof(char)*30);
    //     strcpy(astnode->addr,astnode->childhead->addr);
    //     strcpy(astnode->addr,astnode->childhead->addr);
    //     if(astnode->sibling!=NULL){

    //     }
    //  }
    if(strcmp(astnode->label,"<arithmeticExpr>")==0){
        astnode->addr=malloc(sizeof(char)*30);
       astree* newnode;
       newnode =astnode->childhead;
       while(newnode->sibling!=NULL){
        newnode=newnode->sibling;
       }
        strcpy(astnode->addr,newnode->addr);
    }

    if(strcmp(astnode->label,"<term>")==0){
        astnode->addr=malloc(sizeof(char)*30);
        astnode->syn=malloc(sizeof(char)*30);
        astree* newnode;
        newnode =astnode->childhead;
        while(newnode->sibling!=NULL){
            newnode=newnode->sibling;
       }
       strcpy(astnode->addr,newnode->addr);
       strcpy(astnode->syn,astnode->childhead->addr);

        if(astnode->sibling!=NULL){
            astnode->sibling->sibling->inh=malloc(sizeof(char)*30);
            sprintf(astnode->sibling->sibling->inh,astnode->addr,strlen(astnode->addr));
            strcat(astnode->sibling->sibling->inh,astnode->sibling->lexval);
        }
        if(astnode->inh!=NULL){
            astnode->intermediatecode=malloc(sizeof(char)*30);
            sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
            strcat(astnode->intermediatecode," , ");
             char opera[10];
            if(astnode->inh[strlen(astnode->inh)-1]=='+'){
                strcpy(opera,"sum");
            }
            if(astnode->inh[strlen(astnode->inh)-1]=='-'){
                strcpy(opera,"diff");
            }
            strncat(astnode->intermediatecode,astnode->inh,strlen(astnode->inh)-1);
            strcat(astnode->intermediatecode," , ");
            strcat(astnode->intermediatecode,astnode->addr);
            
            if(strncmp(astnode->addr,"int",3)==0)
            printf("        %s_int %s\n\n",opera,astnode->intermediatecode);
            if(strncmp(astnode->addr,"real",4)==0)
            printf("        %s_real %s\n\n",opera,astnode->intermediatecode);
            if(strncmp(astnode->addr,"bool",4)==0)
            printf("        %s_bool %s\n\n",opera,astnode->intermediatecode);
        }
    }
    if(strcmp(astnode->label,"<factor>")==0){
        astnode->addr=malloc(sizeof(char)*30);
        astnode->syn=malloc(sizeof(char)*30);
       strcpy(astnode->addr,astnode->childhead->addr);
       strcpy(astnode->syn,astnode->childhead->addr);
       
       if(astnode->sibling!=NULL){
            //printf("last seen here1\n");
            astnode->sibling->sibling->inh=malloc(sizeof(char)*30);
            //printf("last seen here2\n");
            sprintf(astnode->sibling->sibling->inh,astnode->addr,strlen(astnode->addr));
            strcat(astnode->sibling->sibling->inh,astnode->sibling->lexval);
        }
        if(astnode->inh!=NULL){
            astnode->intermediatecode=malloc(sizeof(char)*30);
            
            sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
            
            strcat(astnode->intermediatecode," , ");
             char opera[10];
            if(astnode->inh[strlen(astnode->inh)-1]=='*'){
                strcpy(opera,"mul");
            }
            if(astnode->inh[strlen(astnode->inh)-1]=='/'){
                strcpy(opera,"div");
            }
            strncat(astnode->intermediatecode,astnode->inh,strlen(astnode->inh)-1);
           strcat(astnode->intermediatecode," , ");
            strcat(astnode->intermediatecode,astnode->addr);
            if(strncmp(astnode->addr,"int",3)==0)
            printf("        %s_int %s\n\n",opera,astnode->intermediatecode);
            if(strncmp(astnode->addr,"real",4)==0)
            printf("        %s_real %s\n\n",opera,astnode->intermediatecode);
            if(strncmp(astnode->addr,"bool",4)==0)
            printf("        %s_bool %s\n\n",opera,astnode->intermediatecode);

        }
    }
    if(strcmp(astnode->label,"<arithmeticOrBooleanExpr>")==0){
        astnode->addr=malloc(sizeof(char)*30);
       astree* newnode;
       newnode =astnode->childhead;
       while(newnode->sibling!=NULL){
        newnode=newnode->sibling;
       }
        strcpy(astnode->addr,newnode->addr);
        if(strcmp(astnode->parent->label,"<iterativeStmt>")==0){
            printf("        CMP %s , 0 \n\n",astnode->addr);
            printf("        JE %s\n\n",astnode->parent->next);
        }
    }

    if(strcmp(astnode->label,"<AnyTerm>")==0){
        
        if(strcmp(astnode->childhead->label,"<boolConstt>")==0){
            astnode->addr=malloc(sizeof(char)*30);
            astnode->syn=malloc(sizeof(char)*30);
            strcpy(astnode->addr,astnode->childhead->addr);
            strcpy(astnode->syn,astnode->childhead->addr);

        }
        if(strcmp(astnode->childhead->label,"<arithmeticExpr>")==0){
            astnode->addr=malloc(sizeof(char)*30);
            astnode->syn=malloc(sizeof(char)*30);
            astnode->intermediatecode=malloc(sizeof(char)*30);
            //strcpy(astnode->addr,genname());
                
            strcpy(astnode->syn,astnode->addr);
            
            if(astnode->childhead->sibling!=NULL){
                //printf("--------------------- addr is %s\n\n",astnode->addr);
                strcpy(astnode->addr,genbool());
                //printf("----------------------------supposed address is %s \n",astnode->addr);

            memset(astnode->intermediatecode,0,strlen(astnode->intermediatecode));
            char startlabel[5];
            char endlabel[5];
            strcpy(startlabel,newtemp());
            strcpy(endlabel,newtemp());
            printf("        PUSH EAX\n\n");
            printf("        PUSH EBX\n\n");
            printf("        MOV EAX , %s\n\n",astnode->childhead->addr);
            printf("        MOV EBX , %s\n\n",astnode->childhead->sibling->sibling->addr);
            //strcat(astnode->intermediatecode,astnode->childhead->sibling->lexval);
            printf("        CMP EAX , EBX \n\n");
            printf("        POP EBX\n\n");
            printf("        POP EAX\n\n");
            //printf("--------------------- %s\n\n",astnode->childhead->sibling->lexval);
            if(strcmp(astnode->childhead->sibling->lexval,"<=")==0){
                printf("        JG %s\n\n",endlabel);
            }
            if(strcmp(astnode->childhead->sibling->lexval,"<")==0){
                printf("        JGE %s\n\n",endlabel);
            }
            if(strcmp(astnode->childhead->sibling->lexval,">=")==0){
                printf("        JL %s\n\n",endlabel);
            }
            if(strcmp(astnode->childhead->sibling->lexval,">")==0){
                printf("        JLE %s\n\n",endlabel);
            }
            if(strcmp(astnode->childhead->sibling->lexval,"==")==0){
                printf("        JNE %s\n\n",endlabel);
            }
            if(strcmp(astnode->childhead->sibling->lexval,"!=")==0){
                printf("        JE %s\n\n",endlabel);
            }

            printf("%s :\n",startlabel);
            strncat(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
            strcat(astnode->intermediatecode," , ");
            strcat(astnode->intermediatecode,"1");
            printf("        assgn_bool %s\n\n",astnode->intermediatecode);
            printf("%s :   assgn_bool  %s , 0 \n\n",endlabel ,astnode->addr);

            //printf("        %s\n\n",astnode->intermediatecode);
            }
            else{
                strcpy(astnode->addr,astnode->childhead->addr);
            }
        }

        if(astnode->sibling!=NULL){
            //printf("here at last\n");
            astnode->sibling->sibling->inh=malloc(sizeof(char)*30);
            sprintf(astnode->sibling->sibling->inh,astnode->addr,strlen(astnode->addr));
            strcat(astnode->sibling->sibling->inh," ");
            strcat(astnode->sibling->sibling->inh,astnode->sibling->lexval);
        }
        if(astnode->inh!=NULL){
            astnode->intermediatecode=malloc(sizeof(char)*30);
            sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
            strcat(astnode->intermediatecode,"=");
            strcat(astnode->intermediatecode,astnode->inh);
            strcat(astnode->intermediatecode," ");
            strcat(astnode->intermediatecode,astnode->addr);
            printf("        %s\n\n",astnode->intermediatecode);
        }


    }
    if(strcmp(astnode->label,"<moduleReuseStmt>")==0){
        printf("        %s ",astnode->childhead->sibling->lexval);
        astree* new;
        new=astnode->childhead;
        if(new->childhead!=NULL){
            new=new->childhead->childhead;
            while(new->sibling!=NULL){
                printf(" %s ,",new->lexval);
                new=new->sibling;
            }
                printf(" %s ,",new->lexval);
            
        }
        new=astnode->childhead->sibling->sibling;
        if(new->childhead==NULL){
            printf("\b");
        }
        else{
            new=new->childhead;
            //printf("ip list== ");
            while(new->sibling!=NULL){
                printf(" %s ,",new->lexval);
                new=new->sibling;
            }
                printf(" %s ",new->lexval);
            
        }
        
        printf("\n\n");
    }
    if(strcmp(astnode->label,"<boolConstt>")==0){
        printf("-----------------------hi\n\n");
        astnode->addr=malloc(sizeof(char)*5);
        astnode->intermediatecode=malloc(sizeof(char)*30);
        strcpy(astnode->addr,genbool());
        sprintf(astnode->intermediatecode,astnode->addr,strlen(astnode->addr));
        strcat(astnode->intermediatecode," , ");
        if(strcmp(astnode->lexval,"true")==0){
        strcat(astnode->intermediatecode," 1");
        }
        else{
            strcat(astnode->intermediatecode," 0");
        }
        printf("       assgnimm_bool  %s\n\n",astnode->intermediatecode);
    }

    if(strcmp(astnode->label,"<statements>")==0 && strcmp(astnode->parent->label,"<iterativeStmt>")==0){
        if(strcmp(astnode->parent->childhead->label,"FOR")==0){
        //printf("--------------------- label is %s\n\n\n",astnode->parent->childhead->label);
        printf("        sum_int %s , %s , 1\n\n",astnode->parent->childhead->sibling->lexval,astnode->parent->childhead->sibling->lexval);
        printf("        PUSH EAX\n\n");
        printf("        PUSH EBX\n\n");
        printf("        MOVE EAX , %s \n\n",astnode->parent->childhead->sibling->lexval);
        printf("        MOVE EBX , %s \n\n",astnode->parent->childhead->sibling->sibling->end);
        printf("        CMP EAX , EBX \n\n");
        printf("        POP EBX\n\n");
        printf("        POP EAX\n\n");
        printf("        JLE %s\n\n",astnode->parent->labelname);
        }

        printf("%s:\n        NOP\n\n",astnode->parent->next);
        
    }
    if(strcmp(astnode->label,"<statements>")==0 && strcmp(astnode->parent->label,"<moduleDef>")==0){ 
        if(strcmp(astnode->parent->parent->label,"<module>")==0){
        astree* newl;
        newl=astnode->parent->parent;
        newl=newl->childhead->sibling->sibling;
        if(newl->childhead!=NULL)
        {
            newl=newl->childhead->childhead;
        int i=1;
        while(newl!=NULL){
            char ch[10];
    
                 //strcpy(ch,newl->sibling->childhead->sibling->type);
                 if(newl->sibling->type==INTEGER)
                 strcpy(ch,"int");
                 if(newl->sibling->type==REAL)
                 strcpy(ch,"real");
                 if(newl->sibling->type==BOOLEAN)
                 strcpy(ch,"bool");
                 if(newl->sibling!=NULL)
                printf("        assgn_%s %s , %%%d\n\n",ch,newl->lexval,i);
            
            i++;
            newl=newl->sibling->sibling;
        }
        }
    }
        printf("        %%endmacro\n\n");
    }
    if(strcmp(astnode->label,"<statements>")==0 && (strcmp(astnode->parent->label,"<caseStmts>")==0 || strcmp(astnode->parent->label,"<default>")==0)){

        printf("%s:\n        NOP\n\n",astnode->next);
        
    }
    
}
void printfunctionlabel(astree* astnode){
    strcmp(astnode->labelname,"\0");
    if(strcmp(astnode->label,"<module>")==0){
        strcpy(astnode->labelname,astnode->childhead->lexval);
        symfuncentry* new=getinfooffunction(functiontable,astnode->childhead->lexval);
        if(new!=NULL){
        printf("%%macro %s  %d\n\n",astnode->childhead->lexval, new->input_no + new->output_no);
        int i;
        i=new->output_no+1;
        astree* newl;
        newl=astnode->childhead->sibling->childhead;
        while(newl!=NULL){
            char ch[10];
            if(strcmp(newl->sibling->childhead->label,"<range_arrays>")==0)
            {   
                if(newl->sibling->childhead->sibling->type==INTEGER)
                 strcpy(ch,"int");
                 if(newl->sibling->childhead->sibling->type==REAL)
                 strcpy(ch,"real");
                 if(newl->sibling->childhead->sibling->type==BOOLEAN)
                 strcpy(ch,"bool");
                printf("        assgn_arr_%s %s , %%%d\n\n",ch,newl->lexval,i);
            }
            else{
                 //strcpy(ch,newl->sibling->childhead->sibling->type);
                 if(newl->sibling->childhead->type==INTEGER)
                 strcpy(ch,"int");
                 if(newl->sibling->childhead->type==REAL)
                 strcpy(ch,"real");
                 if(newl->sibling->childhead->type==BOOLEAN)
                 strcpy(ch,"bool");
                printf("        assgn_%s %s , %%%d\n\n",ch,newl->lexval,i);
            }
            
            i++;
            newl=newl->sibling->sibling;
        }

        }
    }
    if(strcmp(astnode->label,"<driverModule>")==0){
        strcpy(astnode->labelname,"main");
        printf("%%macro main 0\n\n");
    }
    if(strcmp(astnode->label,"<iterativeStmt>")==0){
        if(strcmp(astnode->childhead->label,"FOR")==0){
        printf("        assign_int %s , %s\n\n",astnode->childhead->sibling->lexval ,astnode->childhead->sibling->sibling->start);
        }
        strcpy(astnode->labelname,newtemp());
        strcpy(astnode->next,newtemp());
        printf("%s: \n",astnode->labelname);
        
    }
    if(strcmp(astnode->label,"<statements>")==0 && (strcmp(astnode->parent->label,"<caseStmts>")==0 || strcmp(astnode->parent->label,"<default>")==0) ){
        strcpy(astnode->labelname,newtemp());
        strcpy(astnode->next,newtemp());
        printf("%s: \n",astnode->labelname);
        if(strcmp(astnode->parent->label,"<default>")!=0){
        printf("        PUSH EAX\n\n");
        printf("        MOV EAX , %s \n\n",astnode->parent->parent->childhead->lexval);
        if(strcmp(astnode->parent->childhead->lexval,"true")==0){
            printf("        CMP EAX , 1\n\n");
        }
        else if (strcmp(astnode->parent->childhead->lexval,"false")==0)
        {
            printf("        CMP EAX , 0\n\n");
        }
        else
        {
           printf("        CMP EAX , %s\n\n",astnode->parent->childhead->lexval);
        }
        
        
        printf("        POP EAX\n\n");
        printf("        JNE %s\n\n",astnode->next);   
        }
    }


}

// void astlabeltraverse(astree* astnode){
//     astree* ast;
//     ast=astnode->childhead;
//     while(ast!=NULL){
//     putlabel();
//     ast=ast->sibling;
//     }
//     if(astnode==NULL){
//         return;
//     }
// }
// void putlabel(astree* astnode){

//}