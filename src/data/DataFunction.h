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
template <typename Scalar = float>
class DataFunctionT : public DataParametricT<Scalar>
{
  public:
    using Compute = typename grafici::ComputationType<Scalar>::type;
    using DataNorm = DataNormT<Scalar>;
    using DataParametric = DataParametricT<Scalar>;
    using DataParametric::size;
    using DataFunction = DataFunctionT<Scalar>;
protected:
    using DataParametric::update_range;
    using DataParametric::_range;
  public:
	/**
	 * @brief Construct a data source from a given function [f(0) .. f(size-1)]
	 * 
	 * @param size size of the data source
	 * @param fn function to compute the value of each data point
	 */
	DataFunctionT(size_t size, Compute (*fn)(size_t))
	    : DataParametric{ size }
	    , _fn{ fn }
	{
		if (!_fn) this->_size = 0;
		update_range();
	}

	/**
	 * @brief Construct a data source from a given function [f(0) .. f(size-1)]
	 * 
	 * @param size size of the data source
	 * @param fn function to compute the value of each data point
	 * @param range value range against which f() is normalized
	 */
	DataFunctionT(size_t size, Compute (*fn)(size_t), Range<Scalar> range)
	    : DataParametric{ size, range }
	    , _fn{ fn }
	{
		if (!_fn) this->_size = 0;
	}

  protected:
	Compute at(size_t idx) const override
	{
		return _fn(idx);
	}

  private:
	Compute (*_fn)(size_t);
};

using DataFunction = DataFunctionT<float>;

#endif /* GRAFICI_DATA_FUNCTION_H */

/** @}*/