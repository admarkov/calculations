#include "lab1.h"

Lab1::Lab1(QWidget* w)
    : GenericLab(w)
{
    separatingStepLabel = new QLabel(this);
    separatingStepLabel->setText("Шаг отделения корней");
    separatingStepLabel->setGeometry(10, 10, 260, 30);

    separatingStepInput = new QLineEdit(this);
    separatingStepInput->setGeometry(300, 10, 200, 30);

    decreasingAccuracyLabel = new QLabel(this);
    decreasingAccuracyLabel->setText("eps сужения интервалов");
    decreasingAccuracyLabel->setGeometry(10, 50, 260, 30);

    decreasingAccuracyInput = new QLineEdit(this);
    decreasingAccuracyInput->setGeometry(300, 50, 200, 30);

    decreasingKLabel = new QLabel(this);
    decreasingKLabel->setText("Максимум итераций сужения");
    decreasingKLabel->setGeometry(10, 90, 260, 30);

    decreasingKInput = new QLineEdit(this);
    decreasingKInput->setGeometry(300, 90, 200, 30);

    calcBtn = new QPushButton(this);
    calcBtn->setText("Run");
    calcBtn->setGeometry(10, 130, 490, 30);
    connect(calcBtn, SIGNAL(clicked(bool)), this, SLOT(run()));
}

void Lab1::run() {
    separateRoots();
    decreaseIntervals();
    Newton();
    secantsMethod();
}
