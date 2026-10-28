#include <iostream>
#include <cmath>
#include <iomanip> // (setprecision)

using namespace std;

// ОПИСАНИЕ ФУНКЦИЙ УРАВНЕНИЙ

// Уравнение 1: sqrt(x) - 3*cos(0.39x) = 0
double f1(double x) {
    return sqrt(x) - 3.0 * cos(0.39 * x);
}

// Уравнение 2: x^3 - 0.2x^2 + 0.5x + 1.4 = 0
double f2(double x) {
    return pow(x, 3) - 0.2 * pow(x, 2) + 0.5 * x + 1.4;
}

// Структура для возврата двух значений (корень и число итераций)
struct Result {
    double root;
    int iterations;
};

// МЕТОД БИСЕКЦИЙ (ПОЛОВИННОГО ДЕЛЕНИЯ)

Result bisection(double (*func)(double), double a, double b, double eps) {
    if (func(a) * func(b) > 0) {
        cout << "Ошибка: корни не отделены!" << endl;
        return { 0, 0 };
    }

    int it = 0;
    while ((b - a) >= eps) {
        double c = (a + b) / 2.0;

        if (func(a) * func(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        it++;
    }
    return { (a + b) / 2.0, it };
}

// МЕТОД ХОРД

Result chord_method(double (*func)(double), double a, double b, double eps) {
    int it = 0;
    double c_prev = a; // Начальное значение предыдущего шага
    double c;

    while (true) {
        // Формула хорд
        c = (a * func(b) - b * func(a)) / (func(b) - func(a));

        if (func(a) * func(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        it++;

        // Условие остановки |c_i+1 - c_i| < eps
        if (abs(c - c_prev) < eps) {
            break;
        }
        c_prev = c;
    }
    return { c, it };
}


int main() {

    setlocale(LC_ALL, "Russian");

    // Устанавливаем точность вывода и погрешность
    cout << fixed << setprecision(5);
    double eps = 0.0001;

    cout << "--- Уравнение 1: sqrt(x) - 3*cos(0.39x) = 0 ---" << endl;
    cout << "Отрезок: [2, 3]" << endl;

    Result res1_bis = bisection(f1, 2.0, 3.0, eps);
    cout << "Метод бисекций: корень = " << res1_bis.root
        << " (итераций: " << res1_bis.iterations << ")" << endl;

    Result res1_chord = chord_method(f1, 2.0, 3.0, eps);
    cout << "Метод хорд:     корень = " << res1_chord.root
        << " (итераций: " << res1_chord.iterations << ")" << endl;

    cout << "\n-------------------------------------------------" << endl;

    cout << "--- Уравнение 2: x^3 - 0.2x^2 + 0.5x + 1.4 = 0 ---" << endl;
    cout << "Отрезок: [-1, 0]" << endl;

    Result res2_bis = bisection(f2, -1.0, 0.0, eps);
    cout << "Метод бисекций: корень = " << res2_bis.root
        << " (итераций: " << res2_bis.iterations << ")" << endl;

    Result res2_chord = chord_method(f2, -1.0, 0.0, eps);
    cout << "Метод хорд:     корень = " << res2_chord.root
        << " (итераций: " << res2_chord.iterations << ")" << endl;

    return 0;
}