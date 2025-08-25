/* 
 * File:   modbus_RTU.h
 * Author: linhLV
 *
 * Created on October 9, 2017, 2:56 PM
 */

#ifndef MODBUS_RTU_H
#define	MODBUS_RTU_H

#include "CRC16.h"


#define DEFAULT_DEVICE_ID					1	// Default device's ID

#define MODBUS_COIL_QTY     				3
#define MODBUS_DISCRETE_INPUT_POINT_QTY 	2
#define MODBUS_ANALOG_INPUT_REG_QTY     	8
#define MODBUS_HOLDING_REG_QTY          	2


typedef union tuReg32
{
	uint32_t Val32;
	struct
	{
		uint16_t LW;
		uint16_t HW;
	} Word;
	uint8_t Val[4]; //val[0]-lsb, val[3]-msb
	float flo;
} uReg32;

typedef union tuReg16
{
	uint16_t Val16;
	uint8_t Val[2]; //val[0]-lsb, val[3]-msb
} uReg16;

typedef struct
{
//    uint8_t   updateFlag;
	uint8_t Coil[MODBUS_COIL_QTY];
	uint8_t DIn[MODBUS_DISCRETE_INPUT_POINT_QTY];
	uint16_t AIn[MODBUS_ANALOG_INPUT_REG_QTY];
	uint16_t Holding_Regiters[MODBUS_HOLDING_REG_QTY];
} MODBUS_DATA_STRUCT;

typedef enum
{
	NO_ERR,
	ILLEGAL_FUNCTION = 1,
	ILLEGAL_DATA_ADDR,
	ILLEGAL_DATA_VALUE,
	SLAVE_DEVICE_FAILURE,
	ACK,
	SLAVE_DEVICE_BUSY,
	NEGATIVE_ACK,
	MEMORY_PARITY_ERR,
	GATEWAY_PATH_UNAVAILABLE,
	GATEWAY_TARGET_DEVICE_FAILURE
} MODBUS_EXCEPTION_CODE;

typedef enum
{
	NO_FUNC,
	READ_COIL = 1,
	READ_DISCRETE_INPUT,
	READ_HOLDING_REG,
	READ_INPUT_REG,
	WRITE_SINGLE_COIL,
	WRITE_HOLDING_REG,
	WRITE_MULTI_COILS = 15,
	WRITE_MULTI_HOLDING_REGS
} MODBUS_FUNCTION_CODE;

extern MODBUS_DATA_STRUCT Modbus_Data;

uint16_t Modbus_Process(uint8_t *Data, uint16_t dataLen, uint8_t *Reponse);


#endif	/* MODBUS_RTU_H */
