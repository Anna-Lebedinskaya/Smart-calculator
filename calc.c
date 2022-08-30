#include "calc.h"

double str_to_double(char* str, int* pos_i) {
  char chislo[256] = {0};
  double res = 0;
  int j = 0;

  for (; *(str + *pos_i) != '\0' && strchr("0123456789", *(str + *pos_i));
       (*pos_i)++) {
    chislo[j] = str[*pos_i];
    j++;
  }
  if (str[*pos_i] == '.') {
    chislo[j] = '.';
    j++;
    (*pos_i)++;
    for (; *(str + *pos_i) != '\0' && strchr("0123456789", *(str + *pos_i));
         (*pos_i)++) {
      chislo[j] = str[*pos_i];
      j++;
    }
  }
  res = atof(chislo);
  (*pos_i)--;
  return res;
}

double unar_func(char oper, double x) {
  double res = 0;
  if (oper == 's') res = sin(x);
  if (oper == 'c') res = cos(x);
  if (oper == 't') res = tan(x);
  if (oper == 'S') res = asin(x);
  if (oper == 'C') res = acos(x);
  if (oper == 'T') res = atan(x);
  if (oper == 'q') res = sqrt(x);
  if (oper == 'l') res = log(x);
  if (oper == 'L') res = log10(x);
  if (oper == '~') res = 0 - x;
  return res;
}

double binar_func(char oper, double x, double y) {
  double res = 0;
  if (oper == '+') res = x + y;
  if (oper == '-') res = x - y;
  if (oper == '*') res = x * y;
  if (oper == '/') res = x / y;
  if (oper == '^') res = pow(x, y);
  if (oper == 'm') res = fmod(x, y);
  return res;
}

Stack* pars(char* str, double* x) {
  int error = 0;
  int open_bracket = 0;
  Stack* top = NULL;
  for (int i = 0; *(str + i) != '\0'; i++) {
    if (strchr("sctalm()+-*/^0123456789x. ", *(str + i)) == NULL) {
      error = 1;
      break;
    } else if (*(str + i) == ' ') {
      continue;
    } else if (!strncmp(str + i, "sin", 3)) {
      i += 2;
      push(&top, 0, 's');
    } else if (!strncmp(str + i, "cos", 3)) {
      i += 2;
      push(&top, 0, 'c');
    } else if (!strncmp(str + i, "tan", 3)) {
      i += 2;
      push(&top, 0, 't');
    } else if (!strncmp(str + i, "acos", 4)) {
      i += 3;
      push(&top, 0, 'C');
    } else if (!strncmp(str + i, "asin", 4)) {
      i += 3;
      push(&top, 0, 'S');
    } else if (!strncmp(str + i, "atan", 4)) {
      i += 3;
      push(&top, 0, 'T');
    } else if (!strncmp(str + i, "sqrt", 4)) {
      i += 3;
      push(&top, 0, 'q');
    } else if (!strncmp(str + i, "ln", 2)) {
      i++;
      push(&top, 0, 'l');
    } else if (!strncmp(str + i, "log", 3)) {
      i += 2;
      push(&top, 0, 'L');
    } else if (!strncmp(str + i, "mod", 3)) {
      i += 2;
      push(&top, 0, 'm');
    } else if (strchr(".0123456789", *(str + i)) != NULL) {
      push(&top, str_to_double(str, &i), 'x');
      if (*(str + i + 1) != '\0' && *(str + i + 1) == '.') {
        error = 1;
        break;
      }
    } else if (strchr("/^*()", *(str + i)) != NULL) {
      open_bracket += *(str + i) == '(';  //
      open_bracket -= *(str + i) == ')';
      push(&top, 0, *(str + i));
    } else if (*(str + i) == 'x') {
      push(&top, *x, 'x');
    } else if (*(str + i) == '+') {
      if (top != NULL && strchr(")x", top->operation)) push(&top, 0, '+');
    } else if (*(str + i) == '-') {
      if (top != NULL && strchr(")x", top->operation))
        push(&top, 0, '-');
      else
        push(&top, 0, '~');
    } else {
      error = 1;
      break;
    }
  }
  error = error || open_bracket < 0;  //
  while (open_bracket > 0) {
    push(&top, 0, ')');
    open_bracket--;
  }
  if (((error == 1) && (top != NULL)) ||
      (top != NULL && top->operation != 'x' && top->operation != ')')) {
    free_stack(top);
    top = NULL;
  }

  return top;
}

Stack* get_polish_notation(Stack* top) {
  Stack* res = NULL;
  Stack* oper = NULL;
  while (top != NULL) {
    if (top->operation == 'x') {
      push(&res, top->value, top->operation);
    } else if (strchr("sScCtTlLq~(", top->operation)) {
      push(&oper, top->value, top->operation);
    } else if (strchr("+-*/m^", top->operation)) {
      if (oper == NULL || oper->priority <= top->priority) {
        push(&oper, top->value, top->operation);
      } else {
        while (oper != NULL && oper->priority > top->priority) {
          push(&res, oper->value, oper->operation);
          pop(&oper);
        }
        push(&oper, top->value, top->operation);
      }
    } else if (top->operation == ')') {
      while (oper != NULL && oper->operation != '(') {
        push(&res, oper->value, oper->operation);
        pop(&oper);
      }
      pop(&oper);
    }
    top = top->next;
  }
  while (oper != NULL) {
    push(&res, oper->value, oper->operation);
    pop(&oper);
  }
  return res;
}

double get_res(Stack* top, int* error) {
  double result = 0;
  Stack* res = NULL;
  while (top != NULL) {
    if (top->operation == 'x') {
      push(&res, top->value, top->operation);
    } else if (strchr("+-*/m^", top->operation)) {
      if ((res != NULL) && (res->next != NULL)) {
        res->next->value =
            binar_func(top->operation, res->next->value, res->value);
        pop(&res);
      } else {
        *error = 1;
        break;
      }
    } else if (strchr("sScCtTlLq~", top->operation) != NULL) {
      if (res != NULL) {
        res->value = unar_func(top->operation, res->value);
      } else {
        *error = 1;
        break;
      }
    }
    top = top->next;
  }
  if ((*error == 0) && (res != NULL && res->next == NULL)) {
    result = res->value;
  } else {
    *error = 1;
  }
  free_stack(res);

  return result;
}

int main_func(char* str, double* x, double* result) {
  int error = 0;  // ok
  Stack* head = NULL;
  head = pars(str, x);
  if (head == NULL) {
    error = 1;
  } else {
    head = revers(&head);
    Stack* res = get_polish_notation(head);
    res = revers(&res);
    double s = get_res(res, &error);
    // printf("%f", s);
    if (error == 0) *result = s;
    free_stack(head);
    free_stack(res);
  }

  return error;
}

int credit_func(double sum, int month, double proc, double* payment,
                double* over, double* total, int type) {
  int error = 0;
  if (sum > 0 && month > 0 && month < 600 && proc > 0 && proc < 100) {
    if (type == 1) {
      *payment =
          sum * (proc / 1200) / (1 - pow((1 + proc / 1200), (month * (-1))));
      *total = (*payment) * month;
      *over = *total - sum;
    } else if (type == 2) {
      *payment = (sum / month) + sum * (proc / 1200);
      double part = sum / month;
      double sum_temp = sum;
      while (month) {
        *total += sum_temp * (proc / 1200) + sum_temp / month;
        sum_temp -= part;
        month--;
      }
      *over = *total - sum;
    } else {
      error = 1;
    }
  } else {
    error = 2;
  }
  return error;
}
