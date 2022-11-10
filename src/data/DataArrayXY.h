/*!
* \file DataArrayXY.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef GRAFICI_DATA_ARRAY_XY_H
#define GRAFICI_DATA_ARRAY_XY_H

/*! Importation of librairies*/
#include "DataArray.h"
#include "DataLinear.h"
#include "DataSelect.h"
#include "DataVector.h"
/**
 * @brief Data source obtained from a C array
 * 
 * @tparam T type of the array
 */
template <typename T>
class DataArrayXY : public DataSource<DataVector>
{
  public:
	/**
     * @brief Construct a new data source from a C array
     * 
     * @param data pointer to the data array. Note that the array does not get copied. 
     * @param size number of elements in the array. This will also become the size of the data source.
     */
	DataArrayXY(const T *data, size_t size)
	    : DataSource<DataVector>{ size }
	    , _y_data{ data, size }
	{
	}

	DataArrayXY(const T *data, size_t size, Range<float> range)
	    : DataSource<DataVector>{ size }
	    , _y_data{ data, size, range }
	{
	}

	const DataVector operator[](const unsigned long idx) const
	{
		if (idx < size())
		{
			return {
				{ static_cast<float>(idx), { 0, static_cast<float>(_size-1) } },
				_y_data[idx],
			};
		}
		else
		{
			return INVALID_DATA_VECTOR;
		}
	}

	/* methods to get a datasource from the interpolated dataset */
	DataSelect x() const
	{
		return DataSelect(*this, VectorComponents::x);
	}

	DataSelect y() const
	{
		return DataSelect(*this, VectorComponents::y);
	}

  private:
	DataArray<T> _y_data;
};

#endif /* GRAFICI_DATA_ARRAY_XY_H */
