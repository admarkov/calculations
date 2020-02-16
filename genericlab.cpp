#include "genericlab.h"
#include <QLabel>

GenericLab::GenericLab(QWidget* parent)
    : QDialog(parent)
{

    int w = 1200, h = 800;
    setFixedSize(w, h);

    logging = new QListWidget(this);
    logging->setGeometry(0, h - 300, w, 300);

}
