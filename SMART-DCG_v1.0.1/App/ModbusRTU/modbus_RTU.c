#include "modbus_RTU.h"

MODBUS_DATA_STRUCT Modbus_Data;

//#define DBUG_ON

#define Endian_Swap_16(x) ((x>>8)|(x<<8))

uint16_t Modbus_Exeption_Response(uint8_t *Request, uint8_t *Response, MODBUS_EXCEPTION_CODE err_Code);
uint16_t Modbus_FC1_ReadCoilStatus(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC2_ReadDisceteInput(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC3_ReadHoldingReg(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC4_ReadInputReg(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC5_ForceSingleCoil(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC6_WriteSingleReg(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC15_ForceMultiCoil(uint8_t *Msg, uint8_t *Response);
uint16_t Modbus_FC16_WriteMultiReg(uint8_t *Msg, uint8_t *Response);

/**
 * ID | Func Code | Address |  Data...
 * 1      1          2          ... 
 **/
typedef struct
{
	uint8_t Id;
	uint8_t Func_Code;
	uint16_t Add;
	uint8_t *Data;
} MODBUS_MESSAGE;            //Modbus message struct

/**Modbus exception message
 */
typedef struct _MODBUS_EXCEPTION_MESSAGE
{
	uint8_t Id;
	uint8_t funcCode;
	uint8_t ExceptionCode;
} MODBUS_EXCEPTION_MESSAGE;

/**Modbus process function
 <p><b>Function prototype: </b>uint16_t uint16_t Modbus_Process(uint8_t * Data, uint16_t dataLen, uint8_t * Response)</p>
 <p><b>Description: </b>Check if *data is modbus request call corresponding function </p>
 <p><b>Parameters: </b></p>
 <p>*Data: Request message pointer</p>
 *  <p>dataLen: Request message data len (Byte)</p>
 *  <p>*Response: Response message pointer</p>
 <p><b>Returns: </b>u Response message Byte count  (5)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_Process(uint8_t *Data, uint16_t dataLen, uint8_t *Response)
{
	MODBUS_MESSAGE *ModbusMesg;
	uReg16 crcCalc, crc;
	uint16_t byteCount;

	ModbusMesg = (MODBUS_MESSAGE*) Data;		//point to Data

	if (ModbusMesg->Id != DEFAULT_DEVICE_ID)    //Check device ID fist
		return 0;		// if wrong ID, don't care this Message -> return
	if (dataLen < 8)
#ifdef DBUG_ON
        return sprintf(Response,"Message length too short [%d]",dataLen);
#endif
		return 0;		// Too short to be Modbus message, do nothing

	crcCalc.Val16 = CRCCalc(Data, dataLen - 2);

	crc.Val[0] = Data[dataLen - 1];
	crc.Val[1] = Data[dataLen - 2];

	if (crc.Val16 != crcCalc.Val16)
#ifdef DBUG_ON
        return sprintf(Response,"CRC error. Received [%H] <> Calculated [%H]",crc.Val16,crcCalc.Val16);
#endif
		return 0;			// CRC error, but return nothing

	switch (ModbusMesg->Func_Code)
	{
		case READ_COIL:					// Function 1
			byteCount = Modbus_FC1_ReadCoilStatus(Data, Response);
			break;

		case READ_DISCRETE_INPUT:		// Function 2
			byteCount = Modbus_FC2_ReadDisceteInput(Data, Response);
			break;

		case WRITE_SINGLE_COIL:			// Function 5
			byteCount = Modbus_FC5_ForceSingleCoil(Data, Response);
			break;

		case WRITE_MULTI_COILS:			// Function 15
			byteCount = Modbus_FC15_ForceMultiCoil(Data, Response);
			break;

		case READ_INPUT_REG:			// Function 4
			byteCount = Modbus_FC4_ReadInputReg(Data, Response);
			break;

		case READ_HOLDING_REG:			// Function 3
			byteCount = Modbus_FC3_ReadHoldingReg(Data, Response);
			break;

		case WRITE_HOLDING_REG:			// Function 6
			byteCount = Modbus_FC6_WriteSingleReg(Data, Response);
			break;

		case WRITE_MULTI_HOLDING_REGS:	// Function 16
			byteCount = Modbus_FC16_WriteMultiReg(Data, Response);
			break;

		default:
			byteCount = Modbus_Exeption_Response(Data, Response, ILLEGAL_FUNCTION);
			break;
	}

	if (byteCount)		// If response not empty, calculate and add CRC
	{
		crcCalc.Val16 = CRCCalc(Response, byteCount);
		Response[byteCount++] = crcCalc.Val[1];
		Response[byteCount++] = crcCalc.Val[0];		// Byte count +2
	}

	return byteCount;
}

void Modbus_Uint2AnalogIn(MODBUS_DATA_STRUCT *mbData, uint16_t index, uint32_t uData)
{
	uReg32 temp;

	temp.Val32 = uData;
	mbData->AIn[index] = temp.Word.HW;
	mbData->AIn[index + 1] = temp.Word.LW;
}

void Modbus_Float2AnalogIn(MODBUS_DATA_STRUCT *mbData, uint16_t index, float fData)
{
	uReg32 temp;

	temp.flo = fData;
	mbData->AIn[index] = temp.Word.HW;
	mbData->AIn[index + 1] = temp.Word.LW;
}

void Modbus_Float2HoldReg(MODBUS_DATA_STRUCT *mbData, uint16_t index, float fData)
{
	uReg32 temp;

	temp.flo = fData;
	mbData->Holding_Regiters[index] = temp.Word.HW;
	mbData->Holding_Regiters[index + 1] = temp.Word.LW;
}

void Modbus_HoldReg2Float(MODBUS_DATA_STRUCT *mbData, uint16_t index, float *fData)
{
	uReg32 temp;

	temp.Word.HW = mbData->Holding_Regiters[index];
	temp.Word.LW = mbData->Holding_Regiters[index + 1];
	*fData = temp.flo;
}

//<editor-fold defaultstate="collapsed" desc=" EXCEPTION RESPONSE">

/**Modbus Error message return
 <p><b>Function prototype: </b>u32uint16_t ErrMsg(MODBUS_MESSGAE *ModbusMsg, MODBUS_EXCEPTION_CODE err)</p>
 <p><b>Description: </b>Built error message in *ModbusMsg and return byte count</p>
 <p><b>Parameters: </b></p>
 <p>  Msg        : Pointer to modbus message</p>
 <p>  Response   : pointer to respont message</p>
 <p>  err_Code   : Modbus Error code
 <p><b>Returns: </b>u32 Byte count (5)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_Exeption_Response(uint8_t *Request, uint8_t *Response, MODBUS_EXCEPTION_CODE err_Code)
{
	MODBUS_EXCEPTION_MESSAGE *ExeptionResponse = (MODBUS_EXCEPTION_MESSAGE*) Response;
	MODBUS_MESSAGE *ModbusMesg = (MODBUS_MESSAGE*) Request;

	ExeptionResponse->funcCode = ModbusMesg->Func_Code | 0x80;
	ExeptionResponse->ExceptionCode = err_Code;
	return 3;
}
//</editor-fold >

//<editor-fold defaultstate="collapsed" desc=" FUNTION 1: READ COIL STATUS">

/******FUNCTION 1: Read Coil Status 
 <p><b>Function prototype: </b>uint16_t Function1(uint8_t *Msg, uint8_t *Response )</p>
 <p><b>Description: </b>Process modbus function 1</p>
 <p><b>Parameters: </b></p>
 <p>  Msg: Pointer to modbus message</p>
 <p>  Response: pointer to respont message</p>
 <p><b>Returns: </b>uint16_t Byte count (5)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_FC1_ReadCoilStatus(uint8_t *Msg, uint8_t *Response)
{
	typedef struct _MODBUS_F2_REQUEST
	{
		uint8_t Id;
		uint8_t Func_Code;
		uint16_t fist_Coil_Addr;
		uint16_t number_Coil_Request;
		uint16_t crc;
	} MODBUS_F1_REQUEST;

	typedef struct _MODBUS_F1_RESPONSE
	{
		uint8_t Id;
		uint8_t Func_Code;
		uint8_t byteQty;
		uint8_t DataFllow[];
	} MODBUS_F1_RESPONSE;

	uint16_t addr, endAddr, i;
	uint16_t byteIndex, bitIndex, tem;
	MODBUS_F1_REQUEST *F1_Request;
	MODBUS_F1_RESPONSE *F1_Response;

	F1_Request = (MODBUS_F1_REQUEST*) Msg;
	addr = Endian_Swap_16(F1_Request->fist_Coil_Addr);
	tem = Endian_Swap_16(F1_Request->number_Coil_Request);

	if (tem == 0)
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //return error if num. of coil requested is zero

	endAddr = addr + tem - 1;

	if ( //addr < MODBUS_COIL_OFFSET   ||
	endAddr >= MODBUS_COIL_QTY
	// +MODBUS_COIL_OFFSET
	)
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR);
	}

	F1_Response = (MODBUS_F1_RESPONSE*) Response;
	F1_Response->Id = F1_Request->Id;
	F1_Response->Func_Code = F1_Request->Func_Code;
	F1_Response->DataFllow[0] = 0;
	byteIndex = 0;
	bitIndex = 0;
	for (i = addr; i <= endAddr; ++i)
	{
		if (bitIndex >= 8)             //prepare for new byte
		{
			bitIndex = 0;
			byteIndex++;
			F1_Response->DataFllow[byteIndex] = 0;
		}
//		tem = Modbus_GetCoil(i) << bitIndex;
		tem = Modbus_Data.Coil[i] << bitIndex;
		F1_Response->DataFllow[byteIndex] |= tem;
		++bitIndex;
	}

	F1_Response->byteQty = byteIndex + 1;

	return F1_Response->byteQty + 3;
}

uint16_t Modbus_FC2_ReadDisceteInput(uint8_t *Msg, uint8_t *Response)
{
	typedef struct _MODBUS_F2_REQUEST
	{
		uint8_t Id;
		uint8_t Func_Code;
		uint16_t first_Input_Addr;
		uint16_t number_Input_Request;
		uint16_t crc;
	} MODBUS_F2_REQUEST;

	typedef struct _MODBUS_F2_RESPONSE
	{
		uint8_t Id;
		uint8_t Func_Code;
		uint8_t byteQty;
		uint8_t DataFllow[];
	} MODBUS_F2_RESPONSE;

	uint16_t addr, endAddr, i;
	uint16_t byteIndex, bitIndex, numbRequest;
	MODBUS_F2_REQUEST *F2_Request;
	MODBUS_F2_RESPONSE *F2_Response;

	F2_Request = (MODBUS_F2_REQUEST*) Msg;
	addr = Endian_Swap_16(F2_Request->first_Input_Addr);
	numbRequest = Endian_Swap_16(F2_Request->number_Input_Request);

	if (numbRequest == 0)
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //return error if num. of coil requested is zero

	endAddr = addr + numbRequest - 1;

	if ( //addr < MODBUS_COIL_OFFSET   ||
	endAddr >= MODBUS_COIL_QTY
	// +MODBUS_COIL_OFFSET
	)
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR);
	}

	F2_Response = (MODBUS_F2_RESPONSE*) Response;
	F2_Response->Id = F2_Request->Id;
	F2_Response->Func_Code = F2_Request->Func_Code;
	F2_Response->DataFllow[0] = 0;
	byteIndex = 0;
	bitIndex = 0;
	for (i = addr; i <= endAddr; ++i)
	{
		if (bitIndex >= 8)             //prepare for new byte
		{
			bitIndex = 0;
			byteIndex++;
			F2_Response->DataFllow[byteIndex] = 0;
		}

//		F2_Response->DataFllow[byteIndex] |= Modbus_GetDIn(i) << bitIndex;
		F2_Response->DataFllow[byteIndex] |= Modbus_Data.DIn[i] << bitIndex;
		++bitIndex;
	}

	F2_Response->byteQty = byteIndex + 1;

	return F2_Response->byteQty + 3;
}

//</editor-fold> 

// <editor-fold defaultstate="collapsed" desc="FUNCTION 3: READ HOLDING REGISTER">

/******FUNCTION 3: READ HOLDING REGITERS
 <p><b>Function prototype: </b>uint16_t Function3(uint8_t *Msg, uint8_t *Response )/p>
 <p><b>Description: </b>Process modbus function 5</p>
 <p><b>Parameters: </b></p>
 <p>  Msg: Pointer to modbus message</p>
 <p>  Response: pointer to respont message</p>
 <p><b>Returns: </b>uint16_t Byte count (exclude CRC)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_FC3_ReadHoldingReg(uint8_t *Msg, uint8_t *Response)
{

	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t reg_Addr;
		uint16_t reg_Qty;
	} MODBUS_F3_REQUEST;

	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint8_t byte_Follow_Qty;
		uint8_t Regiter_Data[];
	} MODBUS_F3_RESPONSE;

	MODBUS_F3_REQUEST *F3_Request = (MODBUS_F3_REQUEST*) Msg;
	MODBUS_F3_RESPONSE *F3_Response = (MODBUS_F3_RESPONSE*) Response;
	uint16_t i, regAddr, regQty, byteCount = 0;
	uReg16 tem;

	regAddr = Endian_Swap_16(F3_Request->reg_Addr);
	regQty = Endian_Swap_16(F3_Request->reg_Qty);
	if (regAddr + regQty > MODBUS_HOLDING_REG_QTY || // Check address range
			regQty > 127) // byte follow < 256
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //Return error if out of address;
	}

	//prepare Response message
	F3_Response->Id = DEFAULT_DEVICE_ID;
	F3_Response->function_Code = 3;
	F3_Response->byte_Follow_Qty = (uint8_t) (regQty * 2);

	for (i = regAddr; i < regAddr + regQty; ++i)
	{
		tem.Val16 = Modbus_Data.Holding_Regiters[i];
		F3_Response->Regiter_Data[byteCount++] = tem.Val[1];
		F3_Response->Regiter_Data[byteCount++] = tem.Val[0];
	}

	return (3 + byteCount);

	return 0;
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="FUNCTION 4: READ INPUT REGITER">

/******FUNCTION 4: READ INPUT REGISTER
 <p><b>Function prototype: </b>uint16_t Function4(uint8_t *Msg, uint8_t *Response )</p>
 <p><b>Description: </b>Process modbus function 4</p>
 <p><b>Parameters: </b></p>
 <p>  Msg: Pointer to modbus message</p>
 <p>  Response: pointer to respont message</p>
 <p><b>Returns: </b>uint16_t Byte count (5)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_FC4_ReadInputReg(uint8_t *Msg, uint8_t *Response)
{
	typedef struct _MODBUS_F4_REQUEST
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t reg_Addr;
		uint16_t reg_Qty;
		uint16_t crc;
	} MODBUS_F4_REQUEST;

	typedef struct _MODBUS_F4_RESPONSE
	{
		uint8_t Id;
		uint8_t function_Code;
		uint8_t byte_Follow_Qty;
		uint8_t Regiter_Data[];
	} MODBUS_F4_RESPONSE;

	MODBUS_F4_REQUEST *F4_Request = (MODBUS_F4_REQUEST*) Msg;
	MODBUS_F4_RESPONSE *F4_Response = (MODBUS_F4_RESPONSE*) Response;
	uint16_t i, regAddr, regQty, byteCount = 0;
	uReg16 tem;

	regAddr = Endian_Swap_16(F4_Request->reg_Addr);
	regQty = Endian_Swap_16(F4_Request->reg_Qty);
	if (regAddr + regQty > MODBUS_ANALOG_INPUT_REG_QTY || // Check address range
			regQty > 127) // byte follow < 256
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //Return error if out of address;
	}

	//prepare Response message
	F4_Response->Id = DEFAULT_DEVICE_ID;
	F4_Response->function_Code = 4;
	F4_Response->byte_Follow_Qty = (uint8_t) (regQty * 2);

	for (i = regAddr; i < regAddr + regQty; ++i)
	{
//		tem.Val16 = Modbus_GetAIn(i);
		tem.Val16 = Modbus_Data.AIn[i];
		F4_Response->Regiter_Data[byteCount++] = tem.Val[1];
		F4_Response->Regiter_Data[byteCount++] = tem.Val[0];
	}

	return (3 + byteCount);
} // </editor-fold>

//<editor-fold defaultstate="collapsed" desc="FUNCTION 5: WRITE SINGLE COIL OUTPUT">

/******FUNCTION 5: FORCE SIGNLE COIL 
 <p><b>Function prototype: </b>uint16_t Function1(uint8_t *Msg, uint8_t *Response )</p>
 <p><b>Description: </b>Process modbus function 5</p>
 <p><b>Parameters: </b></p>
 <p>  Msg: Pointer to modbus message</p>
 <p>  Response: pointer to respont message</p>
 <p><b>Returns: </b>uint16_t Byte count (5)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_FC5_ForceSingleCoil(uint8_t *Msg, uint8_t *Response)
{
	typedef struct
	{
		uint8_t Id;
		uint8_t Func_Code;
		uint16_t Coil_addr;
		uint16_t Vallue;
		uint16_t crc;
	} MODBUS_F5_REQUEST;

	typedef struct
	{
		uint8_t Id;
		uint8_t Func_Code;
		uint16_t Coil_addr;
		uint16_t Status_Writen;
	} MODBUS_F5_RESPONSE;

	uint16_t coilAddr;

	MODBUS_F5_REQUEST *F5_Request = (MODBUS_F5_REQUEST*) Msg;
	MODBUS_F5_RESPONSE *F5_Response = (MODBUS_F5_RESPONSE*) Response;

	coilAddr = Endian_Swap_16(F5_Request->Coil_addr);

	// Check address range,
	if (coilAddr >= MODBUS_COIL_QTY)
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); // return Error

	switch (F5_Request->Vallue)
	{
		case 0:
			Modbus_Data.Coil[coilAddr] = 0;
			break;
		case 0x00FF:
			Modbus_Data.Coil[coilAddr] = 1;
			break;
		default:
			return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_VALUE);
	}
	// Everything OK, just echo Request
	F5_Response->Id = F5_Request->Id;
	F5_Response->Func_Code = F5_Request->Func_Code;
	F5_Response->Coil_addr = F5_Request->Coil_addr;
	F5_Response->Status_Writen = F5_Request->Vallue;

	return sizeof(MODBUS_F5_RESPONSE);
}
//</editor-fold>

// <editor-fold defaultstate="collapsed" desc="FUNCTION 6: WRITE HOLDING REGISTER">

/******FUNCTION 6: WRITE SIGNLE REGITER 
 <p><b>Function prototype: </b>uint16_t Function6(uint8_t *Msg, uint8_t *Response )</p>
 <p><b>Description: </b>Process modbus function 6</p>
 <p><b>Parameters: </b></p>
 <p>  Msg: Pointer to modbus message</p>
 <p>  Response: pointer to response message</p>
 <p><b>Returns: </b>uint16_t Byte count (5)</p>
 <p><b>By: </b>LinhLV</p>
 */
uint16_t Modbus_FC6_WriteSingleReg(uint8_t *Msg, uint8_t *Response)
{
	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t reg_Addr;
		uint16_t value_To_Write;
	} MODBUS_F6_REQUEST;

	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t reg_Addr;
		uint16_t value_Writen;
	} MODBUS_F6_RESPONSE;

	MODBUS_F6_REQUEST *F6_Request = (MODBUS_F6_REQUEST*) Msg;
	MODBUS_F6_RESPONSE *F6_Response = (MODBUS_F6_RESPONSE*) Response;
	uint16_t regAddr;

	regAddr = Endian_Swap_16(F6_Request->reg_Addr);

	if (regAddr >= MODBUS_HOLDING_REG_QTY)
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //Return error if out of address;
	}

	//Write value to holding reg.
	Modbus_Data.Holding_Regiters[regAddr] = Endian_Swap_16(F6_Request->value_To_Write);

	//private for ats-charger
	//prevent hi-threshold lower than low one
	//If un-suitable data was written, keep high threshold bigger than low threshold 1
//	if (Modbus_Data.Holding_Regiters[1] <= Modbus_Data.Holding_Regiters[2]) // check threshold
//	{
//		if (regAddr == 1)
//			Modbus_Data.Holding_Regiters[2] = Modbus_Data.Holding_Regiters[1] - 1;
//		else
//			Modbus_Data.Holding_Regiters[1] = Modbus_Data.Holding_Regiters[2] + 1;
//	}

	//prepare Response message
	F6_Response->Id = F6_Request->Id;
	F6_Response->function_Code = F6_Request->function_Code;
	F6_Response->reg_Addr = F6_Request->reg_Addr;
	F6_Response->value_Writen = F6_Request->value_To_Write;

	return sizeof(MODBUS_F6_RESPONSE);
}    // </editor-fold>

uint16_t Modbus_FC15_ForceMultiCoil(uint8_t *Msg, uint8_t *Response)
{
	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t firstCoil_Addr;
		uint16_t numb_Coils;
		uint8_t numb_bData;
		uint8_t data[];
	} MODBUS_F15_REQUEST;

	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t firstCoil_Addr;
		uint16_t numb_Coils;
	} MODBUS_F15_RESPONSE;

	MODBUS_F15_REQUEST *F15_Request = (MODBUS_F15_REQUEST*) Msg;
	MODBUS_F15_RESPONSE *F15_Response = (MODBUS_F15_RESPONSE*) Response;
	uint16_t coilAddr = Endian_Swap_16(F15_Request->firstCoil_Addr);
	uint16_t numbCoils = Endian_Swap_16(F15_Request->numb_Coils);

	if (coilAddr >= MODBUS_COIL_QTY)
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //Return error if out of address;
	}

	for (uint16_t i = 0; i < numbCoils; i++)
	{
		Modbus_Data.Coil[coilAddr + i] =
				(F15_Request->data[i / 8] & 0x01 << (i % 8)) ? 1 : 0;
	}

	F15_Response->Id = F15_Request->Id;
	F15_Response->function_Code = F15_Request->function_Code;
	F15_Response->firstCoil_Addr = F15_Request->firstCoil_Addr;
	F15_Response->numb_Coils = F15_Request->numb_Coils;

	return sizeof(MODBUS_F15_RESPONSE);
}

uint16_t Modbus_FC16_WriteMultiReg(uint8_t *Msg, uint8_t *Response)
{
	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t firstReg_Addr;
		uint16_t numb_Regs;
		uint8_t numb_dData;
		uint8_t data[];
	} MODBUS_F16_REQUEST;

	typedef struct
	{
		uint8_t Id;
		uint8_t function_Code;
		uint16_t firstReg_Addr;
		uint16_t numb_Regs;
	} MODBUS_F16_RESPONSE;

	MODBUS_F16_REQUEST *F16_Request = (MODBUS_F16_REQUEST*) Msg;
	MODBUS_F16_RESPONSE *F16_Response = (MODBUS_F16_RESPONSE*) Response;
	uint16_t regAddr = Endian_Swap_16(F16_Request->firstReg_Addr);
	uint16_t numbRegs = Endian_Swap_16(F16_Request->numb_Regs);

	if (regAddr >= MODBUS_HOLDING_REG_QTY)
	{
		return Modbus_Exeption_Response(Msg, Response, ILLEGAL_DATA_ADDR); //Return error if out of address;
	}

	for (uint16_t i = 0; i < numbRegs; i++)
	{
		Modbus_Data.Holding_Regiters[regAddr + i] = (F16_Request->data[i * 2] << 8) | F16_Request->data[(i * 2) + 1];
	}

	F16_Response->Id = F16_Request->Id;
	F16_Response->function_Code = F16_Request->function_Code;
	F16_Response->firstReg_Addr = F16_Request->firstReg_Addr;
	F16_Response->numb_Regs = F16_Request->numb_Regs;

	return sizeof(MODBUS_F16_RESPONSE);
}

