/********************************************************************************
*                                                                       *
* @file			canfromego.cpp	                                        *
* @beief		parse the can-data from ego				                *
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
*  2020/10/30 | 1.0.0     | Andy.Yang      | Create file                *
*-----------------------------------------------------------------------*
*********************************************************************************/

#include "canfromego.hpp"
#include "utils.hpp"

bool App2RTE_getCanFromEgo(Can_from_Ego& m_canfromego, const char* m_canfromego_pth)
{
	string jsonstr = App2App_readJsonToBuf(m_canfromego_pth, 30);

	Document d;
	if (d.Parse(jsonstr.c_str()).HasParseError())
	{
		throw string("parse error!\n");
		return false;
	}
	if (!d.IsObject())
	{
		throw string("should be an object!\n");
		return false;
	}

	if (d.HasMember("radar_front"))
	{
		Value& m_radar_front = d["radar_front"];

		if (m_radar_front.HasMember("ego_rotat"))
		{
			Value& m_ego_rotat_list = m_radar_front["ego_rotat"];
			if (m_ego_rotat_list.IsArray())
			{
				for (auto& m_ego_rotat : m_ego_rotat_list.GetArray())
				{	
					vector<double> vec_rotat;
					if (m_ego_rotat.IsArray())
					{
						for(auto& x:m_ego_rotat.GetArray())
							vec_rotat.push_back(x.GetDouble());
					}
					m_canfromego.vec_radar_ego_rotat.push_back(
						Quaterniond(vec_rotat.at(0), vec_rotat.at(1), vec_rotat.at(2), vec_rotat.at(3))); 
				}
			}
		}

		if (m_radar_front.HasMember("ego_trans"))
		{
			Value& m_ego_trans_list = m_radar_front["ego_trans"];
			if (m_ego_trans_list.IsArray())
			{
				for (auto& m_ego_trans : m_ego_trans_list.GetArray())
				{
					vector<double> vec_trans;
					if (m_ego_trans.IsArray())
					{
						for(auto& x:m_ego_trans.GetArray())
							vec_trans.push_back(x.GetDouble());
					}
					m_canfromego.vec_radar_ego_trans.push_back(
						Vector3d(vec_trans.at(0), vec_trans.at(1), vec_trans.at(2)));
				}
			}
		}
	}

	return true;
}