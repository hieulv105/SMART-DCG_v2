/*
 * Utinity.h
 *
 *  Created on: Sep 11, 2024
 *      Author: Admin
 */

#ifndef UTINITY_H_
#define UTINITY_H_

#include "stdint.h"
#include "main.h"

#define MEMBER_COUNT(A) (sizeof(A)/sizeof(A[0]))
#define timeReached(current, last, duration) (((int32_t)current - (int32_t)last) >= (int32_t)duration)

#define USB_DISABLE()	HAL_GPIO_WritePin(USB_DP_F_GPIO_Port, USB_DP_F_Pin, GPIO_PIN_RESET);
#define USB_ENABLE()	HAL_GPIO_WritePin(USB_DP_F_GPIO_Port, USB_DP_F_Pin, GPIO_PIN_SET);

typedef enum sys_stage_en
{
	sys_stage_normal = 0,
	sys_stage_boardOverHeat,
	sys_stage_mcuOverHeat,
	sys_stage_mpuReset,
} sys_stage_t;

typedef struct IO_para_st
{
	float voltage;
	float volThresholdUp;
	float volThresholdDown;
	float current;
	float curThresholdUp;
	float curThresholdDown;
	int8_t digital;
} IO_para_t;

typedef struct WDT_para_st
{
	uint8_t mpuWDTenable;
	uint16_t mpuWDTcount;
	uint16_t mpuWDTwaitTime;
	uint16_t mpuWDTdelayTime;
	uint16_t mpuWDTupdateTime;
} WDT_para_t;

typedef struct
{
	enum sys_stage_en sysStage;
	float DCIN_voltage;
	float mcu_temperature;
	float board_temperature;
	WDT_para_t WDT_parameters;
	IO_para_t IO_parameters[2];

	uint32_t idExFlash;
} sys_para_t;
extern sys_para_t systemParameter;

typedef enum
{
	IO_INPUT_VOLTAGE = 0,
	IO_INPUT_CURRENT,
	IO_OUTPUT_OD,
}IO_mode_t;

typedef struct GPIO_HW_st
{
	uint32_t pin;
	GPIO_TypeDef *port;
}GPIO_HW_t;

typedef struct IOpin_st
{
	IO_mode_t mode;
	GPIO_HW_t outputPin;
	GPIO_HW_t inputModePin;
	uint8_t ADCbuf_index;
}IOpin_t;

#define MCU_FIRMWARE_VER 101		// v1.0.1 (MCU firmware version)

#define ADC_MEASURE_TICK_TIME 10 	// mS
#define ModbusTask_TICK_TIME 20		// mS
#define LED_TASK_TICK_TIME 100 		// mS
#define WDT_TASK_TICK_TIME 1000 	// mS

#define MPU_RESET_TIME 10 			// Time shutdown power to restart MPU (S)
#define MPU_WAIT_FEEDBACK_TIME 100 	// Time wait MPU feedback after restart (S)
#define MPU_WDT_OVERTIME 600 		// Watchdog overtime (S)
#define MPU_WDT_DELAY_TIME 80 		// Watchdog starting delay time (S)
#define MPU_WDT_UPDATE_TIME 300 	// Suspended time for MPU update feature (S)

#define IO_VOL_THRESHOLD_UP_DEFAULT 10 	//V
#define IO_VOL_THRESHOLD_DOWN_DEFAULT 3 //V
#define IO_CUR_THRESHOLD_UP_DEFAULT 30 	//mA
#define IO_CUR_THRESHOLD_DOWN_DEFAULT 5 //mA

#define LED_DELAY_3S (3 * (1000 / LED_TASK_TICK_TIME))
#define LED_DELAY_1S (1 * (1000 / LED_TASK_TICK_TIME))
#define LED_DELAY_500MS (0.5 * (1000 / LED_TASK_TICK_TIME))

#define BOARD_OVERHEAT 50 	//*C
#define MCU_OVERHEAT 60 	//*C

#define	ACK_OK			0
#define	BUZY			1
#define	TIME_OUT		2
#define	RETURN_ERROR	3

#define IO_PIN_NUMBS 2

void IO_init(void);
void LED_task(void);
void WDT_task(void);

void IO_set_mode(uint8_t pin, IO_mode_t mode);
IO_mode_t IO_get_mode(uint8_t pin);
GPIO_PinState IO_get_ouput(uint8_t pin);
HAL_StatusTypeDef IO_set_output(uint8_t pin, GPIO_PinState state);


#endif /* UTINITY_H_ */
