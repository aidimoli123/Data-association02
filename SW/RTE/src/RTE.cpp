/********************************************************************************
*                                                                       *
* @file			rte.cpp                                                 *
* @beief		cluster the Detections                                  *
* realize virtual function bus                                          *
*                                                                       *
* @author		Andy.Yang                                               *
* @email		yjd2008@hotmail.com                                     *
* @version		1.0.0                                                   *
* @data			2020.10.23                                              *
* @license		see the  license in root-Dir of project                 *
*                                                                       *
------------------------------------------------------------------------*
*  Remark         : Description                                         *
*-----------------------------------------------------------------------*
*  Change History :                                                     *
*  <Date>     | <Version> | <Author>       | <Description>              *
*-----------------------------------------------------------------------*
*  2020/10/23 | 1.0.0     | Andy.Yang      | Create file                *
*-----------------------------------------------------------------------*
*  2020/10/29 | 1.0.1     | Andy.Yang      | add RTE2BSW_getInitVars    *
*  2020/10/30 | 1.0.2     | Andy.Yang      | add RTE2BSW_getCanFromEgo  *
*  2020/10/31 | 1.0.3     | Andy.Yang      | add RTE2BSW_map3DBoxto2D   *
*********************************************************************************/

#include "rte.hpp"

#include "initVars.hpp"
#include "canfromego.hpp"
#include "3DBoxMap2D.hpp"

unique_ptr<Vars_of_Sensor> p_sensorArgs(new Vars_of_Sensor);
unique_ptr< Can_from_Ego> p_canfromego(new Can_from_Ego);

bool RTE2BSW_getDetections(const double *m_Detections)
{
	return true;
}

/**
 * @brief initialize the calibrated vars of Sensors
 * @return bool
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
bool RTE2BSW_getInitVars()
{
	bool st_initVars = App2RTE_initSensorsCaliVars(*p_sensorArgs);
	if (!st_initVars)
		return false;
	else
		return true;
}

/**
 * @brief get Ego vars from CAN
 * @return bool
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
bool RTE2BSW_getCanFromEgo(const char* canfromego_pth)
{
	bool st_getCanFromEgo = App2RTE_getCanFromEgo(*p_canfromego, canfromego_pth);
	if (!st_getCanFromEgo)
		return false;
	else
		return true;
}

/**
 * @brief map 3D-Box to 2D in radar coordinate system
 * @return bool
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
bool RTE2BSW_map3DBoxto2D(const char* box3D_pth)
{
	bool st_map3Dto2D = App2RTE_map3DBoxto2D(box3D_pth, *p_sensorArgs, *p_canfromego);
	if (!st_map3Dto2D)
		return false;
	else
		return true;
}