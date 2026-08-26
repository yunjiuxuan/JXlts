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
    QWidget *widget1;
    QHBoxLayout *h3;
    QSlider *hSliderVolume;
    QLabel *label;
    QWidget *widget2;
    QHBoxLayout *h2;
    QPushButton *btnplay;
    QPushButton *btnpause;
    QPushButton *btnstop;
    QPushButton *btnlast;
    QPushButton *btnnext;
    QCheckBox *checkBox;
    QWidget *widget3;
    QHBoxLayout *h5;
    QSlider *hSlider;
    QLabel *label_postiion;
    QLabel *label_4;
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
        groupBox->setGeometry(QRect(0, 0, 301, 591));
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
        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(950, 560, 109, 19));
        h3 = new QHBoxLayout(widget1);
        h3->setObjectName(QString::fromUtf8("h3"));
        h3->setContentsMargins(0, 0, 0, 0);
        hSliderVolume = new QSlider(widget1);
        hSliderVolume->setObjectName(QString::fromUtf8("hSliderVolume"));
        hSliderVolume->setMaximum(100);
        hSliderVolume->setValue(50);
        hSliderVolume->setOrientation(Qt::Horizontal);

        h3->addWidget(hSliderVolume);

        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));

        h3->addWidget(label);

        widget2 = new QWidget(centralwidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(330, 550, 542, 50));
        h2 = new QHBoxLayout(widget2);
        h2->setObjectName(QString::fromUtf8("h2"));
        h2->setContentsMargins(0, 0, 0, 0);
        btnplay = new QPushButton(widget2);
        btnplay->setObjectName(QString::fromUtf8("btnplay"));
        btnplay->setFont(font);

        h2->addWidget(btnplay);

        btnpause = new QPushButton(widget2);
        btnpause->setObjectName(QString::fromUtf8("btnpause"));
        btnpause->setFont(font);

        h2->addWidget(btnpause);

        btnstop = new QPushButton(widget2);
        btnstop->setObjectName(QString::fromUtf8("btnstop"));
        btnstop->setFont(font);

        h2->addWidget(btnstop);

        btnlast = new QPushButton(widget2);
        btnlast->setObjectName(QString::fromUtf8("btnlast"));
        btnlast->setFont(font);

        h2->addWidget(btnlast);

        btnnext = new QPushButton(widget2);
        btnnext->setObjectName(QString::fromUtf8("btnnext"));
        btnnext->setFont(font);

        h2->addWidget(btnnext);

        checkBox = new QCheckBox(widget2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        h2->addWidget(checkBox);

        widget3 = new QWidget(centralwidget);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(308, 530, 761, 20));
        h5 = new QHBoxLayout(widget3);
        h5->setObjectName(QString::fromUtf8("h5"));
        h5->setContentsMargins(0, 0, 0, 0);
        hSlider = new QSlider(widget3);
        hSlider->setObjectName(QString::fromUtf8("hSlider"));
        hSlider->setOrientation(Qt::Horizontal);

        h5->addWidget(hSlider);

        label_postiion = new QLabel(widget3);
        label_postiion->setObjectName(QString::fromUtf8("label_postiion"));

        h5->addWidget(label_postiion);

        label_4 = new QLabel(widget3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        h5->addWidget(label_4);

        label_duration = new QLabel(widget3);
        label_duration->setObjectName(QString::fromUtf8("label_duration"));

        h5->addWidget(label_duration);

        Media->setCentralWidget(centralwidget);

        retranslateUi(Media);

        QMetaObject::connectSlotsByName(Media);
    } // setupUi

    void retranslateUi(QMainWindow *Media)
    {
        Media->setWindowTitle(QApplication::translate("Media", "Media", nullptr));
        groupBox->setTitle(QApplication::translate("Media", "\345\244\232\345\252\222\344\275\223\345\210\227\350\241\250", nullptr));
        btnadd->setText(QApplication::translate("Media", "\346\267\273\345\212\240", nullptr));
        btndel->setText(QApplication::translate("Media", "\345\210\240\351\231\244", nullptr));
        btnclear->setText(QApplication::translate("Media", "\346\270\205\347\251\272", nullptr));
        label->setText(QApplication::translate("Media", "50", nullptr));
        btnplay->setText(QApplication::translate("Media", "\346\222\255\346\224\276", nullptr));
        btnpause->setText(QApplication::translate("Media", "\346\232\202\345\201\234", nullptr));
        btnstop->setText(QApplication::translate("Media", "\345\201\234\346\255\242", nullptr));
        btnlast->setText(QApplication::translate("Media", "\344\270\212\344\270\200\346\233\262", nullptr));
        btnnext->setText(QApplication::translate("Media", "\344\270\213\344\270\200\346\233\262", nullptr));
        checkBox->setText(QApplication::translate("Media", "\351\232\217\346\234\272\346\222\255\346\224\276", nullptr));
        label_postiion->setText(QApplication::translate("Media", "00:00:00", nullptr));
        label_4->setText(QApplication::translate("Media", "/", nullptr));
        label_duration->setText(QApplication::translate("Media", "00:00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Media: public Ui_Media {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIA_H
