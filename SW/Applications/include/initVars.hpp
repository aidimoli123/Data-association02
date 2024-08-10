/********************************************************************************
*                                                                       *
* @file			initVars.hpp                                           *
* @beief		initialize some args of System                          *
* For example, the calibrated args of sensors                           *
*                                                                       *
* @author		Andy.Yang                                               *
* @email		yjd2008@hotmail.com                                     *
* @version		1.0.0                                                   *
* @data			2020.10.29                                             *
* @license		see the  license in root-dir of project                 *
*                                                                       *
------------------------------------------------------------------------*
*  Remark         : Description                                         *
*-----------------------------------------------------------------------*
*  Change History :                                                     *
*  <Date>     | <Version> | <Author>       | <Description>              *
*-----------------------------------------------------------------------*
*  2020/10/29 | 1.0.0     | Andy.Yang      | Create file                *
*-----------------------------------------------------------------------*
*********************************************************************************/

#pragma once

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "rte.hpp"

using namespace Eigen;

/**
 * @brief initialize the calibrated vars of Sensors
 *
 * @return bool
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
bool App2RTE_initSensorsCaliVars(Vars_of_Sensor&);