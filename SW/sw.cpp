/********************************************************************************
*                                                                       *
* @file			sw.cpp													*
* @beief		the entry of SW			                                *
* cluster the Detections and get object-list                            *
*                                                                       *
* @author		Andy.Yang                                               *
* @email		yjd2008@hotmail.com                                     *
* @version		1.0.0                                                   *
* @data			2020.10.23                                              *
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

#include <iostream>

#include "rte.hpp"

/**
 * @brief set the entry of program
 * @param argc  the number of cmd args
 * @param argv  the list of string of cmd args
 */
int main(int argc, char** argv)
{
	using namespace std;

	bool st_initVar= RTE2BSW_getInitVars();

	bool st_CANfromEgo = RTE2BSW_getCanFromEgo(
		"D:\\Projects\\set-sail2\\SIM\\offline\\data\\CANfromEgo\\can.json");

	bool st_3DboxMap2D = RTE2BSW_map3DBoxto2D(
		"D:\\Projects\\set-sail2\\SIM\\offline\\data\\true\\anns.json");

	return 0;
}