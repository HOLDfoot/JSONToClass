/********************************************************************************
** Form generated from reading UI file 'jsonwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JSONWINDOW_H
#define UI_JSONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JsonWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JsonWindow)
    {
        if (JsonWindow->objectName().isEmpty())
            JsonWindow->setObjectName(QStringLiteral("JsonWindow"));
        JsonWindow->resize(400, 300);
        menuBar = new QMenuBar(JsonWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        JsonWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(JsonWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        JsonWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(JsonWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        JsonWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(JsonWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        JsonWindow->setStatusBar(statusBar);

        retranslateUi(JsonWindow);

        QMetaObject::connectSlotsByName(JsonWindow);
    } // setupUi

    void retranslateUi(QMainWindow *JsonWindow)
    {
        JsonWindow->setWindowTitle(QApplication::translate("JsonWindow", "JsonWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JsonWindow: public Ui_JsonWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JSONWINDOW_H
