#include <check.h>
#include <math.h>

#include "s21_bank.h"
#include "s21_postfix.h"

START_TEST(calc_test_0) {
  char *str = "0.07*(1 + 0.07)^12";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 0.15765341122, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_1) {
  char *str = "2 * tan(6) / (1 + tan(5)^2)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -0.0468311814, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_2) {
  char *str = "tan(5)^2";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 11.4278817075, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_3) {
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix("/0", postfix);
  double result = calculatePostfix(postfix, 1);

  printf("result - %f\n", result);
  ck_assert_int_eq(0, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_4) {
  char *str =
      "+10833.33+10750.00+10666.67+10583.33+10500.00+10416.67+10333.33+10250."
      "00+10166.67+10083.33";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  printf("result - %f\n", result);
  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 104583.33, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_5) {
  char *str = "100000 * (0.07*(1 + 0.07)^12)/((1+0.07)^12 - 1)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 12590.1988655, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_6) {
  char *str = "tan(log(x))/cos(x)- tan(log(x))/sin(x)=";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 2);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -1.08748127511, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_7) {
  char *str = "x/cos(x)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 2);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -4.80599592344, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_8) {
  char *str = "5-*-5";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(0, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_9) {
  char *str = "2^3^2";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 512, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_10) {
  char *str = "-(3)*(-1-(7*(-(-(-(-7))))))";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -144, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_11) {
  char *str = "(1+2)*4*(cos(2*7-2)+sin(2*3))*70^(-10)+5*(-3)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -15, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_12) {
  char *str = "-cos(5) - tan(4 % 5)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -1.44148346781, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_13) {
  char *str = "-tan((4)%5)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -1.15782128235, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_14) {
  char *str = "";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_15) {
  char *str = "-7-----7";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(0, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_16) {
  char *str = "cos(-5) +(-1/sin(3))";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -6.80250521027, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_17) {
  char *str = "QString::number";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(0, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_18) {
  char *str = "-9-8";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -17, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_19) {
  char *str = "9 + 8 * 7 - 6 / 5";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 63.8, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_20) {
  char *str = "100.235+x-(x+10)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 2);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 90.235, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_21) {
  char *str = "cos(4)+(3-1)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 1.34635637914, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_22) {
  char *str = "2 * tan(6) / (1 + tan(5)^2)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -0.0468311814, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_23) {
  char *str = "2 ^ (-3))";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(0, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_24) {
  char *str = "2 ^ (-3)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 0.125, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_25) {
  char *str =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -30.0721649485, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_26) {
  char *str = "4^acos(x/4)/tan(2*x)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 3.5);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 2.31214930869, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_27) {
  char *str = "-sqrt(x^log(5-x))+ln(55/(2+x))";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 3.5);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 1.18597174919, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_28) {
  char *str = "4^cos(x/4)/tan(2*x) + sin(4)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 3);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -10.2326565899, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_29) {
  char *str = "4^acos(x/4)/tan(2*x)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 3);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -9.35895040639, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_30) {
  char *str = "4^asin(x/4)/tan(2*x)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 3);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, -11.1347896959, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_31) {
  char *str = "4^sin(x/4)/atan(2*x)";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 3);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 1.83025227465, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_32) {
  char *str = "-";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 0, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_33) {
  char *str = "2+";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 2, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(calc_test_34) {
  char *str = "+2";
  char *postfix = malloc(MAX_SIZE * sizeof(char));

  int code = doInfixToPostfix(str, postfix);
  double result = calculatePostfix(postfix, 1);

  ck_assert_int_eq(1, code);
  ck_assert_double_eq_tol(result, 2, 1e-7);

  free(postfix);
}
END_TEST

START_TEST(credit_test_0) {
  double creditSum = 157150;
  int months = 24;
  double percent = 14;

  double monthPayment, totalPayment, overpayment;

  monthPayment = calculateAnnuity(creditSum, percent, months);

  totalPayment = monthPayment * months;
  overpayment = calculateOverpayment(totalPayment, creditSum);

  ck_assert_double_eq_tol(monthPayment, 7545.22, 1e-2);
  ck_assert_double_eq_tol(overpayment, 23935.28, 1e-2);
  ck_assert_double_eq_tol(totalPayment, 181085.28, 1e-2);
}
END_TEST

START_TEST(credit_test_1) {
  double creditSum = 25000;
  int months = 12;
  double percent = 7.7;

  double totalPayment = 0, overpayment = 0;
  double payments[months];

  for (int month = 1; month <= months; month++) {
    payments[month - 1] =
        calculateDifferentiated(creditSum, percent, months, month);
  }

  for (int i = 0; i < months; i++) {
    totalPayment += payments[i];
    overpayment += payments[i] - creditSum / months;
  }

  ck_assert_double_eq_tol(payments[0], 2243.75, 1e-2);
  ck_assert_double_eq_tol(payments[months - 1], 2096.70, 1e-2);
  ck_assert_double_eq_tol(overpayment, 1042.71, 1e-2);
  ck_assert_double_eq_tol(totalPayment, 26042.71, 1e-2);
}
END_TEST

START_TEST(deposit_test_0) {
  double initialDeposit = 1000000;
  long double balance = 0;
  int months = 18;
  double interestRate = 20;
  double taxRate = 5.25;
  int capitalizationPeriod = 1;
  int paymentsPeriod = 0;

  double *deposits = generateDeposits(5000, 1, months);
  double *withdrawals = generateDeposits(0, 1, months);
  struct data results[months];

  balance = calculateDepositEarnings(
      initialDeposit, months, interestRate, taxRate, capitalizationPeriod,
      paymentsPeriod, deposits, withdrawals, 1, 8, 2023, results);

  long double totalInterest = 0.0;
  long double totalTax = 0.0;
  long double depositsSum = 0;

  for (int i = 0; i < months; i++) {
    totalInterest += results[i].interest;
    totalTax += results[i].tax;
    depositsSum += results[i].deposits;
  }

  free(deposits);
  free(withdrawals);

  ck_assert_double_eq_tol(totalInterest, 358884.83, 1e-2);
  ck_assert_double_eq_tol(depositsSum, 85000.00, 1e-2);
  ck_assert_double_eq_tol(totalTax, 18841.45, 1e-2);
  ck_assert_double_eq_tol(totalInterest - totalTax, 340043.38, 1e-2);
  ck_assert_double_eq_tol(balance, 1425043.38, 1e-2);
}
END_TEST

START_TEST(deposit_test_1) {
  double initialDeposit = 1000000;
  long double balance = 0;
  int months = 12;
  double interestRate = 20;
  double taxRate = 5.25;
  int capitalizationPeriod = 0;
  int paymentsPeriod = 1;

  double *deposits = generateDeposits(0, 1, months);
  double *withdrawals = generateDeposits(0, 1, months);
  struct data results[months];

  balance = calculateDepositEarnings(
      initialDeposit, months, interestRate, taxRate, capitalizationPeriod,
      paymentsPeriod, deposits, withdrawals, 1, 8, 2023, results);

  long double totalInterest = 0.0;
  long double totalTax = 0.0;
  long double depositsSum = 0;

  for (int i = 0; i < months; i++) {
    totalInterest += results[i].interest;
    totalTax += results[i].tax;
    depositsSum += results[i].deposits;
  }

  free(deposits);
  free(withdrawals);

  ck_assert_double_eq_tol(totalInterest, 200229.06, 1e-2);
  ck_assert_double_eq_tol(depositsSum, 0.00, 1e-2);
  ck_assert_double_eq_tol(totalTax, 10512.03, 1e-2);
  ck_assert_double_eq_tol(totalInterest - totalTax, 189717.03, 1e-2);
  ck_assert_double_eq_tol(balance, 1189717.03, 1e-2);
}
END_TEST

int main() {
  Suite *s = suite_create("Calc suite");
  TCase *tc = tcase_create("Calc test case");
  SRunner *runner = srunner_create(s);

  suite_add_tcase(s, tc);
  tcase_add_test(tc, calc_test_0);
  tcase_add_test(tc, calc_test_1);
  tcase_add_test(tc, calc_test_2);
  tcase_add_test(tc, calc_test_3);
  tcase_add_test(tc, calc_test_4);
  tcase_add_test(tc, calc_test_5);
  tcase_add_test(tc, calc_test_6);
  tcase_add_test(tc, calc_test_7);
  tcase_add_test(tc, calc_test_8);
  tcase_add_test(tc, calc_test_9);
  tcase_add_test(tc, calc_test_10);
  tcase_add_test(tc, calc_test_11);
  tcase_add_test(tc, calc_test_12);
  tcase_add_test(tc, calc_test_13);
  tcase_add_test(tc, calc_test_14);
  tcase_add_test(tc, calc_test_15);
  tcase_add_test(tc, calc_test_16);
  tcase_add_test(tc, calc_test_17);
  tcase_add_test(tc, calc_test_18);
  tcase_add_test(tc, calc_test_19);
  tcase_add_test(tc, calc_test_20);
  tcase_add_test(tc, calc_test_21);
  tcase_add_test(tc, calc_test_22);
  tcase_add_test(tc, calc_test_23);
  tcase_add_test(tc, calc_test_24);
  tcase_add_test(tc, calc_test_25);
  tcase_add_test(tc, calc_test_26);
  tcase_add_test(tc, calc_test_27);
  tcase_add_test(tc, calc_test_28);
  tcase_add_test(tc, calc_test_29);
  tcase_add_test(tc, calc_test_30);
  tcase_add_test(tc, calc_test_31);
  tcase_add_test(tc, calc_test_32);
  tcase_add_test(tc, calc_test_33);
  tcase_add_test(tc, calc_test_34);
  tcase_add_test(tc, credit_test_0);
  tcase_add_test(tc, credit_test_1);
  tcase_add_test(tc, deposit_test_0);
  tcase_add_test(tc, deposit_test_1);

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);

  return 0;
}
