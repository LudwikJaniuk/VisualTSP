#include "mainwindow.h"
#include "connectionthread.h"
#include "ui_mainwindow.h"

#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect signals & slots so that when a certain signal fires, the specified slot receives it.
    // This is a QT-specific feature.
    connect(&conThread, SIGNAL(solution(QString)), this, SLOT(displaySolution(QString)));
    connect(&conThread, SIGNAL(sendingJson(QString)), this, SLOT(displaySending(QString)));
    connect(&conThread, SIGNAL(error(QString)), this, SLOT(displayError(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displaySending(QString json) {
    ui->SendingLabel->setText(json);
}

void MainWindow::displaySolution(QString json) {
    ui->ResponseLabel->setText(json);
}

void MainWindow::displayError(QString err) {
    ui->ErrorLabel->setText(err);
}

void MainWindow::on_SendButton_clicked()
{
    ui->SendingLabel->setText("SLAMANADER");
    conThread.sendProblem("127.0.0.1", "3000");
}

void MainWindow::on_xSlider_valueChanged(int value)
{
    ui->openGLWidget->setXRotation(value);
}

void MainWindow::on_ySlider_valueChanged(int value)
{
    ui->openGLWidget->setYRotation(value);
}

void MainWindow::on_zSlider_valueChanged(int value)
{
    ui->openGLWidget->setZRotation(value);
}
