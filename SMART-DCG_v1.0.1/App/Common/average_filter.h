/*
 * average_filter.h
 *
 *  Created on: May 9, 2021
 *      Author: linhLV
 */

#ifndef AVERAGE_FILTER_H_
#define AVERAGE_FILTER_H_

#include "main.h"


typedef struct
{
  float sum;
  uint32_t oldest_post;
  uint32_t size;
  float value_array[];
} AVERAGE_FILTER;


AVERAGE_FILTER * AVERAGE_FILTER_creat( uint32_t filter_size );
float AVERAGE_FILTER_update(AVERAGE_FILTER * filter,  float newVal);
float AVERAGE_FILTER_getAverageValue(AVERAGE_FILTER * filter);
void AVERAGE_FILTER_reset(AVERAGE_FILTER * filter );
void AVERAGE_FILTER_delete(AVERAGE_FILTER * filter );


#endif /* AVERAGE_FILTER_H_ */
