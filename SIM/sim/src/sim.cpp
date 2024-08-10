#include "sim.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

Sim::Sim(QWidget *parent)
	: QWidget(parent)
{
	ui->setupUi(this);
	ui->cBox_mode->setCurrentIndex(0);
	initUI();
	initSigalSlotsConnect();
	onPause();
}

Sim::~Sim()
{
	delete ui;
	delete p_dlg_cam;
	delete btn_cycle;
	delete btn_pause;
	delete btn_play;
	delete slider;
	delete spinBox;
	delete p_timer;
	delete chart;
	delete axisX;
	delete axisY;
	delete series_pos;
	delete series_fov_long;
	delete series_fov_short;

	if (!vec_p_curSeries_sample_rectPoints.empty())
	{
		for (auto &p_series_rectPoints : vec_p_curSeries_sample_rectPoints)
			delete p_series_rectPoints;
		vec_p_curSeries_sample_rectPoints.clear();
	}

	if (!vec_p_curSeries_vel.empty())
	{
		for (auto & p_series_vel : vec_p_curSeries_vel)
		{
			delete p_series_vel;
		}
		vec_p_curSeries_vel.clear();
	}
}

void Sim::initUI(void)
{
	ui->cBox_mode->setMaximumWidth(100);
	ui->btn_data->setMaximumWidth(50);
	ui->btn_load->setMaximumWidth(50);

	QSize icon_size = QSize(30, 30);
	QIcon icon = QIcon();
	icon.addPixmap(
		QPixmap(":/Sim/images/cycle.png"),
		QIcon::Normal,
		QIcon::Off);
	btn_cycle = new QToolButton();
	btn_cycle->setIcon(icon);
	btn_cycle->setIconSize(icon_size);
	btn_cycle->setAutoRaise(true);
	btn_cycle->setToolTip("Cycle");

	icon.addPixmap(
		QPixmap(":/Sim/images/play.png"),
		QIcon::Normal,
		QIcon::Off);
	btn_play = new QToolButton();
	btn_play->setIcon(icon);
	btn_play->setIconSize(icon_size);
	btn_play->setAutoRaise(true);
	btn_play->setToolTip("Play");

	icon.addPixmap(
		QPixmap(":/Sim/images/pause.png"),
		QIcon::Normal,
		QIcon::Off);
	btn_pause = new QToolButton();
	btn_pause->setIcon(icon);
	btn_pause->setIconSize(icon_size);
	btn_pause->setAutoRaise(true);
	btn_pause->setToolTip("Pause");
	btn_pause->setVisible(false);

	slider = new QSlider(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setSingleStep(1);
	slider->setTickInterval(1);

	spinBox = new QSpinBox();
	spinBox->setMinimum(0);
	spinBox->setSingleStep(1);
	spinBox->setMaximumWidth(110);

	ui->gBox_bottom->addWidget(btn_cycle, 0, 0);
	ui->gBox_bottom->addWidget(btn_play, 0, 1);
	ui->gBox_bottom->addWidget(btn_pause, 0, 1);
	ui->gBox_bottom->addWidget(slider, 0, 2);
	ui->gBox_bottom->addWidget(spinBox, 0, 3);

	for (int i = 0; i < 4; i++)
	{
		ui->gBox_bottom->setColumnMinimumWidth(i, 0);
		ui->gBox_bottom->setColumnStretch(i, 2);
	}
	ui->gBox_bottom->setColumnStretch(2, 200);
	ui->gBox_bottom->setColumnStretch(3, 1);

	ui->qcharts_data->setRenderHint(QPainter::Antialiasing);
	ui->qcharts_data->setChart(chart);
	ui->qcharts_data->setRubberBand(QChartView::RectangleRubberBand);

	// initialize the charts
	chart->setTitle("BirdView of Radar(m)");

	axisX->setTickCount(31);
	axisX->setMinorTickCount(9);
	axisX->setTitleText("X");
	axisX->setMinorGridLineVisible(false);

	axisY->setTitleText("Y");
	axisY->setTickCount(9);
	axisY->setMinorTickCount(4);

	QPen blue_pen;
	blue_pen.setStyle(Qt::DashLine);
	blue_pen.setWidth(2);
	blue_pen.setColor(Qt::blue);
	series_fov_long->setPen(blue_pen);
	series_fov_short->setPen(blue_pen);

	vector<qreal> vec_fovL_x{0, -23.76, -17.48, 17.48, 23.76, 0};
	vector<qreal> vec_fovL_y{ 0, 150, 250, 250, 150, 0};
	for (size_t i=0;i<vec_fovL_x.size();i++)
	{
		series_fov_long->append(
			vec_fovL_x.at(i), vec_fovL_y.at(i));
	}

	chart->addSeries(series_fov_long);
	chart->setAxisX(axisY, series_fov_long);
	chart->setAxisY(axisX, series_fov_long);

	vector<qreal> vec_fovS_x{ 0, 17.32, 49.5, 45.0, 35,    23.94, 12.16, 0, -12.16, -23.94, -35,  -45.0, -49.5, -17.32, 0};
	vector<qreal> vec_fovS_y{ 0, 10,    49.5, 53.6, 60.62, 65.78, 68.94, 70, 68.94, 65.78, 60.62, 53.6, 49.5,  10,     0 };
	for (size_t i = 0; i < vec_fovS_x.size(); i++)
	{
		series_fov_short->append(
			vec_fovS_x.at(i), vec_fovS_y.at(i));
	}

	chart->addSeries(series_fov_short);
	chart->setAxisX(axisY, series_fov_short);
	chart->setAxisY(axisX, series_fov_short);
	chart->legend()->setVisible(false);
}

void Sim::initSigalSlotsConnect(void)
{
	connect(
		ui->btn_data,
		SIGNAL(clicked()),
		this,
		SLOT(getDataPth()));
	connect(
		btn_cycle,
		SIGNAL(clicked()),
		this,
		SLOT(onCycle()));
	connect(
		btn_play,
		SIGNAL(clicked()),
		this,
		SLOT(onPlay()));
	connect(
		btn_pause,
		SIGNAL(clicked()),
		this,
		SLOT(onPause()));
	connect(
		slider,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(updateSlider(int)));
	connect(
		spinBox,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(updateSpinBox(int)));
	connect(
		ui->btn_load,
		SIGNAL(clicked()),
		this,
		SLOT(onBtnLoad()));
}

void Sim::updateSpinBox(int current_spinBox_value)
{
	id_current_frame = current_spinBox_value;
	slider->setValue(id_current_frame);
}

void Sim::onPause(void)
{
	b_pause = true;
	b_play = false;
	b_cycle = false;

	updateMovieUI();
	updateSlider(id_current_frame);
}

void Sim::onPlay(void)
{
	b_play = true;
	b_pause = false;

	updateMovieUI();
	playMovie();
}

void Sim::onCycle(void)
{
	b_cycle = true;
	onPlay();
}

void Sim::playMovie(void)
{
	if (b_play)
	{
		if (id_current_frame == (sample_num - 1))
		{
			if (b_cycle)
			{
				id_current_frame = 0;
				playMovie();
			}
			else
				onPause();
		}
		else
		{
			p_timer = new QTimer();
			p_timer->setSingleShot(true);
			p_timer->start(0.5 * 1000);
			connect(
				p_timer,
				SIGNAL(timeout()),
				this,
				SLOT(onTimeOut()));
		}
	}
}

void Sim::onTimeOut(void)
{
	if (id_current_frame < (sample_num - 1))
	{
		id_current_frame += 1;
		updateSliderValue();
		delete p_timer;
		playMovie();
	}
}

void Sim::updateMovieUI(void)
{
	if (b_pause)
	{
		btn_play->setVisible(true);
		btn_play->setEnabled(true);
		btn_play->setCheckable(true);

		btn_pause->setVisible(false);
		btn_pause->setEnabled(false);
		btn_pause->setCheckable(false);

		btn_cycle->setEnabled(true);
		btn_cycle->setCheckable(true);

		slider->setEnabled(true);
		spinBox->setEnabled(true);
	}
	else
	{
		btn_play->setVisible(false);
		btn_play->setEnabled(false);
		btn_play->setCheckable(false);

		btn_pause->setVisible(true);
		btn_pause->setEnabled(true);
		btn_pause->setCheckable(true);

		btn_cycle->setEnabled(false);
		btn_cycle->setCheckable(false);

		slider->setEnabled(false);
		spinBox->setEnabled(false);
	}
}

void Sim::updateSlider(int value)
{
	id_current_frame = slider->value();
	spinBox->setValue(id_current_frame);

	if (p_dlg_cam != NULL)
	{
		updateCam();
		updateRadar();
	}
	else
	{
		/*
		p_dlg_cam = new Dlg_Cam;
		p_dlg_cam->show();
		*/
	}
}

void Sim::updateSliderValue(void)
{
	if (id_current_frame >= 0)
	{
		slider->setValue(id_current_frame);
	}
	else
		slider->setMaximum(0);
}

void Sim::getDataPth(void)
{
	if (ui->cBox_mode->currentIndex() == 0)
	{
		QString curPth = QDir::currentPath();
		QString title = "Select the Data File";
		QString file_filter = "Files(*.json)";
		QString file_pth = QFileDialog::getOpenFileName(
			this,
			title,
			curPth,
			file_filter);
		if (file_pth == "")
			QMessageBox::warning(
				this,
				"No Data File is be select",
				"Please select a data file");
		else
		{
			ui->lab_data->setText(file_pth);

			QByteArray file_pth_ba = file_pth.toLatin1();
			string jsonstr = readJson(file_pth_ba.data(), 16);

			try
			{
				parseDataJSON(jsonstr.c_str());
			}
			catch (string e)
			{
				printf("error:%s \n", e.c_str());
			}
		}
	}
	else
		QMessageBox::warning(
			this,
			"Mode is on-Line",
			"Warning: on-Line don't need data file");
}

string Sim::readJson(const char *filename, uint num_KB)
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, filename, "rb");
	if (fp && err != 0)
	{
		QMessageBox::warning(
			this,
			"readJson Error",
			"readJson fail");
		throw string("open %s fail!\n", filename);
		return "";
	}
	else
	{
		UINT64 buf_size = 1024 * num_KB;
		char *buf = new char[buf_size];
		int n = fread_s(buf, buf_size, 1, buf_size, fp);
		if (fclose(fp) != 0)
		{
			QMessageBox::warning(
				this,
				"readJson Error",
				"readJson::fclose fp fail");
			throw string("close %s fail!\n", filename);
		}

		string result;
		if (n >= 0)
		{
			result.append(buf, 0, n);
		}
		delete[] buf;
		return result;
	}
}

void Sim::parseDataJSON(const char *jsonstr)
{
	Document d;
	if (d.Parse(jsonstr).HasParseError())
	{
		QMessageBox::warning(
			this,
			"parseDataJSON Error",
			"parseDataJSON parse json fail");
		throw string("parse error!\n");
	}
	if (!d.IsObject())
	{
		QMessageBox::warning(
			this,
			"parseDataJSON Error",
			"The root is't a object!");
		throw string("should be an object!\n");
	}

	if (d.HasMember("sample_num"))
	{
		Value &m = d["sample_num"];
		sample_num = m.GetUint64();
	}

	if (d.HasMember("sample_interval"))
	{
		Value &m = d["sample_interval"];
		sample_interval = m.GetDouble();
	}

	if (d.HasMember("camera_pth"))
	{
		Value &m = d["camera_pth"];
		cam_pth = m.GetString();
	}

	if (d.HasMember("radar_pth"))
	{
		Value &m = d["radar_pth"];
		radar_pth = m.GetString();
	}

	if (d.HasMember("true_pth"))
	{
		Value &m = d["true_pth"];
		true_pth = m.GetString();
	}

	if (d.HasMember("anns_2D"))
	{
		Value &m = d["anns_2D"];
		anns2D_pth = m.GetString();
	}

	p_dlg_cam->show();

	readRadarDetections();
	parseJsonAnns2D();
	updateCam();
	updateRadar();

	initVar();
}

void Sim::initVar()
{
	id_current_frame = 0;

	slider->setMaximum((sample_num - 1));
	slider->setValue(0);
	spinBox->setMaximum((sample_num - 1));
}

void Sim::updateCam(void)
{
	if (cam_pth.length() != 0 && id_current_frame < sample_num)
	{
		stringstream ss;
		string current_cam_file;

		ss << id_current_frame + 1;
		ss >> current_cam_file;
		ss.clear();
		ss.str("");

		string cam_file_suffix{".jpg"};
		string cam_file_pth = cam_pth + "\\" + current_cam_file + cam_file_suffix;
		QString cam_file_pth_qstring = QString::fromStdString(cam_file_pth);

		QImage *img = new QImage;
		if (!img->load(cam_file_pth_qstring))
		{
			QMessageBox::warning(
				this,
				tr("Load Camera-Image fail"),
				tr("Load Camera-Image fail"));
		}
		else
		{
			p_dlg_cam->showCam(QPixmap::fromImage(*img));
			// ui->lab_image->setPixmap(QPixmap::fromImage(*img));
		}
		/*
		QMessageBox::information(
			this,
			"Camera Path",
			cam_file_pth_qstring
		);*/
	}
}

void Sim::updateRadar(void)
{
	if (!vec_radar_detections.empty() && !vec_all_sample_rectPoints.empty())
	{
		if (series_pos != nullptr)
		{
			delete series_pos;
		}
		if (!vec_p_curSeries_vel.empty())
		{
			for (auto& p_series_vel : vec_p_curSeries_vel)
			{
				delete p_series_vel;
			}
			vec_p_curSeries_vel.clear();
		}

		series_pos = new QScatterSeries();

		series_pos->setName(("Pos"));

		Radar_detections current_detections{vec_radar_detections.at(id_current_frame)};
		for (int i = 0; i < current_detections.num_detections; i++)
		{
			series_pos->append(
				-current_detections.vec_y.at(i),
				current_detections.vec_x.at(i));

			QLineSeries* p_series_vel = new QLineSeries();
			p_series_vel->append(
				-current_detections.vec_y.at(i),
				current_detections.vec_x.at(i));

			p_series_vel->append(
				-current_detections.vec_y.at(i)-current_detections.vec_vy_comp.at(i),
				current_detections.vec_x.at(i)+current_detections.vec_vx_comp.at(i));
			vec_p_curSeries_vel.push_back(p_series_vel);
		}

		double min_x, max_x, min_y, max_y;
		// min_x = *min_element(current_detections.vec_x.begin(), current_detections.vec_x.end());
		max_x = *max_element(current_detections.vec_x.begin(), current_detections.vec_x.end());
		min_y = *min_element(current_detections.vec_y.begin(), current_detections.vec_y.end());
		max_y = *max_element(current_detections.vec_y.begin(), current_detections.vec_y.end());
		axisX->setRange(0, static_cast<int>(ceil(max_x / 10)) * 10);
		double dou_lim_y = abs(max_y) > abs(min_y) ? abs(max_y) : abs(min_y);
		int lim_y = int(ceil(dou_lim_y / 10) * 10);
		axisY->setRange(-lim_y, lim_y);

		/*
		QPen blue_pen;
		blue_pen.setColor(Qt::blue);
		blue_pen.setWidth(0.5);
		series_pos->setPen(blue_pen);
		*/
		series_pos->setMarkerSize(10);
		chart->addSeries(series_pos);
		chart->setAxisX(axisY, series_pos);
		chart->setAxisY(axisX, series_pos);

		connect(series_pos, SIGNAL(hovered(const QPointF & , bool)), this, SLOT(onScatterPointsHover(const QPointF&, bool)));

		// add the vel-comp line to the birdview
		for (auto& p_LSeries_vel : vec_p_curSeries_vel)
		{
			QPen black_pen;
			black_pen.setColor(Qt::black);
			p_LSeries_vel->setPen(black_pen);
			chart->addSeries(p_LSeries_vel);
			chart->setAxisX(axisY, p_LSeries_vel);
			chart->setAxisY(axisX, p_LSeries_vel);
		}

		// add the rectangle points of anns in radar coordinate system
		if (!vec_p_curSeries_sample_rectPoints.empty())
		{
			for (auto &p_series_rectPoints : vec_p_curSeries_sample_rectPoints)
				delete p_series_rectPoints;
			vec_p_curSeries_sample_rectPoints.clear();
		}
		OneSampleRectPoints cur_sample_rectPoints = vec_all_sample_rectPoints.at(id_current_frame);
		for (auto &cur_rectPoints : cur_sample_rectPoints)
		{
			QLineSeries *p_series_cur_rectPoints = new QLineSeries;
			for (int i = 0; i < 4; i++)
			{
				p_series_cur_rectPoints->append(
					-cur_rectPoints.vec_y.at(i),
					cur_rectPoints.vec_x.at(i)
				);
			}
			// add the first point to the line
			p_series_cur_rectPoints->append(
				-cur_rectPoints.vec_y.at(0),
				cur_rectPoints.vec_x.at(0)
			);


			QPen red_pen;
			red_pen.setColor(Qt::red);
			p_series_cur_rectPoints->setPen(red_pen);
			chart->addSeries(p_series_cur_rectPoints);
			chart->setAxisX(axisY, p_series_cur_rectPoints);
			chart->setAxisY(axisX, p_series_cur_rectPoints);
			
			vec_p_curSeries_sample_rectPoints.push_back(p_series_cur_rectPoints);
		}

		chart->legend()->setVisible(false);
	}
}

void Sim::readRadarDetections(void)
{
	if (radar_pth.length() != 0)
	{
		const char *radar_pth_cstr = radar_pth.c_str();
		string radar_jsonstr = readJson(radar_pth_cstr, 30000);

		try
		{
			parseRadarJSON(radar_jsonstr.c_str());
		}
		catch (string e)
		{
			QMessageBox::warning(
				this,
				"readRadarDetections Error",
				"readRadarDetections fail");
		}
	}
}

void Sim::parseRadarJSON(const char *jsonstr)
{
	Document d;
	if (d.Parse(jsonstr).HasParseError())
	{
		QMessageBox::warning(
			this,
			"parseRadarJSON Error",
			"parseRadarJSON fail");
	}
	if (!d.IsArray())
	{
		QMessageBox::warning(
			this,
			"parseRadarJSON Error",
			"parseRadarJSON: the Root of radar.json should be Array");
		throw string("should be an Array!\n");
	}

	for (auto &detections : d.GetArray())
	{
		if (!detections.IsObject())
		{
			QMessageBox::warning(
				this,
				"parseRadarJSON Error",
				"parseRadarJSON: detections is object");
		}
		else
		{
			Radar_detections stu_detections;
			if (detections.HasMember("num"))
			{
				Value &m = detections["num"];
				stu_detections.num_detections = m.GetUint();
			}
			if (detections.HasMember("x"))
			{
				const Value &x_list = detections["x"];
				if (x_list.IsArray())
				{
					for (auto &x : x_list.GetArray())
					{
						stu_detections.vec_x.push_back(x.GetDouble());
					}
				}
			}
			if (detections.HasMember("y"))
			{
				const Value &y_list = detections["y"];
				if (y_list.IsArray())
				{
					for (auto &y : y_list.GetArray())
					{
						stu_detections.vec_y.push_back(y.GetDouble());
					}
				}
			}
			if (detections.HasMember("vx_comp"))
			{
				const Value &vx_comp_list = detections["vx_comp"];
				if (vx_comp_list.IsArray())
				{
					for (auto &vx_comp : vx_comp_list.GetArray())
					{
						stu_detections.vec_vx_comp.push_back(vx_comp.GetDouble());
					}
				}
			}
			if (detections.HasMember("vy_comp"))
			{
				const Value &vy_comp_list = detections["vy_comp"];
				if (vy_comp_list.IsArray())
				{
					for (auto &vy_comp : vy_comp_list.GetArray())
					{
						stu_detections.vec_vy_comp.push_back(vy_comp.GetDouble());
					}
				}
			}
			vec_radar_detections.push_back(stu_detections);
		}
	}
	/*
	Radar_detections first_detectons{ vec_radar_detections.at(37) };
	for(auto& vy : first_detectons.vec_vy_comp)
		qDebug() << vy << endl;
	*/

	/*
	if (d.HasMember("sample_num"))
	{
		Value& m = d["sample_num"];
		sample_num = m.GetUint64();
	}
	*/
}

void Sim::onBtnLoad(void)
{
	if (ui->cBox_mode->currentIndex() == 0)
	{
		QString cur_Pth = QDir::currentPath();
		QString title = "Select the SW Executable Program";
		QString file_filter = "Files(*.exe)";
		QString sw_pth = QFileDialog::getOpenFileName(
			this,
			title,
			cur_Pth,
			file_filter);
		if (sw_pth == "")
			QMessageBox::warning(
				this,
				"No Data File is be select",
				"Please select a data file");
		else
		{
			QStringList strlist_arguments;
			strlist_arguments << QString::number(ui->cBox_mode->currentIndex());
			invokeExe(sw_pth, strlist_arguments);
		}
	}
	else
		QMessageBox::warning(
			this,
			"Mode is on-Line",
			"Warning: on-Line don't need data file");
}

void Sim::invokeExe(const QString &m_sw_pth, const QStringList &str_list)
{
	QProcess qpro_invoke_exe(this);
	qpro_invoke_exe.start(m_sw_pth, str_list);
	while (qpro_invoke_exe.waitForFinished(1000) == false)
	{
		QByteArray qByteRead = qpro_invoke_exe.readAllStandardOutput();
		if (!qByteRead.isEmpty())
		{
			qDebug() << (QString::fromLocal8Bit(qByteRead)) << endl;
		}
	}
	QByteArray qByteRead = qpro_invoke_exe.readAllStandardOutput();
	qDebug() << QString::fromLocal8Bit(qByteRead);
	// qDebug() << strlist_arguments << endl;
}

void Sim::parseJsonAnns2D(void)
{
	if (anns2D_pth.length() != 0)
	{
		const char *anns2D_pth_cstr = anns2D_pth.c_str();
		string anns2D_jsonstr = readJson(anns2D_pth_cstr, 2100);

		Document doc;
		if (!doc.Parse(anns2D_jsonstr.data()).HasParseError())
		{
			if (doc.IsArray())
			{
				for (auto &sample_anns2D : doc.GetArray())
				{
					if (sample_anns2D.IsObject())
					{
						if (sample_anns2D.HasMember("rectPoints"))
						{
							Value &m_rect_points = sample_anns2D["rectPoints"];

							OneSampleRectPoints cur_one_sample_rectPoints;
							for (auto &ins_rect_points : m_rect_points.GetArray())
							{
								if (ins_rect_points.IsObject())
								{
									RectPoints cur_rectPoints{};

									if (ins_rect_points.HasMember("x"))
									{
										Value &m = ins_rect_points["x"];
										if (m.IsArray())
										{
											for (auto &m_x : m.GetArray())
												cur_rectPoints.vec_x.push_back(m_x.GetDouble());
										}
									}

									if (ins_rect_points.HasMember("y"))
									{
										Value &m = ins_rect_points["y"];
										if (m.IsArray())
										{
											for (auto &m_y : m.GetArray())
												cur_rectPoints.vec_y.push_back(m_y.GetDouble());
										}
									}

									cur_one_sample_rectPoints.push_back(cur_rectPoints);
								}
							}
							vec_all_sample_rectPoints.push_back(cur_one_sample_rectPoints);
						}
					}
				}
			}
		}
	}
	else
		throw string("No anns-Radar 2D file load");
}

void Sim::onScatterPointsHover(const QPointF& point, bool state)
{
	if (state)
		ui->lab_coordMouse->setText(QString::asprintf("%1.2f, %1.2f", point.x(), point.y()));
}