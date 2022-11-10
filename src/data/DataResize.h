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


#ifndef GRAFICI_DATA_RESIZE_H
#define GRAFICI_DATA_RESIZE_H

/*! Importation of librairies*/
#include "DataSourceNorm.h"

/**
 * @brief Data source generated from resizing another data source
 * 
 */
class DataResize : public DataSourceNorm
{
  public:
	/**
	* @brief Construct a new Data Resize object
	* 
	* @param source 
	* @param range Normally a data source outputs values from 0 to 1. The output values of this data source will be dicated by parameter 'range'
	*/
	DataResize(const DataSourceNorm &source, Range<float> range)
	    : DataSourceNorm{ source.size() }
	    , _source{ source }

	{
		_range = range;
	}

	const DataNorm operator[](const unsigned long idx) const override
	{
		if (idx < DataSource<DataNorm>::size())
		{
			return { _range.norm_to_value(_source[idx].norm()), { 0, 1 } };
		}
		else
		{
			return INVALID_DATA_NORM;
		}
	};

  private:
	const DataSourceNorm &_source;
};

#endif /* GRAFICI_DATA_RESIZE_H */
