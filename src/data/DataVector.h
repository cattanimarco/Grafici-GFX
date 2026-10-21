#ifndef GRAFICI_DATA_VECTOR_H
#define GRAFICI_DATA_VECTOR_H

#include "../Vector.h"
#include "DataNorm.h"

/** \addtogroup Data
 *  @{
 */

// clang-format off
#define INVALID_DATA_VECTOR  \
	{                        \
		{ 0.0, {0.0, 0.0} }, \
		{ 0.0, {0.0, 0.0} }  \
	}
// clang-format on

/**
 * @brief Multi component (normalized) data point
 * 
 */
template <typename Scalar = float>
using DataVectorT = Vector<DataNormT<Scalar>>;

using DataVector = DataVectorT<float>;

#endif /* GRAFICI_DATA_VECTOR_H */

/** @}*/