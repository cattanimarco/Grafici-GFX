/*!
* \file DataArray.h
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

#ifndef GRAFICI_DATA_ARRAY_H
#define GRAFICI_DATA_ARRAY_H

/*! Importation of librairies*/
#include "DataSourceNorm.h"

/**
 * @brief Data source obtained from a C array
 * 
 * @tparam T type of the array
 */
template <typename T>
class DataArray : public DataSourceNorm
{
  public:
	/**
     * @brief Construct a new data source from a C array
     * 
     * @param data pointer to the data array. Note that the array does not get copied. 
     * @param size number of elements in the array. This will also become the size of the data source.
     */
	DataArray(const T *data, size_t size)
	    : DataSourceNorm{ size }
	    , _arrayPtr{ data }

	{
		if (!_arrayPtr) _size = 0;
		update_range();
	}

	DataArray(const T *data, size_t size, Range<float> range)
	    : DataSourceNorm{ size , range}
	    , _arrayPtr{ data }

	{
		if (!_arrayPtr) _size = 0;
	}

	/**
	 * @brief Returns the data point at specified location idx. 
	 * 
	 * @param idx position of the element to return. To be valid, idx must be between 0 and size-1.
	 * @return const DataNorm Copy of the requested element in case the provided idx is valid, DataNorm::invalid() otherwise.
	 */
	const DataNorm operator[](const unsigned long idx) const override
	{
		if ((_arrayPtr != nullptr) && (idx < DataSource<DataNorm>::size()))
		{
			return DataSourceNorm::float_to_data_norm(static_cast<float>(_arrayPtr[idx]));
		}
		else
		{
			return DataNorm::invalid();
		}
	};

  private:
	void update_range()
	{
		DataSourceNorm::_range = Range<float>::invalid();
		if (_arrayPtr)
			for (size_t idx = 0; idx < size(); ++idx)
				DataSourceNorm::_range.update(static_cast<float>(_arrayPtr[idx]));
	}

	const T *_arrayPtr{ nullptr };
};

#endif /* GRAFICI_DATA_ARRAY_H */

/** @}*/