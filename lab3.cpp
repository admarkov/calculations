#include "lab3.h"

Lab3::Lab3(QWidget* parent)
    : GenericLab(parent)
{
    runBtn = new QPushButton(this);
    runBtn->setText("Run");
    runBtn->setGeometry(10, 10, 200, 30);
    connect(runBtn, SIGNAL(clicked(bool)), this, SLOT(run()));

    table = new QTableWidget(this);
    table->setRowCount(12);
    table->setColumnCount(10);
    table->setGeometry(10, 50, 1050, 400);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            table->setItem(i, j, new QTableWidgetItem);
        }
    }
    table->item(0, 0)->setText("x");
    table->item(0, 1)->setText("f(x)");
    table->item(0, 2)->setText("f`(x)");
    table->item(0, 3)->setText("f`(x) + O(h)");
    table->item(0, 4)->setText("O(h)");
    table->item(0, 5)->setText("f`(x) + O(h^2)");
    table->item(0, 6)->setText("O(h^2)");
    table->item(0, 7)->setText("f``(x)");
    table->item(0, 8)->setText("f``(x) + O(h^2)");
    table->item(0, 9)->setText("O(h^2)");
}
