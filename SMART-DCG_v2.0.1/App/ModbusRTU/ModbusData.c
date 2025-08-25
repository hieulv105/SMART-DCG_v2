#include "ModbusData.h"

#include "Utinity.h"
#include "modbus_RTU.h"


const uint32_t firmwareVer = MCU_FIRMWARE_VER;


void LoadConfigData(void)
{
	systemParameter.sysStage = sys_stage_normal;

	systemParameter.DCIN_voltage = 0;
	systemParameter.board_temperature = -10;
	systemParameter.mcu_temperature = -10;

	systemParameter.WDT_parameters.mpuWDTenable = 1;
	systemParameter.WDT_parameters.mpuWDTcount = 0;
	systemParameter.WDT_parameters.mpuWDTdelayTime = 0;

	systemParameter.resetCount = 0;
	systemParameter.mpuIsOnline = 0;
}


void WriteConfig(void)
{


}

void SaveConfig(void)
{

}


void ModbusData(void)
{
	static uint8_t CoilIndex[MODBUS_COIL_QTY];

	// set coil
	for (uint8_t i = 0; i < MODBUS_COIL_QTY; i++)
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

	// fill data to analog register
	uReg32 tData;

	tData.flo = systemParameter.DCIN_voltage;
	Modbus_Data.AIn[0] = tData.Word.HW;
	Modbus_Data.AIn[1] = tData.Word.LW;

	tData.flo = systemParameter.mcu_temperature;
	Modbus_Data.AIn[2] = tData.Word.HW;
	Modbus_Data.AIn[3] = tData.Word.LW;

	tData.flo = systemParameter.board_temperature;
	Modbus_Data.AIn[4] = tData.Word.HW;
	Modbus_Data.AIn[5] = tData.Word.LW;

	tData.Val32 = firmwareVer;
	Modbus_Data.AIn[6] = tData.Word.HW;
	Modbus_Data.AIn[7] = tData.Word.LW;

	// get coil status
	Modbus_Data.Coil[0] = IO_get_ouput(0);
	Modbus_Data.Coil[1] = IO_get_ouput(1);
	Modbus_Data.Coil[2] = systemParameter.WDT_parameters.mpuWDTenable;
}
