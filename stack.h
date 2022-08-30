#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
  char operation;
  double value;
  int priority;
  struct Stack* next;
} Stack;

Stack* init(double val, char oper);
int push(Stack** head, double val, char oper);
int pop(Stack** top);
void free_stack(Stack* head);
Stack* revers(Stack** head);

#endif  // SRC_STACK_H_
