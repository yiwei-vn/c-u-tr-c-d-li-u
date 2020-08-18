#include <stdio.h>
#include <stdlib.h>
 
#define MAX_LEV 3
 
typedef struct node
{
  int data;
  struct node *next[MAX_LEV];
} *NODE;
 
NODE new_node(int data)
{
  int i;
  NODE np;
 
  np = malloc(sizeof *np);
  np->data = data;
  for (i = 0; i < MAX_LEV; i++)
  {
    np->next[i] = 0;
  }
 
  return np;
}
 
NODE set_skip(NODE list)
{
  int i, j, k;
  NODE np, nn;
 
  for (j = 1, k = 2; j < MAX_LEV; j++, k += 3)
  {
    for (i = 0, nn = np = list; np != 0; np = np->next[0], i++)
    {
      if (i % k == 0)
      {
        nn->next[j] = np;
        nn = np;
      }
    }
  }
 
  return list;
}
 
void del_skip(NODE list)
{
  int i;
  NODE np, nn;
 
  for (i = MAX_LEV - 1; i >= 0; i--)
  {
    for (np = list->next[i]; np != 0; np = nn)
    {
      nn = np->next[i];
      free(np);
    }
  }
}
 
void print_skip(NODE list)
{
  int i;
  NODE np;
  static char *lev[] = {
    "->",
    "----->",
    "----------------->",
  };
 
  for (i = MAX_LEV - 1; i >= 0; i--)
  {
    for (np = list; np != 0; np = np->next[i])
    {
      printf("%02d%s", np->data, np->next[i] == 0 ? "\n" : lev[i]);
    }
  }
}
 
int main(void)
{
  int i;
  NODE head = 0, np;
 
  for (i = 11; i > 0; i--)
  {
    np = new_node(i);
    np->next[0] = head;
    head = np;
  }
 
  head = set_skip(head);
  print_skip(head);
 
  return 0;
}