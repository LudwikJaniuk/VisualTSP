#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "connectionthread.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

// These receive data to show in the gui.
public slots:
    void displaySending(QString result);
    void displaySolution(QString result);
    void displayError(QString err);

private slots:
    // This function must be named exactly like this, it's generated by Qt. Kinda. I think.
    void on_SendButton_clicked();

    void on_xSlider_valueChanged(int value);
    void on_ySlider_valueChanged(int value);
    void on_zSlider_valueChanged(int value);

    void on_ScaleSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    // We'll use this to send the problem and wait for an answer without blocking the GUI.
    ConnectionThread conThread;
};

#endif // MAINWINDOW_H
