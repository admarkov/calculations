#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPushButton* openLab1Btn;
    QPushButton* openLab2Btn;
    QPushButton* openLab3Btn;
    QPushButton* openLab4Btn;
    QPushButton* openLab5Btn;

private:
    Ui::MainWindow *ui;

public slots:
    void openLab1();
    void openLab2();
    void openLab3();
    void openLab4();
    void openLab5();
};
#endif // MAINWINDOW_H
