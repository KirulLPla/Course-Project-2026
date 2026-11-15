#include <stdio.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define X_MIN        5.0
#define X_MAX        70.0
#define X_NORM_LO    25.0
#define X_NORM_HI    48.0
#define Q0           45.0
#define DQ_MAX       11.0
#define DQ_ALARM     25.0
#define Q_MIN_SAFE   10.0
#define N_MEASURES   70

#define STATE_NORMAL  1
#define STATE_WARNING 2
#define STATE_ALARM   3

int validate_x(double x);
double calculate_q(double x);
int check_control(double q);
int read_input(double* x);
int run_self_tests(void);

int process_series(int n);
int print_report(int n);

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    double x = 0.0;
    double q = 0.0;
    int state = 0;
    int tests_passed = 0;

    printf("=====================================================\n");
    printf("Программа мониторинга расхода продукта в реакторе\n");
    printf("=====================================================\n\n");

    tests_passed = run_self_tests();
    if (tests_passed == 1) {
        printf("Результат автотестов (3 случая): ВСЕ ПРОЙДЕНЫ\n\n");
    }
    else {
        printf("Результат автотестов: ОБНАРУЖЕНЫ РАСХОЖДЕНИЯ\n\n");
    }

    printf("Введите расход X (от %.1f до %.1f л/мин): ", X_MIN, X_MAX);
    if (read_input(&x) != 1) {
        printf("Ошибка: введено не число!\n");
        return 1;
    }

    if (validate_x(x) != 1) {
        printf("Ошибка: X = %.2f не входит в область допустимых значений [%.1f; %.1f]!\n",
            x, X_MIN, X_MAX);
        return 1;
    }

    q = calculate_q(x);

    state = check_control(q);

    printf("\n--- Результаты мониторинга ---\n");
    printf("Расход X = %.2f л/мин\n", x);
    printf("Значение Q = %.2f\n", q);

    if (state == STATE_NORMAL) {
        printf("STATE: НОРМА (|Q - Q0| <= %.2f)\n", DQ_MAX);
    }
    else if (state == STATE_WARNING) {
        printf("STATE: ПРЕДУПРЕЖДЕНИЕ (отклонение |Q - Q0| > %.2f)\n", DQ_MAX);
    }
    else {
        printf("STATE: ТРЕВОГА (критическое отклонение показателя Q)\n");
    }

    return 0;
}

int read_input(double* x) {
    if (x == NULL) {
        return 0;
    }
    if (scanf("%lf", x) != 1) {
        return 0;
    }
    return 1;
}

int validate_x(double x) {
    if (x < X_MIN || x > X_MAX) {
        return 0;
    }
    if (x > X_NORM_HI && (x - X_NORM_HI + 1.0) < 0.0) {
        return 0;
    }
    return 1;
}

double calculate_q(double x) {
    if (x < X_NORM_LO) {
        return 2.0 * (x - X_NORM_LO) + 10.0;
    }
    else if (x <= X_NORM_HI) {
        return pow(x - 36.5, 2.0) / 7.0 + Q0;
    }
    else {
        return 3.0 * sqrt(x - X_NORM_HI + 1.0) + 55.0;
    }
}

int check_control(double q) {
    double diff = fabs(q - Q0);

    if (diff <= DQ_MAX) {
        return STATE_NORMAL;
    }
    else if (diff <= DQ_ALARM && q >= Q_MIN_SAFE) {
        return STATE_WARNING;
    }
    else {
        return STATE_ALARM;
    }
}

int run_self_tests(void) {
    double x1 = 30.0;
    double q1 = calculate_q(x1);
    int st1 = check_control(q1);

    double x2 = 25.0;
    double q2 = calculate_q(x2);
    int st2 = check_control(q2);

    double x3 = 20.0;
    double q3 = calculate_q(x3);
    int st3 = check_control(q3);

    int ok_count = 0;

    printf("[Тест 1 - Норма]   X = %.2f -> Q = %.2f (ожид. 51.04) | STATE = %d (НОРМА)\n", x1, q1, st1);
    if (fabs(q1 - 51.04) < 0.01 && st1 == STATE_NORMAL) {
        ok_count = ok_count + 1;
    }

    printf("[Тест 2 - Граница] X = %.2f -> Q = %.2f (ожид. 63.89) | STATE = %d (ПРЕДУПРЕЖДЕНИЕ)\n", x2, q2, st2);
    if (fabs(q2 - 63.89) < 0.01 && st2 == STATE_WARNING) {
        ok_count = ok_count + 1;
    }

    printf("[Тест 3 - Авария]  X = %.2f -> Q = %.2f (ожид. 0.00)  | STATE = %d (ТРЕВОГА)\n", x3, q3, st3);
    if (fabs(q3 - 0.00) < 0.01 && st3 == STATE_ALARM) {
        ok_count = ok_count + 1;
    }

    if (ok_count == 3) {
        return 1;
    }
    return 0;
}

int process_series(int n) {
    (void)n;
    return 0;
}

int print_report(int n) {
    (void)n;
    return 0;
}
