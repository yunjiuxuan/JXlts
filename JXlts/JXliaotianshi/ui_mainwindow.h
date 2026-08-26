/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *userregister;
    QPushButton *userlogin;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *usernamelabel;
    QLabel *pswlabel;
    QVBoxLayout *verticalLayout;
    QLineEdit *username;
    QLineEdit *password;
    QWidget *layoutWidget2;
    QHBoxLayout *mibaoLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *mibaowenti;
    QLabel *mibaodaan;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *inputmbwt;
    QLineEdit *inputmbda;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        userregister = new QPushButton(centralwidget);
        userregister->setObjectName(QString::fromUtf8("userregister"));
        userregister->setGeometry(QRect(250, 320, 89, 41));
        userlogin = new QPushButton(centralwidget);
        userlogin->setObjectName(QString::fromUtf8("userlogin"));
        userlogin->setGeometry(QRect(390, 320, 89, 41));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(220, 180, 281, 121));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        usernamelabel = new QLabel(layoutWidget);
        usernamelabel->setObjectName(QString::fromUtf8("usernamelabel"));

        verticalLayout_2->addWidget(usernamelabel);

        pswlabel = new QLabel(layoutWidget);
        pswlabel->setObjectName(QString::fromUtf8("pswlabel"));

        verticalLayout_2->addWidget(pswlabel);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        username = new QLineEdit(layoutWidget);
        username->setObjectName(QString::fromUtf8("username"));

        verticalLayout->addWidget(username);

        password = new QLineEdit(layoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        verticalLayout->addWidget(password);


        horizontalLayout->addLayout(verticalLayout);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(220, 370, 281, 80));
        mibaoLayout = new QHBoxLayout(layoutWidget2);
        mibaoLayout->setObjectName(QString::fromUtf8("mibaoLayout"));
        mibaoLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        mibaowenti = new QLabel(layoutWidget2);
        mibaowenti->setObjectName(QString::fromUtf8("mibaowenti"));
        verticalLayout_3->addWidget(mibaowenti);
        mibaodaan = new QLabel(layoutWidget2);
        mibaodaan->setObjectName(QString::fromUtf8("mibaodaan"));
        verticalLayout_3->addWidget(mibaodaan);
        mibaoLayout->addLayout(verticalLayout_3);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        inputmbwt = new QLineEdit(layoutWidget2);
        inputmbwt->setObjectName(QString::fromUtf8("inputmbwt"));
        verticalLayout_4->addWidget(inputmbwt);
        inputmbda = new QLineEdit(layoutWidget2);
        inputmbda->setObjectName(QString::fromUtf8("inputmbda"));
        verticalLayout_4->addWidget(inputmbda);
        mibaoLayout->addLayout(verticalLayout_4);
        layoutWidget2->setVisible(false);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        userregister->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        userlogin->setText(QApplication::translate("MainWindow", "\347\231\273\351\231\206", nullptr));
        usernamelabel->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        pswlabel->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        mibaowenti->setText(QApplication::translate("MainWindow", "\345\257\206\344\277\235\351\227\256\351\242\230\357\274\232", nullptr));
        mibaodaan->setText(QApplication::translate("MainWindow", "\345\257\206\344\277\235\347\255\224\346\241\210\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
