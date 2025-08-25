/*
 * ringBuffer.h
 *
 *  Created on: Sep 14, 2022
 *      Author: Manhld
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include "main.h"
enum ring_buffer_mode_e
{
	ring_buffer_mode_normal = 0, ring_buffer_mode_pushout,
};

typedef enum ring_buffer_mode_e ring_buffer_mode_t;

struct ring_buffer_st
{
	uint16_t headIndex;
	uint16_t tailIndex;
	uint16_t size;
	ring_buffer_mode_t mode;
	uint8_t buffer[];
};

typedef struct ring_buffer_st ring_buffer_t;

ring_buffer_t* ringBuffer_creat(size_t sizeBuf, ring_buffer_mode_t mode);
uint16_t ringBuffer_write(ring_buffer_t *ringBuf, uint8_t *dataBuf, size_t len);
uint16_t ringBuffer_read(ring_buffer_t *ringBuf, uint8_t *dataBuf, size_t len);
uint8_t ringBuffer_peek(ring_buffer_t *ringBuf, uint16_t offset);
int32_t ringBuffer_find(ring_buffer_t *ringBuf, uint8_t reference);
uint16_t ringBuffer_getLength(ring_buffer_t *ringBuf);
void ringBuffer_setMode(ring_buffer_t *ringBuf, ring_buffer_mode_t mode);
void ringBuffer_flush(ring_buffer_t *ringBuf);
void ringBuffer_delete(ring_buffer_t *ringBuf);

#endif /* RINGBUFFER_H_ */
