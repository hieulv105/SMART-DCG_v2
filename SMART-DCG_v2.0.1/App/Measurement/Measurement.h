/*
 * Measurement.h
 *
 *  Created on: Sep 11, 2024
 *      Author: Admin
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_


void ADC_init(void);
void ADC_cap_temp_vol(void);

float get_DCIN_voltage(void);
float get_board_temperature(void);
float get_mcu_temperature(void);

void ADC_measure(void);

#endif /* MEASUREMENT_H_ */
