#ifndef LAB2_H
#define LAB2_H

#include "genericlab.h"

#include <QTableWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>

#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>

using std::vector;
using std::sort;

class Lab2 : public GenericLab
{
public:
    Lab2(QWidget* parent);

    QTableWidget* dtable;
    QTableWidget* rtable;
    QPushButton* runBtn;

    double f(double x) {
        return std::sin(x);
    }

    std::function<double(double)> der[5] {
        [](double x) { return sin(x); },
        [](double x) { return cos(x); },
        [](double x) { return -sin(x); },
        [](double x) { return -cos(x); },
        [](double x) { return sin(x); }
    };

    vector<double> x = {-0.6, -0.5, -0.3, -0.2, 0, 0.1};
    double X = -0.4;
    double Y = -0.6;

    double d[4][6];

    void printD() {
        for (int i = 0; i < x.size(); i++) {
            auto it = new QTableWidgetItem;
            it->setText(QString::number(x[i], 'g', 6));
            dtable->setItem(i, 0, it);
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                auto it = new QTableWidgetItem;
                it->setText(QString::number(d[i][j], 'g', 6));
                dtable->setItem(j, i + 1, it);
            }
        }
    }

    double calc(int i, double y) {
        double res = d[0][0];
        double P = 1;
        for (int j = 0; j < i; j++) {
            P *= y - x[j];
            res += d[j + 1][0] * P;
        }
        return res;
    }

    double calc(double y) {
        return calc(3, y) - Y;
    }

    void interpolate() {
        sort(begin(x), end(x), [X = X](double a, double b) {
            return abs(X - a) < abs(X - b);
        });
        for (int i = 0; i < x.size(); i++) {
            d[0][i] = f(x[i]);
        }
        for (int i = 1; i < 4; i++) {
            for (int j = 0; j + i < 6; j++) {
                d[i][j] = (d[i-1][j+1] - d[i-1][j]) / (x[j + i] - x[j]);
            }
        }
        printD();
        logging->addItem("A0 = " + QString::number(d[0][0], 'g', 10));
        logging->addItem("A1 = " + QString::number(d[1][0], 'g', 10));
        logging->addItem("A2 = " + QString::number(d[2][0], 'g', 10));
        logging->addItem("A3 = " + QString::number(d[3][0], 'g', 10));
        vector<double> M(5);
        // отрезок [-0.6, 0.1]
        M[1] = 1;
        M[2] = abs(sin(-0.6));
        M[3] = 1;
        M[4] = abs(sin(-0.6));

        double P = 1;
        double fact = 1;
        vector<double> R(4);
        for (int i = 0; i < 4; i++) {
            P *= abs(X - x[i]);
            fact *= i + 1;
            R[i] = P * M[i+1] / fact;
        }

        for (int i = 0; i < 4; i++) {
            rtable->item(1, i + 1)->setText(QString::number(x[i]));
        }
        for (int i = 0; i < 4; i++) {
            rtable->item(2, i + 1)->setText(QString::number(calc(i, X)));
        }
        for (int i = 0; i < 4; i++) {
            rtable->item(3, i + 1)->setText(QString::number(f(X) - calc(i, X)));
        }
        for (int i = 0; i < 4; i++) {
            rtable->item(4, i + 1)->setText(QString::number(M[i + 1]));
        }
        for (int i = 0; i < 4; i++) {
            rtable->item(5, i + 1)->setText(QString::number(R[i]));
        }
    }

    void reverseinterpolate() {
        vector<double> roots;
        double eps = 0.0000001;
        for (double x = -1; x <= 1; x += eps) {
            if (calc(x) * calc(x + eps) < 0) roots.push_back(x);
            if (calc(x) == 0) roots.push_back(x);
        }
        logging->addItem("Найдено корней: " + QString::number(roots.size()));
        for (double r: roots) {
            logging->addItem("f(" + QString::number(r) + ") = " + QString::number(calc(r) + Y) + " (" + QString::number(f(r)) + ")");
        }
    }

    void run() override {
        interpolate();
        reverseinterpolate();
    }

};

#endif // LAB2_H
