#ifndef GRAFICI_DATA_VECTOR_H
#define GRAFICI_DATA_VECTOR_H

#include "../Vector.h"
#include "DataNorm.h"

/** \addtogroup Data
 *  @{
 */

// Compatibility alias; prefer DataVector::invalid().
#define INVALID_DATA_VECTOR DataVector::invalid()

/**
 * @brief Multi component (normalized) data point
 * 
 */
using DataVector = Vector<DataNorm>;

#endif /* GRAFICI_DATA_VECTOR_H */

/** @}*/