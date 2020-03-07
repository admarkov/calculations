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

    double Gauss() {
        double a = 0, b = 1;
        auto sd = (b - a) / 2;
        auto ss = (b + a) / 2;
        auto x1 = -1/sqrt(3), x2 = 1/sqrt(3);
        return sd * (f(sd * x1 + ss) + f(sd * x2 + ss));
    }

    double Gassa() {
        double m0 = 1.3333333333;
        double m1 = 0.7619047619;
        double m2 = 0.55411255411;
        double m3 = 0.44329004329;

        logging->addItem("m0 = " + QString::number(m0, 'g', 10));
        logging->addItem("m1 = " + QString::number(m1, 'g', 10));
        logging->addItem("m2 = " + QString::number(m2, 'g', 10));
        logging->addItem("m3 = " + QString::number(m3, 'g', 10));

        double a1 = (m0 * m3 - m2 * m1) / (m1 * m1 - m2 * m0);
        double a2 = (m2 * m2 - m3 * m1) / (m1 * m1 - m2 * m0);

        double x1 = (-a1 - sqrt(a1 * a1 - 4 * a2)) / 2;
        double x2 = (-a1 + sqrt(a1 * a1 - 4 * a2)) / 2;

        logging->addItem("x1 = " + QString::number(x1, 'g', 10));
        logging->addItem("x2 = " + QString::number(x2, 'g', 10));

        double A1 = (m1 - x2 * m0) / (x1 - x2);
        double A2 = (m1 - x1 * m0) / (x2 - x1);

        logging->addItem("A1 = " + QString::number(A1, 'g', 10));
        logging->addItem("A2 = " + QString::number(A2, 'g', 10));

        logging->addItem("A1 + A2 = " + QString::number(A1 + A2, 'g', 10) + " ;  m0 = " + QString::number(m0, 'g', 10));

        return A1 * f(x1) + A2 * f(x2);
    }

    void run() override {
        logging->addItem("Точное значение: 1.0714361983");

        logging->addItem("");
        logging->addItem("Формула средних прямоугольников с 3 узлами: " + QString::number(simpleIntegral(0, 1, 3), 'g', 10));
        logging->addItem("Погрешность: " + QString::number(abs(accurate - simpleIntegral(0, 1, 3)), 'g', 10));

        logging->addItem("");
        logging->addItem("Квадратурная формула с весовой функцией 1/(1 - x)^(1/4): " + QString::number(interpolIntegral(), 'g', 10));
        logging->addItem("Погрешность: " + QString::number(abs(accurate - interpolIntegral()), 'g', 10));

        logging->addItem("");
        logging->addItem("По формуле Гаусса (2 узла): " + QString::number(Gauss(), 'g', 10));
        logging->addItem("Погрешность: " + QString::number(abs(accurate - Gauss()), 'g', 10));

        logging->addItem("");
        double gassa = Gassa();
        logging->addItem("По формуле типа Гаусса (2 узла): " + QString::number(gassa, 'g', 10));
        logging->addItem("Погрешность: " + QString::number(abs(gassa - accurate), 'g', 10));

    }
};

#endif // LAB4_H
