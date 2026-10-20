/*!
* \file DataSourceVector.h
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

#ifndef GRAFICI_DATA_SOURCE_VECTOR_H
#define GRAFICI_DATA_SOURCE_VECTOR_H

/*! Importation of librairies*/
#include "DataVector.h"
#include "DataSource.h"

/**
 * @brief Data source with multi component (normalized) data points
 * 
 */
template <typename Scalar = float>
using DataSourceVectorT = DataSource<DataVectorT<Scalar>>;

using DataSourceVector = DataSourceVectorT<float>;

#endif /* GRAFICI_DATA_SOURCE_VECTOR_H */

/** @}*/
