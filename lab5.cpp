#include "lab5.h"

Lab5::Lab5(QWidget* parent)
    : GenericLab(parent)
{
    runBtn = new QPushButton(this);
    runBtn->setText("Run");
    runBtn->setGeometry(10, 10, 200, 30);
    connect(runBtn, SIGNAL(clicked(bool)), this, SLOT(run()));
}
