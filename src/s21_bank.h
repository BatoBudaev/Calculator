#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef C7_SMARTCALC_V1_0_1_S21_CREDIT_H
#define C7_SMARTCALC_V1_0_1_S21_CREDIT_H

/**
 * @file s21_bank.h
 * @brief Заголовочный файл для банковских функций.
 */

/**
 * @brief Структура для хранения данных о депозите.
 */
struct data {
  int number;           /**< Номер операции. */
  long double interest; /**< Начисленные проценты. */
  long double tax;      /**< Удержанный налог. */
  long double deposits; /**< Сумма внесенных депозитов. */
  long double withdrawals; /**< Сумма снятых депозитов. */
  long double sum;         /**< Итоговая сумма. */
};

/**
 * @brief Вычисляет аннуитетный платеж для кредита.
 *
 * @param creditSum Сумма кредита.
 * @param percent Процентная ставка.
 * @param months Количество месяцев.
 * @return Аннуитетный платеж.
 */
double calculateAnnuity(double creditSum, double percent, int months);

/**
 * @brief Вычисляет переплату по кредиту.
 *
 * @param totalPayment Общая сумма выплаты.
 * @param creditSum Сумма кредита.
 * @return Переплата.
 */
double calculateOverpayment(double totalPayment, double creditSum);

/**
 * @brief Вычисляет дифференцированный платеж для кредита.
 *
 * @param creditSum Сумма кредита.
 * @param percent Процентная ставка.
 * @param months Количество месяцев.
 * @param currentMonth Текущий месяц (начиная с 1).
 * @return Дифференцированный платеж.
 */
double calculateDifferentiated(double creditSum, double percent, int months,
                               int currentMonth);

/**
 * @brief Вычисляет начисленные проценты по остатку долга.
 *
 * @param balance Остаток долга.
 * @param rate Процентная ставка.
 * @param days Количество дней.
 * @param daysInYear Количество дней в году.
 * @return Начисленные проценты.
 */
long double calculateInterest(long double balance, double rate, int days,
                              int daysInYear);

/**
 * @brief Вычисляет сумму налога на доход.
 *
 * @param income Доход.
 * @param untaxedIncome Необлагаемый доход.
 * @param taxRate Ставка налога.
 * @return Сумма налога.
 */
long double calculateTax(long double income, long double untaxedIncome,
                         double taxRate);

/**
 * @brief Получает количество дней в указанном месяце и году.
 *
 * @param year Год.
 * @param month Месяц.
 * @return Количество дней в месяце.
 */
int getDaysInMonth(int year, int month);

/**
 * @brief Вычисляет прирост депозита с учетом начисленных процентов и уплаченных
 * налогов.
 *
 * @param initialDeposit Начальная сумма депозита.
 * @param months Количество месяцев.
 * @param interestRate Процентная ставка.
 * @param taxRate Ставка налога.
 * @param capitalizationPeriod Период капитализации (в месяцах).
 * @param paymentsPeriod Период выплат (в месяцах).
 * @param deposits Указатель на массив сумм внесенных депозитов.
 * @param withdrawals Указатель на массив сумм снятых депозитов.
 * @param startDay День начала расчета.
 * @param startMonth Месяц начала расчета.
 * @param startYear Год начала расчета.
 * @param results Указатель на структуру для хранения результатов.
 * @return Итоговая сумма депозита.
 */
long double calculateDepositEarnings(double initialDeposit, int months,
                                     double interestRate, double taxRate,
                                     int capitalizationPeriod,
                                     int paymentsPeriod, double *deposits,
                                     double *withdrawals, int startDay,
                                     int startMonth, int startYear,
                                     struct data *results);

/**
 * @brief Генерирует массив сумм депозитов для каждого периода начисления
 * процентов.
 *
 * @param depositAmount Сумма депозита.
 * @param periodType Тип периода (ежемесячно, раз в квартал и т.д.).
 * @param totalMonths Общее количество месяцев.
 * @return Указатель на массив сумм депозитов.
 */
double *generateDeposits(double depositAmount, int periodType, int totalMonths);

#endif  // C7_SMARTCALC_V1_0_1_S21_CREDIT_H