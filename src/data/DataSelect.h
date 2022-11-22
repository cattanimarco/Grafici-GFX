/*!
* \file DataSelect.h
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

#ifndef GRAFICI_DATA_SELECT_H
#define GRAFICI_DATA_SELECT_H

enum class VectorComponents
{
	x,
	y,
};

/*! Importation of librairies*/
#include "DataSourceNorm.h"
#include "DataVector.h"

/**
 * @brief Data source generated from selecting a component from a vector data source
 * 
 */
class DataSelect : public DataSourceNorm
{
  public:
	DataSelect(const DataSource<DataVector> &source, VectorComponents selection)
	    : DataSourceNorm{ source.size() }
	    , _source{ source }
	    , _selection{ selection }
	{
	}

	const Range<float> range() const override
	{
		auto data_vector = _source[0];
		switch (_selection)
		{
		case VectorComponents::x:
		{
			return data_vector.x.range();
		}
		case VectorComponents::y:
		{
			return data_vector.y.range();
		}
		default:
		{
			return INVALID_RANGE_FLOAT;
		}
		}
		//get range using [], this is the only way to get back a vector
	}

	const DataNorm operator[](const unsigned long idx) const override
	{
		auto data_vector = _source[idx];
		switch (_selection)
		{
		case VectorComponents::x:
		{
			return data_vector.x;
		}
		case VectorComponents::y:
		{
			return data_vector.y;
		}
		default:
		{
			return INVALID_DATA_NORM;
		}
		}
	};

  private:
	const DataSource<DataVector> &_source;
	VectorComponents _selection;
};

#endif /* GRAFICI_DATA_SELECT_H */

/** @}*/