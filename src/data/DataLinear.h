/*!
* \file DataLinear.h
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

#ifndef GRAFICI_DATA_LINEAR_H
#define GRAFICI_DATA_LINEAR_H

/*! Importation of librairies*/
#include "DataParametric.h"
/**
 * @brief Data source generated from a linear function
 * 
 */
template <typename Scalar = float>
class DataLinearT : public DataParametricT<Scalar>
{
  public:
	using Compute = typename grafici::ComputationType<Scalar>::type;
	using DataNorm = DataNormT<Scalar>;
	using DataParametric = DataParametricT<Scalar>;
	using DataParametric::size;
	using DataLinear = DataLinearT<Scalar>;
protected:
	using DataParametric::_range;
  public:
	/**
     * @brief Construct a new Data Linear object
     * 
     * @param size 
     * @param offset 
     * @param slope 
     */
	DataLinearT(size_t size, Scalar offset = 0, Scalar slope = 1)
	    : DataParametric{ size }
	    , _offset{ offset }
	    , _slope{ slope }
	{
		update_range();
	}
	/**
	 * @brief Construct a new Data Linear object
	 * 
	 * @param size 
	 * @param range 
	 * @param offset 
	 * @param slope 
	 */
	DataLinearT(size_t size, Range<Scalar> range, Scalar offset = 0, Scalar slope = 1)
	    : DataParametric{ size, range }
	    , _offset{ offset }
	    , _slope{ slope }
	{
	}

  protected:
	Compute at(size_t idx) const override
	{
		return idx * _slope + _offset;
	}

  private:
	void update_range() override
	{
		_range = { at(0), at(size() - 1) };
	}

	Scalar _offset;
	Scalar _slope;
};

using DataLinear = DataLinearT<float>;

#endif /* GRAFICI_DATA_LINEAR_H */

/** @}*/