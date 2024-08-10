/**************************************************************************************
*																				 *
* @file			utils.cpp														 *
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
*************************************************************************************/

#include "utils.hpp"

Vector3d App2App_transCoord( const Vector3d& pos_,
	const Isometry3d& T_, const Matrix3d& Mat_intri_ )
{
	Vector3d return_pos;

	if (Mat_intri_.isZero())

		return_pos = T_ * pos_;
	else
		return_pos = Mat_intri_ * T_ * pos_;

	return return_pos;
}

string App2App_readJsonToBuf(const char* filename, unsigned int num_KB)
{
	errno_t err;
	FILE* fp;
	err = fopen_s(&fp, filename, "rb");
	if (fp==0 || err != 0)
	{
		throw string("open %s fail!\n", filename);
		return "";
	}
	else
	{
		unsigned long long buf_size = static_cast<unsigned long long>(1024 * num_KB);
		char* buf = new char[buf_size];
		size_t n = fread_s(buf, buf_size, 1, buf_size, fp);
		if (fclose(fp) != 0)
		{
			throw string("close %s fail!\n", filename);
		}

		string result;
		if (n >= 0)
		{
			result.append(buf, 0, n);
		}
		delete[] buf;
		return result;
	}
}

Isometry3d App2App_getTransMatfromQuatVec(const Quaterniond& m_quta, const Vector3d& m_vec)
{
	double x, y, z, w;
	x = m_quta.coeffs()[0];
	y = m_quta.coeffs()[1];
	z = m_quta.coeffs()[2];
	w = m_quta.coeffs()[3];

	// construct rotate matrix from Quaternion in left-hand coordinate system
	double mat_rotat[9];
	mat_rotat[0] = 1 - 2 * y *y - 2 * z * z;
	mat_rotat[1] = 2 * x * y + 2 * w * z;
	mat_rotat[2] = 2 * x * z - 2 * w * y;
	mat_rotat[3] = 2 * x * y - 2 * w * z;
	mat_rotat[4] = 1 - 2 * x * x - 2 * z * z;
	mat_rotat[5] = 2 * y * z + 2 * w * x;
	mat_rotat[6] = 2 * x * z + 2 * w * y;
	mat_rotat[7] = 2 * y * z - 2 * w * x;
	mat_rotat[8] = 1 - 2 * x * x - 2 * y * y;

	Eigen::Isometry3d mat_transForm = Eigen::Isometry3d::Identity();
	mat_transForm(0, 0) = mat_rotat[0];
	mat_transForm(0, 1) = mat_rotat[1];
	mat_transForm(0, 2) = mat_rotat[2];
	mat_transForm(0, 3) = m_vec[0];
	mat_transForm(1, 0) = mat_rotat[3];
	mat_transForm(1, 1) = mat_rotat[4];
	mat_transForm(1, 2) = mat_rotat[5];
	mat_transForm(1, 3) = m_vec[1];
	mat_transForm(2, 0) = mat_rotat[6];
	mat_transForm(2, 1) = mat_rotat[7];
	mat_transForm(2, 2) = mat_rotat[8];
	mat_transForm(2, 3) = m_vec[2];
	mat_transForm(3, 0) = 0.0;
	mat_transForm(3, 1) = 0.0;
	mat_transForm(3, 2) = 0.0;
	mat_transForm(3, 3) = 1.0;

	return mat_transForm;
}
