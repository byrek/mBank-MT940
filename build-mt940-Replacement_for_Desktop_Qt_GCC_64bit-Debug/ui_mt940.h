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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MT940
{
public:
    QWidget *centralwidget;
    QTableWidget *tLista;
    QTableWidget *tWynik;
    QPushButton *pushButton;
    QPlainTextEdit *saldo_poczatkowe;
    QMenuBar *menubar;
    QMenu *menuPlik;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MT940)
    {
        if (MT940->objectName().isEmpty())
            MT940->setObjectName(QString::fromUtf8("MT940"));
        MT940->resize(1500, 853);
        centralwidget = new QWidget(MT940);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tLista = new QTableWidget(centralwidget);
        tLista->setObjectName(QString::fromUtf8("tLista"));
        tLista->setGeometry(QRect(60, 60, 1241, 371));
        tWynik = new QTableWidget(centralwidget);
        tWynik->setObjectName(QString::fromUtf8("tWynik"));
        tWynik->setGeometry(QRect(70, 440, 1241, 371));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1340, 370, 87, 26));
        saldo_poczatkowe = new QPlainTextEdit(centralwidget);
        saldo_poczatkowe->setObjectName(QString::fromUtf8("saldo_poczatkowe"));
        saldo_poczatkowe->setGeometry(QRect(1330, 70, 104, 70));
        MT940->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MT940);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1500, 23));
        menuPlik = new QMenu(menubar);
        menuPlik->setObjectName(QString::fromUtf8("menuPlik"));
        MT940->setMenuBar(menubar);
        statusbar = new QStatusBar(MT940);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MT940->setStatusBar(statusbar);

        menubar->addAction(menuPlik->menuAction());

        retranslateUi(MT940);

        QMetaObject::connectSlotsByName(MT940);
    } // setupUi

    void retranslateUi(QMainWindow *MT940)
    {
        MT940->setWindowTitle(QCoreApplication::translate("MT940", "MT940", nullptr));
        pushButton->setText(QCoreApplication::translate("MT940", "+", nullptr));
        saldo_poczatkowe->setPlainText(QCoreApplication::translate("MT940", "0,00", nullptr));
        menuPlik->setTitle(QCoreApplication::translate("MT940", "Plik", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MT940: public Ui_MT940 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MT940_H
