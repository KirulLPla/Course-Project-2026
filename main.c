#include <stdio.h>
#include <math.h>

int main() {
    double x = 0.0;
    double q = 0.0;

    printf("Введите X: ");
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

    const double q0 = 45.00;
    const double dq_max = 11.0;
    double dq = fabs(q - q0);

    if (dq <= dq_max) {
        printf("STATE = Норма, X = %.2f, Q = %.2f\n", x, q);
    } else {
        printf("STATE = Отклонение (скачок)\n");
    }

    return 0;
}
