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

#ifndef GRAFICI_DATA_LINEAR_H
#define GRAFICI_DATA_LINEAR_H

/*! Importation of librairies*/
#include "DataParametric.h"
/**
 * @brief Data source generated from a linear function
 * 
 */
class DataLinear : public DataParametric
{
  public:
	/**
     * @brief Construct a new Data Linear object
     * 
     * @param size 
     * @param offset 
     * @param slope 
     */
	DataLinear(size_t size, float offset = 0, float slope = 1)
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
	DataLinear(size_t size, Range<float> range, float offset = 0, float slope = 1)
	    : DataParametric{ size, range }
	    , _offset{ offset }
	    , _slope{ slope }
	{
	}

  protected:
	float at(size_t idx) const override
	{
		return idx * _slope + _offset;
	}

  private:
	void update_range() override
	{
		_range = { at(0), at(size() - 1) };
	}

	float _offset;
	float _slope;
};

#endif /* GRAFICI_DATA_LINEAR_H */
