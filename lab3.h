#ifndef LAB3_H
#define LAB3_H

#include "genericlab.h"
#include <cmath>
#include <vector>
#include <QTableWidget>
#include <QPushButton>

using std::vector;

class Lab3 : public GenericLab
{
public:
    Lab3(QWidget* parent);

    QTableWidget* table;
    QPushButton* runBtn;

    std::function<double(double)> f = [](double x) {
        return  std::exp(3 * x);
    };

    std::function<double(double, int)> dfdx = [](double x, int ord) {
        double der = exp(3 * x);
        while (ord) {
            der *= 3;
            --ord;
        }
        return der;
    };

    double h = 0.1;
    vector<double> X;
    vector<double> fx;
    vector<double> dfdxs;
    vector<double> ddfdxs;
    vector<double> Oh;
    vector<double> ddfdxs2;
    vector<double> Oh2;
    vector<double> d2fdx2s;
    vector<double> dd2fdx2s;
    vector<double> O2h2;

public slots:
    void run() override {
        for (double x = 0; x <= 1; x += 0.1) X.push_back(x);
        for (double x: X) fx.push_back(f(x));
        for (double x: X) dfdxs.push_back(dfdx(x, 1));
        for (double x: X)
            ddfdxs.push_back((f(x + h) - f(x)) / h);
        for (int i = 0; i < 11; i++)
            Oh.push_back(dfdxs[i] - ddfdxs[i]);
        for (double x: X)
            ddfdxs2.push_back((f(x + h) - f(x - h)) / (2 * h));
        for (int i = 0; i < 11; i++)
            Oh2.push_back(dfdxs[i] - ddfdxs2[i]);
        for (double x: X) d2fdx2s.push_back(dfdx(x, 2));
        for (double x: X)
            dd2fdx2s.push_back((f(x + h) - 2 * f(x) + f(x - h)) / (h * h));
        for (int i = 0; i < 11; i++)
            O2h2.push_back(d2fdx2s[i] - dd2fdx2s[i]);

        renderTable();

        {
            vector<double> H;
            vector<double> der;
            vector<double> delta;
            double x = 1;
            while (delta.size() < 2 || delta[delta.size() - 1] - delta[delta.size() - 2] <= 0) {
                H.push_back(h);
                der.push_back((f(x + h) - 2 * f(x) + f(x - h)) / (h * h));
                delta.push_back(abs(dfdx(x, 2) - der.back()));
                H.back() = int(H.back() * 1e5) / 1e5;
                der.back() = int(der.back() * 1e5) / 1e5;
                delta.back() = int(delta.back() * 1e5) / 1e5;
                h /= 2;
            }
            for (int i = 0; i < H.size(); i++) {
                QString at = "h = " + QString::number(H[i], 'g', 10);
                QString bt = "f``(1) + O(h^2) = " + QString::number(der[i], 'g', 10);
                QString ct = "погрешность = " + QString::number(delta[i], 'g', 10);
                logging->addItem(at + "\t" + bt + "\t" + ct);
            }
            logging->addItem("");
            logging->addItem("h_opt = 0.000135774");
            logging->addItem("");
        }

        {
            double x0 = 0.7;
            vector<double> xs = X;
            sort(begin(xs), end(xs), [x0](double l, double r) { return abs(l - x0) < abs(r - x0); });
            double difs[10][10];
            for (int i = 0; i < xs.size(); i++) {
                difs[0][i] = f(xs[i]);
            }
            for (int i = 1; i < 4; i++) {
                for (int j = 0; j + i < xs.size(); j++) {
                    difs[i][j] = (difs[i-1][j+1] - difs[i-1][j]) / (xs[j + i] - xs[j]);
                }
            }
            double derivative = 2 * difs[2][0] - 2 * difs[3][0] * (xs[0] + xs[1] + xs[2]) + 6 * difs[3][0] * x0;
            logging->addItem("y``(x) = 2*A_2 - 2*A_3 * (x0 + x1 + x2) + 6 * A_3 * x");
            logging->addItem("y``(" + QString::number(x0, 'g', 10) + ") = " + QString::number(derivative, 'g', 10));
            logging->addItem("погрешность: " + QString::number(abs(derivative - dfdx(x0, 2))));
        }
    }

public:
    void renderTable() {
        for (int i = 0; i < 11; i++) {
            table->item(i + 1, 0)->setText(QString::number(X[i], 'g', 8));
            table->item(i + 1, 1)->setText(QString::number(fx[i], 'g', 8));
            table->item(i + 1, 2)->setText(QString::number(dfdxs[i], 'g', 8));
            table->item(i + 1, 3)->setText(QString::number(ddfdxs[i], 'g', 8));
            table->item(i + 1, 4)->setText(QString::number(Oh[i], 'g', 8));
            table->item(i + 1, 5)->setText(QString::number(ddfdxs2[i], 'g', 8));
            table->item(i + 1, 6)->setText(QString::number(Oh2[i], 'g', 8));
            table->item(i + 1, 7)->setText(QString::number(d2fdx2s[i], 'g', 8));
            table->item(i + 1, 8)->setText(QString::number(dd2fdx2s[i], 'g', 8));
            table->item(i + 1, 9)->setText(QString::number(O2h2[i], 'g', 8));
        }
    }
};

#endif // LAB3_H
