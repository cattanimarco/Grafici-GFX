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

#ifndef GRAFICI_USE_STD_FUNCTION
#define GRAFICI_USE_STD_FUNCTION 0
#endif

#if GRAFICI_USE_STD_FUNCTION
#include <functional>
#endif

/**
 * @brief Data source generated from a function
 * 
 */
class DataFunction : public DataParametric
{
  public:
#if GRAFICI_USE_STD_FUNCTION
	using Callback = std::function<float(size_t)>;
#else
	using Callback = float (*)(size_t);
#endif

	/**
	 * @brief Construct a data source from a given function [f(0) .. f(size-1)]
	 * 
	 * @param size size of the data source
	 * @param fn function to compute the value of each data point
	 */
	DataFunction(size_t size, Callback fn)
	    : DataParametric{ size }
	    , _fn{ static_cast<Callback &&>(fn) }
	{
		if (!_fn) _size = 0;
		update_range();
	}

	/**
	 * @brief Construct a data source from a given function [f(0) .. f(size-1)]
	 * 
	 * @param size size of the data source
	 * @param fn function to compute the value of each data point
	 * @param range value range against which f() is normalized
	 */
	DataFunction(size_t size, Callback fn, Range<float> range)
	    : DataParametric{ size, range }
	    , _fn{ static_cast<Callback &&>(fn) }
	{
		if (!_fn) _size = 0;
	}

  protected:
	float at(size_t idx) const override
	{
		return _fn(idx);
	}

  private:
	Callback _fn;
};

#endif /* GRAFICI_DATA_FUNCTION_H */

/** @}*/