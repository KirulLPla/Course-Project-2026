#include <stdio.h>
#include <math.h>

int main() {
    double x = 0.0;
    double q = 0.0;

    if (fabs(x - 25.00) < 0.001) {
        const double expected_q = 63.89;
        if (fabs(q - expected_q) < 0.01) {
            printf("[Контрольный пример пройден: ожидалось %.2f, получено %.2f]\n", expected_q, q);
        } else {
            printf("[Ошибка контрольного примера: ожидалось %.2f, получено %.2f]\n", expected_q, q);
        }
    }

    printf("Введите X (л/мин): ");
    if (scanf("%lf", &x) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    if (x < 25.0) {
        q = 2.0 * (x - 25.0) + 10.0;
    } else if (x <= 48.0) {
        q = pow(x - 36.5, 2.0) / 7.0 + 45.0;
    } else {
        q = 3.0 * sqrt(x - 48.0 + 1.0) + 55.0;
    }

    printf("Результат: Q = %.2f\n", q);

    const double q0 = 45.00;
    const double dq_max = 11.0;
    double dq = fabs(q - q0);

    if (dq <= dq_max) {
        printf("STATE = Норма (X = %.2f, Q = %.2f)\n", x, q);
    } else {
        printf("STATE = Отклонение (скачок |Q - Q0| = %.2f > %.2f)\n", dq, dq_max);
    }

    return 0;
}