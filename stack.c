#include "stack.h"
// number, x,  // 1
//     +,      // 2
//     -,      // 3
//     *,      // 4
//     /,      // 5
//     (,      // 6
//      ),     // 7
//     ^,      // 8
//     mod,    // 9
//     cos,    // 10
//     sin,    // 11
//     tan,    // 12
//     acos,   // 13
//     asin,   // 14
//     atan,   // 15
//     sqrt,   // 16
//     ln,     // 17
//     log,    // 18

Stack* init(double val, char oper) {
  Stack* head = (Stack*)calloc(1, sizeof(Stack));
  if (head != NULL) {
    head->operation = oper;
    head->next = NULL;
    if (oper == 'x') {
      head->value = val;
      head->priority = 0;
    } else {
      head->value = 0;
      if (oper == ')')
        head->priority = 10;
      else if (oper == '(')
        head->priority = -1;
      else if (oper == '+' || oper == '-')
        head->priority = 1;
      else if (oper == '/' || oper == '*' || oper == 'm')
        head->priority = 2;
      else if (oper == '^')
        head->priority = 3;
      else if (strchr("sScCtTlLq~", oper) != NULL)
        head->priority = 4;
    }
  }
  return head;
}

int push(Stack** head, double val, char oper) {
  int res = 0;  // память не выделилась
  Stack* new_head = init(val, oper);
  if (new_head != NULL) {
    new_head->next = *head;
    *head = new_head;
    res = 1;
  }
  return res;
}

int pop(Stack** head) {
  int res = 0;  // не получилось
  if (*head != NULL) {
    Stack* free_head = *head;
    *head = (*head)->next;
    free(free_head);
    res = 1;
  }
  return res;
}

void free_stack(Stack* head) {
  if (head != NULL) {
    Stack* next_head = head->next;
    free(head);
    free_stack(next_head);
    // free_stack(head->next);
    // free(head);
  }
}

Stack* revers(Stack** head) {
  Stack* new_head = NULL;
  if (*head != NULL) {
    new_head = init((*head)->value, (*head)->operation);
    pop(head);
  }
  while (*head != NULL) {
    push(&new_head, (*head)->value, (*head)->operation);
    pop(head);
  }

  return new_head;
}
