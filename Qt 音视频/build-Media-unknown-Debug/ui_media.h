/********************************************************************************
** Form generated from reading UI file 'media.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIA_H
#define UI_MEDIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Media
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Media)
    {
        if (Media->objectName().isEmpty())
            Media->setObjectName(QString::fromUtf8("Media"));
        Media->resize(800, 600);
        centralwidget = new QWidget(Media);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 130, 241, 101));
        QFont font;
        font.setPointSize(25);
        pushButton->setFont(font);
        Media->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Media);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        Media->setMenuBar(menubar);
        statusbar = new QStatusBar(Media);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Media->setStatusBar(statusbar);

        retranslateUi(Media);

        QMetaObject::connectSlotsByName(Media);
    } // setupUi

    void retranslateUi(QMainWindow *Media)
    {
        Media->setWindowTitle(QApplication::translate("Media", "Media", nullptr));
        pushButton->setText(QApplication::translate("Media", "\346\222\255\346\224\276\351\237\263\344\271\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Media: public Ui_Media {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIA_H
