/********************************************************************************
** Form generated from reading UI file 'userhome.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERHOME_H
#define UI_USERHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserHome
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QTableView *show_ListInfo;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *jiuxuanliaotianshi;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *show_myname;
    QComboBox *comboBox;
    QHBoxLayout *updatapassword;
    QLineEdit *newpswText;
    QPushButton *updatapsw;
    QWidget *mibaoyout;
    QVBoxLayout *mibaoLayout;
    QLabel *mibaowentiLabel;
    QLineEdit *inputmbda;

    void setupUi(QWidget *UserHome)
    {
        if (UserHome->objectName().isEmpty())
            UserHome->setObjectName(QString::fromUtf8("UserHome"));
        UserHome->setEnabled(true);
        UserHome->resize(800, 600);
        QFont font;
        font.setKerning(true);
        UserHome->setFont(font);
        horizontalLayoutWidget = new QWidget(UserHome);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 130, 521, 461));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        show_ListInfo = new QTableView(horizontalLayoutWidget);
        show_ListInfo->setObjectName(QString::fromUtf8("show_ListInfo"));

        horizontalLayout_2->addWidget(show_ListInfo);

        layoutWidget = new QWidget(UserHome);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 20, 265, 99));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        jiuxuanliaotianshi = new QLabel(layoutWidget);
        jiuxuanliaotianshi->setObjectName(QString::fromUtf8("jiuxuanliaotianshi"));

        verticalLayout->addWidget(jiuxuanliaotianshi);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        show_myname = new QLineEdit(layoutWidget);
        show_myname->setObjectName(QString::fromUtf8("show_myname"));
        show_myname->setEnabled(true);
        show_myname->setMaximumSize(QSize(888888, 16777215));

        horizontalLayout->addWidget(show_myname);

        comboBox = new QComboBox(layoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        verticalLayout_2->addLayout(horizontalLayout);

        updatapassword = new QHBoxLayout();
        updatapassword->setObjectName(QString::fromUtf8("updatapassword"));
        newpswText = new QLineEdit(layoutWidget);
        newpswText->setObjectName(QString::fromUtf8("newpswText"));

        updatapassword->addWidget(newpswText);

        updatapsw = new QPushButton(layoutWidget);
        updatapsw->setObjectName(QString::fromUtf8("updatapsw"));

        updatapassword->addWidget(updatapsw);

        verticalLayout_2->addLayout(updatapassword);

        verticalLayout->addLayout(verticalLayout_2);

        mibaoyout = new QWidget(UserHome);
        mibaoyout->setObjectName(QString::fromUtf8("mibaoyout"));
        mibaoyout->setGeometry(QRect(310, 20, 231, 91));
        mibaoLayout = new QVBoxLayout(mibaoyout);
        mibaoLayout->setObjectName(QString::fromUtf8("mibaoLayout"));
        mibaoLayout->setContentsMargins(0, 0, 0, 0);
        mibaowentiLabel = new QLabel(mibaoyout);
        mibaowentiLabel->setObjectName(QString::fromUtf8("mibaowentiLabel"));

        mibaoLayout->addWidget(mibaowentiLabel);

        inputmbda = new QLineEdit(mibaoyout);
        inputmbda->setObjectName(QString::fromUtf8("inputmbda"));

        mibaoLayout->addWidget(inputmbda);

        retranslateUi(UserHome);

        QMetaObject::connectSlotsByName(UserHome);
    } // setupUi

    void retranslateUi(QWidget *UserHome)
    {
        UserHome->setWindowTitle(QApplication::translate("UserHome", "Form", nullptr));
        jiuxuanliaotianshi->setText(QApplication::translate("UserHome", "\344\271\235\347\216\204\350\201\212\345\244\251\345\256\244", nullptr));
        label->setText(QApplication::translate("UserHome", "\346\230\265\347\247\260\357\274\232", nullptr));
        comboBox->setItemText(0, QApplication::translate("UserHome", "\345\234\250\347\272\277", nullptr));
        comboBox->setItemText(1, QApplication::translate("UserHome", "\351\232\220\350\272\253", nullptr));

        updatapsw->setText(QApplication::translate("UserHome", "\346\224\271\345\257\206\347\240\201", nullptr));
        mibaowentiLabel->setText(QApplication::translate("UserHome", "\345\257\206\344\277\235\351\227\256\351\242\230\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserHome: public Ui_UserHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERHOME_H
