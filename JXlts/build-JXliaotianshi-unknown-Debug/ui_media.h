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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Media
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *h1;
    QPushButton *btnadd;
    QPushButton *btndel;
    QPushButton *btnclear;
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *h3;
    QLabel *label_2;
    QLabel *label;
    QSlider *hSliderVolume;
    QWidget *layoutWidget1;
    QHBoxLayout *h2;
    QPushButton *btnlast;
    QPushButton *btnback10;
    QPushButton *btnpause;
    QPushButton *btnforward10;
    QPushButton *btnnext;
    QCheckBox *checkBox;
    QWidget *layoutWidget2;
    QHBoxLayout *h5;
    QLabel *label_postiion;
    QSlider *hSlider;
    QLabel *label_duration;

    void setupUi(QMainWindow *Media)
    {
        if (Media->objectName().isEmpty())
            Media->setObjectName(QString::fromUtf8("Media"));
        Media->resize(1088, 600);
        centralwidget = new QWidget(Media);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 311, 611));
        QFont font;
        font.setPointSize(20);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setFont(font);

        verticalLayout->addWidget(listWidget);

        h1 = new QHBoxLayout();
        h1->setObjectName(QString::fromUtf8("h1"));
        btnadd = new QPushButton(groupBox);
        btnadd->setObjectName(QString::fromUtf8("btnadd"));
        btnadd->setFont(font);

        h1->addWidget(btnadd);

        btndel = new QPushButton(groupBox);
        btndel->setObjectName(QString::fromUtf8("btndel"));
        btndel->setFont(font);

        h1->addWidget(btndel);

        btnclear = new QPushButton(groupBox);
        btnclear->setObjectName(QString::fromUtf8("btnclear"));
        btnclear->setFont(font);

        h1->addWidget(btnclear);


        verticalLayout->addLayout(h1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(310, 10, 771, 511));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(880, 550, 201, 51));
        h3 = new QHBoxLayout(layoutWidget);
        h3->setObjectName(QString::fromUtf8("h3"));
        h3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        h3->addWidget(label_2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        h3->addWidget(label);

        hSliderVolume = new QSlider(layoutWidget);
        hSliderVolume->setObjectName(QString::fromUtf8("hSliderVolume"));
        hSliderVolume->setMaximum(100);
        hSliderVolume->setValue(50);
        hSliderVolume->setOrientation(Qt::Horizontal);

        h3->addWidget(hSliderVolume);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(310, 550, 567, 50));
        h2 = new QHBoxLayout(layoutWidget1);
        h2->setObjectName(QString::fromUtf8("h2"));
        h2->setContentsMargins(0, 0, 0, 0);
        btnlast = new QPushButton(layoutWidget1);
        btnlast->setObjectName(QString::fromUtf8("btnlast"));
        btnlast->setFont(font);

        h2->addWidget(btnlast);

        btnback10 = new QPushButton(layoutWidget1);
        btnback10->setObjectName(QString::fromUtf8("btnback10"));
        btnback10->setFont(font);

        h2->addWidget(btnback10);

        btnpause = new QPushButton(layoutWidget1);
        btnpause->setObjectName(QString::fromUtf8("btnpause"));
        btnpause->setFont(font);

        h2->addWidget(btnpause);

        btnforward10 = new QPushButton(layoutWidget1);
        btnforward10->setObjectName(QString::fromUtf8("btnforward10"));
        btnforward10->setFont(font);

        h2->addWidget(btnforward10);

        btnnext = new QPushButton(layoutWidget1);
        btnnext->setObjectName(QString::fromUtf8("btnnext"));
        btnnext->setFont(font);

        h2->addWidget(btnnext);

        checkBox = new QCheckBox(layoutWidget1);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        h2->addWidget(checkBox);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(308, 530, 771, 20));
        h5 = new QHBoxLayout(layoutWidget2);
        h5->setObjectName(QString::fromUtf8("h5"));
        h5->setContentsMargins(0, 0, 0, 0);
        label_postiion = new QLabel(layoutWidget2);
        label_postiion->setObjectName(QString::fromUtf8("label_postiion"));

        h5->addWidget(label_postiion);

        hSlider = new QSlider(layoutWidget2);
        hSlider->setObjectName(QString::fromUtf8("hSlider"));
        hSlider->setOrientation(Qt::Horizontal);

        h5->addWidget(hSlider);

        label_duration = new QLabel(layoutWidget2);
        label_duration->setObjectName(QString::fromUtf8("label_duration"));

        h5->addWidget(label_duration);

        Media->setCentralWidget(centralwidget);

        retranslateUi(Media);

        QMetaObject::connectSlotsByName(Media);
    } // setupUi

    void retranslateUi(QMainWindow *Media)
    {
        Media->setWindowTitle(QApplication::translate("Media", "\344\271\235\347\216\204\350\201\212\345\244\251\345\256\244", nullptr));
        groupBox->setTitle(QApplication::translate("Media", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        btnadd->setText(QApplication::translate("Media", "\346\267\273\345\212\240", nullptr));
        btndel->setText(QApplication::translate("Media", "\345\210\240\351\231\244", nullptr));
        btnclear->setText(QApplication::translate("Media", "\346\270\205\347\251\272", nullptr));
        label_2->setText(QApplication::translate("Media", "\351\237\263\351\207\217\357\274\232", nullptr));
        label->setText(QApplication::translate("Media", "50", nullptr));
        btnlast->setText(QApplication::translate("Media", "\344\270\212\344\270\200\346\233\262", nullptr));
        btnback10->setText(QApplication::translate("Media", "<<10\347\247\222", nullptr));
        btnpause->setText(QApplication::translate("Media", "\347\273\247\347\273\255", nullptr));
        btnforward10->setText(QApplication::translate("Media", ">>10\347\247\222", nullptr));
        btnnext->setText(QApplication::translate("Media", "\344\270\213\344\270\200\346\233\262", nullptr));
        checkBox->setText(QApplication::translate("Media", "\351\232\217\346\234\272\346\222\255\346\224\276", nullptr));
        label_postiion->setText(QApplication::translate("Media", "00:00:00", nullptr));
        label_duration->setText(QApplication::translate("Media", "00:00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Media: public Ui_Media {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIA_H
