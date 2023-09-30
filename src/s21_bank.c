#include "s21_bank.h"

#include "s21_postfix.h"
/**
 * @file s21_bank.c
 * @brief Функции для работы с банковскими расчетами.
 */

/**
 * @brief Рассчитывает аннуитетный платеж для кредита.
 *
 * @param creditSum Сумма кредита.
 * @param percent Годовая процентная ставка.
 * @param months Количество месяцев кредита.
 * @return Аннуитетный платеж.
 */
double calculateAnnuity(double creditSum, double percent, int months) {
  double monthlyPercent = percent / 12 / 100;
  double numerator = monthlyPercent * pow(1 + monthlyPercent, months);
  double denominator = pow(1 + monthlyPercent, months) - 1;
  double monthPayment = creditSum * (numerator / denominator);

  char formattedNumber[20];
  sprintf(formattedNumber, "%.2lf", monthPayment);
  double formattedMonthPayment = strtod(formattedNumber, NULL);

  return formattedMonthPayment;
}

/**
 * @brief Рассчитывает переплату по кредиту.
 *
 * @param totalPayment Общий платеж по кредиту (с учетом процентов).
 * @param creditSum Сумма кредита.
 * @return Сумма переплаты.
 */
double calculateOverpayment(double totalPayment, double creditSum) {
  return totalPayment - creditSum;
}

/**
 * @brief Рассчитывает дифференцированный платеж для кредита.
 *
 * @param creditSum Сумма кредита.
 * @param percent Годовая процентная ставка.
 * @param months Количество месяцев кредита.
 * @param currentMonth Текущий месяц для расчета платежа.
 * @return Дифференцированный платеж для текущего месяца.
 */
double calculateDifferentiated(double creditSum, double percent, int months,
                               int currentMonth) {
  double monthlyPercent = percent / 12 / 100;
  double basePayment = creditSum / months;
  double remainingBalance = creditSum - basePayment * (currentMonth - 1);
  double interestPayment = remainingBalance * monthlyPercent;

  return basePayment + interestPayment;
}

/**
 * @brief Рассчитывает начисленные проценты для заданного баланса.
 *
 * @param balance Текущий баланс на счете.
 * @param rate Процентная ставка в год.
 * @param days Количество дней для начисления процентов.
 * @param daysInYear Количество дней в году.
 * @return Начисленные проценты.
 */
long double calculateInterest(long double balance, double rate, int days,
                              int daysInYear) {
  return balance * rate / 100 * days / daysInYear;
}

/**
 * @brief Рассчитывает сумму налога на начисленные проценты.
 *
 * @param income Начисленные проценты.
 * @param untaxedIncome Сумма начисленных процентов, не облагаемых налогом.
 * @param taxRate Ставка налога в процентах.
 * @return Сумма налога на начисленные проценты.
 */
long double calculateTax(long double income, long double untaxedIncome,
                         double taxRate) {
  long double taxableIncome = income - untaxedIncome;
  if (taxableIncome <= 0) {
    return 0.0;
  }
  return taxableIncome * taxRate / 100;
}

/**
 * @brief Проверяет, является ли заданный год високосным.
 *
 * @param year Год.
 * @return 1, если год високосный, иначе 0.
 */
int isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Получает количество дней в заданном месяце и году.
 *
 * @param year Год.
 * @param month Месяц (1-12).
 * @return Количество дней в месяце.
 */
int getDaysInMonth(int year, int month) {
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  return daysInMonth[month - 1];
}

/**
 * @brief Рассчитывает доход по депозиту с учетом капитализации и начисления
 * налога.
 *
 * @param initialDeposit Начальная сумма депозита.
 * @param months Количество месяцев.
 * @param interestRate Процентная ставка по депозиту в год.
 * @param taxRate Ставка налога на доход в процентах.
 * @param capitalizationPeriod Период капитализации (в месяцах).
 * @param paymentsPeriod Период выплат (в месяцах).
 * @param deposits Массив довложений по месяцам.
 * @param withdrawals Массив снятий по месяцам.
 * @param startDay День начала депозита.
 * @param startMonth Месяц начала депозита.
 * @param startYear Год начала депозита.
 * @param results Массив с результатами по месяцам.
 * @return Итоговый баланс по окончании депозита.
 */
long double calculateDepositEarnings(double initialDeposit, int months,
                                     double interestRate, double taxRate,
                                     int capitalizationPeriod,
                                     int paymentsPeriod, double *deposits,
                                     double *withdrawals, int startDay,
                                     int startMonth, int startYear,
                                     struct data *results) {
  long double totalInterest = 0.0;
  long double totalInterestForPeriod = 0.0;
  long double totalTax = 0.0;
  long double totalTaxForPeriod = 0.0;
  long double balance = initialDeposit;
  long double depositsSum = 0;
  long double taxForYear = 0;

  int currentYear = startYear;
  int currentMonth = startMonth;
  int nextYear = 0;
  int nextYearDays = 365;

  if (paymentsPeriod < 1) {
    paymentsPeriod = 1;
  }

  for (int month = 1; month <= months; month++) {
    if (currentMonth > 12) {
      currentMonth -= 12;
      currentYear++;
    }

    int daysInYear = 365;

    if (isLeapYear(currentYear)) {
      daysInYear++;
    }

    int daysInMonth = getDaysInMonth(currentYear, currentMonth);

    long double earnedInterest = 0;

    if (currentMonth == 12) {
      nextYear = currentYear + 1;
      if (isLeapYear(nextYear)) {
        nextYearDays = 366;
      } else {
        nextYearDays = 365;
      }
    }

    if (currentMonth == 12 &&
        (isLeapYear(currentYear) || isLeapYear(nextYear))) {
      int decemberDays = 31 - startDay + 1;
      long double dec =
          calculateInterest(balance, interestRate, decemberDays, daysInYear);
      long double jan = calculateInterest(balance, interestRate,
                                          31 - decemberDays, nextYearDays);
      earnedInterest = dec + jan;
      totalInterestForPeriod += earnedInterest;
      totalInterest += earnedInterest;
    } else {
      earnedInterest =
          calculateInterest(balance, interestRate, daysInMonth, daysInYear);
      totalInterestForPeriod += earnedInterest;
      totalInterest += earnedInterest;
    }

    long double tax = calculateTax(earnedInterest, 0, taxRate);
    totalTaxForPeriod += tax;
    totalTax += tax;

    balance += deposits[month - 1];
    depositsSum += deposits[month - 1];

    if (balance > withdrawals[month - 1]) {
      balance -= withdrawals[month - 1];
    } else {
      withdrawals[month - 1] = 0;
    }

    if (capitalizationPeriod > 0 && month % capitalizationPeriod == 0) {
      balance += totalInterestForPeriod;
      balance -= totalTaxForPeriod;

      results[month - 1].number = month;
      results[month - 1].interest = totalInterestForPeriod;
      results[month - 1].tax = totalTaxForPeriod;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;

      taxForYear += totalTaxForPeriod;
      totalInterestForPeriod = 0;
      totalTaxForPeriod = 0;

    } else if (capitalizationPeriod > 0) {
      results[month - 1].number = month;
      results[month - 1].interest = 0;
      results[month - 1].tax = 0;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;
    }

    if (capitalizationPeriod == 0 && month % paymentsPeriod == 0) {
      results[month - 1].number = month;
      results[month - 1].interest = totalInterestForPeriod;
      results[month - 1].tax = totalTaxForPeriod;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;

      totalInterestForPeriod = 0;
      totalTaxForPeriod = 0;
    } else if (capitalizationPeriod == 0 && paymentsPeriod > 0) {
      results[month - 1].number = month;
      results[month - 1].interest = 0;
      results[month - 1].tax = 0;
      results[month - 1].deposits = deposits[month - 1];
      results[month - 1].withdrawals = withdrawals[month - 1];
      results[month - 1].sum = balance;
    }
    currentMonth++;
  }

  if (capitalizationPeriod == 0) {
    balance += totalInterest;
    balance -= totalTax;
  }

  printf("Начисленные проценты: %.2Lf\n", totalInterest);
  printf("Сумма довложений: %.2Lf\n", depositsSum);
  printf("Сумма налога: %.2Lf\n", totalTax);
  printf("Доход за вычетом налогов: %.2Lf\n", totalInterest - totalTax);
  printf("Сумма на вкладе к концу срока: %.2Lf\n", balance);

  return balance;
}

/**
 * @brief Генерирует массив довложений для депозита в зависимости от типа
 * периода.
 *
 * @param depositAmount Сумма довложения.
 * @param periodType Тип периода (1 - ежемесячно, 6 - каждые 6 месяцев, 12 -
 * ежегодно).
 * @param totalMonths Общее количество месяцев.
 * @return Указатель на массив довложений.
 */
double *generateDeposits(double depositAmount, int periodType,
                         int totalMonths) {
  if (totalMonths < 1) {
    return NULL;
  }

  double *deposits = (double *)malloc(totalMonths * sizeof(double));

  if (deposits == NULL) {
    return NULL;
  }

  for (int i = 0; i < totalMonths - 1; i++) {
    deposits[i] = 0.0;

    if (periodType == 1) {
      deposits[i] = depositAmount;
    } else if (periodType == 6 && i % 6 == 0) {
      deposits[i] = depositAmount;
    } else if (periodType == 12 && i % 12 == 0) {
      deposits[i] = depositAmount;
    }
  }

  deposits[totalMonths - 1] = 0.0;

  return deposits;
}