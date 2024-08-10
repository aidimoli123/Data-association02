#include "dlg_cam.h"
#include <QMessageBox>

Dlg_Cam::Dlg_Cam(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setAutoFillBackground(true);
	palette = this->palette;
}

void Dlg_Cam::showCam(const QPixmap& cam)
{
	m_cam = cam;
	palette.setBrush
	(
		this->backgroundRole(),
		QBrush(cam)
	);
	this->setPalette(palette);
}

void Dlg_Cam::resizeEvent(QResizeEvent*)
{
	scaleCamera();
}

void Dlg_Cam::scaleCamera(void)
{
	if (m_cam.isNull())
	{	/*
		QMessageBox::warning
		(
			this,
			"Camera",
			"No Pixmap in Dialog"
		);*/
	}
	else
	{
		palette.setBrush
		(
			this->backgroundRole(),
			QBrush(
				m_cam.scaled
				(
					this->size(),
					Qt::IgnoreAspectRatio,
					Qt::SmoothTransformation
				)
			)
		);
		this->setPalette(palette);
	}
}