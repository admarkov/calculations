#ifndef LAB1_H
#define LAB1_H

#include "genericlab.h"
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <functional>
#include <cmath>
#include <vector>

using std::pair;
using std::vector;

class Lab1 : public GenericLab
{
public:
    Lab1(QWidget* w);

    QLabel*    separatingStepLabel;
    QLineEdit* separatingStepInput;
    QLabel*    decreasingAccuracyLabel;
    QLineEdit* decreasingAccuracyInput;
    QLabel*    decreasingKLabel;
    QLineEdit* decreasingKInput;
    QPushButton* calcBtn;


    std::function<double(double)> f = [](double x) {
        return std::log(x) - (double)1/(x * x);
    };

    std::function<double(double)> derivative = [](double x) {
        return 1 / x + 2 / (x * x * x);
    };

    vector<pair<double,double>> rootsSegs;
    vector<double> NewtonRoots;

    void separateRoots() {
        logging->addItem("Отделение корней с шагом " + separatingStepInput->text() + "...");
        double h = separatingStepInput->text().toDouble();
        for (double x = h; x < 100; x += h) {
            if (f(x) * f(x + h) < 0) {
                logging->addItem("Найден корень на отрезке [" + QString::number(x, 'g', 10) + ", " + QString::number(x + h, 'g', 10) + "]");
                rootsSegs.emplace_back(x, x + h);
            }
        }
    }

    void decreaseIntervals() {
        logging->addItem("Сужение интервалов...");
        int k = decreasingKInput->text().toInt();
        double eps = decreasingAccuracyInput->text().toDouble();
        for (auto& seg: rootsSegs) {
            QString initial = "[" + QString::number(seg.first, 'g' ,10) + ", " + QString::number(seg.second, 'g', 10) + "]";
            int it = 0;
            double& a = seg.first;
            double& b = seg.second;
            while (b - a > eps && it < k) {
                if (f(a) == 0) b = a;
                if (f(b) == 0) a = b;
                double m = (a + b) / 2;
                if (f(m) == 0) a = b = m;
                if (f(a) * f(m) < 0) b = m;
                else a = m;
                it++;
            }
            logging->addItem(initial + " -> " + "[" + QString::number(a, 'g', 10) + ", " + QString::number(b, 'g', 10) + "]" + " (" + QString::number(it) + " итераций)");
        }
    }

    void Newton() {
        double eps = 0.000001;
        logging->addItem("Вычисление корней методом Ньютона c точностью " + QString::number(eps, 'g', 10));
        for (auto seg: rootsSegs) {
            double a = seg.first, b = seg.second;
            double x0 = (a + b) / 2 - 1;
            double x1 = (a + b) / 2;
            int it = 0;
            logging->addItem("x_0 = " + QString::number(x1, 'g', 10));
            while (abs(x1 - x0) > eps) {
                it++;
                x0 = x1;
                x1 = x0 - f(x0) / derivative(x0);
                logging->addItem("x_" + QString::number(it) + " = " + QString::number(x1, 'g', 10));
            }
            NewtonRoots.push_back(x1);
            logging->addItem("f(" + QString::number(x1, 'g', 10) + ") = 0");
        }
    }

    void secantsMethod() {
        double eps = 0.0001;
        logging->addItem("Вычисление корней методом секущих c точностью " + QString::number(eps, 'g', 10));
        int segn = -1;
        for (auto seg: rootsSegs) {
            segn++;
            double a = seg.first, b = seg.second;
            vector<double> x = {a, (a + b) / 2, b};
            int it = 0;
            logging->addItem("x_0 = " + QString::number(x[1], 'g', 10));
            logging->addItem("x_1 = " + QString::number(x[2], 'g', 10));
            while (abs(x[2] - x[1]) > eps) {
                it++;
                x[0] = x[1];
                x[1] = x[2];
                x[2] = x[1] - f(x[1]) / (f(x[1]) - f(x[0])) * (x[1] - x[0]);
                logging->addItem("x_" + QString::number(it) + " = " + QString::number(x[2], 'g', 10));
            }
            logging->addItem("f(" + QString::number(x[2], 'g', 10) + ") = 0");
            logging->addItem("|x - x*| = " + QString::number(std::abs(x[2] - NewtonRoots[segn]), 'g', 10));
        }
    }

public slots:
    void run() override;

};

#endif // LAB1_H
