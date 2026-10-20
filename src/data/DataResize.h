/*!
* \file DataResize.h
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

#ifndef GRAFICI_DATA_RESIZE_H
#define GRAFICI_DATA_RESIZE_H

/*! Importation of librairies*/
#include "DataSourceNorm.h"

/**
 * @brief Data source generated from resizing another data source
 * 
 */
template <typename Scalar = float>
class DataResizeT : public DataSourceNormT<Scalar>
{
  public:
    using Compute = typename grafici::ComputationType<Scalar>::type;
    using DataNorm = DataNormT<Scalar>;
    using DataSourceNorm = DataSourceNormT<Scalar>;
    using DataResize = DataResizeT<Scalar>;
protected:
    using DataSourceNorm::_range;
  public:
	/**
	* @brief Construct a new Data Resize object
	* 
	* @param source 
	* @param range Normally a data source outputs values from 0 to 1. The output values of this data source will be dicated by parameter 'range'
	*/
	DataResizeT(const DataSourceNorm &source, Range<Scalar> range)
	    : DataSourceNorm{ source.size() }
	    , _source{ source }

	{
		_range = range;
	}

	const DataNorm operator[](const unsigned long idx) const override
	{
		if (idx < DataSource<DataNorm>::size())
		{
			const auto value = _source[idx];
			if (!value.valid() || !_range.valid()) return INVALID_DATA_NORM;
			return { _range.norm_to_value(value.norm()), { 0, 1 } };
		}
		else
		{
			return INVALID_DATA_NORM;
		}
	};

  private:
	const DataSourceNorm &_source;
};

using DataResize = DataResizeT<float>;

#endif /* GRAFICI_DATA_RESIZE_H */

/** @}*/