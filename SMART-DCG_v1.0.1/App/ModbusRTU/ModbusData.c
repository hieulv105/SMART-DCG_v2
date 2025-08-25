#include "ModbusData.h"

#include "Utinity.h"
#include "modbus_RTU.h"



const uint32_t firmwareVer = MCU_FIRMWARE_VER;


void LoadConfigData(void)
{
	systemParameter.sysStage = sys_stage_normal;
	systemParameter.WDT_parameters.mpuWDTenable = 1;

	for (uint8_t i = 0; i < IO_PIN_NUMBS; i++)
	{
		systemParameter.IO_parameters[i].digital = 0;
		systemParameter.IO_parameters[i].voltage = -1;
		systemParameter.IO_parameters[i].current = -1;
		systemParameter.IO_parameters[i].volThresholdUp = IO_VOL_THRESHOLD_UP_DEFAULT;
		systemParameter.IO_parameters[i].volThresholdDown = IO_VOL_THRESHOLD_DOWN_DEFAULT;
		systemParameter.IO_parameters[i].curThresholdUp = IO_CUR_THRESHOLD_UP_DEFAULT;
		systemParameter.IO_parameters[i].curThresholdDown =	IO_CUR_THRESHOLD_DOWN_DEFAULT;
	}
	systemParameter.DCIN_voltage = -1;
	systemParameter.board_temperature = -50;
	systemParameter.mcu_temperature = -50;
	systemParameter.WDT_parameters.mpuWDTcount = 0;
	systemParameter.WDT_parameters.mpuWDTdelayTime = 0;
}


void ModbusData(void)
{
//	static uint16_t preHolding_Regiters[MODBUS_HOLDING_REG_QTY];
	static uint8_t CoilIndex[MODBUS_COIL_QTY];

	if (systemParameter.mcu_temperature >= MCU_OVERHEAT)
		systemParameter.sysStage = sys_stage_mcuOverHeat;
	else if (systemParameter.board_temperature >= BOARD_OVERHEAT)
		systemParameter.sysStage = sys_stage_boardOverHeat;
	else if (systemParameter.WDT_parameters.mpuWDTcount >= MPU_WDT_OVERTIME)
		systemParameter.sysStage = sys_stage_mpuReset;
	else
		systemParameter.sysStage = sys_stage_normal;

//	for (uint16_t i = 0; i < MODBUS_HOLDING_REG_QTY; i++)
//	{
//		if (preHolding_Regiters[i] != Modbus_Data.Holding_Regiters[i])
//		{
//			if (i < 2)
//				IO_set_mode(i % 2, (IO_mode_t) Modbus_Data.Holding_Regiters[i]);
//			else if (i < 6)
//			{
//				if (i < 4)
//					Modbus_HoldReg2Float(&Modbus_Data, 2, &systemParameter.IO_parameters[0].volThresholdUp);
//				else
//					Modbus_HoldReg2Float(&Modbus_Data, 4, &systemParameter.IO_parameters[1].volThresholdUp);
//			}
//			else if (i < 10)
//			{
//				if (i < 8)
//					Modbus_HoldReg2Float(&Modbus_Data, 6, &systemParameter.IO_parameters[0].volThresholdDown);
//				else
//					Modbus_HoldReg2Float(&Modbus_Data, 8, &systemParameter.IO_parameters[1].volThresholdDown);
//			}
//			else if (i < 14)
//			{
//				if (i < 12)
//					Modbus_HoldReg2Float(&Modbus_Data, 10, &systemParameter.IO_parameters[0].curThresholdUp);
//				else
//					Modbus_HoldReg2Float(&Modbus_Data, 12, &systemParameter.IO_parameters[1].curThresholdUp);
//			}
//			else if (i < 18)
//			{
//				if (i < 16)
//					Modbus_HoldReg2Float(&Modbus_Data, 14, &systemParameter.IO_parameters[0].curThresholdDown);
//				else
//					Modbus_HoldReg2Float(&Modbus_Data, 16, &systemParameter.IO_parameters[1].curThresholdDown);
//			}
//			else if (i == 18)
//				serial_set_mode((serial_mode_t) Modbus_Data.Holding_Regiters[18]);
//
//			preHolding_Regiters[i] = Modbus_Data.Holding_Regiters[i];
//		}
//	}

	for (uint16_t i = 0; i < MODBUS_COIL_QTY; i++)
	{
		if (CoilIndex[i] != Modbus_Data.Coil[i])
		{
			if (i < 2)
			{
				IO_set_output(i % 2, (GPIO_PinState) Modbus_Data.Coil[i]);
			}
			else if (i == 2)
			{
				systemParameter.WDT_parameters.mpuWDTenable = Modbus_Data.Coil[2];
			}
			CoilIndex[i] = Modbus_Data.Coil[i];
		}
	}

	Modbus_Float2AnalogIn(&Modbus_Data, 0, systemParameter.DCIN_voltage);
	Modbus_Float2AnalogIn(&Modbus_Data, 2, systemParameter.mcu_temperature);
	Modbus_Float2AnalogIn(&Modbus_Data, 4, systemParameter.board_temperature);
//	Modbus_Float2AnalogIn(&Modbus_Data, 6, systemParameter.IO_parameters[0].voltage);
//	Modbus_Float2AnalogIn(&Modbus_Data, 8, systemParameter.IO_parameters[1].voltage);
//	Modbus_Float2AnalogIn(&Modbus_Data, 10, systemParameter.IO_parameters[0].current);
//	Modbus_Float2AnalogIn(&Modbus_Data, 12, systemParameter.IO_parameters[1].current);
	Modbus_Uint2AnalogIn(&Modbus_Data, 6, firmwareVer);

//	Modbus_Data.Holding_Regiters[0] = (uint16_t) IO_get_mode(0);
//	Modbus_Data.Holding_Regiters[1] = (uint16_t) IO_get_mode(1);

//	Modbus_Float2HoldReg(&Modbus_Data, 2, systemParameter.IO_parameters[0].volThresholdUp);
//	Modbus_Float2HoldReg(&Modbus_Data, 4, systemParameter.IO_parameters[1].volThresholdUp);
//	Modbus_Float2HoldReg(&Modbus_Data, 6, systemParameter.IO_parameters[0].volThresholdDown);
//	Modbus_Float2HoldReg(&Modbus_Data, 8, systemParameter.IO_parameters[1].volThresholdDown);
//	Modbus_Float2HoldReg(&Modbus_Data, 10, systemParameter.IO_parameters[0].curThresholdUp);
//	Modbus_Float2HoldReg(&Modbus_Data, 12, systemParameter.IO_parameters[1].curThresholdUp);
//	Modbus_Float2HoldReg(&Modbus_Data, 14, systemParameter.IO_parameters[0].curThresholdDown);
//	Modbus_Float2HoldReg(&Modbus_Data, 16, systemParameter.IO_parameters[1].curThresholdDown);

//	Modbus_Data.Holding_Regiters[18] = (uint16_t) serial_get_mode();

//	Modbus_Data.DIn[0] = systemParameter.IO_parameters[0].digital;
//	Modbus_Data.DIn[1] = systemParameter.IO_parameters[1].digital;

	Modbus_Data.Coil[0] = IO_get_ouput(0);
	Modbus_Data.Coil[1] = IO_get_ouput(1);
	Modbus_Data.Coil[2] = systemParameter.WDT_parameters.mpuWDTenable;
}
