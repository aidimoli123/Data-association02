/********************************************************************************
*                                                                       *
* @file			3DBoxMap2D.hpp	                                        *
* @beief		map the 3D box to 2D in radar coordinate system         *
*                                                                       *
* @author		Andy.Yang                                               *
* @email		yjd2008@hotmail.com                                     *
* @version		1.0.0                                                   *
* @data			2020.10.30                                              *
* @license		see the  license in root-Dir of project                 *
*                                                                       *
------------------------------------------------------------------------*
*  Remark         : Description                                         *
*-----------------------------------------------------------------------*
*  Change History :                                                     *
*  <Date>     | <Version> | <Author>       | <Description>              *
*-----------------------------------------------------------------------*
*  2020/10/31 | 1.0.0     | Andy.Yang      | Create file                *
*-----------------------------------------------------------------------*
*********************************************************************************/

#include "3DBoxMap2D.hpp"

bool App2RTE_map3DBoxto2D(
	const char *m_3Dbox_pth, Vars_of_Sensor &ins_sensor, Can_from_Ego &ins_can)
{
	string jsonstr = App2App_readJsonToBuf(m_3Dbox_pth, 2000);
	vector<Box3D> vec_box3D;

	bool st_parseJsonToStruct = parseJsonToStruct(jsonstr, vec_box3D);
	if (!st_parseJsonToStruct)
	{
		throw string("Error in return value of parseJsonToStruct");
		return false;
	}

	bool st_create2DBoxCoord = create2DBoxCoord(vec_box3D, ins_sensor, ins_can);
	if (!st_create2DBoxCoord)
	{
		throw string("Error in return value of create2DBoxCoord");
		return false;
	}

	return true;
}

static bool create2DBoxCoord(
	vector<Box3D> &m_vec_box3D, Vars_of_Sensor &m_sensor, Can_from_Ego &m_can)
{
	// set a type to store the transformed data in radar coordinate system
	vector<OneSampleRectRadar> vec_all_sample_rectPoints_radar;
	StringBuffer strBuf;
	Writer<StringBuffer> writer(strBuf);
	Document d;

	Isometry3d mat_radarToEgo = Isometry3d::Identity();
	mat_radarToEgo.rotate(m_sensor.quate_radar_rotat);
	mat_radarToEgo.pretranslate(m_sensor.vec3d_radar_trans_m);
	/*
	Isometry3d mat_radarToEgo = App2App_getTransMatfromQuatVec(
		m_sensor.quate_radar_rotat, m_sensor.vec3d_radar_trans_m);
	*/
	Isometry3d mat_EgoToRadar = mat_radarToEgo.inverse();

	writer.StartArray();

	for (unsigned int id_sample = 0; id_sample < m_vec_box3D.size(); id_sample++)
	{
		writer.StartObject();
		writer.Key("Rect_Points");
		writer.StartArray();

		
		Isometry3d mat_EgoToWorld = Isometry3d::Identity();
		mat_EgoToWorld.rotate((m_can.vec_radar_ego_rotat).at(id_sample));
		mat_EgoToWorld.pretranslate((m_can.vec_radar_ego_trans).at(id_sample));
		/*
		Isometry3d mat_EgoToWorld = App2App_getTransMatfromQuatVec(
			(m_can.vec_radar_ego_rotat).at(id_sample), (m_can.vec_radar_ego_trans).at(id_sample));
		*/
		Isometry3d mat_WorldToEgo = mat_EgoToWorld.inverse();

		p_Box3D p_cur_box3D = &(m_vec_box3D.at(id_sample));
		OneSampleRectRadar vec_cur_rectPoints_radar;
		for (unsigned int id_box3d = 0; id_box3d < (p_cur_box3D->num_Box3D); id_box3d++)
		{
			Vector3d cur_size_box3d{(p_cur_box3D->size_Box3D).at(id_box3d)};
			Quaterniond cur_rotat_box3d{(p_cur_box3D->rotat_Box3D).at(id_box3d)};
			Vector3d cur_trans_box3d{(p_cur_box3D->trans_Box3D).at(id_box3d)};

			RectPoints ins_rect_points_box3d;
			ins_rect_points_box3d.at(0) << 0.5 * cur_size_box3d(1), 0.5 * cur_size_box3d(0), 1.0;
			ins_rect_points_box3d.at(1) << -0.5 * cur_size_box3d(1), 0.5 * cur_size_box3d(0), 1.0;
			ins_rect_points_box3d.at(2) << -0.5 * cur_size_box3d(1), -0.5 * cur_size_box3d(0), 1.0;
			ins_rect_points_box3d.at(3) << 0.5 * cur_size_box3d(1), -0.5 * cur_size_box3d(0), 1.0;

			Isometry3d mat_box3dToWorld = Isometry3d::Identity();
			mat_box3dToWorld.rotate(cur_rotat_box3d);
			mat_box3dToWorld.pretranslate(cur_trans_box3d);
			/*
			Isometry3d mat_box3dToWorld = App2App_getTransMatfromQuatVec(
				cur_rotat_box3d, cur_trans_box3d);
			*/

			RectPoints ins_rect_points_radar;

			for (unsigned int id_rect = 0; id_rect < 4; id_rect++)
			{
				Vector3d points_in_radar = mat_EgoToRadar * mat_WorldToEgo * mat_box3dToWorld * ins_rect_points_box3d.at(id_rect);
				ins_rect_points_radar.at(id_rect) = points_in_radar;
			}
			vec_cur_rectPoints_radar.one_sample_rectPoints.push_back(ins_rect_points_radar);

			writer.StartObject();

			writer.Key("x");
			writer.StartArray();
			writer.Double((ins_rect_points_radar.at(0))(0));
			writer.Double((ins_rect_points_radar.at(1))(0));
			writer.Double((ins_rect_points_radar.at(2))(0));
			writer.Double((ins_rect_points_radar.at(3))(0));
			writer.EndArray();

			writer.Key("y");
			writer.StartArray();
			writer.Double((ins_rect_points_radar.at(0))(1));
			writer.Double((ins_rect_points_radar.at(1))(1));
			writer.Double((ins_rect_points_radar.at(2))(1));
			writer.Double((ins_rect_points_radar.at(3))(1));
			writer.EndArray();

			// each rect_points end
			writer.EndObject();
		}

		vec_cur_rectPoints_radar.num_one_sample_rectPoints = vec_cur_rectPoints_radar.one_sample_rectPoints.size();
		vec_all_sample_rectPoints_radar.push_back(vec_cur_rectPoints_radar);

		writer.EndArray();
		writer.Key("num_RectPoints");
		writer.Uint(vec_cur_rectPoints_radar.one_sample_rectPoints.size());
		writer.EndObject();
	}

	writer.EndArray();
	string data = strBuf.GetString();
	const size_t size_data = data.size();

	FILE *p_file;
	errno_t st_fopen_file = fopen_s(&p_file, "rect_points_in_radar.json", "wb");
	if (st_fopen_file != 0)
	{
		throw string("Error in 3DBoxMap2D.cpp: fopen_s json");
		return false;
	}
	else
	{
		fputs(data.c_str(), p_file);
		fclose(p_file);
	}

	/*
	char* write_buffer = new char[size_data+100];
	FileWriteStream os(p_file, write_buffer, size_data);
	Writer<FileWriteStream> writeFile(os);
	d.Accept(writer);
	delete [] write_buffer;
	*/

	return true;
}

static bool parseJsonToStruct(const string &m_jsonstr, vector<Box3D> &m_vec_box3D)
{
	Document d;
	if (d.Parse(m_jsonstr.c_str()).HasParseError())
	{
		throw string("parse error!\n");
		return false;
	}
	if (!d.IsArray())
	{
		throw string("should be an array!\n");
		return false;
	}

	for (auto &instrance_Box3D : d.GetArray())
	{
		if (instrance_Box3D.IsObject())
		{
			Box3D temp_box3D_instrance{};

			if (instrance_Box3D.HasMember("num_anns"))
			{
				Value &m = instrance_Box3D["num_anns"];
				temp_box3D_instrance.num_Box3D = m.GetUint();
			}

			if (instrance_Box3D.HasMember("translation"))
			{
				Value &m_trans_list = instrance_Box3D["translation"];
				if (m_trans_list.IsArray())
				{
					for (auto &m_trans : m_trans_list.GetArray())
					{
						vector<double> vec_trans{};
						for (auto &item : m_trans.GetArray())
							vec_trans.push_back(item.GetDouble());
						temp_box3D_instrance.trans_Box3D.push_back(
							Vector3d(vec_trans.at(0), vec_trans.at(1), vec_trans.at(2)));
					}
				}
			}

			if (instrance_Box3D.HasMember("rotation"))
			{
				Value &m_rotat_list = instrance_Box3D["rotation"];
				if (m_rotat_list.IsArray())
				{
					for (auto &m_rotat : m_rotat_list.GetArray())
					{
						vector<double> vec_rotat{};
						for (auto &item : m_rotat.GetArray())
							vec_rotat.push_back(item.GetDouble());
						temp_box3D_instrance.rotat_Box3D.push_back(
							Quaterniond(vec_rotat.at(0), vec_rotat.at(1), vec_rotat.at(2), vec_rotat.at(3)));
					}
				}
			}

			if (instrance_Box3D.HasMember("size"))
			{
				Value &m_size_list = instrance_Box3D["size"];
				if (m_size_list.IsArray())
				{
					for (auto &m_size : m_size_list.GetArray())
					{
						vector<double> vec_size{};
						for (auto &item : m_size.GetArray())
							vec_size.push_back(item.GetDouble());
						temp_box3D_instrance.size_Box3D.push_back(
							Vector3d(vec_size.at(0), vec_size.at(1), vec_size.at(2)));
					}
				}
			}

			if (instrance_Box3D.HasMember("category"))
			{
				Value &m_categ_list = instrance_Box3D["category"];
				if (m_categ_list.IsArray())
				{
					for (auto &m_categ : m_categ_list.GetArray())
					{
						if (m_categ.IsString())
							temp_box3D_instrance.categ_Box3D.push_back(
								m_categ.GetString());
					}
				}
			}

			m_vec_box3D.push_back(temp_box3D_instrance);
		}
		else
			return false;
	}

	return true;
}