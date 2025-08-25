/*
 * Utinity.c
 *
 *  Created on: Sep 12, 2024
 *      Author: Admin
 */
#include "main.h"
#include "iwdg.h"
#include "Communication.h"
#include "Utinity.h"
#include "usart.h"

sys_para_t systemParameter;
IOpin_t IOpin[IO_PIN_NUMBS];

/**
 * @brief Init all IO pin parameters
 * @param none
 * @retval none
 */
void IO_init(void)
{
	for (uint8_t i = 0; i < IO_PIN_NUMBS; i++)
	{
		IOpin[i].mode = IO_INPUT_VOLTAGE;

		if (i == 0)
		{
			IOpin[i].outputPin.port = OUT_WATCHDOG_GPIO_Port;
			IOpin[i].outputPin.pin = OUT_WATCHDOG_Pin;
			continue;
		}
		if (i == 1)
		{
			IOpin[i].outputPin.port = OUT_ALARM_GPIO_Port;
			IOpin[i].outputPin.pin = OUT_ALARM_Pin;
			continue;
		}
	}
}

/**
 * @brief Get IO pin active mode
 * @param pin: number of pin to get active mode
 * @retval Active mode of IO pin in IO_mode_t type
 */
IO_mode_t IO_get_mode(uint8_t pin)
{
	if (pin >= IO_PIN_NUMBS) pin = IO_PIN_NUMBS - 1;

	return IOpin[pin].mode;
}

/**
 * @brief Set output stage
 * @param pin: number of pin to set output stage
 * @param stage: Stage set to pin IO with GPIO_PinState type
 * @retval HAL_OK if IO pin in output mode else return HAL_ERROR
 */
HAL_StatusTypeDef IO_set_output(uint8_t pin, GPIO_PinState state)
{
	if (pin >= IO_PIN_NUMBS) pin = IO_PIN_NUMBS - 1;

	HAL_GPIO_WritePin(IOpin[pin].outputPin.port, IOpin[pin].outputPin.pin, state);

	return HAL_OK;
}

/**
 * @brief Get output state of IO pin
 * @param pin: number of pin to get output state
 * @retval State of output pin in GPIO_Pinstate type
 */
GPIO_PinState IO_get_ouput(uint8_t pin)
{
	if (pin >= IO_PIN_NUMBS) pin = IO_PIN_NUMBS - 1;

	return HAL_GPIO_ReadPin(IOpin[pin].outputPin.port, IOpin[pin].outputPin.pin);
}

void LED_task(void)
{
	static uint8_t ledTick = 0;
	static enum sys_stage_en preStage = sys_stage_normal;

	// get system states
	if (systemParameter.mcu_temperature >= MCU_OVERHEAT)
		systemParameter.sysStage = sys_stage_mcuOverHeat;
	else if (systemParameter.board_temperature >= BOARD_OVERHEAT)
		systemParameter.sysStage = sys_stage_boardOverHeat;
	else if(systemParameter.WDT_parameters.mpuWDTcount >= MPU_WDT_TIMECYCLE
			&& systemParameter.WDT_parameters.mpuWDTcount < MPU_WDT_OVERTIME)
	{
		systemParameter.sysStage = sys_stage_wdtNotDetect;
		systemParameter.mpuIsOnline = 0;
	}

	else if (systemParameter.WDT_parameters.mpuWDTcount >= MPU_WDT_OVERTIME)
		systemParameter.sysStage = sys_stage_mpuReset;
	else
		systemParameter.sysStage = sys_stage_normal;

	if (preStage != systemParameter.sysStage)
	{
		preStage = systemParameter.sysStage;
		ledTick = 0;
		HAL_GPIO_WritePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin, GPIO_PIN_SET);
	}

	switch (systemParameter.sysStage)
	{
		case sys_stage_boardOverHeat:
			if (ledTick >= LED_DELAY_500MS)
			{
				ledTick = 0;
				HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
			}
			break;
		case sys_stage_mcuOverHeat:
			if (ledTick >= LED_DELAY_500MS)
			{
				ledTick = 0;
				HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
			}
			break;
		case sys_stage_wdtNotDetect:
			if (ledTick >= LED_DELAY_1S)
			{
				ledTick = 0;
				HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
			}
			break;
		case sys_stage_mpuReset:
			if (ledTick >= LED_DELAY_200MS)
			{
				ledTick = 0;
				HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
			}
			break;
		default:
			if (ledTick >= LED_DELAY_3S)
			{
				ledTick = 0;
				HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
			}
			break;
	}
	ledTick++;
}


void WDT_task(void)
{
	static uint8_t preStageWDT = 0;

	HAL_IWDG_Refresh(&hiwdg);
//	LL_IWDG_ReloadCounter(IWDG);

	if (systemParameter.WDT_parameters.mpuWDTdelayTime >= MPU_WDT_DELAY_TIME)		// wait for MPU to finish booting
	{
		if (systemParameter.WDT_parameters.mpuWDTenable)							// default 1
		{
			if (systemParameter.WDT_parameters.mpuWDTwaitTime == 0)
			{
				if (systemParameter.WDT_parameters.mpuWDTcount >= MPU_WDT_OVERTIME)
				{
					// Check the condition to disconnect the connections to the MPU
					if (HAL_GPIO_ReadPin(MPU_PWR_DIS_GPIO_Port, MPU_PWR_DIS_Pin) == GPIO_PIN_RESET)
					{
						HAL_UART_DeInit(&huart1);
					}
					else
					{
						MX_USART1_UART_Init();
					}

					HAL_GPIO_TogglePin(MPU_PWR_DIS_GPIO_Port, MPU_PWR_DIS_Pin);

					// get & update waitTime
					if (HAL_GPIO_ReadPin(MPU_PWR_DIS_GPIO_Port, MPU_PWR_DIS_Pin) == GPIO_PIN_SET)	// if power off
					{
						systemParameter.resetCount++;
						systemParameter.WDT_parameters.mpuWDTwaitTime = MPU_RESET_TIME;
					}
					else	// power on
					{
						systemParameter.WDT_parameters.mpuWDTwaitTime = MPU_WAIT_FEEDBACK_TIME;

						uint32_t startTick = HAL_GetTick();
						while ((HAL_GetTick() - startTick) < 2000)
						{

						}

						if(!systemParameter.mpuIsOnline && systemParameter.resetCount >=2)
						{
							RST_CM4_byResetPin();
						}
					}
				}
				else systemParameter.WDT_parameters.mpuWDTcount++;
			}
			else systemParameter.WDT_parameters.mpuWDTwaitTime--;
		}
		else
		{
			if (preStageWDT != systemParameter.WDT_parameters.mpuWDTenable)
			{
				systemParameter.WDT_parameters.mpuWDTcount = 0;
				systemParameter.WDT_parameters.mpuWDTwaitTime = 0;
				systemParameter.WDT_parameters.mpuWDTupdateTime = MPU_WDT_UPDATE_TIME;
				HAL_GPIO_WritePin(MPU_PWR_DIS_GPIO_Port, MPU_PWR_DIS_Pin, GPIO_PIN_RESET);
			}
			else
			{
				if (--systemParameter.WDT_parameters.mpuWDTupdateTime == 0)
				{
					systemParameter.WDT_parameters.mpuWDTenable = 1;
				}
			}
		}
		preStageWDT = systemParameter.WDT_parameters.mpuWDTenable;
	}
	else systemParameter.WDT_parameters.mpuWDTdelayTime++;
}



void RST_CM4_byResetPin(void)
{
    uint32_t startTick;

    HAL_GPIO_WritePin(MPU_RESET_GPIO_Port, MPU_RESET_Pin, GPIO_PIN_RESET);	// Pull RESET pin low

    startTick = HAL_GetTick();	    // get tick
    while ((HAL_GetTick() - startTick) < 500); 		// Wait for 500ms

    HAL_GPIO_WritePin(MPU_RESET_GPIO_Port, MPU_RESET_Pin, GPIO_PIN_SET);	// Pull RESET pin high

    startTick = HAL_GetTick();
    while ((HAL_GetTick() - startTick) < 1000);	    // Wait for CM4 to boot
}

