/********************************************************************************
** Form generated from reading UI file 'mt940.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MT940_H
#define UI_MT940_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MT940
{
public:
    QAction *LoadReport;
    QAction *actionSave_to_MT940;
    QAction *actionExit;
    QWidget *centralwidget;
    QTableWidget *tLista;
    QTableWidget *tWynik;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MT940)
    {
        if (MT940->objectName().isEmpty())
            MT940->setObjectName(QString::fromUtf8("MT940"));
        MT940->resize(1500, 853);
        LoadReport = new QAction(MT940);
        LoadReport->setObjectName(QString::fromUtf8("LoadReport"));
        actionSave_to_MT940 = new QAction(MT940);
        actionSave_to_MT940->setObjectName(QString::fromUtf8("actionSave_to_MT940"));
        actionExit = new QAction(MT940);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MT940);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tLista = new QTableWidget(centralwidget);
        tLista->setObjectName(QString::fromUtf8("tLista"));
        tLista->setGeometry(QRect(60, 60, 1241, 371));
        tWynik = new QTableWidget(centralwidget);
        tWynik->setObjectName(QString::fromUtf8("tWynik"));
        tWynik->setGeometry(QRect(70, 440, 1241, 371));
        MT940->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MT940);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1500, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MT940->setMenuBar(menubar);
        statusbar = new QStatusBar(MT940);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MT940->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(LoadReport);
        menuFile->addAction(actionSave_to_MT940);
        menuFile->addAction(actionExit);

        retranslateUi(MT940);
        QObject::connect(menubar, SIGNAL(triggered(QAction*)), MT940, SLOT(menu(QAction*)));

        QMetaObject::connectSlotsByName(MT940);
    } // setupUi

    void retranslateUi(QMainWindow *MT940)
    {
        MT940->setWindowTitle(QCoreApplication::translate("MT940", "MT940", nullptr));
        LoadReport->setText(QCoreApplication::translate("MT940", "Load report file", nullptr));
        actionSave_to_MT940->setText(QCoreApplication::translate("MT940", "Save to MT940", nullptr));
        actionExit->setText(QCoreApplication::translate("MT940", "Exit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MT940", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MT940: public Ui_MT940 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MT940_H
