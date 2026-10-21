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

// Compatibility alias; prefer DataNorm::invalid().
#define INVALID_DATA_NORM DataNorm::invalid()

/**
 * @brief Normalized data point
 * 
 */
class DataNorm
{
  public:
	DataNorm()
	    : _raw{ 0 }
	    , _range{ Range<float>::invalid() }
	{
	}

	DataNorm(const float value, const Range<float> range = { 0, 1 })
	    : _raw{ 0 }
	    , _range{ Range<float>::invalid() }
	{
		if (!range.valid() || !isfinite(value)) return;
		_raw = range.trim(value);
		_range = range;
	}

	static DataNorm invalid() { return {}; }

	bool valid() const
	{
		return _range.valid();
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
		if (!valid() || !isfinite(val)) { *this = DataNorm{}; return; }
		_raw = _range.normalized_to_value(val);
	}

	Range<float> range() const
	{
		return _range;
	}

	bool operator<(const DataNorm &other) const
	{
		return valid() && other.valid() && norm() < other.norm();
	}

	bool operator>(const DataNorm &other) const
	{
		return valid() && other.valid() && norm() > other.norm();
	}

  private:
	float _raw;
	Range<float> _range;
};

#endif //#ifndef GRAFICI_DATA_NORM_H

/** @}*/