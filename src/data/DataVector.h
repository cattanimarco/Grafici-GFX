#ifndef GRAFICI_DATA_VECTOR_H
#define GRAFICI_DATA_VECTOR_H

#include "../Vector.h"
#include "DataNorm.h"

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
using DataVector = Vector<DataNorm>;

#endif /* GRAFICI_DATA_VECTOR_H */
