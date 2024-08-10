/********************************************************************************
*                                                                       *
* @file			canfromego.hpp	                                        *
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

#pragma once

#include <string>

#include "rapidjson/include/document.h"
#include "rapidjson/include/writer.h"
#include "rapidjson/include/stringbuffer.h"

#include "rte.hpp"

using namespace std;
using namespace rapidjson;

/**
 * @brief get the Ego data from CAN
 * @param m_canfromego<Can_from_Ego> store data
 * @param m_canfromego_pth<const char*> the path of can json file
 *
 * @return bool
 */
bool App2RTE_getCanFromEgo(Can_from_Ego& m_canfromego, const char* m_canfromego_pth);