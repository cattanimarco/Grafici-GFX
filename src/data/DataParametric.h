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
template <typename Scalar = float>
class DataParametricT : public DataSourceNormT<Scalar>
{
  public:
	using Compute = typename grafici::ComputationType<Scalar>::type;
	using DataNorm = DataNormT<Scalar>;
	using DataSourceNorm = DataSourceNormT<Scalar>;
	using DataSourceNorm::size;
	using DataParametric = DataParametricT<Scalar>;
protected:
	using DataSourceNorm::_range;
  public:
	DataParametricT(size_t size)
	    : DataSourceNorm{ size }
	{
	}

	DataParametricT(size_t size, Range<Scalar> range)
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
			return INVALID_DATA_NORM;
		}
	}

  protected:
	virtual Compute at(size_t idx) const = 0;

	virtual void update_range()
	{
		if (DataSource<DataNorm>::size() > 0)
		{
			DataSourceNorm::_range = {at(0),at(0)};
			for (size_t idx = 1; idx < DataSource<DataNorm>::size(); ++idx)
			{
				DataSourceNorm::_range.update(at(idx));
			}
		}
	}
};

using DataParametric = DataParametricT<float>;

#endif /* GRAFICI_DATA_PARAMETRIC_H */

/** @}*/