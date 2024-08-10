#pragma once

#include <QtWidgets/QDialog>
#include "ui_dlg_cam.h"

class Dlg_Cam : public QDialog
{
	Q_OBJECT

public:
	Dlg_Cam(QWidget *parent = Q_NULLPTR);
	void showCam(const QPixmap&);
private:
	Ui::dlg_cam ui;

	QPixmap m_cam;
	QPalette palette;

	void scaleCamera(void);

protected:
	void Dlg_Cam::resizeEvent(QResizeEvent*);
};
