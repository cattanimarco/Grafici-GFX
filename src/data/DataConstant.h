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
class DataConstant : public DataParametric
{
  public:
	/**
	* @brief Construct a new data source from a normalized data point
	* 
	* @param size size of the data source
	* @param val value of the normalized data source that will be returned
	*/
	DataConstant(size_t size, DataNorm val)
	    : DataParametric{ size, val.range() }
	{
		_value = val.raw();
	}

  protected:
	float at(size_t idx __attribute__((unused))) const override
	{
		return _value;
	}

  private:
	float _value;
};

#endif /* GRAFICI_DATA_CONSTANT_H */

/** @}*/