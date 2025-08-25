/*
 * Communication.c
 *
 *  Created on: Sep 9, 2022
 *      Author: Manhld
 */
#include "usbd_cdc_if.h"

#include "Communication.h"
#include "Utinity.h"
#include "ringBuffer.h"
#include "modbus_RTU.h"
#include "ModbusData.h"


#define MODBUS_IDLETIMEOUT 10 //mS
#define MODBUS_COUNTING_OVER (MODBUS_IDLETIMEOUT / ModbusTask_TICK_TIME)
#define MODBUS_DATA_SIZE 256

ring_buffer_t *usbBuf;


void Comunication_init(void)
{
	usbBuf = ringBuffer_creat(1000, ring_buffer_mode_normal);
}


void USB_Reconnect(void)
{
	HAL_GPIO_WritePin(USB_DP_F_GPIO_Port, USB_DP_F_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(USB_DP_F_GPIO_Port, USB_DP_F_Pin, GPIO_PIN_SET);
}


void Modbus_service(void)
{
	uint16_t dataLen = 0;
	static uint8_t modbusRequest[MODBUS_DATA_SIZE],	modbusResponse[MODBUS_DATA_SIZE];
	static uint16_t requestLen = 0, responseLen = 0, idleTime = 0;

	dataLen = ringBuffer_read(usbBuf, modbusRequest + requestLen, MODBUS_DATA_SIZE);
	if (dataLen)
	{
		requestLen += dataLen;
		idleTime = 0;
	}
	if (idleTime >= MODBUS_COUNTING_OVER)
	{
		responseLen = Modbus_Process(modbusRequest, requestLen, modbusResponse);
		//while (
				CDC_Transmit_FS(modbusResponse, responseLen)
		//== USBD_BUSY)
		;
		for (uint16_t i = 0; i < MODBUS_DATA_SIZE; i++)
		{
			modbusRequest[i] = modbusResponse[i] = 0;
		}
		requestLen = responseLen = 0;
	}
	else
	{
		idleTime++;
	}
}


void ModbusTask(void)
{
	ModbusData();
	Modbus_service();
}

