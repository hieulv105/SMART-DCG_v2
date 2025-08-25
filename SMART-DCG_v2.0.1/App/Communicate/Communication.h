/*
 * Communication.h
 *
 *  Created on: Sep 9, 2022
 *      Author: Manhld
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


void Communication_init(void);
void USB_Reconnect(void);
void USB_disablePullDown(void);
void Modbus_service(void);
void ModbusTask(void);


#endif /* COMMUNICATION_H_ */
