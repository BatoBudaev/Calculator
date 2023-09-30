#include "s21_postfix.h"

/**
 * @file s21_postfix.c
 * @brief Реализация функций для работы с постфиксными выражениями.
 */

/**
 * @brief Проверяет, является ли символ оператором.
 *
 * @param c Символ для проверки.
 * @return 1, если символ - оператор, 0 - в противном случае.
 */
int isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

/**
 * @brief Получает приоритет оператора.
 *
 * @param c Оператор.
 * @return Приоритет оператора.
 */
int getPriority(char c) {
  int priority = -1;

  if (c == '(') {
    priority = 0;
  } else if (c == '+' || c == '-') {
    priority = 1;
  } else if (c == '*' || c == '/' || c == '%') {
    priority = 2;
  } else if (c == '^') {
    priority = 3;
  } else if (c == 'c' || c == 's' || c == 't' || c == 'C' || c == 'S' ||
             c == 'T' || c == 'Q' || c == 'L' || c == 'l') {
    priority = 4;
  }

  return priority;
}

/**
 * @brief Преобразует инфиксное выражение в постфиксное выражение.
 *
 * @param expression Инфиксное выражение.
 * @param postfix Буфер для хранения постфиксного выражения.
 * @return 0 в случае успешного преобразования, -1 - при ошибке.
 */
int doInfixToPostfix(const char *expression, char *postfix) {
  Stack stack;
  initStack(&stack);

  int i = 0, j = 0;

  char prevChar = '\0';
  int prevIsOperand = 0;

  while (expression[i] != '\0') {
    char current = expression[i];

    if (isspace(current)) {
      i++;
      continue;
    }

    if (isdigit(current) || current == '.' || current == 'x') {
      if (prevIsOperand == 1 || (!isdigit(prevChar) && current == '.')) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return 0;
      }

      while (isdigit(expression[i]) || expression[i] == '.' ||
             expression[i] == 'x') {
        postfix[j++] = expression[i++];
      }

      postfix[j++] = ' ';
      i--;
      prevIsOperand = 1;
    } else if (isalpha(current)) {
      if (prevIsOperand == 1) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return 0;
      }

      char function[5] = {'\0'};
      int k = 0;

      while (isalpha(expression[i])) {
        function[k++] = expression[i++];
      }

      i--;

      if (strcmp(function, "cos") == 0) {
        pushChar(&stack, 'c');
      } else if (strcmp(function, "sin") == 0) {
        pushChar(&stack, 's');
      } else if (strcmp(function, "tan") == 0) {
        pushChar(&stack, 't');
      } else if (strcmp(function, "acos") == 0) {
        pushChar(&stack, 'C');
      } else if (strcmp(function, "asin") == 0) {
        pushChar(&stack, 'S');
      } else if (strcmp(function, "atan") == 0) {
        pushChar(&stack, 'T');
      } else if (strcmp(function, "sqrt") == 0) {
        pushChar(&stack, 'Q');
      } else if (strcmp(function, "ln") == 0) {
        pushChar(&stack, 'L');
      } else if (strcmp(function, "log") == 0) {
        pushChar(&stack, 'l');
      } else {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неизвестная функция \n");

        return 0;
      }

      prevIsOperand = 1;
    } else if (isOperator(current)) {
      if ((current == '-' || current == '+') &&
          (i == 0 || expression[i - 1] == '(' || expression[i - 1] == '^')) {
        if (current == '-') {
          if (i == 0) {
            pushChar(&stack, '-');
          } else {
            pushChar(&stack, '_');
          }
        } else {
          pushChar(&stack, '#');
        }
      } else if (isOperator(prevChar) || prevIsOperand == 0 ||
                 (isalpha(prevChar) && prevChar != 'x')) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return 0;
      } else {
        while (!isEmpty(&stack) && stack.data[stack.top] != '(' &&
               getPriority(stack.data[stack.top]) >= getPriority(current)) {
          if ((current == '^' && stack.data[stack.top] == '^')) {
            break;
          } else {
            postfix[j++] = popChar(&stack);
            postfix[j++] = ' ';
          }
        }

        pushChar(&stack, current);
      }

      prevIsOperand = 0;
    } else if (current == '(') {
      if (prevIsOperand == 1 && (!isalpha(prevChar) || prevChar == 'x')) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return 0;
      }

      pushChar(&stack, current);
      prevIsOperand = 0;
    } else if (current == ')') {
      if (prevChar == '(' || prevIsOperand == 0) {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return 0;
      }

      while (!isEmpty(&stack) && stack.data[stack.top] != '(') {
        postfix[j++] = popChar(&stack);
        postfix[j++] = ' ';
      }

      if (!isEmpty(&stack) && stack.data[stack.top] == '(') {
        popChar(&stack);
      } else {
        memset(postfix, 0, MAX_SIZE);
        printf("Ошибка: неправильное выражение\n");

        return 0;
      }

      prevIsOperand = 1;
    }

    prevChar = current;
    i++;
  }

  while (!isEmpty(&stack)) {
    if (stack.data[stack.top] == '(') {
      memset(postfix, 0, MAX_SIZE);
      printf("Ошибка: неправильное выражение\n");

      return 0;
    }

    postfix[j++] = popChar(&stack);
    postfix[j++] = ' ';
  }

  postfix[j] = '\0';
  printf("postfix: %s\n", postfix);

  return 1;
}

/**
 * @brief Вычисляет значение постфиксного выражения, зависящее от переменной x.
 *
 * @param postfix Постфиксное выражение.
 * @param x Значение переменной x.
 * @return Результат вычисления.
 */
double calculatePostfix(char *postfix, double x) {
  if (strlen(postfix) == 0) {
    return 0;
  }
  printf("postfix: %s\n", postfix);

  Stack stack;
  initStack(&stack);
  int i = 0;
  while (postfix[i] != '\0') {
    if (postfix[i] == 'x') {
      pushDouble(&stack, x);
      i++;
    } else if (isdigit(postfix[i])) {
      char *endPtr;
      double number = strtod(&postfix[i], &endPtr);
      pushDouble(&stack, number);
      i = endPtr - postfix;
    } else if (postfix[i] == ' ') {
      i++;
    } else {
      double operand1 = 0, operand2;

      switch (postfix[i]) {
        case '+':
          operand2 = popDouble(&stack);
          if (!isEmpty(&stack)) {
            operand1 = popDouble(&stack);
          }
          pushDouble(&stack, operand1 + operand2);
          break;
        case '-':
          operand2 = popDouble(&stack);
          if (!isEmpty(&stack)) {
            operand1 = popDouble(&stack);
          }
          pushDouble(&stack, operand1 - operand2);
          break;
        case '_':
          operand2 = popDouble(&stack);
          pushDouble(&stack, -1 * operand2);
          break;
        case '#':
          break;
        case '*':
          operand2 = popDouble(&stack);
          if (!isEmpty(&stack)) {
            operand1 = popDouble(&stack);
          }
          pushDouble(&stack, operand1 * operand2);
          break;
        case '/':
          operand2 = popDouble(&stack);
          if (!isEmpty(&stack)) {
            operand1 = popDouble(&stack);
          }
          pushDouble(&stack, operand1 / operand2);
          break;
        case '%':
          operand2 = popDouble(&stack);
          if (!isEmpty(&stack)) {
            operand1 = popDouble(&stack);
          }
          pushDouble(&stack, fmod(operand1, operand2));
          break;
        case '^':
          operand2 = popDouble(&stack);
          if (!isEmpty(&stack)) {
            operand1 = popDouble(&stack);
          }
          pushDouble(&stack, pow(operand1, operand2));
          break;
        case 'c':
          operand2 = popDouble(&stack);
          pushDouble(&stack, cos(operand2));
          break;
        case 's':
          operand2 = popDouble(&stack);
          pushDouble(&stack, sin(operand2));
          break;
        case 't':
          operand2 = popDouble(&stack);
          pushDouble(&stack, tan(operand2));
          break;
        case 'C':
          operand2 = popDouble(&stack);
          pushDouble(&stack, acos(operand2));
          break;
        case 'S':
          operand2 = popDouble(&stack);
          pushDouble(&stack, asin(operand2));
          break;
        case 'T':
          operand2 = popDouble(&stack);
          pushDouble(&stack, atan(operand2));
          break;
        case 'Q':
          operand2 = popDouble(&stack);
          pushDouble(&stack, sqrt(operand2));
          break;
        case 'L':
          operand2 = popDouble(&stack);
          pushDouble(&stack, log(operand2));
          break;
        case 'l':
          operand2 = popDouble(&stack);
          pushDouble(&stack, log10(operand2));
          break;
        default:
          printf("Ошибка: неизвестный оператор %c\n", postfix[i]);
      }
      i++;
    }
  }

  return popDouble(&stack);
}
