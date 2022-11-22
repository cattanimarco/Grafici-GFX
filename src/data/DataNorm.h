/*!
* \file DataNorm.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Data
 *  @{
 */

#ifndef GRAFICI_DATA_NORM_H
#define GRAFICI_DATA_NORM_H

/*! Importation of librairies*/
#include "../Range.h"

// clang-format off
/*!
* \def INVALID_DATA_NORM
* Description
*/
#define INVALID_DATA_NORM \
	{                     \
		0.0, {0.0, 0.0}     \
	}
// clang-format on

/**
 * @brief Normalized data point
 * 
 */
class DataNorm
{
  public:
	DataNorm()
	    : _raw{ 0 }
	    , _range{ 0, 0 }
	{
	}

	DataNorm(const float value, const Range<float> range = { 0, 1 })
	    : _raw{ range.trim(value) }
	    , _range{ range }
	{
	}

	float norm() const
	{
		return _range.value_to_norm(_raw);
	}

	float raw() const
	{
		return _raw;
	}

	void norm(float val)
	{
		_raw = _range.norm_to_value(val);
	}

	Range<float> range() const
	{
		return _range;
	}

	bool operator<(const DataNorm &other) const
	{
		return norm() < other.norm();
	}

	bool operator>(const DataNorm &other) const
	{
		return norm() > other.norm();
	}

  private:
	float _raw;
	Range<float> _range;
};

#endif //#ifndef GRAFICI_DATA_NORM_H

/** @}*/