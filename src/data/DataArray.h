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
template <typename T, typename Scalar = float>
class DataArray : public DataSourceNormT<Scalar>
{
  public:
    using Compute = typename grafici::ComputationType<Scalar>::type;
    using DataNorm = DataNormT<Scalar>;
    using DataSourceNorm = DataSourceNormT<Scalar>;
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
		if (!_arrayPtr) this->_size = 0;
		update_range();
	}

	DataArray(const T *data, size_t size, Range<Scalar> range)
	    : DataSourceNorm{ size , range}
	    , _arrayPtr{ data }

	{
		if (!_arrayPtr) this->_size = 0;
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
			return DataSourceNorm::float_to_data_norm(static_cast<Scalar>(_arrayPtr[idx]));
		}
		else
		{
			return INVALID_DATA_NORM;
		}
	};

  private:
	void update_range()
	{
		DataSourceNorm::_range = Range<Scalar>::invalid();
		if (_arrayPtr)
			for (size_t idx = 0; idx < this->size(); ++idx)
				DataSourceNorm::_range.update(static_cast<Scalar>(_arrayPtr[idx]));
	}

	const T *_arrayPtr{ nullptr };
};

#endif /* GRAFICI_DATA_ARRAY_H */

/** @}*/