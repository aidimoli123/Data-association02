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

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <memory>

#include "canfromego.hpp"
#include "utils.hpp"

#include "Eigen/Core"
#include "Eigen/Geometry"
#include "rapidjson/include/stringbuffer.h"
#include "rapidjson/include/writer.h"
#include "rapidjson/include/filewritestream.h"


using namespace Eigen;
using namespace std;;

typedef struct
{
	unsigned int num_Box3D;
	vector<Vector3d> trans_Box3D;
	vector<Quaterniond> rotat_Box3D;
	vector<Vector3d> size_Box3D;
	vector<string> categ_Box3D;
}Box3D, *p_Box3D;

typedef array<Vector3d, 4> RectPoints;

typedef struct
{
	size_t num_one_sample_rectPoints;
	vector<RectPoints> one_sample_rectPoints;
}OneSampleRectRadar, *p_OneSampleRectRadar;

/**
 * @brief map 3D-Box to 2D in radar coordinate system
 * @return bool
 */
bool App2RTE_map3DBoxto2D(const char* m_3Dbox_pth, Vars_of_Sensor&, Can_from_Ego&);

/**
 * @brief store the data in 3D-Box to the type Box3D
 * @return bool
 */
static bool parseJsonToStruct(const string& m_jsonstr, vector<Box3D>& m_vec_box3D);

/**
 * @brief create the 2D rectangle coordinate from 3D-Box
 * @return bool
 */
static bool create2DBoxCoord(vector<Box3D>& m_vec_box3D, Vars_of_Sensor&, Can_from_Ego&);