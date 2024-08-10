/********************************************************************************
** Form generated from reading UI file 'sim.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIM_H
#define UI_SIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwchartview.h>

QT_BEGIN_NAMESPACE

class Ui_SimUI
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hbox_above;
    QComboBox *cBox_mode;
    QPushButton *btn_data;
    QLabel *lab_data;
    QPushButton *btn_load;
    QSplitter *splitter_mid;
    QLabel *lab_image;
    QWChartView *qcharts_data;
    QGridLayout *gBox_bottom;

    void setupUi(QWidget *SimUI)
    {
        if (SimUI->objectName().isEmpty())
            SimUI->setObjectName(QString::fromUtf8("SimUI"));
        SimUI->resize(835, 559);
        verticalLayout = new QVBoxLayout(SimUI);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        hbox_above = new QHBoxLayout();
        hbox_above->setSpacing(6);
        hbox_above->setObjectName(QString::fromUtf8("hbox_above"));
        cBox_mode = new QComboBox(SimUI);
        cBox_mode->addItem(QString());
        cBox_mode->addItem(QString());
        cBox_mode->setObjectName(QString::fromUtf8("cBox_mode"));

        hbox_above->addWidget(cBox_mode);

        btn_data = new QPushButton(SimUI);
        btn_data->setObjectName(QString::fromUtf8("btn_data"));

        hbox_above->addWidget(btn_data);

        lab_data = new QLabel(SimUI);
        lab_data->setObjectName(QString::fromUtf8("lab_data"));
        lab_data->setAlignment(Qt::AlignCenter);

        hbox_above->addWidget(lab_data);

        btn_load = new QPushButton(SimUI);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));

        hbox_above->addWidget(btn_load);

        hbox_above->setStretch(0, 1);
        hbox_above->setStretch(1, 1);
        hbox_above->setStretch(2, 8);
        hbox_above->setStretch(3, 1);

        verticalLayout->addLayout(hbox_above);

        splitter_mid = new QSplitter(SimUI);
        splitter_mid->setObjectName(QString::fromUtf8("splitter_mid"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_mid->sizePolicy().hasHeightForWidth());
        splitter_mid->setSizePolicy(sizePolicy);
        splitter_mid->setAutoFillBackground(true);
        splitter_mid->setFrameShape(QFrame::Panel);
        splitter_mid->setFrameShadow(QFrame::Plain);
        splitter_mid->setLineWidth(1);
        splitter_mid->setOrientation(Qt::Horizontal);
        splitter_mid->setHandleWidth(0);
        lab_image = new QLabel(splitter_mid);
        lab_image->setObjectName(QString::fromUtf8("lab_image"));
        lab_image->setAlignment(Qt::AlignCenter);
        splitter_mid->addWidget(lab_image);
        qcharts_data = new QWChartView(splitter_mid);
        qcharts_data->setObjectName(QString::fromUtf8("qcharts_data"));
        splitter_mid->addWidget(qcharts_data);

        verticalLayout->addWidget(splitter_mid);

        gBox_bottom = new QGridLayout();
        gBox_bottom->setSpacing(6);
        gBox_bottom->setObjectName(QString::fromUtf8("gBox_bottom"));

        verticalLayout->addLayout(gBox_bottom);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 20);
        verticalLayout->setStretch(2, 2);

        retranslateUi(SimUI);

        QMetaObject::connectSlotsByName(SimUI);
    } // setupUi

    void retranslateUi(QWidget *SimUI)
    {
        SimUI->setWindowTitle(QCoreApplication::translate("SimUI", "Sim", nullptr));
        cBox_mode->setItemText(0, QCoreApplication::translate("SimUI", "offLine", nullptr));
        cBox_mode->setItemText(1, QCoreApplication::translate("SimUI", "inLine", nullptr));

        btn_data->setText(QCoreApplication::translate("SimUI", "Data", nullptr));
        lab_data->setText(QCoreApplication::translate("SimUI", "Pls select a data source", nullptr));
        btn_load->setText(QCoreApplication::translate("SimUI", "Load", nullptr));
        lab_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SimUI: public Ui_SimUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIM_H
