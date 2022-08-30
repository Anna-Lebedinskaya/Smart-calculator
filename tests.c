// leaks -atExit -- ./test
// valgrind --leak-check=full --show-leak-kinds=all -s ./test

// gcc - o test tests.c calc.c stack.c - lcheck - lpthread -lm &&./ test
#include <check.h>

#include "calc.h"

START_TEST(test_error) {
  char str1[] = ")(3-4)";
  double x = 0;
  double result = 0;
  int error = main_func(str1, &x, &result);
  ck_assert_int_eq(error, 1);

  char str2[] = "/25-46";
  error = main_func(str2, &x, &result);
  ck_assert_int_eq(error, 1);

  char str4[] = "25-46..";
  error = main_func(str4, &x, &result);
  ck_assert_int_eq(error, 1);

  char str5[] = "14.16 + 2.2.6";
  error = main_func(str5, &x, &result);
  ck_assert_int_eq(error, 1);

  char str7[] = "(22))(+13))";
  error = main_func(str7, &x, &result);
  ck_assert_int_eq(error, 1);

  char str8[] = "1+5mod2-sin(sin((-4)mod2))";
  error = main_func(str8, &x, &result);
  ck_assert_int_eq(error, 0);

  char str9[] =
      "1+5mod2-sin(4)-cos(8)-tan(1)-acos(9)+asin(78)-atan(8)*sqrt(4)*ln(9)*log("
      "x)";
  error = main_func(str9, &x, &result);
  ck_assert_int_eq(error, 0);

  char str10[] = "1+(-3)";
  error = main_func(str10, &x, &result);
  ck_assert_int_eq(error, 0);

  char str11[] = "1    +    3";
  error = main_func(str11, &x, &result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_main_func) {
  char str1[] = "(3-x)";
  double x = 3;
  double result = 0;
  int error = main_func(str1, &x, &result);
  ck_assert_int_eq(result, 0);

  char str2[] = "25 +4.6/ 4 - 54 * sqrt(4)";
  error = main_func(str2, &x, &result);
  ck_assert_int_eq(result, -81.85);

  char str3[] = "1+5mod2-sin(4)-cos(8)-tan(1)";
  error = main_func(str3, &x, &result);
  ck_assert_int_eq(result, 1.34489480446);

  char str4[] = "(cos(-2^4)^2)*5/3";
  error = main_func(str4, &x, &result);
  ck_assert_int_eq(result, 1.52851946709);

  char str5[] = "(ln(sqrt(+25))-(sin(-4)))";
  error = main_func(str5, &x, &result);
  ck_assert_int_eq(result, 0.0479164609);

  char str6[] = "atan(15) *(-34.67) / tan(30) * 34 mod 15 - acos(0.34)";
  error = main_func(str6, &x, &result);
  ck_assert_int_eq(result, 0.811596520796);
}
END_TEST

START_TEST(test_credit_func) {
  double payment;
  double over;
  double total;
  double sum = 200000;
  int month = 30;
  double proc = 10;
  int type = 1;
  credit_func(sum, month, proc, &payment, &over, &total, type);
  ck_assert_double_eq_tol(payment, 7562.0, 1);
  type = 2;
  credit_func(sum, month, proc, &payment, &over, &total, type);
  ck_assert_double_eq_tol(payment, 8333.0, 1);
}
END_TEST

int main() {
  Suite* s = suite_create("calc_tests");
  TCase* tc_core = tcase_create("Core");
  SRunner* sr = srunner_create(s);
  int number_failed;

  suite_add_tcase(s, tc_core);

  tcase_add_test(tc_core, test_error);
  tcase_add_test(tc_core, test_main_func);
  tcase_add_test(tc_core, test_credit_func);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
