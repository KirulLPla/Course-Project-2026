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
#define N_MEASURES   70

double calculate_q(double x);
int check_control(double q);
void run_self_test(void);
void process_series(int n);
void print_report(int n);

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    double x = 0.0;
    double q = 0.0;
    int is_normal = 0;

    printf("=====================================================\n");
    printf("Программа мониторинга расхода продукта в реакторе\n");
    printf("Вводит X (л/мин), вычисляет Q(X) и определяет состояние.\n");
    printf("=====================================================\n\n");

    run_self_test();

    printf("Введите расход X (от %.1f до %.1f л/мин): ", X_MIN, X_MAX);
    if (scanf("%lf", &x) != 1) {
        printf("Ошибка: введено не число!\n");
        return 1;
    }

    if (x < X_MIN || x > X_MAX) {
        printf("Ошибка: число вне диапазона от %.1f до %.1f!\n", X_MIN, X_MAX);
        return 1;
    }

    q = calculate_q(x);

    is_normal = check_control(q);

    printf("\n--- Результаты мониторинга ---\n");
    printf("Расход X = %.2f л/мин\n", x);
    printf("Значение Q = %.2f\n", q);

    if (is_normal == 1) {
        printf("STATE: Норма (|Q - Q0| <= %.2f)\n", DQ_MAX);
    } else {
        printf("STATE: Отклонение (скачок |Q - Q0| > %.2f)\n", DQ_MAX);
    }

    return 0;
}

double calculate_q(double x) {
    if (x < X_NORM_LO) {
        return 2.0 * (x - X_NORM_LO) + 10.0;
    } else if (x <= X_NORM_HI) {
        return pow(x - 36.5, 2.0) / 7.0 + Q0;
    } else {
        return 3.0 * sqrt(x - X_NORM_HI + 1.0) + 55.0;
    }
}

int check_control(double q) {
    if (fabs(q - Q0) <= DQ_MAX) {
        return 1;
    } else {
        return 0;
    }
}

void run_self_test(void) {
    double test_x = 25.00;
    double expected_q = 63.89;
    double actual_q = calculate_q(test_x);

    printf("[Самоконтроль] Тест X = %.2f -> Q = %.2f (ожидается %.2f)... ",
           test_x, actual_q, expected_q);

    if (fabs(actual_q - expected_q) < 0.01) {
        printf("OK\n\n");
    } else {
        printf("Ошибка\n\n");
    }
}

void process_series(int n) {
    (void)n;
}

void print_report(int n) {
    (void)n;
}