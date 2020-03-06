#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lab1.h"
#include "lab2.h"
#include "lab3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(600, 600);

    openLab1Btn = new QPushButton(this);
    openLab1Btn->setText("Нахождение корней уравнения");
    openLab1Btn->setGeometry(5, 5, 590, 40);
    connect(openLab1Btn, SIGNAL(clicked(bool)), this, SLOT(openLab1()));

    openLab2Btn = new QPushButton(this);
    openLab2Btn->setText("Интерполирование");
    openLab2Btn->setGeometry(5, 50, 590, 40);
    connect(openLab2Btn, SIGNAL(clicked(bool)), this, SLOT(openLab2()));

    openLab3Btn = new QPushButton(this);
    openLab3Btn->setText("Численное дифференцирование");
    openLab3Btn->setGeometry(5, 95, 590, 40);
    connect(openLab3Btn, SIGNAL(clicked(bool)), this, SLOT(openLab3()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openLab1() {
    auto lab = new Lab1(this);
    lab->show();
}

void MainWindow::openLab2() {
    auto lab = new Lab2(this);
    lab->show();
}

void MainWindow::openLab3() {
    auto lab = new Lab3(this);
    lab->show();
}
