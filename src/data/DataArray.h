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
		update_range();
	}

	DataArray(const T *data, size_t size, Range<float> range)
	    : DataSourceNorm{ size , range}
	    , _arrayPtr{ data }

	{
	}

	/**
	 * @brief Returns the data point at specified location idx. 
	 * 
	 * @param idx position of the element to return. To be valid, idx must be between 0 and size-1.
	 * @return const DataNorm Copy of the requested element in case the provided idx is valid, INVALID_DATA_NORM otherwise.
	 */
	const DataNorm operator[](const unsigned long idx) const override
	{
		if ((_arrayPtr != nullptr) && (idx < DataSource<DataNorm>::size()))
		{
			return DataSourceNorm::float_to_data_norm(static_cast<float>(_arrayPtr[idx]));
		}
		else
		{
			return INVALID_DATA_NORM;
		}
	};

  private:
	void update_range()
	{
		if ((_arrayPtr != nullptr) && (DataSource<DataNorm>::size() > 0))
		{
			DataSourceNorm::_range = { static_cast<float>(_arrayPtr[0]), static_cast<float>(_arrayPtr[0]) };
			for (size_t idx = 1; idx < DataSource<DataNorm>::size(); ++idx)
			{
				DataSourceNorm::_range.update(static_cast<float>(_arrayPtr[idx]));
			}
		}
	}

	const T *_arrayPtr{ nullptr };
};

#endif /* GRAFICI_DATA_ARRAY_H */
