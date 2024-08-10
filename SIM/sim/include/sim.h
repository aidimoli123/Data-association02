#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include<algorithm>
#include <cmath>
#include <memory>

#include <QProcess>
#include <QtCharts>
#include <QtWidgets/QWidget>
#include "ui_sim.h"
#include "dlg_cam.h"
#include "qwchartview.h"
#include "rapidjson/include/document.h"
#include "rapidjson/include/writer.h"
#include "rapidjson/include/stringbuffer.h"


using namespace std;
using namespace rapidjson;


typedef struct
{
	UINT num_detections;
	vector<double> vec_x;
	vector<double> vec_y;
	vector<double> vec_vx_comp;
	vector<double> vec_vy_comp;
}Radar_detections, *p_Radar_detections;

typedef struct  
{
	vector<double> vec_x;
	vector<double> vec_y;
}RectPoints, *p_RectPoints;

typedef vector<RectPoints> OneSampleRectPoints;

class Sim : public QWidget
{
	Q_OBJECT

public:
	Sim(QWidget *parent = Q_NULLPTR);
	~Sim();

private:
	Ui::SimUI* ui = new Ui::SimUI;
	Dlg_Cam* p_dlg_cam = new Dlg_Cam;

	QToolButton* btn_cycle, *btn_play, *btn_pause;
	QSlider* slider;
	QSpinBox* spinBox;

	UINT64 sample_num;
	double sample_interval;
	string cam_pth{};
	string radar_pth{};
	string true_pth{};
	string anns2D_pth{};

	UINT64 id_current_frame;

	bool b_pause;
	bool b_play;
	bool b_cycle;

	QTimer* p_timer;
	
	vector<Radar_detections> vec_radar_detections;
	vector<OneSampleRectPoints> vec_all_sample_rectPoints;

	QChart* chart = new QChart();
	QValueAxis* axisX = new QValueAxis;
	QValueAxis* axisY = new QValueAxis;
	QScatterSeries* series_pos{ nullptr };
	vector<QLineSeries*> vec_p_curSeries_vel;
	// QLineSeries* series_vel = new QLineSeries();
	vector<QLineSeries*> vec_p_curSeries_sample_rectPoints;
	QLineSeries* series_fov_long = new QLineSeries();
	QLineSeries* series_fov_short = new QLineSeries();

	void initUI(void);
	void initVar(void);
	void initSigalSlotsConnect(void);
	string readJson(const char* filename, uint num_KB);
	void parseDataJSON(const char* jsonstr);

	void updateMovieUI(void);
	void playMovie(void);
	void updateSliderValue(void);

	void updateCam(void);
	void updateRadar(void);
	void readRadarDetections(void);
	void parseRadarJSON(const char* jsonstr);
	void parseJsonAnns2D(void);

	void invokeExe(const QString&, const QStringList&);

private slots:
	void getDataPth(void);
	void onCycle(void);
	void onPlay(void);
	void onPause(void);
	void updateSlider(int);
	void updateSpinBox(int);
	void onTimeOut(void);
	void onBtnLoad(void);

	void onScatterPointsHover(const QPointF& point, bool state);
};
