/*!
* \file DataConstant.h
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

#ifndef GRAFICI_DATA_CONSTANT_H
#define GRAFICI_DATA_CONSTANT_H

/*! Importation of librairies*/
#include "DataParametric.h"

/**
 * @brief Data source returning a constant value
 * 
 */
template <typename Scalar = float>
class DataConstantT : public DataParametricT<Scalar>
{
  public:
	using Compute = typename grafici::ComputationType<Scalar>::type;
	using DataNorm = DataNormT<Scalar>;
	using DataParametric = DataParametricT<Scalar>;
	using DataParametric::size;
	using DataConstant = DataConstantT<Scalar>;
protected:
	using DataParametric::_range;
  public:
	/**
	* @brief Construct a new data source from a normalized data point
	* 
	* @param size size of the data source
	* @param val value of the normalized data source that will be returned
	*/
	DataConstantT(size_t size, DataNorm val)
	    : DataParametric{ size, val.range() }
	{
		_value = val.raw();
	}

  protected:
	Compute at(size_t idx __attribute__((unused))) const override
	{
		return _value;
	}

  private:
	Scalar _value;
};

using DataConstant = DataConstantT<float>;

#endif /* GRAFICI_DATA_CONSTANT_H */

/** @}*/