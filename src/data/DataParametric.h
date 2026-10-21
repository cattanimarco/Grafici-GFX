/*!
* \file DataParametric.h
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

#ifndef GRAFICI_DATA_PARAMETRIC_H
#define GRAFICI_DATA_PARAMETRIC_H

/*! Importation of librairies*/
#include "DataSourceNorm.h"

/**
 * @brief Interface for generated data sources
 * 
 */
class DataParametric : public DataSourceNorm
{
  public:
	DataParametric(size_t size)
	    : DataSourceNorm{ size }
	{
	}

	DataParametric(size_t size, Range<float> range)
	    : DataSourceNorm{ size , range}
	{
	}

	/**
	 * @brief Return a data point
	 * 
	 * @param idx index of the requested data point. Indext must be between 0 and size-1.
	 * @return const DataNorm 
	 */
	const DataNorm operator[](const unsigned long idx) const override
	{
		if (idx < DataSource<DataNorm>::size())
		{
			return { at(idx), DataSourceNorm::range() };
		}
		else
		{
			return DataNorm::invalid();
		}
	}

  protected:
	virtual float at(size_t idx) const = 0;

	virtual void update_range()
	{
		_range = Range<float>::invalid();
		for (size_t idx = 0; idx < size(); ++idx)
			_range.update(static_cast<float>(at(idx)));
			}

};

#endif /* GRAFICI_DATA_PARAMETRIC_H */

/** @}*/