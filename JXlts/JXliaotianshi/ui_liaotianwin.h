/********************************************************************************
** Form generated from reading UI file 'liaotianwin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIAOTIANWIN_H
#define UI_LIAOTIANWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTableView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_liaotianWin
{
public:
    QTextBrowser *liaotianInfo;
    QLabel *targetName;
    QLabel *targetStatus;
    QDateEdit *dateEdit;
    QCalendarWidget *calendarWidget;
    QTableView *QMediaPlayer;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *sendmsg;
    QVBoxLayout *verticalLayout;
    QPushButton *send;
    QPushButton *sendFile;
    QPushButton *cancel;
    QProgressBar *progressBar;

    void setupUi(QWidget *liaotianWin)
    {
        if (liaotianWin->objectName().isEmpty())
            liaotianWin->setObjectName(QString::fromUtf8("liaotianWin"));
        liaotianWin->resize(854, 648);
        liaotianInfo = new QTextBrowser(liaotianWin);
        liaotianInfo->setObjectName(QString::fromUtf8("liaotianInfo"));
        liaotianInfo->setGeometry(QRect(30, 80, 491, 351));
        targetName = new QLabel(liaotianWin);
        targetName->setObjectName(QString::fromUtf8("targetName"));
        targetName->setGeometry(QRect(30, 50, 121, 17));
        targetStatus = new QLabel(liaotianWin);
        targetStatus->setObjectName(QString::fromUtf8("targetStatus"));
        targetStatus->setGeometry(QRect(220, 50, 231, 20));
        dateEdit = new QDateEdit(liaotianWin);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(410, 50, 110, 25));
        dateEdit->setDisplayFormat(QString::fromUtf8("yyyy-MM-dd"));
        calendarWidget = new QCalendarWidget(liaotianWin);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(40, 90, 471, 301));
        calendarWidget->setVisible(false);
        QMediaPlayer = new QTableView(liaotianWin);
        QMediaPlayer->setObjectName(QString::fromUtf8("QMediaPlayer"));
        QMediaPlayer->setGeometry(QRect(530, 50, 221, 571));
        layoutWidget = new QWidget(liaotianWin);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 453, 491, 171));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sendmsg = new QTextEdit(layoutWidget);
        sendmsg->setObjectName(QString::fromUtf8("sendmsg"));

        horizontalLayout->addWidget(sendmsg);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        send = new QPushButton(layoutWidget);
        send->setObjectName(QString::fromUtf8("send"));

        verticalLayout->addWidget(send);

        sendFile = new QPushButton(layoutWidget);
        sendFile->setObjectName(QString::fromUtf8("sendFile"));

        verticalLayout->addWidget(sendFile);

        cancel = new QPushButton(layoutWidget);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        verticalLayout->addWidget(cancel);


        horizontalLayout->addLayout(verticalLayout);

        progressBar = new QProgressBar(liaotianWin);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 410, 491, 25));
        progressBar->setVisible(false);


        retranslateUi(liaotianWin);

        QMetaObject::connectSlotsByName(liaotianWin);
    } // setupUi

    void retranslateUi(QWidget *liaotianWin)
    {
        liaotianWin->setWindowTitle(QApplication::translate("liaotianWin", "Form", nullptr));
        targetName->setText(QApplication::translate("liaotianWin", "targetUserName", nullptr));
        targetStatus->setText(QApplication::translate("liaotianWin", "targetStatus", nullptr));
        send->setText(QApplication::translate("liaotianWin", "\345\217\221\351\200\201", nullptr));
        sendFile->setText(QApplication::translate("liaotianWin", "\346\226\207\344\273\266", nullptr));
        cancel->setText(QApplication::translate("liaotianWin", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class liaotianWin: public Ui_liaotianWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIAOTIANWIN_H