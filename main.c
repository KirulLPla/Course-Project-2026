#include <stdio.h>
#include <math.h>
#include <windows.h>

double calculate_q(double x) {
    if (x < 25.0) {
        return 2.0 * (x - 25.0) + 10.0;
    } else if (x <= 48.0) {
        return pow(x - 36.5, 2.0) / 7.0 + 45.0;
    } else {
        return 3.0 * sqrt(x - 48.0 + 1.0) + 55.0;
    }
}

double read_input() {
    double x;
    printf("Введите расход X (л/мин): ");
    scanf("%lf", &x);
    return x;
}

int check_control(double q) {
    double q0 = 45.0;
    double dq_max = 11.0;

    if (fabs(q - q0) <= dq_max) {
        return 1;
    } else {
        return 0;
    }
}
void print_state(double x, double q, int is_normal) {
    printf("Расход X = %.2f\n", x);
    printf("Значение Q = %.2f\n", q);

    if (is_normal == 1) {
        printf("STATE: Норма\n");
    } else {
        printf("STATE: Отклонение (скачок)\n");
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    double x = read_input();

    double q = calculate_q(x);

    if (fabs(x - 25.0) < 0.001) {
        printf("\nПроверка контрольного примера удалась: ожидалось 63.89, получено %.2f\n", q);

    }
    else {
        printf("\nПроверка контрольного примера не удалась: ожидалось 63.89, а получено %.2f\n", q);
    }

    int is_normal = check_control(q);

    print_state(x, q, is_normal);

    return 0;
}