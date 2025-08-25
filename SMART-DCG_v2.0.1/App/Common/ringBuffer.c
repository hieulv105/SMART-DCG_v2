/*
 * ringBuffer.c
 *
 *  Created on: Sep 14, 2022
 *      Author: Manhld
 */

#include "ringBuffer.h"
#include "stdlib.h"
#include "string.h"

ring_buffer_t* ringBuffer_creat(size_t sizeBuf, ring_buffer_mode_t mode)
{
	ring_buffer_t *newRingBuffer;

	newRingBuffer = malloc(sizeof(ring_buffer_t) + sizeBuf * sizeof(uint8_t));

	if (newRingBuffer)
	{
		newRingBuffer->headIndex = 0;
		newRingBuffer->tailIndex = 0;
		newRingBuffer->size = sizeBuf;
		newRingBuffer->mode = ring_buffer_mode_normal;
		memset(newRingBuffer->buffer, 0, sizeBuf);
	}

	return newRingBuffer;
}

uint16_t ringBuffer_write(ring_buffer_t *ringBuf, uint8_t *dataBuf, size_t len)
{
	uint16_t i;

	for (i = 0; i < len; i++)
	{
		if (ringBuffer_getLength(ringBuf) >= (ringBuf->size - 1))
		{
			if (ringBuf->mode == ring_buffer_mode_normal)
				break;
			else if (ringBuf->mode == ring_buffer_mode_pushout)
				ringBuf->headIndex = (ringBuf->headIndex + 1) % ringBuf->size;
		}
		ringBuf->buffer[ringBuf->tailIndex] = dataBuf[i];
		ringBuf->tailIndex = (ringBuf->tailIndex + 1) % ringBuf->size;
	}

	return i;
}

uint16_t ringBuffer_read(ring_buffer_t *ringBuf, uint8_t *dataBuf, size_t len)
{
	uint16_t i;

	for (i = 0; i < len; i++)
	{
		if (ringBuffer_getLength(ringBuf) == 0)
			break;
		dataBuf[i] = ringBuf->buffer[ringBuf->headIndex];
		ringBuf->headIndex = (ringBuf->headIndex + 1) % ringBuf->size;
	}

	return i;
}

uint8_t ringBuffer_peek(ring_buffer_t *ringBuf, uint16_t offset)
{
	if (offset >= ringBuffer_getLength(ringBuf))
		offset = ringBuffer_getLength(ringBuf) - 1;
	return ringBuf->buffer[(ringBuf->headIndex + offset) % ringBuf->size];
}

int32_t ringBuffer_find(ring_buffer_t *ringBuf, uint8_t reference)
{
	uint16_t offset = 0, leng = 0;

	leng = ringBuffer_getLength(ringBuf);
	while (offset < leng)
	{
		if (ringBuffer_peek(ringBuf, offset) == reference)
			return offset;
		offset++;
	}

	return -1;
}

uint16_t ringBuffer_getLength(ring_buffer_t *ringBuf)
{
	return (ringBuf->tailIndex >= ringBuf->headIndex) ?
			(ringBuf->tailIndex - ringBuf->headIndex) :
			(ringBuf->tailIndex + (ringBuf->size - ringBuf->headIndex));
}

void ringBuffer_setMode(ring_buffer_t * ringBuf, ring_buffer_mode_t mode)
{
	ringBuf->mode = mode;
}

void ringBuffer_flush(ring_buffer_t *ringBuf)
{
	for (uint16_t i = 0; i < ringBuf->size; i++)
		ringBuf->buffer[i] = 0;
	ringBuf->tailIndex = 0;
	ringBuf->headIndex = 0;
}

void ringBuffer_delete(ring_buffer_t *ringBuf)
{
	free(ringBuf);
}

