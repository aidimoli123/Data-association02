/********************************************************************************
*                                                                       *
* @file			rte.hpp													*
* @beief		define some structure and functions for RTE             *
*                                                                       *
* @author		Andy.Yang                                               *
* @email		yjd2008@hotmail.com                                     *
* @version		1.0.0                                                   *
* @data			2020.10.29                                              *
* @license		see the  license in root-Dir of project                 *
*                                                                       *
------------------------------------------------------------------------*
*  Remark         : Description                                         *
*-----------------------------------------------------------------------*
*  Change History :                                                     *
*  <Date>     | <Version> | <Author>       | <Description>              *
*-----------------------------------------------------------------------*
*  2020/10/29 | 1.0.0     | Andy.Yang      | Create file                *
*  2020/10/29 | 1.0.1     | Andy.Yang      | change type Vars_of_Sensor *
*  2020/10/30 | 1.0.2     | Andy.Yang      | add type: Can_from_Ego     *
*  2020/10/31 | 1.0.3     | Andy.Yang      | add RTE2BSW_map3DBoxto2D   *
*-----------------------------------------------------------------------*
*********************************************************************************/

#pragma once

#include <memory>
#include <iostream>
#include <vector>

#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;


typedef struct
{
	Quaterniond quate_cam_rotat;
	Vector3d vec3d_cam_trans_m;
	Matrix3d mat3d_cam_intri;
	Quaterniond quate_radar_rotat;
	Vector3d vec3d_radar_trans_m;
} Vars_of_Sensor, *p_Vars_of_Sensor;

bool RTE2BSW_getInitVars();

typedef struct
{
	vector<Quaterniond> vec_radar_ego_rotat;
	vector<Vector3d> vec_radar_ego_trans;
} Can_from_Ego, *p_Can_from_Ego;

bool RTE2BSW_getCanFromEgo(const char* canfromego_pth);

bool RTE2BSW_map3DBoxto2D(const char* Box3D_pth);