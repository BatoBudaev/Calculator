/**
 * @file s21_stack.c
 * @brief Реализация функций для работы со стеком.
 */
#include "s21_stack.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Инициализирует стек, устанавливая вершину на -1.
 *
 * @param stack Указатель на структуру стека.
 */
void initStack(Stack *stack) { stack->top = -1; }

/**
 * @brief Проверяет, является ли стек пустым.
 *
 * @param stack Указатель на структуру стека.
 * @return 1, если стек пуст, 0 - в противном случае.
 */
int isEmpty(Stack *stack) { return stack->top == -1; }

/**
 * @brief Добавляет символ в стек.
 *
 * @param stack Указатель на структуру стека.
 * @param c Символ, который нужно добавить в стек.
 */
void pushChar(Stack *stack, char c) {
  if (stack->top == MAX_SIZE - 1) {
    printf("Стэк переполнен\n");
    return;
  }

  stack->top++;
  stack->data[stack->top] = c;
}

/**
 * @brief Добавляет число с плавающей запятой в стек.
 *
 * @param stack Указатель на структуру стека.
 * @param d Число с плавающей запятой, которое нужно добавить в стек.
 */
void pushDouble(Stack *stack, double d) {
  if (stack->top >= MAX_SIZE - 1) {
    printf("Стэк переполнен\n");
    return;
  }

  stack->top++;
  stack->data[stack->top] = d;
}

/**
 * @brief Извлекает символ из вершины стека.
 *
 * @param stack Указатель на структуру стека.
 * @return Извлеченный символ.
 */
char popChar(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Стэк пуст\n");
    return 0;
  }

  return stack->data[stack->top--];
}

/**
 * @brief Извлекает число с плавающей запятой из вершины стека.
 *
 * @param stack Указатель на структуру стека.
 * @return Извлеченное число с плавающей запятой.
 */
double popDouble(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Стэк пуст\n");
    return 0;
  }

  return stack->data[stack->top--];
}
