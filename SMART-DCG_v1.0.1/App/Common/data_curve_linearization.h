/*
 * data_curve_linearization.h
 *
 *  Created on: Jul 28, 2021
 *      Author: linhLV
 */

#ifndef DATA_CURVE_LINEARIZATION_H_
#define DATA_CURVE_LINEARIZATION_H_



typedef struct
{
  float x;
  float y;
}CURVE_POINT_t;




float Linearization_data( const CURVE_POINT_t * pointSet, int pointQty, float inputData );






#endif /* DATA_CURVE_LINEARIZATION_H_ */
