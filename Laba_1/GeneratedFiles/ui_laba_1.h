/********************************************************************************
** Form generated from reading UI file 'laba_1.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABA_1_H
#define UI_LABA_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Laba_1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Laba_1Class)
    {
        if (Laba_1Class->objectName().isEmpty())
            Laba_1Class->setObjectName(QStringLiteral("Laba_1Class"));
        Laba_1Class->resize(600, 400);
        menuBar = new QMenuBar(Laba_1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Laba_1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Laba_1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Laba_1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Laba_1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Laba_1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Laba_1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Laba_1Class->setStatusBar(statusBar);

        retranslateUi(Laba_1Class);

        QMetaObject::connectSlotsByName(Laba_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Laba_1Class)
    {
        Laba_1Class->setWindowTitle(QApplication::translate("Laba_1Class", "Laba_1", 0));
    } // retranslateUi

};

namespace Ui {
    class Laba_1Class: public Ui_Laba_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABA_1_H
