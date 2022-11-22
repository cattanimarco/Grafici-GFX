/*!
* \file DataSourceNorm.h
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

#ifndef GRAFICI_DATA_SOURCE_NORM_H
#define GRAFICI_DATA_SOURCE_NORM_H

/*! Importation of librairies*/
#include "../Range.h"
#include "DataNorm.h"
#include "DataSource.h"


/**
 * @brief Data sources with normalized data points
 * 
 * @note This type of data source is used as input for all Grafici's plotting functions 
 */
class DataSourceNorm : public DataSource<DataNorm>
{
  public:
	/**
	 * @brief Create a data source with n DataNorm data points
	 * 
	 * @param n size of the data source
	 */
	DataSourceNorm(size_t n)
	    : DataSource<DataNorm>{ n }
	{
	}

	DataSourceNorm(size_t n, Range<float> range)
	    : DataSource<DataNorm>{ n },
		_range{range}
	{
	}

	/**
	 * @brief Return the range of the DataNorm data point 
	 * 
	 * @return const Range<float> 
	 * 
	 * @note All DataNorm data points in a DataSourceNorm share the same range. This is in order to make the the normalized value of data points comparable.
	 */
	virtual const Range<float> range() const
	{
		return { _range.low, _range.high };
	}

	/**
     * @brief Utility funtion to return the minimum size among a list of DataNorm data sources
     * 
     * @return size_t 
     *
	 * @note Implemented as a recursive variadic function
     */
	template <typename... Args>
	static size_t min_data_source_size(const DataSourceNorm &data_source, const Args &...args)
	{
		size_t other = min_data_source_size(args...);
		return other < data_source.size() ? other : data_source.size();
	}

	static size_t min_data_source_size(const DataSourceNorm &data_source)
	{
		return data_source.size();
	}

  protected:
	/**
     * @brief Utility function to return a DataNorm from a float value 
     * 
     * @param val value to encapsulate in the DataNorm
     * @return const DataNorm 
     */
	const DataNorm float_to_data_norm(float val) const
	{
		return { val, range() };
	}

	Range<float> _range{ static_cast<float>(0), static_cast<float>(0) };
};

#endif //GRAFICI_DATA_SOURCE_NORM_H

/** @}*/