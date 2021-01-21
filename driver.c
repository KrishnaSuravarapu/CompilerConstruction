#include "stackdef.h"
#include "semanticsdef.h"
#include "intermediatecode.h"
#include <stdio.h>
#include <sys/timeb.h>
#include<time.h>
int main(int argc , char* argv[])
{
    time_t start1,end1,start2,end2,taken1,taken2; 
    start1 = time(NULL); 

    int newnum;
    parsetree *new;
    new = getparsetree(argv[1]);
    populateast(new);
    populatetables(new);


    while (1)
    {
        printf("\n\n\n");
        printf("Select 0 for %-30s\n", "exit");
        printf("Select 1 for %-30s\n", "Lexer");
        printf("Select 2 for %-30s\n", "Parser");
        printf("Select 3 for %-30s\n", "AST");
        printf("Select 4 for %-30s\n", "Memory");
        printf("Select 5 for %-30s\n", "Symbol Table");
        printf("Select 6 for %-30s\n", "Activation record size");
        printf("Select 7 for %-30s\n", "Static And Dynamic Arrays");
        printf("Select 8 for %-30s\n", "Error Reporting and Total Compile time");
        printf("Select 9 for %-30s\n", "Intermediate Code Generation");
        printf("Enter a Number: ");
        scanf("%d", &newnum);
        if (newnum == 0)
        {
             end1=time(NULL);
            taken1=end1-start1;
            printf("Total time in the program %ld seconds \n", taken1);
            exit(0);
        }
        if (newnum == 1)
        {
            start2=time(NULL);
            FILE *fp;
            fp = fopen("t2.txt", "r");
            tokenise(fp);
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for tokenising %ld seconds  \n",taken2);
        }
        if (newnum == 2)
        {

            start2=time(NULL);
            printparsetetree(new);
            printf("\nParsing Phase Over \n");
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for printing parsetree %ld seconds  \n",taken2);
        }
        if (newnum == 3)
        {

            start2=time(NULL);
            printf("LEVEL ORDER TRAVERSAL BEING USED \n\n");
            printast(new->astaddr);
            printf("\nAST BUILT\n");
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for printing ast %ld seconds  \n",taken2);
        }
        if (newnum == 4)
        {
            start2=time(NULL);
            printmemcount();
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for printing ast %ld seconds  \n",taken2);
        }
        if (newnum == 5)
        {
            start2=time(NULL);
            printallsymboltables(new);
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for printing symboltable %ld seconds  \n",taken2);
        }
        if (newnum == 6)
        {
            start2=time(NULL);
            printactivationrecord();
            //semantics(new->astaddr);
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for printing activation records %ld seconds  \n",taken2);
        }
        if (newnum == 7)
        {
            start2=time(NULL);
            customprint(new);
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for printing static and dynamic Arrays %ld seconds  \n",taken2);
        }
        if (newnum == 8)
        {
            start2=time(NULL);
            if(semantics(new->astaddr)){
                printf("Semantic check successful\n");
            }
            else{
                printf("Inavalid Semantics\n");
            }
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for semantic check %ld seconds  \n",taken2);
        }

        if (newnum == 9)
        {
            start2=time(NULL);
            astpostordertraverse(new->astaddr);
            end2=time(NULL);
            taken2=end2-start2;
            printf("Time taken for intermediate code  generation%ld seconds  \n",taken2);
        }
    }
}