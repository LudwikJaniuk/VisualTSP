#include <iostream>
#include <sstream>

#include <QApplication>

#include "mainwindow.h"
#include "connectionthread.h"

using namespace std;

string port = "3000";
bool pretty_json = false;


int main(int argc, char** argv)
{
    QApplication application(argc, argv);
    MainWindow w;
    w.show();

    return application.exec();
}

