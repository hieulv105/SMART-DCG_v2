/*
 * Measurement.c
 *
 *  Created on: Sep 11, 2024
 *      Author: Admin
 */

#include "Measurement.h"
#include "Utinity.h"

#include "average_filter.h"
#include "data_curve_linearization.h"


extern ADC_HandleTypeDef hadc1;


#define ADC_CHANNEL_ACT 3
#define IO_ADC_BUF_OFFSET 2

#define DCIN_R1 100000	// R11 = 100k
#define DCIN_R2 7500	// R12 = 7k5

const float DCIN_VOL_RATIO = (float) ((DCIN_R1 + DCIN_R2) / DCIN_R2);

const float AVG_SLOPE = 4.3E-3; 			// slope (gradient) of temperature line function  [V/°C]
const float V25 = 1.43;         			// sensor's voltage at 25°C [V]
const float ADC_TO_VOLT = (3.30 / 4095); 	// conversion coefficient of digital value to voltage [V]

uint32_t ADC1_value[ADC_CHANNEL_ACT];
AVERAGE_FILTER *ADC_average[ADC_CHANNEL_ACT];

const CURVE_POINT_t NTC_TABLE[] =
{
{ .x = 206.8496012, .y = 125 },
{ .x = 231.0634082, .y = 120 },
{ .x = 258.2155907, .y = 115 },
{ .x = 288.8841900, .y = 110 },
{ .x = 324.2817680, .y = 105 },
{ .x = 364.1326531, .y = 100 },
{ .x = 409.7948164, .y = 95  },
{ .x = 461.4596273, .y = 90  },
{ .x = 520.1418595, .y = 85  },
{ .x = 586.9043948, .y = 80  },
{ .x = 662.1892028, .y = 75  },
{ .x = 747.4973433, .y = 70  },
{ .x = 843.1934408, .y = 65  },
{ .x = 950.8046683, .y = 60  },
{ .x = 1070.404387, .y = 55  },
{ .x = 1203.050847, .y = 50  },
{ .x = 1348.705318, .y = 45  },
{ .x = 1507.158746, .y = 40  },
{ .x = 1677.501919, .y = 35  },
{ .x = 1858.395052, .y = 30  },
{ .x = 2047.500000, .y = 25  },
{ .x = 2241.974976, .y = 20  },
{ .x = 2438.446602, .y = 15  },
{ .x = 2633.022135, .y = 10  },
{ .x = 2821.877040, .y = 5 	 },
{ .x = 3001.396048, .y = 0 	 },
{ .x = 3168.445561, .y = -5  },
{ .x = 3320.736921, .y = -10 },
{ .x = 3456.811551, .y = -15 },
{ .x = 3576.087246, .y = -20 },
{ .x = 3678.761092, .y = -25 },
{ .x = 3765.661091, .y = -30 },
{ .x = 3838.083004, .y = -35 },
{ .x = 3897.545928, .y = -40 },
};

/**
 * @brief
 * @param
 * @retval
 */
void ADC_init(void)
{
	for (uint8_t i = 0; i < ADC_CHANNEL_ACT; i++)
	{
		ADC1_value[i] = 0;
		ADC_average[i] = AVERAGE_FILTER_creat(10);
	}

	while (HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)
		HAL_Delay(100);
	HAL_ADC_Start_DMA(&hadc1, ADC1_value, ADC_CHANNEL_ACT);
}

/**
 * @brief ADC_cap_temp_vol capture all ADC value
 * @param none
 * @retval none
 */
void ADC_cap_temp_vol(void)
{
	for (uint8_t i = 0; i < ADC_CHANNEL_ACT; i++)
		AVERAGE_FILTER_update(ADC_average[i], ADC1_value[i]);
}

/**
 * @brief get_board_temperature get temperature on board
 * @param none
 * @retval float type temperature on board in C unit
 */
float get_board_temperature(void)
{
	return Linearization_data(NTC_TABLE, MEMBER_COUNT(NTC_TABLE), AVERAGE_FILTER_getAverageValue(ADC_average[0]));
}

/**
 * @brief get_DCIN_voltage get supply DC voltage
 * @param none
 * @retval float type supply DC voltage in V unit
 */
float get_DCIN_voltage(void)
{
	return AVERAGE_FILTER_getAverageValue(ADC_average[1]) * ADC_TO_VOLT	* DCIN_VOL_RATIO;
}

/**
 * @brief get_mcu_temperature get temperature inside mcu
 * @param none
 * @retval float type temperature inside mcu in C unit
 */
float get_mcu_temperature(void)
{
	return ((V25 - (AVERAGE_FILTER_getAverageValue(ADC_average[2]) * ADC_TO_VOLT)) / AVG_SLOPE) + 25.0;
}

/**
 * @brief
 * @param none
 * @retval
 */
void ADC_measure(void)
{
	ADC_cap_temp_vol();
	systemParameter.DCIN_voltage = get_DCIN_voltage() + 0.520000;
	systemParameter.mcu_temperature = get_mcu_temperature();
	systemParameter.board_temperature = get_board_temperature();
}


