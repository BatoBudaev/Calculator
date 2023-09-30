#ifndef C7_SMARTCALC_V1_0_1_S21_STACK_H
#define C7_SMARTCALC_V1_0_1_S21_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file s21_stack.h
 * @brief Определение структуры стека и функций для работы с ним.
 */
#define MAX_SIZE 255

/**
 * @brief Структура, представляющая стек для хранения символов и чисел.
 */
typedef struct {
  double data[MAX_SIZE]; /**< Массив для хранения данных стека. */
  int top;               /**< Индекс вершины стека. */
} Stack;

/**
 * @brief Инициализирует стек, устанавливая вершину на -1.
 *
 * @param stack Указатель на структуру стека.
 */
void initStack(Stack *stack);

/**
 * @brief Проверяет, является ли стек пустым.
 *
 * @param stack Указатель на структуру стека.
 * @return 1, если стек пуст, 0 - в противном случае.
 */
int isEmpty(Stack *stack);

/**
 * @brief Добавляет символ в стек.
 *
 * @param stack Указатель на структуру стека.
 * @param c Символ, который нужно добавить в стек.
 */
void pushChar(Stack *stack, char c);

/**
 * @brief Добавляет число с плавающей запятой в стек.
 *
 * @param stack Указатель на структуру стека.
 * @param d Число с плавающей запятой, которое нужно добавить в стек.
 */
void pushDouble(Stack *stack, double d);

/**
 * @brief Извлекает символ из вершины стека.
 *
 * @param stack Указатель на структуру стека.
 * @return Извлеченный символ.
 */
char popChar(Stack *stack);

/**
 * @brief Извлекает число с плавающей запятой из вершины стека.
 *
 * @param stack Указатель на структуру стека.
 * @return Извлеченное число с плавающей запятой.
 */
double popDouble(Stack *stack);

#ifdef __cplusplus
}
#endif

#endif  // C7_SMARTCALC_V1_0_1_S21_STACK_H
