################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/ModbusRTU/Src/CRC16.c \
../App/ModbusRTU/Src/modbus_RTU.c 

OBJS += \
./App/ModbusRTU/Src/CRC16.o \
./App/ModbusRTU/Src/modbus_RTU.o 

C_DEPS += \
./App/ModbusRTU/Src/CRC16.d \
./App/ModbusRTU/Src/modbus_RTU.d 


# Each subdirectory must supply rules for building sources it contributes
App/ModbusRTU/Src/%.o App/ModbusRTU/Src/%.su App/ModbusRTU/Src/%.cyclo: ../App/ModbusRTU/Src/%.c App/ModbusRTU/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/average filter" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/communication" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/data curve linearization" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/IO_ADC" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/ModbusRTU/Inc" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/ringbuffer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-ModbusRTU-2f-Src

clean-App-2f-ModbusRTU-2f-Src:
	-$(RM) ./App/ModbusRTU/Src/CRC16.cyclo ./App/ModbusRTU/Src/CRC16.d ./App/ModbusRTU/Src/CRC16.o ./App/ModbusRTU/Src/CRC16.su ./App/ModbusRTU/Src/modbus_RTU.cyclo ./App/ModbusRTU/Src/modbus_RTU.d ./App/ModbusRTU/Src/modbus_RTU.o ./App/ModbusRTU/Src/modbus_RTU.su

.PHONY: clean-App-2f-ModbusRTU-2f-Src

