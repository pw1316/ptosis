/********************************************************************************
** Form generated from reading UI file 'QTLBF.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLBF_H
#define UI_QTLBF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTLBFClass
{
public:
    QWidget *widget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTLBFClass)
    {
        if (QTLBFClass->objectName().isEmpty())
            QTLBFClass->setObjectName(QStringLiteral("QTLBFClass"));
        QTLBFClass->resize(800, 600);
        widget = new QWidget(QTLBFClass);
        widget->setObjectName(QStringLiteral("widget"));
        QTLBFClass->setCentralWidget(widget);
        menuBar = new QMenuBar(QTLBFClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        QTLBFClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(QTLBFClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTLBFClass->setStatusBar(statusBar);

        retranslateUi(QTLBFClass);

        QMetaObject::connectSlotsByName(QTLBFClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTLBFClass)
    {
        QTLBFClass->setWindowTitle(QApplication::translate("QTLBFClass", "QTLBF", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QTLBFClass: public Ui_QTLBFClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLBF_H
