#ifndef LAB4_H
#define LAB4_H

#include "genericlab.h"

#include <QPushButton>

#include <cmath>

class Lab4 : public GenericLab
{
public:
    Lab4(QWidget* parent);

    QPushButton* runBtn;

    double f(double x) {
        return cos(x) / sqrt(sqrt(1 - x));
    }

    double accurate = 1.0714361983;

    double simpleIntegral(double a, double b, double n) {
        double h = (b - a) / (n - 1);
        double res = 0;
        while (a < b) {
            res += h * f(a + h / 2);
            a += h;
        }
        return res;
    }

    double AIntegral(double a, double b) {
        return 4 * (11 * a * (7 * b - 4) - 44 * b + 32) / 231;
    }

    double interpolIntegral() {
        double x1 = 1./6., x2 = 1./2., x3 = 5./6.;

        auto p = [](double x) { return 1 / sqrt(sqrt(1 - x)); };
        auto F = [](double x) { return cos(x); };

         double A1 = AIntegral(x2, x3) / (x1 - x2) / (x1 - x3);
         double A2 = AIntegral(x1, x3) / (x2 - x1) / (x2 - x3);
         double A3 = AIntegral(x1, x2) / (x3 - x1) / (x3 - x2);

         return A1 * F(x1) + A2 * F(x2) + A3 * F(x3);
    }

    void run() override {
        logging->addItem("Точное значение: 1.0714361983");
        logging->addItem("Формула средних прямоугольников с 3 узлами: " + QString::number(simpleIntegral(0, 1, 3), 'g', 10));
        logging->addItem("Погрешность: " + QString::number(abs(accurate - simpleIntegral(0, 1, 3)), 'g', 10));

        logging->addItem("Квадратурная формула с весовой функцией 1/(1 - x)^(1/4): " + QString::number(interpolIntegral(), 'g', 10));
        logging->addItem("Погрешность: " + QString::number(abs(accurate - interpolIntegral()), 'g', 10));

    }
};

#endif // LAB4_H
