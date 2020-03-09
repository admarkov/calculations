#ifndef LAB5_H
#define LAB5_H

#include "genericlab.h"

#include <QPushButton>

#include <vector>

using std::vector;
using std::pair;

class Lab5 : public GenericLab
{
public:
    Lab5(QWidget* parent);
    ~Lab5() = default;

    QPushButton* runBtn;

    vector<double> b = {200, -600};
    vector<double> b2 = {199, -601};
    using matrix = vector<vector<double>>;
    matrix A;

    double det(matrix a) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }

    pair<double,double> solve(matrix a, vector<double> b) {
        matrix C = a;
        C[0][0] = b[0];
        C[1][0] = b[1];
        double x = det(C) / det(a);
        C = a;
        C[0][1] = b[0];
        C[1][1] = b[1];
        double y = det(C) / det(a);
        return {x, y};
    }

    matrix T(matrix a) {
        auto c = a;
        std::swap(c[1][0], c[0][1]);
        return c;
    }

    double norm(vector<double> v) {
        return std::max(abs(v[0]), abs(v[1]));
    }

    double norm(matrix a) {
        return std::max(abs(a[0][0]) + abs(a[0][1]), abs(a[1][0]) + abs(a[1][1]));
    }

    double norm(pair<double,double> p) {
        return norm(vector<double>({p.first, p.second}));
    }

    matrix alg(matrix a) {
        return {
            {a[1][1], -a[1][0]},
            {-a[0][1], a[0][0]}
        };
    }

    matrix mul(matrix a, matrix b) {
        return {
          {a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]},
          {a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]}
        };
    }

    matrix inv(matrix a) {
        auto res = T(alg(a));
        auto d = det(a);
        res[0][0] /= d;
        res[0][1] /= d;
        res[1][0] /= d;
        res[1][1] /= d;
        return res;
    }

    double cond(matrix a) {
        return norm(a) * norm(inv(a));
    }

    vector<double> diff(pair<double,double> a, pair<double, double> b) {
        return {a.first - b.first, a.second - b.second};
    }

    vector<double> diff(vector<double> a, vector<double> b) {
        return {a[0] - b[0], a[1] - b[1]};
    }

    double error(matrix a, matrix da, vector<double> b, vector<double> db) {
        return (cond(a) / (1 - cond(a) * norm(da) / norm(a))) * (norm(db) / norm(b) + norm(da) / norm(a));
    }

    matrix zero() {
        return {
            {0, 0},
            {0, 0}
        };
    }

    void run() override {
        A.resize(2);
        A[0].resize(2); A[1].resize(2);
        A[0][0] = -402.9;
        A[0][1] = 200.7;
        A[1][0] = 1204.2;
        A[1][1] = -603.6;

        logging->addItem("Решение системы методом Крамера");
        auto solution = solve(A, b);
        logging->addItem("x = " + QString::number(solution.first) + "; y = " + QString::number(solution.second));
        logging->addItem("Проверка: A(x, y) = ");
        logging->addItem(QString::number(A[0][0] * solution.first + A[0][1] * solution.second));
        logging->addItem(QString::number(A[1][0] * solution.first + A[1][1] * solution.second));

        logging->addItem("");
        logging->addItem("Решение измененной системы методом Крамера");
        auto solution2 = solve(A, b2);
        logging->addItem("x = " + QString::number(solution2.first) + "; y = " + QString::number(solution2.second));
        logging->addItem("Проверка: A(x, y) = ");
        logging->addItem(QString::number(A[0][0] * solution2.first + A[0][1] * solution2.second));
        logging->addItem(QString::number(A[1][0] * solution2.first + A[1][1] * solution2.second));

        logging->addItem("");
        logging->addItem("condA = " + QString::number(cond(A)));
        logging->addItem("Относительная погрешность = " + QString::number(norm(diff(solution, solution2)) / norm(solution)));

        logging->addItem("Теоретическая погрешность = " + QString::number(error(A, zero(), b, diff(b2, b))));
    }
};

#endif // LAB5_H
