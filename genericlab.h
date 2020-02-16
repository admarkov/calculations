#ifndef GENERICLAB_H
#define GENERICLAB_H

#include <QWidget>
#include <QLabel>
#include <QDialog>
#include <QListWidget>

class GenericLab : public QDialog
{
    Q_OBJECT
public:
    GenericLab(QWidget* parent);

    QListWidget* logging;

public slots:
    virtual void run() {}

};

#endif // GENERICLAB_H
