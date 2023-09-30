#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef C7_SMARTCALC_V1_0_1_S21_POSTFIX_H
#define C7_SMARTCALC_V1_0_1_S21_POSTFIX_H

/**
 * @file s21_postfix.h
 * @brief Заголовочный файл для функций работы с постфиксными выражениями.
 */

/**
 * @brief Преобразует инфиксное выражение в постфиксное выражение.
 *
 * @param express Инфиксное выражение.
 * @param postfix Буфер для хранения постфиксного выражения.
 * @return 0 в случае успешного преобразования, -1 - при ошибке.
 */
int doInfixToPostfix(const char *express, char *postfix);

/**
 * @brief Вычисляет значение постфиксного выражения, зависящее от переменной x.
 *
 * @param postfix Постфиксное выражение.
 * @param x Значение переменной x.
 * @return Результат вычисления.
 */
double calculatePostfix(char *postfix, double x);

/**
 * @brief Проверяет, является ли символ оператором.
 *
 * @param c Символ для проверки.
 * @return 1, если символ - оператор, 0 - в противном случае.
 */
int isOperator(char c);

/**
 * @brief Получает приоритет оператора.
 *
 * @param c Оператор.
 * @return Приоритет оператора.
 */
int getPriority(char c);

#ifdef __cplusplus
}
#endif

#endif  // C7_SMARTCALC_V1_0_1_S21_POSTFIX_H
