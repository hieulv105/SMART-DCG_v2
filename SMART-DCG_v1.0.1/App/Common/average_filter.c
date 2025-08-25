/*
 * filter.c
 *
 *  Created on: May 9, 2021
 *      Author: linhLV
 */

#include "../Common/average_filter.h"

#include "stdlib.h"
#include "string.h"



AVERAGE_FILTER * AVERAGE_FILTER_creat( uint32_t filter_size )
{

  AVERAGE_FILTER * newFilter;

  newFilter =  malloc(sizeof( AVERAGE_FILTER) + filter_size*sizeof(float) );

  if(newFilter)	//mem allocated
  {
    // reset all value to 0
    newFilter->size = filter_size;
    newFilter->oldest_post =0;
    newFilter->sum =0;
    memset(newFilter->value_array,0, filter_size*sizeof(float) );
  }
  return newFilter;
}


float AVERAGE_FILTER_update(AVERAGE_FILTER * filter,  float newVal)
{

  filter->sum -= filter->value_array[filter->oldest_post];	// remove oldest value from total SUM
  filter->value_array[filter->oldest_post] = newVal;		// update new value
  //mark next oldest update
  if( ++filter->oldest_post >= filter->size) filter->oldest_post = 0;
  filter->sum += newVal;

  return filter->sum/filter->size;
}

float AVERAGE_FILTER_getAverageValue(AVERAGE_FILTER * filter)
{
	return filter->sum/filter->size;
}

void AVERAGE_FILTER_reset(AVERAGE_FILTER * filter )
{
  filter->oldest_post =0;
  filter->sum =0;
  memset(filter->value_array,0, filter->size*sizeof(float) );
}

void AVERAGE_FILTER_delete(AVERAGE_FILTER * filter )
{
//  vPortFree(filter);
  free(filter);
}

