/*
 * data_curve_linearization.c
 *
 *  Created on: Jul 28, 2021
 *      Author: linhLV
 */


#include "data_curve_linearization.h"


/*
 * 	... x1 < input < x2 ...
 *
 * 	   (y1−y2)(x−x1)+(x2−x1)(y−y1)=0
 * 	=> (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
 * 	=> (y-y1) = (x-x1)/(x2-x1)*(y2-y1)
 * 	=> y = (x-x1)/(x2-x1)*(y2-y1)+y1
 */


float Linearization_data( const CURVE_POINT_t * pointSet, int pointQty, float inputData )
{
  int i;

  // search for input value possition
  for(i = 0; i < pointQty;++i)
    if(inputData < pointSet[i].x) break;

  // check input range
  if( i==0 ) return pointSet[0].y;
  else if ( i >= pointQty ) return pointSet[pointQty-1].y;

  //		y = (x-x1)/(x2-x1)*(y2-y1)+y1

  return (inputData - pointSet[i - 1].x)	//(x-x1)
  / (pointSet[i].x - pointSet[i - 1].x)		//(x2-x1)
  * (pointSet[i].y - pointSet[i - 1].y)		//(y2-y1)
  + pointSet[i - 1].y;				// +y1

}


