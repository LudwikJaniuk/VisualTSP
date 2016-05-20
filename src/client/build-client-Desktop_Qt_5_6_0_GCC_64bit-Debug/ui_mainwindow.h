/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *HostLine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *PortLine;
    QPushButton *SendButton;
    QLabel *SendingLabel;
    QLabel *ResponseLabel;
    QLabel *ErrorLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(907, 620);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 30, 651, 471));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        HostLine = new QLineEdit(layoutWidget);
        HostLine->setObjectName(QStringLiteral("HostLine"));

        horizontalLayout_2->addWidget(HostLine);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        PortLine = new QLineEdit(layoutWidget);
        PortLine->setObjectName(QStringLiteral("PortLine"));

        horizontalLayout_3->addWidget(PortLine);


        verticalLayout_2->addLayout(horizontalLayout_3);

        SendButton = new QPushButton(layoutWidget);
        SendButton->setObjectName(QStringLiteral("SendButton"));

        verticalLayout_2->addWidget(SendButton);

        SendingLabel = new QLabel(layoutWidget);
        SendingLabel->setObjectName(QStringLiteral("SendingLabel"));
        SendingLabel->setWordWrap(true);

        verticalLayout_2->addWidget(SendingLabel);

        ResponseLabel = new QLabel(layoutWidget);
        ResponseLabel->setObjectName(QStringLiteral("ResponseLabel"));
        ResponseLabel->setWordWrap(true);

        verticalLayout_2->addWidget(ResponseLabel);

        ErrorLabel = new QLabel(layoutWidget);
        ErrorLabel->setObjectName(QStringLiteral("ErrorLabel"));
        ErrorLabel->setWordWrap(true);

        verticalLayout_2->addWidget(ErrorLabel);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 907, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Host", 0));
        label_2->setText(QApplication::translate("MainWindow", "Port", 0));
        SendButton->setText(QApplication::translate("MainWindow", "Send Problem", 0));
        SendingLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        ResponseLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        ErrorLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
