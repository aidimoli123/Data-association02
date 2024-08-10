/********************************************************************************
** Form generated from reading UI file 'dlg_cam.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_CAM_H
#define UI_DLG_CAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_dlg_cam
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *lab_dlg_cam;

    void setupUi(QDialog *dlg_cam)
    {
        if (dlg_cam->objectName().isEmpty())
            dlg_cam->setObjectName(QString::fromUtf8("dlg_cam"));
        dlg_cam->resize(1600, 800);
        horizontalLayout = new QHBoxLayout(dlg_cam);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lab_dlg_cam = new QLabel(dlg_cam);
        lab_dlg_cam->setObjectName(QString::fromUtf8("lab_dlg_cam"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lab_dlg_cam->sizePolicy().hasHeightForWidth());
        lab_dlg_cam->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lab_dlg_cam);


        retranslateUi(dlg_cam);

        QMetaObject::connectSlotsByName(dlg_cam);
    } // setupUi

    void retranslateUi(QDialog *dlg_cam)
    {
        dlg_cam->setWindowTitle(QCoreApplication::translate("dlg_cam", "Dlg_Cam", nullptr));
        lab_dlg_cam->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class dlg_cam: public Ui_dlg_cam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_CAM_H
