/*!
* \file DataFunction.h
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

#ifndef GRAFICI_DATA_FUNCTION_H
#define GRAFICI_DATA_FUNCTION_H

/*! Importation of librairies*/
#include "DataParametric.h"

/**
 * @brief Data source generated from a function
 * 
 */
class DataFunction : public DataParametric
{
  public:
	/**
	 * @brief Construct a data source from a given function [f(0) .. f(size-1)]
	 * 
	 * @param size size of the data source
	 * @param fn function to compute the value of each data point
	 */
	DataFunction(size_t size, float (*fn)(size_t))
	    : DataParametric{ size }
	    , _fn{ fn }
	{
		update_range();
	}

	/**
	 * @brief Construct a data source from a given function [f(0) .. f(size-1)]
	 * 
	 * @param size size of the data source
	 * @param fn function to compute the value of each data point
	 * @param range value range against which f() is normalized
	 */
	DataFunction(size_t size, float (*fn)(size_t), Range<float> range)
	    : DataParametric{ size, range }
	    , _fn{ fn }
	{
	}

  protected:
	float at(size_t idx) const override
	{
		return _fn(idx);
	}

  private:
	float (*_fn)(size_t);
};

#endif /* GRAFICI_DATA_FUNCTION_H */

/** @}*/