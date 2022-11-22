/*!
* \file DataSource.h
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

#ifndef GRAFICI_DATA_SOURCE_H
#define GRAFICI_DATA_SOURCE_H

/**
 * @brief Interface for data sources
 * 
 * @tparam T type of the source data points
 */
template <typename T>
class DataSource
{
  public:
	/**
	 * @brief Create a data source with n data points
	 * 
	 * @param n size of the data source
	 */
	DataSource(size_t n)
	    : _size{ n }
	{
	}

	/**
	 * @brief Return a data point 
	 * 
	 * @param idx index of the requested data point. Indext must be between 0 and size-1.
	 * @return const T 
	 */
	virtual const T operator[](const unsigned long idx) const = 0;

	/**
	 * @brief Return the number of data points in the data source
	 * 
	 * @return const size_t&
	 */
	virtual const size_t &size() const
	{
		return _size;
	};

  protected:
	size_t _size{ 0 };
};

#endif //GRAFICI_DATA_SOURCE_H

/** @}*/