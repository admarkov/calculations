#include "lab2.h"

Lab2::Lab2(QWidget* parent)
    : GenericLab(parent)
{
    runBtn = new QPushButton(this);
    runBtn->setText("Run");
    runBtn->setGeometry(10, 10, 200, 30);
    connect(runBtn, SIGNAL(clicked(bool)), this, SLOT(run()));

    dtable = new QTableWidget(this);
    dtable->setRowCount(6);
    dtable->setColumnCount(5);
    dtable->setGeometry(10, 50, 530, 205);

    rtable = new QTableWidget(this);
    rtable->setRowCount(6);
    rtable->setColumnCount(5);
    rtable->setGeometry(10, 260, 530, 205);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            rtable->setItem(i, j, new QTableWidgetItem);
        }
    }
    rtable->item(0, 0)->setText("i");
    rtable->item(1, 0)->setText("x_i");
    rtable->item(2, 0)->setText("P_i(x*)");
    rtable->item(3, 0)->setText("f(x*) - P_i(x*)");
    rtable->item(4, 0)->setText("M_{i+1}");
    rtable->item(5, 0)->setText("R_i(x*)");
    rtable->item(0, 1)->setText("0");
    rtable->item(0, 2)->setText("1");
    rtable->item(0, 3)->setText("2");
    rtable->item(0, 4)->setText("3");
}

