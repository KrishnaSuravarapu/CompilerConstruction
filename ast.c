// 2017A7PS0222P- Abhishek Reddy
// 2017A7PS0237P - Krishna Suravarapu
// 2017A7PS0076P - Shiva Krishna
// 2017A7PS0037P - Aqeel Shaik 
// 2017A7PS0119P - Surya Sumanth

#include "ast.h"
#include "lexerDef.h"
int *newlen;
astree **astfinal;
astree *createastnode(char *label)
{
  astree *new;
  new = malloc(sizeof(astree));
  strcpy(new->label, label);
  strcpy(new->lexval, "");
  new->sibling = NULL;
  new->childhead = NULL;
  new->parent = NULL;
  new->symtab = NULL;
  new->symboltabpointer = NULL;
  astnode_count++;
  return new;
}
void *astreenodegen(parsetree *node)
{

  switch (node->rulenum)
  {
  case 1:
    //printf("hashvalue of random is %d\n ",hashFunction("pasrogram"));
    node->astaddr = createastnode(node->node);

    for (int i = 0; i < node->no_of_childs; i++)
    {
      node->child[i]->astaddr = createastnode(node->child[i]->node);
      //printf("node created for %s\n",node->child[i]->node);
      node->child[i]->astaddr->parent = node->astaddr;
    }
    //node->astaddr->parent = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = node->child[3]->astaddr;
    node->child[3]->astaddr->sibling = NULL;

    break;

  case 2:
    //printf(" \n hi bruh %d \n",node->rulenum);
    if (strcmp(node->parent->node, "<program>") == 0)
    {
      //printf("up here once bruh -------------\n");
      //printf("---------------------------in if parent is %s \n",node->parent->node);
      node->child[0]->astaddr = createastnode(node->child[0]->node);
      node->child[0]->astaddr->parent = node->astaddr;
      node->astaddr->childhead = node->child[0]->astaddr;
      // node->child[1]->astaddr=createastnode(node->child[1]->node);
      // node->child[1]->astaddr->parent=node->astaddr;
      // node->astaddr->no_of_childs++;
    }
    else
    {
      //printf("-----------------------------in else parent is %s\n",node->parent->node);
      node->child[0]->astaddr = createastnode(node->child[0]->node);
      node->parent->child[0]->astaddr->sibling = node->child[0]->astaddr;
      node->child[0]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->child[0]->astaddr->sibling = NULL;
    }
    //printf("done ast\n");
    break;

  case 3:
    //printf(" \n hi bruh %d \n",node->rulenum);
    //printf("here mate look\n");
    break;

  case 4:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[2]->astaddr = createastnode("ID");
    node->child[2]->astaddr->parent = node->astaddr;
    node->astaddr->childhead = node->child[2]->astaddr;
    strcpy(node->child[2]->astaddr->lexval, node->child[2]->value);
    break;

  case 5:
    //printf(" \n hi bruh %d \n",node->rulenum);
    if (strcmp(node->parent->node, "<program>") == 0)
    {
      //printf("---------------------------in if parent is %s \n",node->parent->node);
      //printf("node here is %s\n\n\n",node->node);
      //printf("yes up here once\n");
      node->child[0]->astaddr = createastnode(node->child[0]->node);
      node->child[0]->astaddr->parent = node->astaddr;
      node->astaddr->childhead = node->child[0]->astaddr;
      // node->child[1]->astaddr=createastnode(node->child[1]->node);
      // node->child[1]->astaddr->parent=node->astaddr;
      // node->astaddr->no_of_childs++;
    }
    else
    {
      //printf("---------------------------in else parent is %s \n",node->parent->node);
      //printf("------------------------------------parent is %s\n",node->parent->node);
      //printf("---------------------------------------in else mate");
      node->child[0]->astaddr = createastnode(node->child[0]->node);
      node->parent->child[0]->astaddr->sibling = node->child[0]->astaddr;
      node->child[0]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->child[0]->astaddr->sibling = NULL;
    }
    break;

  case 6:
    //printf(" \n hi bruh %d \n",node->rulenum);
    break;

  case 7:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[4]->astaddr = createastnode("<moduleDef>");
    node->astaddr->childhead = node->child[4]->astaddr;
    node->child[4]->astaddr->parent = node->astaddr;
    break;

  case 8:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[7]->astaddr = createastnode(node->child[7]->node);
    node->child[10]->astaddr = createastnode(node->child[10]->node);
    node->child[11]->astaddr = createastnode(node->child[11]->node);
    node->child[2]->astaddr->sibling = node->child[7]->astaddr;
    node->child[7]->astaddr->sibling = node->child[10]->astaddr;
    node->child[10]->astaddr->sibling = node->child[11]->astaddr;
    node->child[11]->astaddr->sibling = NULL;
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[7]->astaddr->parent = node->astaddr;
    node->child[10]->astaddr->parent = node->astaddr;
    node->child[11]->astaddr->parent = node->astaddr;
    node->astaddr->childhead = node->child[2]->astaddr;
    strcpy(node->child[2]->astaddr->lexval, node->child[2]->value);
    break;

  case 9:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[2]->astaddr->parent = node->astaddr;
    node->astaddr->childhead = node->child[2]->astaddr;
    break;

  case 10:
    //printf(" \n hi bruh %d \n",node->rulenum);
    break;

  case 11:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    break;

  case 12:
    //printf(" \n hi bruh %d \n",node->rulenum);
    // astree* head;
    // head=node->parent->astaddr->childhead;
    // while(head!=NULL){
    //     head=head->
    // }
    if (strcmp(node->parent->node, "<input_plist>") == 0)
    {

      node->child[1]->astaddr = createastnode(node->child[1]->node);
      node->child[3]->astaddr = createastnode(node->child[3]->node);
      node->child[1]->astaddr->sibling = node->child[3]->astaddr;
      node->parent->child[2]->astaddr->sibling = node->child[1]->astaddr;
      node->child[1]->astaddr->parent = node->parent->astaddr;
      node->child[3]->astaddr->parent = node->parent->astaddr;
      strcpy(node->child[1]->astaddr->lexval, node->child[1]->value);
    }
    if (strcmp(node->parent->node, "<N1>") == 0)
    {

      node->child[1]->astaddr = createastnode(node->child[1]->node);
      node->child[3]->astaddr = createastnode(node->child[3]->node);
      node->child[1]->astaddr->sibling = node->child[3]->astaddr;
      node->parent->child[3]->astaddr->sibling = node->child[1]->astaddr;
      node->child[1]->astaddr->parent = node->parent->child[3]->astaddr->parent;
      node->child[1]->astaddr->parent = node->parent->child[3]->astaddr->parent;
      strcpy(node->child[1]->astaddr->lexval, node->child[1]->value);
    }
    break;

  case 13:
    //printf(" \n hi bruh %d \n",node->rulenum);
    break;

  case 14:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    break;

  case 15:
    //printf(" \n hi bruh %d \n",node->rulenum);
    // astree* head;
    // head=node->parent->astaddr->childhead;
    // while(head!=NULL){
    //     head=head->
    // }
    if (strcmp(node->parent->node, "<output_plist>") == 0)
    {

      node->child[1]->astaddr = createastnode(node->child[1]->node);
      node->child[3]->astaddr = createastnode(node->child[3]->node);
      node->parent->child[2]->astaddr->sibling = node->child[1]->astaddr;
      node->parent->child[2]->astaddr->sibling->sibling = node->child[3]->astaddr;
      node->parent->child[2]->astaddr->sibling->parent = node->parent->astaddr;
      node->parent->child[2]->astaddr->sibling->sibling->parent = node->parent->astaddr;
      node->parent->child[2]->astaddr->sibling->sibling->sibling = NULL;
      strcpy(node->child[1]->astaddr->lexval, node->child[1]->value);
    }
    if (strcmp(node->parent->node, "<N2>") == 0)
    {
      //("parent node for %d is %s \n",node->rulenum,node->parent->node);
      node->child[1]->astaddr = createastnode(node->child[1]->node);
      node->child[3]->astaddr = createastnode(node->child[3]->node);
      node->parent->child[3]->astaddr->sibling = node->child[1]->astaddr;
      node->parent->child[3]->astaddr->sibling->sibling = node->child[3]->astaddr;
      node->parent->child[3]->astaddr->sibling->parent = node->parent->astaddr;
      node->parent->child[3]->astaddr->sibling->sibling->parent = node->parent->astaddr;
      node->parent->child[3]->astaddr->sibling->sibling->sibling = NULL;
      strcpy(node->child[1]->astaddr->lexval, node->child[1]->value);
    }
    break;

  case 16:
    //printf(" \n hi bruh %d \n",node->rulenum);
    break;

  case 17:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[5]->astaddr = createastnode(node->child[5]->node);
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[5]->astaddr->parent = node->astaddr;
    node->astaddr->isarray = true;
    node->child[2]->astaddr->sibling = node->child[5]->astaddr;
    node->child[5]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[2]->astaddr;
    break;

  case 18:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 19:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    break;

  case 20:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    break;

  case 21:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->parent = node->astaddr;
    node->astaddr->isarray = true;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;

  case 22:
    if (node->astaddr == NULL)
    {
      //("node is %s and parent is %s \n",node->node,node->parent->node);
      //("yes\n");
    }
    node->astaddr->type = INTEGER;
    //printf(" \n hi bruh %d \n",node->rulenum);
    break;

  case 23:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->astaddr->type = REAL;
    break;

  case 24:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->astaddr->type = BOOLEAN;
    break;

  case 25:
  case 61:
  case 78:
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[1]->astaddr->parent = node->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[1]->astaddr;
    //printf(" \n hi bruh %d \n",node->rulenum);
    break;

  case 26:
    //printf(" \n hi bruh %d ds\n",node->rulenum);
    if (strcmp(node->parent->node, "<moduleDef>") == 0 || strcmp(node->parent->node, "<iterativeStmt>") == 0 || strcmp(node->parent->node, "<N9>") == 0 || strcmp(node->parent->node, "<caseStmts>") == 0 || strcmp(node->parent->node, "<default>") == 0)
    {
      //("26 if\n");
      node->child[0]->astaddr = createastnode(node->child[0]->node);

      node->child[0]->astaddr->parent = node->astaddr;

      node->astaddr->childhead = node->child[0]->astaddr;

      // node->child[1]->astaddr=createastnode(node->child[1]->node);
      // node->child[1]->astaddr->parent=node->astaddr;
      // node->astaddr->no_of_childs++;
    }
    else
    {
      //("26 else\n");
      node->child[0]->astaddr = createastnode(node->child[0]->node);
      //("26 else 1\n");
      //("parent node is %s sibling is %s\n",node->parent->node,node->parent->child[0]->node);
      node->parent->child[0]->astaddr->sibling = node->child[0]->astaddr;
      //("26 else 2\n");
      node->child[0]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      //("26 else 3\n");
      node->child[0]->astaddr->sibling = NULL;
    }
    //("26 ended\n");
    break;

  case 27:
    //printf(" \n hi bruh %d\n",node->rulenum);
    break;

  case 28:
  case 29:
  case 30:
  case 31:
  case 32:
  case 33:
  case 79:

    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    //printf(" \n hi bruh %d\n",node->rulenum);
    break;

  case 34:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[2]->astaddr->lexval, node->child[2]->value);
    break;

  case 35:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 36:
  case 98:
    //("node is %s parent node is %s\n",node->node,node->parent->node);
    node->astaddr->booleanvalue = true;
    strcpy(node->astaddr->lexval, "true");
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 37:
  case 99:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    strcpy(node->astaddr->lexval, "false");
    node->astaddr->booleanvalue = false;
    break;

  case 38:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 39:
  case 97:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;

    node->child[0]->astaddr->sibling = NULL;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    node->child[0]->astaddr->type = INTEGER;
    //("child 0 is %s\n",node->child[0]->node);
    //("\naddress is %d head is %s grand head is %s\n\n",node->astaddr,node->node,node->parent->node);
    node->astaddr->childhead = node->child[0]->astaddr;
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 40:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    node->child[0]->astaddr->type = REAL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 41:
  case 42:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 43:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->parent->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->parent = node->parent->child[0]->astaddr->parent;
    node->parent->child[0]->astaddr->isarray = true;
    break;

  case 44:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 45:
  case 46:
  case 58:
  case 59:
  case 62:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 47:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[1]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    break;

  case 60:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[1]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 48:
  case 49:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 50:
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[1]->astaddr->parent = node->parent->parent->child[1]->astaddr->parent;
    node->child[1]->astaddr->sibling = NULL;
    node->parent->parent->child[1]->astaddr->sibling = node->child[1]->astaddr;
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 51:
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[4]->astaddr = createastnode(node->child[4]->node);
    node->child[1]->astaddr->parent = node->parent->parent->child[1]->astaddr->parent;
    node->child[4]->astaddr->parent = node->parent->parent->child[1]->astaddr->parent;
    node->child[1]->astaddr->sibling = node->child[4]->astaddr;
    node->child[4]->astaddr->sibling = NULL;
    node->parent->parent->child[1]->astaddr->sibling = node->child[1]->astaddr;
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 52:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[3]->astaddr = createastnode(node->child[3]->node);
    node->child[6]->astaddr = createastnode(node->child[6]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[3]->astaddr->parent = node->astaddr;
    node->child[6]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[3]->astaddr;
    node->child[3]->astaddr->sibling = node->child[6]->astaddr;
    node->child[6]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[3]->astaddr->lexval, node->child[3]->value);
    break;

  case 53:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[1]->astaddr->parent = node->astaddr;
    node->astaddr->childhead = node->child[1]->astaddr;
    break;

  case 54:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 55:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    node->child[0]->astaddr->sibling = NULL;
    break;

  case 65:
  case 66:
  case 67:
  case 72:
  case 75:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 56:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    strcpy(node->child[1]->astaddr->lexval, node->child[1]->value);

    if (strcmp(node->parent->node, "<idList>") == 0)
    {
      //printf("-------------------------------in if parent is %s\n",node->parent->node);
      node->child[1]->astaddr->parent = node->parent->astaddr;
      node->parent->astaddr->childhead->sibling = node->child[1]->astaddr;
      node->child[1]->astaddr->sibling = NULL;
    }
    else
    {
      //printf("-------------------------------in else parent is %s\n",node->parent->node);

      node->child[1]->astaddr->parent = node->parent->child[1]->astaddr->parent;
      if (node->parent->child[1]->astaddr != NULL)
      {
        //printf("------------------------------assigning to already created uper %s and parent label is %s\n",node->parent->child[1]->node,node->child[1]->astaddr->parent->label);
      }
      node->parent->child[1]->astaddr->sibling = node->child[1]->astaddr;
      node->child[1]->astaddr->sibling = NULL;
    }
    break;

  case 57:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 63:
  case 64:
  case 80:
  case 81:
  case 82:
  case 83:
  case 84:
  case 85:
  case 86:
  case 87:
  case 88:
  case 89:
  case 90:
  case 91:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    strcpy(node->astaddr->lexval, node->child[0]->value);
    break;

  case 68:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    //node->astaddr->childhead=node->child[0]->astaddr;
    // //printf(" \n hi bruh %d \n",node->rulenum);

    if (strcmp(node->parent->node, "<arithmeticOrBooleanExpr>") == 0)
    {
      node->child[0]->astaddr->parent = node->parent->astaddr;
      node->child[1]->astaddr->parent = node->parent->astaddr;
      node->parent->child[0]->astaddr->sibling = node->child[0]->astaddr;
    }
    else
    {
      node->child[0]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->child[1]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->parent->child[1]->astaddr->sibling = node->child[0]->astaddr;
    }
    break;

  case 69:
  case 71:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 70:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[0]->astaddr->parent = node->parent->child[0]->astaddr;
    node->child[1]->astaddr->parent = node->parent->child[0]->astaddr;
    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    node->parent->child[0]->astaddr->sibling = node->child[0]->astaddr;
    break;

  case 73:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[1]->astaddr = createastnode(node->child[1]->node);

    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    if (strcmp(node->parent->node, "<arithmeticExpr>") == 0)
    {
      node->child[0]->astaddr->parent = node->parent->astaddr;
      node->child[1]->astaddr->parent = node->parent->astaddr;
      node->parent->astaddr->childhead->sibling = node->child[0]->astaddr;
    }
    else
    {
      node->child[0]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->child[1]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->parent->child[1]->astaddr->sibling = node->child[0]->astaddr;
    }
    break;
  case 74:
  case 77:
  case 100:
  case 104:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    break;

  case 76:
    //printf(" \n hi bruh %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[0]->astaddr->sibling = node->child[1]->astaddr;
    node->child[1]->astaddr->sibling = NULL;
    if (strcmp(node->parent->node, "<term>") == 0)
    {
      node->child[0]->astaddr->parent = node->parent->astaddr;
      node->child[1]->astaddr->parent = node->parent->astaddr;
      node->parent->child[0]->astaddr->sibling = node->child[0]->astaddr;
    }
    else
    {
      node->child[0]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->child[1]->astaddr->parent = node->parent->child[0]->astaddr->parent;
      node->parent->child[1]->astaddr->sibling = node->child[0]->astaddr;
    }
    break;

  case 92:
  case 102:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[3]->astaddr = createastnode(node->child[3]->node);
    node->child[1]->astaddr->parent = node->astaddr;
    node->child[3]->astaddr->parent = node->astaddr;
    node->child[1]->astaddr->sibling = node->child[3]->astaddr;
    node->child[3]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[1]->astaddr;
    break;

  case 93:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[5]->astaddr = createastnode(node->child[5]->node);
    node->child[6]->astaddr = createastnode(node->child[6]->node);
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[5]->astaddr->parent = node->astaddr;
    node->child[6]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->sibling = node->child[5]->astaddr;
    node->child[5]->astaddr->sibling = node->child[6]->astaddr;
    strcpy(node->child[2]->astaddr->lexval, node->child[2]->value);
    node->child[6]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[2]->astaddr;
    break;

  case 94:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[5]->astaddr = createastnode(node->child[5]->node);
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[5]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = node->child[5]->astaddr;
    node->child[5]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[0]->astaddr;
    break;

  case 96:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[0]->astaddr->lexval, node->child[0]->value);
    strcpy(node->child[2]->astaddr->lexval, node->child[2]->value);
    strcpy(node->astaddr->start, node->child[0]->value);
    strcpy(node->astaddr->end, node->child[2]->value);
    break;

  case 101:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[1]->astaddr = createastnode(node->child[1]->node);
    node->child[3]->astaddr = createastnode(node->child[3]->node);
    node->child[1]->astaddr->sibling = node->child[3]->astaddr;
    node->child[3]->astaddr->sibling = NULL;
    if (strcmp(node->parent->node, "<caseStmts>") == 0)
    {
      //("in if\n");
      node->child[1]->astaddr->parent = node->parent->astaddr;
      node->child[3]->astaddr->parent = node->parent->astaddr;
      //("in if almost\n");
      node->parent->astaddr->childhead->sibling->sibling = node->child[1]->astaddr;
    }
    else
    {
      //("in else\n");
      node->child[1]->astaddr->parent = node->parent->child[1]->astaddr->parent;
      node->child[3]->astaddr->parent = node->parent->child[1]->astaddr->parent;
      node->parent->child[3]->astaddr->sibling = node->child[1]->astaddr;
    }
    //printf(" \n hi bruh ended  %d \n",node->rulenum);
    break;

  case 103:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->sibling = NULL;
    node->astaddr->childhead = node->child[2]->astaddr;
    //node->parent->child[5]->astaddr->sibling = node->child[0]->astaddr;
    break;

  case 95:
    //printf(" \n hi bruh   %d \n",node->rulenum);
    node->child[0]->astaddr = createastnode(node->child[0]->node);
    node->child[2]->astaddr = createastnode(node->child[2]->node);
    node->child[4]->astaddr = createastnode(node->child[4]->node);
    node->child[7]->astaddr = createastnode(node->child[7]->node);
    node->child[0]->astaddr->sibling = node->child[2]->astaddr;
    node->child[2]->astaddr->sibling = node->child[4]->astaddr;
    node->child[4]->astaddr->sibling = node->child[7]->astaddr;
    node->child[7]->astaddr->sibling = NULL;
    node->child[0]->astaddr->parent = node->astaddr;
    node->child[2]->astaddr->parent = node->astaddr;
    node->child[4]->astaddr->parent = node->astaddr;
    node->child[7]->astaddr->parent = node->astaddr;
    node->astaddr->childhead = node->child[0]->astaddr;
    strcpy(node->child[2]->astaddr->lexval, node->child[2]->value);
    break;

  default:
    break;
  }
}

idsymboltable *initialisesymtab(idsymboltable *nestedparent)
{
  idsymboltable *symboltab;
  symboltab = malloc(sizeof(idsymboltable));
  symboltab->head = NULL;
  symboltab->nestedparent = nestedparent;
  if (nestedparent == NULL)
  {
    symboltab->nestinglevel = 0;
  }
  else
  {
    symboltab->nestinglevel = nestedparent->nestinglevel + 1;
  }

  int i = 0;
  symboltab->head = malloc(sizeof(idsymboltable *) * 30);
  while (i < 30)
  {
    symboltab->head[i] = NULL;
    i++;
  }
  //printf("symboltable initialised\n");
  return symboltab;
}

symfuncentry **initialisefunctable()
{
  symfuncentry **functiontabl;
  functiontabl = malloc(sizeof(symfuncentry *) * 30);
  for (int k = 0; k < 30; k++)
  {
    functiontabl[k] = NULL;
  }
  return functiontabl;
}

void putintosymboltable(idsymboltable *symboltab, parsetree *parsenode)
{
  int hashvalue = hashFunction(parsenode->value);
  symidentry *startpointer = symboltab->head[hashvalue];
  if (startpointer == NULL)
  {
    symboltab->head[hashvalue] = malloc(sizeof(symidentry));
    strcpy(symboltab->head[hashvalue]->name, parsenode->value);
    symboltab->head[hashvalue]->next = NULL;
    symboltab->head[hashvalue]->assigned = false;
    symboltab->head[hashvalue]->active = false;
    strcpy(parsenode->astaddr->namechanged,parsenode->value);
    strcat(parsenode->astaddr->namechanged,"_");
    strncat(parsenode->astaddr->namechanged,symboltab->modulename,5);
    //strncpy(symboltab->modulename);
  }
  else
  {
    //printf("2nd part\n");
    int j = 1;
    while (startpointer->next != NULL && strcmp(startpointer->name, parsenode->value) != 0)
    {
      startpointer = startpointer->next;
      j++;
    }
    if (strcmp(startpointer->name, parsenode->value) != 0)
    {
      startpointer->next = malloc(sizeof(symidentry));
      strcpy(startpointer->next->name, parsenode->value);
      startpointer->next->next = NULL;
      startpointer->next->assigned = false;
      startpointer->next->active = false;
      strcpy(parsenode->astaddr->namechanged,parsenode->value);
      strcat(parsenode->astaddr->namechanged,"_");
    strncat(parsenode->astaddr->namechanged,symboltab->modulename,5);
    }
    else
    {
      // startpointer->
      printf("Multiple declarations of same variable i.e., %s sorry\n", parsenode->value);
      //exit(0);
    }
    //printf("Inserted after %d nodes",j);
  }
  //printf("Node is %s hashvalue is %d \n",parsenode->node,hashvalue);
  //printf("Assigned successfully\n");
}

void putintofunctable(symfuncentry **functiontable, parsetree *parsenode)
{
  //printf("=====================================================================here module name is %s\n",parsenode->value);
  int hashvalue = hashFunction(parsenode->value);
  //printf("its hashvalue is %d\n",hashvalue);
  symfuncentry *startpointer;
  if (functiontable[hashvalue] == NULL)
  {
    //printf("====================================================================================if\n");
    functiontable[hashvalue] = malloc(sizeof(symfuncentry));
    startpointer = functiontable[hashvalue];
    functiontable[hashvalue]->next = NULL;
    strcpy(functiontable[hashvalue]->name, parsenode->value);
    functiontable[hashvalue]->input_no = 0;
    functiontable[hashvalue]->output_no = 0;
    functiontable[hashvalue]->inputparam = NULL;
    functiontable[hashvalue]->outputparam = NULL;
    //printfunctiontable(functiontable);
  }
  else
  {
    //printf("========================================================================================2nd part\n");
    int j = 1;
    startpointer = functiontable[hashvalue];
    while (startpointer->next != NULL)
    {
      startpointer = startpointer->next;
      j++;
    }
    startpointer->next = malloc(sizeof(symfuncentry));
    strcpy(startpointer->next->name, parsenode->value);
    startpointer->next->next = NULL;
    //printf("Inserted after %d nodes",j);
    startpointer->next->input_no = 0;
    startpointer->next->output_no = 0;
    startpointer->next->inputparam = NULL;
    startpointer->next->outputparam = NULL;
  }
}

symidentry *getinfoofsymbol(idsymboltable *symboltab, char *id)
{
  int hashvalue = hashFunction(id);
  //printf("to be searched for %s having hashval%d\n",id,hashvalue);
  idsymboltable *tablecopy = symboltab;
  while (tablecopy != NULL)
  {
    symidentry *entry;
    entry = tablecopy->head[hashvalue];
    while (entry != NULL)
    {
      if (strcmp(entry->name, id) == 0)
      {
        //printf("matched is %s \n", entry->name);
        return entry;
      }
      entry = entry->next;
    }
    //printf("time to check its parent\n");
    tablecopy = tablecopy->nestedparent;
  }
  return NULL;
}

symfuncentry *getinfooffunction(symfuncentry **functiontable, char *id)
{
  int hashvalue = hashFunction(id);
  //printf("to be searched for %s having hashval%d\n",id,hashvalue);
  symfuncentry *entrycopy;
  entrycopy = functiontable[hashvalue];
  while (entrycopy != NULL)
  {
    if (strcmp(entrycopy->name, id) == 0)
    {
      return entrycopy;
    }
    entrycopy = entrycopy->next;
  }
  return NULL;
}

void printsymboltable(idsymboltable *symboltab)
{
  int i = 0;
  symidentry *entry;
  while (i < 30)
  {
    entry = symboltab->head[i];

    while (entry != NULL)
    {
      printf("%-20s   %-20s    %2d - %-15d   ", entry->name, symboltab->modulename, symboltab->startline, symboltab->endline);
      if (entry->type == INTEGER)
      {
        if (entry->isarray != true)
        {
          printf("%-15s", "4");
        }
        else if (entry->isarray == true && entry->dynamic == 0)
        {
          printf("%-15d", (entry->endindex - entry->startindex + 1) * 2 + 1);
        }
        else
        {
          printf("%-15s", "5");
        }
      }
      if (entry->type == REAL)
      {
        if (entry->isarray != true)
        {
          printf("%-15s", "4");
        }
        else if (entry->isarray == true && entry->dynamic == 0)
        {
          printf("%-15d", (entry->endindex - entry->startindex + 1) * 4 + 1);
        }
        else
        {
          printf("%-15s", "5");
        }
      }
      if (entry->type == BOOLEAN)
      {
        if (entry->isarray != true)
        {
          printf("%-15s", "4");
        }
        else if (entry->isarray == true && entry->dynamic == 0)
        {
          printf("%-15d", (entry->endindex - entry->startindex + 1) + 1);
        }
        else
        {
          printf("%-15s", "5");
        }
      }

      if (entry->isarray == true)
      {
        printf("%-15s", "Yes");
        if (entry->dynamic == 0)
        {
          printf("%-20s", "Static");
        }
        else
        {
          printf("%-20s", "Dynamic");
        }
        if (entry->dynamic == 0)
        {
          printf("[%d,%2d%-18s", entry->startindex, entry->endindex, "]");
        }
        if (entry->dynamic == 1)
        {
          printf("[%d, %2s%-18s", entry->startindex, entry->indexid[1]->name, "]");
        }
        if (entry->dynamic == 2)
        {
          printf("[%s,%2d%-18s", entry->indexid[0]->name, entry->endindex, "]");
        }
        if (entry->dynamic == 3)
        {
          printf("[%s,%2s %-18s", entry->indexid[0]->name, entry->indexid[1]->name, "]");
        }
      }
      else
      {
        printf("%-18s", "No");
        printf("%-20s", "--");
        printf("%-20s", "--");
      }
      if (entry->type == REAL)
      {
        printf("%-20s", "REAL");
      }
      if (entry->type == INTEGER)
      {
        printf("%-20s", "INTEGER");
      }
      if (entry->type == BOOLEAN)
      {
        printf("%-20s", "BOOLEAN");
      }
      printf("%d\n", symboltab->nestinglevel);
      entry = entry->next;
    }

    i++;
  }
}
void printcustomsymboltable(idsymboltable *symboltab)
{
  int i = 0;
  symidentry *entry;
  while (i < 30)
  {
    entry = symboltab->head[i];

    while (entry != NULL)
    {
      if(entry->isarray==true){
      printf("%-20s   %-20s    %2d - %-15d   ", entry->name, symboltab->modulename, symboltab->startline, symboltab->endline);
      if (entry->type == INTEGER)
      {
        if (entry->isarray != true)
        {
          printf("%-15s", "4");
        }
        else if (entry->isarray == true && entry->dynamic == 0)
        {
          printf("%-15d", (entry->endindex - entry->startindex + 1) * 2 + 1);
        }
        else
        {
          printf("%-15s", "5");
        }
      }
      if (entry->type == REAL)
      {
        if (entry->isarray != true)
        {
          printf("%-15s", "4");
        }
        else if (entry->isarray == true && entry->dynamic == 0)
        {
          printf("%-15d", (entry->endindex - entry->startindex + 1) * 4 + 1);
        }
        else
        {
          printf("%-15s", "5");
        }
      }
      if (entry->type == BOOLEAN)
      {
        if (entry->isarray != true)
        {
          printf("%-15s", "4");
        }
        else if (entry->isarray == true && entry->dynamic == 0)
        {
          printf("%-15d", (entry->endindex - entry->startindex + 1) + 1);
        }
        else
        {
          printf("%-15s", "5");
        }
      }

      if (entry->isarray == true)
      {
        printf("%-15s", "Yes");
        if (entry->dynamic == 0)
        {
          printf("%-20s", "Static");
        }
        else
        {
          printf("%-20s", "Dynamic");
        }
        if (entry->dynamic == 0)
        {
          printf("[%d,%2d%-18s", entry->startindex, entry->endindex, "]");
        }
        if (entry->dynamic == 1)
        {
          printf("[%d, %2s%-18s", entry->startindex, entry->indexid[1]->name, "]");
        }
        if (entry->dynamic == 2)
        {
          printf("[%s,%2d%-18s", entry->indexid[0]->name, entry->endindex, "]");
        }
        if (entry->dynamic == 3)
        {
          printf("[%s,%2s %-18s", entry->indexid[0]->name, entry->indexid[1]->name, "]");
        }
      }
      else
      {
        printf("%-18s", "No");
        printf("%-20s", "--");
        printf("%-20s", "--");
      }
      if (entry->type == REAL)
      {
        printf("%-20s", "REAL");
      }
      if (entry->type == INTEGER)
      {
        printf("%-20s", "INTEGER");
      }
      if (entry->type == BOOLEAN)
      {
        printf("%-20s", "BOOLEAN");
      }
      printf("%d\n", symboltab->nestinglevel);
      }
      entry = entry->next;
    }

    i++;
  }
}
void printfunctiontable(symfuncentry **functiontable)
{
  int i = 0;
  symfuncentry *entry;
  while (i < 30)
  {
    entry = functiontable[i];
    printf("%d .", i + 1);
    while (entry != NULL)
    {
      printf("Name:-  %s  OutputNo:- %d InputNo %d ", entry->name, entry->output_no, entry->input_no);
      entry = entry->next;
    }
    i++;
    printf("\n");
  }
}

void populatefunctiontable(parsetree *parsenode)
{
  if (strcmp(parsenode->node, "ID") == 0 && parsenode->parent != NULL && strcmp(parsenode->parent->node, "<moduleDeclaration>") == 0)
  {
    //printf("yes moduledec parent for id %s and parent module is %s\n",parsenode->node,parsenode->parent->node);
    putintofunctable(functiontable, parsenode);
    //printfunctiontable(functiontable);
    //printf("\n\n\n");
    //printf("yo done\n");
    //printfunctiontable(functiontable);
  }
}

void populatesymboltable(parsetree *parsenode)
{
  parsetree *nodecopy;

  if (strcmp(parsenode->node, "<moduleDef>") == 0)
  {
    //printf("AT moduledef\n");
    //printf("node is %s and parent is %s\n", parsenode->node, parsenode->parent->node);
    parsenode->child[1]->astaddr->symtab = initialisesymtab(NULL);
    if (strcmp(parsenode->parent->node, "<driverModule>") == 0)
    {
      strcpy(parsenode->child[1]->astaddr->symtab->modulename, "Driver");
    }
    else
    {
      symfuncentry* respentry;
      respentry=getinfooffunction(functiontable,parsenode->parent->child[2]->value);
      if(respentry!=NULL)
      respentry->symtable=parsenode->child[1]->astaddr->symtab;
      else{
        putintofunctable(functiontable,parsenode->parent->child[2]);
        respentry=getinfooffunction(functiontable,parsenode->parent->child[2]->value);
        respentry->symtable=parsenode->child[1]->astaddr->symtab;
      }
      strcpy(parsenode->child[1]->astaddr->symtab->modulename, parsenode->parent->child[2]->value);
      //if(respentry==NULL)
    }
    parsenode->child[1]->astaddr->symtab->startline = parsenode->child[0]->linenum;
    parsenode->child[1]->astaddr->symtab->endline = parsenode->child[2]->linenum;
    //printf("ended\n\n");
  }

  if (strcmp(parsenode->node, "START") == 0 && strcmp(parsenode->parent->node, "<moduleDef>") != 0)
  {
    //printf("case1\n");
    //printf("start and parent not moduledef\n");
    nodecopy = parsenode;
    //printf("node is %s and parent is %s\n", nodecopy->node, nodecopy->parent->node);
    while (nodecopy != NULL && strcmp(nodecopy->node, "<statements>") != 0)
    {
      nodecopy = nodecopy->parent;
    }

    //printf("while done and currently node copy is %s and its parent is %s\n",nodecopy->node,nodecopy->parent->node);

    if (nodecopy == NULL)
    {
      //printf("Nodecopy Null\n");
    }
    if (strcmp(nodecopy->parent->node, "<statements>") == 0)
    {
      //printf("in if stmts node is %s and parent node is %s\n", nodecopy->node, nodecopy->parent->node);
      //printf("in stmts \n");
      while (strcmp(nodecopy->parent->node, "<statements>") == 0)
      {
        nodecopy = nodecopy->parent;
      }
      if (strcmp(parsenode->parent->node, "<iterativeStmt>") == 0 && strcmp(parsenode->parent->child[0]->node, "WHILE") == 0)
      {
        //printf("parent is iterative while and parent is not case stmt\n");
        parsenode->parent->child[5]->astaddr->symtab = initialisesymtab(nodecopy->astaddr->symtab);
        if (nodecopy->astaddr->symtab != NULL)
        {
          strcpy(parsenode->parent->child[5]->astaddr->symtab->modulename, nodecopy->astaddr->symtab->modulename);
        }
        parsenode->parent->child[5]->astaddr->symtab->startline = parsenode->parent->child[4]->linenum;
        parsenode->parent->child[5]->astaddr->symtab->endline = parsenode->parent->child[6]->linenum;
      }
      if (strcmp(parsenode->parent->node, "<iterativeStmt>") == 0 && strcmp(parsenode->parent->child[0]->node, "FOR") == 0)
      {
        //printf("parent is iterative for and parent is not case stmt\n");
        //printf(" no of childs is %d \n",parsenode->parent->no_of_childs);
        //printf("nodecopy is %s and its parent is %s and grand parent is %s \n",nodecopy->node,nodecopy->parent->node,nodecopy->parent->parent->node);
        if (nodecopy->astaddr == NULL)
        {
          //printf("NULL nodecopy\n");
        }
        parsenode->parent->child[7]->astaddr->symtab = initialisesymtab(nodecopy->astaddr->symtab);
        if (nodecopy->astaddr->symtab != NULL)
        {
          strcpy(parsenode->parent->child[7]->astaddr->symtab->modulename, nodecopy->astaddr->symtab->modulename);
        }
        parsenode->parent->child[7]->astaddr->symtab->startline = parsenode->parent->child[6]->linenum;
        parsenode->parent->child[7]->astaddr->symtab->endline = parsenode->parent->child[8]->linenum;

        //printf("done\n");
      }
      if (strcmp(parsenode->parent->node, "<conditionalStmt>") == 0)
      {
        //printf("parent is iterative switch  and parent is not case stmt\n");
        parsenode->parent->child[5]->astaddr->symtab = initialisesymtab(nodecopy->astaddr->symtab);
        if (nodecopy->astaddr->symtab != NULL)
        {
          strcpy(parsenode->parent->child[5]->astaddr->symtab->modulename, nodecopy->astaddr->symtab->modulename);
        }
        parsenode->parent->child[5]->astaddr->symtab->startline = parsenode->parent->child[4]->linenum;
        parsenode->parent->child[5]->astaddr->symtab->endline = parsenode->parent->child[7]->linenum;
      }
    }
    else
    {
      //printf("in else stmts node is %s and parent node is %s\n", nodecopy->node, nodecopy->parent->node);
      while (strcmp(nodecopy->parent->node, "<statements>") == 0)
      {
        nodecopy = nodecopy->parent;
      }
      if (strcmp(parsenode->parent->node, "<iterativeStmt>") == 0 && strcmp(parsenode->parent->child[0]->node, "WHILE") == 0)
      {
        parsenode->parent->child[5]->astaddr->symtab = initialisesymtab(nodecopy->astaddr->symtab);
        if (nodecopy->astaddr->symtab != NULL)
        {
          strcpy(parsenode->parent->child[5]->astaddr->symtab->modulename, nodecopy->astaddr->symtab->modulename);
        }
        parsenode->parent->child[5]->astaddr->symtab->startline = parsenode->parent->child[4]->linenum;
        parsenode->parent->child[5]->astaddr->symtab->endline = parsenode->parent->child[6]->linenum;
        //printf("parent is iterative while and parent is case stmt\n");
      }
      if (strcmp(parsenode->parent->node, "<iterativeStmt>") == 0 && strcmp(parsenode->parent->child[0]->node, "FOR") == 0)
      {
        parsenode->parent->child[7]->astaddr->symtab = initialisesymtab(nodecopy->astaddr->symtab);
        if (nodecopy->astaddr->symtab != NULL)
        {
          strcpy(parsenode->parent->child[7]->astaddr->symtab->modulename, nodecopy->astaddr->symtab->modulename);
        }
        parsenode->parent->child[7]->astaddr->symtab->startline = parsenode->parent->child[6]->linenum;
        parsenode->parent->child[7]->astaddr->symtab->endline = parsenode->parent->child[8]->linenum;
        //printf("parent is iterative for and parent is case stmt\n");
      }
      if (strcmp(parsenode->parent->node, "<conditionalStmt>") == 0)
      {
        parsenode->parent->child[5]->astaddr->symtab = initialisesymtab(nodecopy->astaddr->symtab);
        if (nodecopy->astaddr->symtab != NULL)
        {
          strcpy(parsenode->parent->child[5]->astaddr->symtab->modulename, nodecopy->astaddr->symtab->modulename);
        }
        parsenode->parent->child[5]->astaddr->symtab->startline = parsenode->parent->child[4]->linenum;
        parsenode->parent->child[5]->astaddr->symtab->endline = parsenode->parent->child[7]->linenum;
        //printf("parent is iterative switch  and parent is case stmt\n");
      }
    }
    //printf("\n\n\n");
  }

  if (strcmp(parsenode->node, "ID") == 0 && strcmp(parsenode->parent->parent->node, "<declareStmt>") == 0 && strcmp(parsenode->parent->node, "<idList>") == 0)
  {
    //printf("case2\n");
    //printf("declare stmt encountered\n");
    parsetree *copynode;
    copynode = parsenode->parent->parent->parent;
    while (strcmp(copynode->node, "<statements>") != 0)
    {
      copynode = copynode->parent;
    }
    while (strcmp(copynode->parent->node, "<statements>") == 0)
    {
      copynode = copynode->parent;
    }
    if (strcmp(copynode->parent->node, "<N9>") == 0)
    {
      while (strcmp(copynode->node, "<caseStmts>") != 0)
      {
        copynode = copynode->parent;
      }
    }
    if (strcmp(copynode->parent->node, "<caseStmts>") == 0)
    {
      copynode = copynode->parent;
    }
    //printf("\n\n\n");
    //printf("Now it came upto %s's child i.e., %s\n", copynode->parent->node, copynode->node);
    //printf("name of id is %s \n", parsenode->value);
    if (strcmp(copynode->parent->node, "<default>") == 0)
    {
      copynode = copynode->parent->parent->child[5];
    }
    if (strcmp(parsenode->parent->parent->child[3]->child[0]->node, "ARRAY") == 0)
    {
      //printf("case3\n");
      //printf("type is %s\n", parsenode->parent->parent->child[3]->child[0]->node);
      putintosymboltable(copynode->astaddr->symtab, parsenode);
      symidentry *new;
      new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
      new->isarray = true;
      if (strcmp(parsenode->parent->parent->child[3]->child[5]->child[0]->node, "INTEGER") == 0)
        new->type = INTEGER;
      if (strcmp(parsenode->parent->parent->child[3]->child[5]->child[0]->node, "REAL") == 0)
        new->type = REAL;
      if (strcmp(parsenode->parent->parent->child[3]->child[5]->child[0]->node, "BOOLEAN") == 0)
        new->type = BOOLEAN;
      new->dynamic = 0;
      if (strcmp(parsenode->parent->parent->child[3]->child[2]->child[0]->child[0]->node, "NUM") == 0 && strcmp(parsenode->parent->parent->child[3]->child[2]->child[2]->child[0]->node, "NUM") == 0)
      {
        //printf("yes static array\n");
        new->dynamic = 0;
      }
      else
      {
        if (strcmp(parsenode->parent->parent->child[3]->child[2]->child[0]->child[0]->node, "NUM") != 0)
        {
          if (strcmp(parsenode->parent->parent->child[3]->child[2]->child[2]->child[0]->node, "NUM") != 0)
          {
            new->dynamic = 3;
          }
          new->dynamic = 2;
        }
        else
        {
          new->dynamic = 1;
        }
      }
      if (new->dynamic == 0)
      {
        new->startindex = atoi(parsenode->parent->parent->child[3]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = atoi(parsenode->parent->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
        new->indexid[0] = NULL;
        new->indexid[1] = NULL;
      }
      if (new->dynamic == 1)
      {
        new->startindex = atoi(parsenode->parent->parent->child[3]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = -1;
        new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
        new->indexid[0] = NULL;
      }
      if (new->dynamic == 2)
      {
        new->startindex = -1;
        new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->parent->child[3]->child[2]->child[0]->child[0]->value);
        new->indexid[1] = NULL;
        //printf("start index is %d \n", new->startindex);
        new->endindex = atoi(parsenode->parent->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
      }
      if (new->dynamic == 3)
      {
        new->startindex = -1;
        new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->parent->child[3]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = -1;
        new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
      }
    }
    else
    {
      //printf("type is %s\n", parsenode->parent->parent->child[3]->child[0]->child[0]->node);
      //printf("case2 else last encounterd\n");
      putintosymboltable(copynode->astaddr->symtab, parsenode);
      //printf("hi\n");
      symidentry *new;
      new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
      new->isarray = false;
      if (strcmp(parsenode->parent->parent->child[3]->child[0]->child[0]->node, "INTEGER") == 0)
        new->type = INTEGER;
      if (strcmp(parsenode->parent->parent->child[3]->child[0]->child[0]->node, "REAL") == 0)
        new->type = REAL;
      if (strcmp(parsenode->parent->parent->child[3]->child[0]->child[0]->node, "BOOLEAN") == 0)
        new->type = BOOLEAN;
    }
    //printsymboltable(copynode->astaddr->symtab);
    //printf("\n\n\n");
    parsenode->astaddr->symtab = copynode->astaddr->symtab;
  }

  if (strcmp(parsenode->node, "ID") == 0 && strcmp(parsenode->parent->node, "<N3>") == 0)
  {
    //printf("case4\n");
    parsetree *copynode;
    copynode = parsenode;
    while (copynode != NULL && copynode->parent != NULL && strcmp(copynode->parent->node, "<declareStmt>") != 0)
    {
      copynode = copynode->parent;
    }
    if (copynode == NULL || copynode->parent == NULL)
    {
      //
    }
    else
    {
      //printf("at last at node %s\n",copynode->parent->node);
      //printf("     %s      Multiple               declarations of type %s   \n",parsenode->value,copynode->parent->child[3]->child[0]->child[0]->node);
      //printf("hi\n");
    
      parsetree *node;
      parsetree *datatypenode;
      node = parsenode;
      datatypenode = copynode->parent->child[3];

      while (strcmp(copynode->node, "<statements>") != 0)
      {
        copynode = copynode->parent;
      }
      while (strcmp(copynode->parent->node, "<statements>") == 0)
      {
        copynode = copynode->parent;
      }
      if (strcmp(copynode->parent->node, "<N9>") == 0)
      {
        while (strcmp(copynode->node, "<caseStmts>") != 0)
        {
          copynode = copynode->parent;
        }
      }
      //printf("\n\n\n");
      //printf("Now it came upto %s's child i.e., %s\n", copynode->parent->node, copynode->node);

      if (strcmp(copynode->parent->node, "<default>") == 0)
      {
        copynode = copynode->parent->parent->child[5];
      }
      //printf("name of id is %s \n", parsenode->value);

      if (strcmp(datatypenode->child[0]->node, "ARRAY") == 0)
      {
       // printf("haaai-----------------------\n");
        //printf("type is %s\n",datatypenode->child[0]->child[0]->node);
        putintosymboltable(copynode->astaddr->symtab, node);
        symidentry *new;
        new = getinfoofsymbol(copynode->astaddr->symtab, node->value);
        new->isarray = true;
        if (strcmp(datatypenode->child[5]->child[0]->node, "INTEGER") == 0)
          new->type = INTEGER;
        if (strcmp(datatypenode->child[5]->child[0]->node, "REAL") == 0)
          new->type = REAL;
        if (strcmp(datatypenode->child[5]->child[0]->node, "BOOLEAN") == 0)
          new->type = BOOLEAN;
        new->dynamic = 0;
        if (strcmp(datatypenode->child[2]->child[0]->child[0]->node, "NUM") == 0 && strcmp(datatypenode->child[2]->child[2]->child[0]->node, "NUM") == 0)
        {
          //printf("yes static array\n");
          new->dynamic = 0;
        }
        else
        {
          if (strcmp(datatypenode->child[2]->child[0]->child[0]->node, "NUM") != 0)
          {
            if (strcmp(datatypenode->child[2]->child[2]->child[0]->node, "NUM") != 0)
            {
              new->dynamic = 3;
            }
            new->dynamic = 2;
          }
          else
          {
            new->dynamic = 1;
          }
        }
        if (new->dynamic == 0)
        {
          new->startindex = atoi(datatypenode->child[2]->child[0]->child[0]->value);
          //printf("start index is %d \n", new->startindex);
          new->endindex = atoi(datatypenode->child[2]->child[2]->child[0]->value);
          //printf("end index is %d \n", new->endindex);
          new->indexid[0] = NULL;
          new->indexid[1] = NULL;
        }
        if (new->dynamic == 1)
        {
          new->startindex = atoi(datatypenode->child[2]->child[0]->child[0]->value);
          //printf("start index is %d \n", new->startindex);
          new->endindex = -1;
          new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, datatypenode->child[2]->child[2]->child[0]->value);
          //printf("end index is %d \n", new->endindex);
          new->indexid[0] = NULL;
        }
        if (new->dynamic == 2)
        {
          new->startindex = -1;
          new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, datatypenode->child[2]->child[0]->child[0]->value);
          new->indexid[1] = NULL;
          //printf("start index is %d \n", new->startindex);
          new->endindex = atoi(datatypenode->child[2]->child[2]->child[0]->value);
          //printf("end index is %d \n", new->endindex);
        }
        if (new->dynamic == 3)
        {
          new->startindex = -1;
          new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, datatypenode->child[2]->child[0]->child[0]->value);
          //printf("start index is %d \n", new->startindex);
          new->endindex = -1;
          new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, datatypenode->child[2]->child[2]->child[0]->value);
          //printf("end index is %d \n", new->endindex);
        }
      }
      else
      {
        //printf("hoooooiiiiiiiii-------------------\n");
        //printf("type is %s\n", datatypenode->child[0]->child[0]->node);
        putintosymboltable(copynode->astaddr->symtab, node);
        symidentry *new;
        new = getinfoofsymbol(copynode->astaddr->symtab, node->value);
        new->isarray = false;
        if (strcmp(datatypenode->child[0]->child[0]->node, "INTEGER") == 0)
          new->type = INTEGER;
        if (strcmp(datatypenode->child[0]->child[0]->node, "REAL") == 0)
          new->type = REAL;
        if (strcmp(datatypenode->child[0]->child[0]->node, "BOOLEAN") == 0)
          new->type = BOOLEAN;
      }

      //printsymboltable(copynode->astaddr->symtab);
      //printf("\n\n\n");
    }
    parsenode->astaddr->symtab = copynode->astaddr->symtab;
  }

  if (strcmp(parsenode->node, "ID") == 0 && strcmp(parsenode->parent->node, "<input_plist>") == 0)
  {
    //printf("case5\n");
    parsetree *copynode;
    copynode = parsenode->parent->parent->child[11]->child[1];
    symfuncentry *functionentry;
    functionentry = getinfooffunction(functiontable, parsenode->parent->parent->child[2]->value);
    symidentry *new;
    if (strcmp(parsenode->parent->child[2]->child[0]->node, "ARRAY") == 0)
    {
      //printf("node is  %s\n", parsenode->value);
      putintosymboltable(copynode->astaddr->symtab, parsenode);
      new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
      new->isarray = true;
      if (strcmp(parsenode->parent->child[2]->child[5]->child[0]->node, "INTEGER") == 0)
        new->type = INTEGER;
      if (strcmp(parsenode->parent->child[2]->child[5]->child[0]->node, "REAL") == 0)
        new->type = REAL;
      if (strcmp(parsenode->parent->child[2]->child[5]->child[0]->node, "BOOLEAN") == 0)
        new->type = BOOLEAN;
      new->dynamic = 0;
      if (strcmp(parsenode->parent->child[2]->child[2]->child[0]->child[0]->node, "NUM") == 0 && strcmp(parsenode->parent->child[2]->child[2]->child[2]->child[0]->node, "NUM") == 0)
      {
        //printf("yes static array\n");
        new->dynamic = 0;
      }
      else
      {
        if (strcmp(parsenode->parent->child[2]->child[2]->child[0]->child[0]->node, "NUM") != 0)
        {
          if (strcmp(parsenode->parent->child[2]->child[2]->child[2]->child[0]->node, "NUM") != 0)
          {
            new->dynamic = 3;
          }
          new->dynamic = 2;
        }
        else
        {
          new->dynamic = 1;
        }
      }
      if (new->dynamic == 0)
      {
        new->startindex = atoi(parsenode->parent->child[2]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = atoi(parsenode->parent->child[2]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
        new->indexid[0] = NULL;
        new->indexid[1] = NULL;
      }
      if (new->dynamic == 1)
      {
        new->startindex = atoi(parsenode->parent->child[2]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = -1;
        new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[2]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
        new->indexid[0] = NULL;
      }
      if (new->dynamic == 2)
      {
        new->startindex = -1;
        new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[2]->child[2]->child[0]->child[0]->value);
        new->indexid[1] = NULL;
        //printf("start index is %d \n", new->startindex);
        new->endindex = atoi(parsenode->parent->child[2]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
      }
      if (new->dynamic == 3)
      {
        new->startindex = -1;
        new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[2]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = -1;
        new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[2]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
      }
      new->active=true;
    }
    else
    {
      //printf("type is %s\n", parsenode->parent->child[2]->child[0]->child[0]->node);
      putintosymboltable(copynode->astaddr->symtab, parsenode);
      new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
      new->isarray = false;
      if (strcmp(parsenode->parent->child[2]->child[0]->child[0]->node, "INTEGER") == 0)
        new->type = INTEGER;
      if (strcmp(parsenode->parent->child[2]->child[0]->child[0]->node, "REAL") == 0)
        new->type = REAL;
      if (strcmp(parsenode->parent->child[2]->child[0]->child[0]->node, "BOOLEAN") == 0)
        new->type = BOOLEAN;
      new->active=true;
    }
    parsenode->astaddr->symtab = copynode->astaddr->symtab;
    //printf("\n\n\n\n\nInput plist encountered for id  :- %s \n\n\n\n",parsenode->value);
    if (functionentry != NULL)
    {
      //printfunctiontable(functiontable);
      //printf("functionetry is for function %s\n",functionentry->name);
      functionentry->inputparam = malloc(sizeof(symidentry *));
      functionentry->input_no = 1;
      functionentry->inputparam[0] = new;
    }
    if (functionentry == NULL)
    {
      printf("NULL FUNCTION ENTRY FOR FUNCTION %s\n", parsenode->parent->parent->child[2]->value);
      exit(0);
    }
  }
  if (strcmp(parsenode->node, "ID") == 0 && strcmp(parsenode->parent->node, "<output_plist>") == 0)
  {
   // printf("case6\n");
    parsetree *copynode;
    symfuncentry *functionentry;
    //printf("value of function id is %s\n", parsenode->parent->parent->parent->child[2]->value);
    functionentry = getinfooffunction(functiontable, parsenode->parent->parent->parent->child[2]->value);
    copynode = parsenode->parent->parent->parent->child[11]->child[1];

    //printf("output type is %s\n", parsenode->parent->child[2]->child[0]->node);
    putintosymboltable(copynode->astaddr->symtab, parsenode);
    symidentry *new;
    new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
    new->isarray = false;
    new->active=true;
    if (strcmp(parsenode->parent->child[2]->child[0]->node, "INTEGER") == 0)
      new->type = INTEGER;
    if (strcmp(parsenode->parent->child[2]->child[0]->node, "REAL") == 0)
      new->type = REAL;
    if (strcmp(parsenode->parent->child[2]->child[0]->node, "BOOLEAN") == 0)
      new->type = BOOLEAN;

    parsenode->astaddr->symtab = copynode->astaddr->symtab;
    if (functionentry != NULL)
    {
      functionentry->outputparam = malloc(sizeof(symidentry *));
      functionentry->output_no = 1;
      functionentry->outputparam[0] = new;
    }
    //printf("\n\n\n\n\nOutput plist encountered for id  :- %s\n\n\n\n",parsenode->value);
  }

  if (strcmp(parsenode->node, "ID") == 0 && strcmp(parsenode->parent->node, "<N2>") == 0)
  {
    //printf("case7\n");
    parsetree *copynode;
    copynode = parsenode;
    symfuncentry *functionentry;
    while (strcmp(copynode->node, "<module>") != 0)
    {
      copynode = copynode->parent;
    }
    functionentry = getinfooffunction(functiontable, copynode->child[2]->value);
    copynode = copynode->child[11]->child[1];
    //printf("output type is %s\n", parsenode->parent->child[3]->child[0]->node);
    putintosymboltable(copynode->astaddr->symtab, parsenode);
    symidentry *new;
    new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
    new->active=true;
    new->isarray = false;
    if (strcmp(parsenode->parent->child[3]->child[0]->node, "INTEGER") == 0)
      new->type = INTEGER;
    if (strcmp(parsenode->parent->child[3]->child[0]->node, "REAL") == 0)
      new->type = REAL;
    if (strcmp(parsenode->parent->child[3]->child[0]->node, "BOOLEAN") == 0)
      new->type = BOOLEAN;
    //printf("\n\n\n\n\nOutput plist encountered for id  :- %s and type is %d\n\n\n\n",parsenode->value,new->type);
    //printsymboltable(copynode->astaddr->symtab);
    parsenode->astaddr->symtab = copynode->astaddr->symtab;
    if (functionentry != NULL)
    {
      functionentry->outputparam = realloc(functionentry->outputparam, sizeof(symidentry *) * (functionentry->output_no + 1));
      functionentry->output_no += 1;
      functionentry->outputparam[functionentry->output_no - 1] = new;
    }
  }

  if (strcmp(parsenode->node, "ID") == 0 && strcmp(parsenode->parent->node, "<N1>") == 0)
  {
    //printf("case8\n");
    parsetree *copynode;
    copynode = parsenode;
    symidentry *new;
    symfuncentry *functionentry;
    while (strcmp(copynode->node, "<module>") != 0)
    {
      copynode = copynode->parent;
    }
    functionentry = getinfooffunction(functiontable, copynode->child[2]->value);
    copynode = copynode->child[11]->child[1];
    //printf("node is parse node in else of output plist %s\n",parsenode->value);
    if (strcmp(parsenode->parent->child[3]->child[0]->node, "ARRAY") == 0)
    {
      //printf("in if mate\n\n\n");
      //printf("type is %s\n", parsenode->parent->child[3]->child[0]->node);
      putintosymboltable(copynode->astaddr->symtab, parsenode);
      new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
      new->isarray = true;
      if (strcmp(parsenode->parent->child[3]->child[5]->child[0]->node, "INTEGER") == 0)
        new->type = INTEGER;
      if (strcmp(parsenode->parent->child[3]->child[5]->child[0]->node, "REAL") == 0)
        new->type = REAL;
      if (strcmp(parsenode->parent->child[3]->child[5]->child[0]->node, "BOOLEAN") == 0)
        new->type = BOOLEAN;
      new->dynamic = 0;
      if (strcmp(parsenode->parent->child[3]->child[2]->child[0]->child[0]->node, "NUM") == 0 && strcmp(parsenode->parent->child[3]->child[2]->child[2]->child[0]->node, "NUM") == 0)
      {
        //printf("yes static array\n");
        new->dynamic = 0;
      }
      else
      {

        if (strcmp(parsenode->parent->child[3]->child[2]->child[0]->child[0]->node, "NUM") != 0)
        {
          if (strcmp(parsenode->parent->child[3]->child[2]->child[2]->child[0]->node, "NUM") != 0)
          {
            new->dynamic = 3;
          }
          new->dynamic = 2;
        }
        else
        {
          new->dynamic = 1;
        }
      }
      if (new->dynamic == 0)
      {
        new->startindex = atoi(parsenode->parent->child[3]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = atoi(parsenode->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
        new->indexid[0] = NULL;
        new->indexid[1] = NULL;
      }
      if (new->dynamic == 1)
      {
        new->startindex = atoi(parsenode->parent->child[3]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = -1;
        new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
        new->indexid[0] = NULL;
      }
      if (new->dynamic == 2)
      {
        new->startindex = -1;
        new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[3]->child[2]->child[0]->child[0]->value);
        new->indexid[1] = NULL;
        //printf("start index is %d \n", new->startindex);
        new->endindex = atoi(parsenode->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
      }
      if (new->dynamic == 3)
      {
        new->startindex = -1;
        new->indexid[0] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[3]->child[2]->child[0]->child[0]->value);
        //printf("start index is %d \n", new->startindex);
        new->endindex = -1;
        new->indexid[1] = getinfoofsymbol(copynode->astaddr->symtab, parsenode->parent->child[3]->child[2]->child[2]->child[0]->value);
        //printf("end index is %d \n", new->endindex);
      }
      new->active=true;
    }
    else
    {
      //printf("in else mate \n\n\n");
      //printf("type is %s\n", parsenode->parent->child[3]->child[0]->child[0]->node);
      putintosymboltable(copynode->astaddr->symtab, parsenode);
      new = getinfoofsymbol(copynode->astaddr->symtab, parsenode->value);
      new->isarray = false;
      new->active=true;
      if (strcmp(parsenode->parent->child[3]->child[0]->child[0]->node, "INTEGER") == 0)
        new->type = INTEGER;
      if (strcmp(parsenode->parent->child[3]->child[0]->child[0]->node, "REAL") == 0)
        new->type = REAL;
      if (strcmp(parsenode->parent->child[3]->child[0]->child[0]->node, "BOOLEAN") == 0)
        new->type = BOOLEAN;
    }
    //printf("\n\n\n\n\nInput plist encountered for id  :- %s \n\n\n\n",parsenode->value);
    //printsymboltable(copynode->astaddr->symtab);
    parsenode->astaddr->symtab = copynode->astaddr->symtab;
    if (functionentry != NULL)
    {
      functionentry->inputparam = realloc(functionentry->inputparam, sizeof(symidentry *) * (functionentry->input_no + 1));
      functionentry->input_no += 1;
      functionentry->inputparam[functionentry->input_no - 1] = new;
    }
  }
  if (strcmp(parsenode->node, "ID") == 0)
  {
    if (strcmp(parsenode->parent->node, "<index>") == 0 || strcmp(parsenode->parent->node, "<ioStmt>") == 0 || strcmp(parsenode->parent->node, "<var_id_num>") == 0 || strcmp(parsenode->parent->node, "<assignmentStmt>") == 0 || (strcmp(parsenode->parent->node, "<idList>") == 0 && strcmp(parsenode->parent->parent->node, "<optional>") == 0) || (strcmp(parsenode->parent->node, "<N3>") == 0 && strcmp(parsenode->astaddr->parent->parent->label, "<optional>") == 0))
    {
      //printf("In other id stmts for id %s and parent node is %s\n ",parsenode->value,parsenode->parent->node);
      astree *astnode;
      astnode = parsenode->astaddr;
      while (astnode != NULL && strcmp(astnode->label, "<statements>") != 0 && strcmp(astnode->label, "<caseStmts>") != 0)
      {
        //printf("While traversing %s parent is %s\n",parsenode->value,astnode->label);
        astnode = astnode->parent;
      }
      if (strcmp(astnode->parent->label, "<caseStmts>") == 0)
      {
        astnode = astnode->parent;
      }
      parsenode->astaddr->symboltabpointer = getinfoofsymbol(astnode->symtab, parsenode->value);

    }
  }
}

void printqueue2(astree **que, int *newlen)
{
  printf("------------------");
  for (int i = 0; i < *newlen; i++)
  {
    printf("Label :- %s ", que[i]->label);
    //printf("%s   ", que[i]->lexval);
  }
  printf("-------------------\n");
  //printf("\n");
}
astree **putchildtoqueue2(astree **que, int *newlen)
{
  //printf("ast0 is %s\n\n",que[0]->label);
  //printf("inputchild\n");
  int count = 0;
  int indcount = 0;
  astree **newtree;
  newtree = NULL;
  for (int i = 0; i < *newlen; i++)
  {
    astree *new;
    new = que[i]->childhead;
    //printf("Currently at %s \n",new->label);
    while (new != NULL)
    {
      count += 1;
      newtree = realloc(newtree, sizeof(astree *) * count);
      newtree[count - 1] = new;
      new = new->sibling;
      //printf("value of ast node is %s\n",newtree[count-1]->label);
    }
    //printf("\n\nnow after 1 symbol count is %d\n\n",count);
  }
  *newlen = count;
  if (count == 0)
  {
    return NULL;
  }
  return newtree;
}

void printast(astree *parse)
{
  //printf("hi\n\n\n\n\n");
  newlen = malloc(sizeof(int));
  //printf("\n\n\ncreated for %s \n", parse->lexval);
  astfinal = malloc(sizeof(astree *) * 1);
  astfinal[0] = parse;
  *newlen = 1;
  astfinal = putchildtoqueue2(astfinal, newlen);
  while (astfinal != NULL)
  {
    printqueue2(astfinal, newlen);
    astfinal = putchildtoqueue2(astfinal, newlen);
  }
}