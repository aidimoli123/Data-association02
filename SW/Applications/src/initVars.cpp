/***************************************************************************************
*                                                                              *
* @file			initVars.cpp                                                   *
* @beief		initialize some args of System                                 *
* For example, the calibrated args of sensors                                  *
*                                                                              *
* @author		Andy.Yang                                                      *
* @email		yjd2008@hotmail.com                                            *
* @version		1.0.0                                                          *
* @data			2020.10.23                                                     *
* @license		see the  license in root-dir of project                        *
*                                                                              *
-------------------------------------------------------------------------------*
*  Remark         : Description                                                *
*------------------------------------------------------------------------------*
*  Change History :                                                            *
*  <Date>     | <Version> | <Author>       | <Description>                     *
*------------------------------------------------------------------------------*
*  2020/10/23 | 1.0.0     | Andy.Yang      | Create file                       *
*  2020/10/29 | 1.0.1     | Andy.Yang      | fill App2RTE_initSensorsCaliVars  *
*  2020/10/30 | 1.0.2     | Andy.Yang      | change the type of Vars_of_Sensor *
*****************************************************************************************/

#include "initVars.hpp"

bool App2RTE_initSensorsCaliVars(Vars_of_Sensor& m_sensorArgs)
{	
	m_sensorArgs.quate_cam_rotat=Quaterniond(
		0.4998015430569128,
		-0.5030316162024876,
		0.4997798114386805,
		-0.49737083824542755
	);

	m_sensorArgs.vec3d_cam_trans_m = Vector3d(
		1.70079118954,
		0.0159456324149,
		1.51095763913
	);

	m_sensorArgs.mat3d_cam_intri << 1266.417203046554, 0.0, 816.2670197447984,
		0.0, 1266.417203046554, 491.50706579294757,
		0.0, 0.0, 1.0;

	m_sensorArgs.quate_radar_rotat =Quaterniond(
		0.9999984769132877, 0.0, 0.0, 0.0017453283658983088
	);

	m_sensorArgs.vec3d_radar_trans_m << 3.412, 0.0, 0.5;

	return true;
}

