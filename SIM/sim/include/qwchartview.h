#pragma once

#include    <QtCharts>  
QT_CHARTS_USE_NAMESPACE  


class QWChartView : public QChartView
{
	Q_OBJECT

private:
	QPoint  beginPoint; 
	QPoint  endPoint;  

protected:
	void mousePressEvent(QMouseEvent* event); 
	void mouseMoveEvent(QMouseEvent* event); 
	void mouseReleaseEvent(QMouseEvent* event); 
	void keyPressEvent(QKeyEvent* event);
	void wheelEvent(QWheelEvent* event);

public:
	explicit QWChartView(QWidget* parent = 0);
	~QWChartView();

signals:
	void mouseMovePoint(QPoint point); 
};