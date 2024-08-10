/*************************************************************************************
*																				 *
* @file			utils.hpp														 *
* @beief		supply some functions to  other modules							 *
*																				 *
* @author		Andy.Yang														 *
* @email		yjd2008@hotmail.com												 *
* @version		1.0.0															 *
* @data			2020.10.29														 *
* @license		see the  license in root-Dir of project							 *
*																				 *
---------------------------------------------------------------------------------*
*  Remark         : Description													 *
*--------------------------------------------------------------------------------*
*  Change History :																 *
*  <Date>     | <Version> | <Author>       | <Description>						 *
*--------------------------------------------------------------------------------*
*  2020/10/29 | 1.0.0     | Andy.Yang      | Create file						 *
*  2020/10/30 | 1.0.1     | Andy.Yang      | add App2App_readJsonToBuf			 *
*  2020/11/02 | 1.0.2     | Andy.Yang      | add App2App_getTransMatfromQuatVec  *
*--------------------------------------------------------------------------------*
**************************************************************************************/

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;

/**
 * @brief transform the coordinate system to another
 * @param pos_  the source coordinate
 * @param T_  the transform matrix
 * @param Mat_intri_  the intrinsic matrix of camera
 * 
 * @return Vector3d
 */
Vector3d App2App_transCoord(
	const Vector3d& pos_,
	const Isometry3d& T_,
	const Matrix3d& Mat_intri_ = Matrix3d::Zero()
);

/**
 * @brief transform the coordinate system to another
 * @param pos_  the source coordinate
 * @param T_  the transform matrix
 * @param Mat_intri_  the intrinsic matrix of camera
 *
 * @return Vector3d
 */
string App2App_readJsonToBuf(const char* filename, unsigned int num_KB);


/**
 * @brief get the transform matrix from Quaternion and Vector
 * @param Quaterniond  the rotation args with the type Quaternion
 * @param Vector3d  the translation vector
 *
 * @return Isometry3d the transform matrix
 */
Isometry3d App2App_getTransMatfromQuatVec(const Quaterniond&, const Vector3d&);