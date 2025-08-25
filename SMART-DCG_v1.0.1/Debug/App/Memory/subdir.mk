################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Memory/W25Q_Memory.c 

OBJS += \
./App/Memory/W25Q_Memory.o 

C_DEPS += \
./App/Memory/W25Q_Memory.d 


# Each subdirectory must supply rules for building sources it contributes
App/Memory/%.o App/Memory/%.su App/Memory/%.cyclo: ../App/Memory/%.c App/Memory/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"Z:/OneDrive - ATS JSC/01_PROJECT/SMART DCG v2/04_SOFTWARE/01_MCU/SMART-DCG_v1.0.1/App/Common" -I"Z:/OneDrive - ATS JSC/01_PROJECT/SMART DCG v2/04_SOFTWARE/01_MCU/SMART-DCG_v1.0.1/App/ModbusRTU" -I"Z:/OneDrive - ATS JSC/01_PROJECT/SMART DCG v2/04_SOFTWARE/01_MCU/SMART-DCG_v1.0.1/App/Measurement" -I"Z:/OneDrive - ATS JSC/01_PROJECT/SMART DCG v2/04_SOFTWARE/01_MCU/SMART-DCG_v1.0.1/App/Communicate" -I"Z:/OneDrive - ATS JSC/01_PROJECT/SMART DCG v2/04_SOFTWARE/01_MCU/SMART-DCG_v1.0.1/App/Memory" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Memory

clean-App-2f-Memory:
	-$(RM) ./App/Memory/W25Q_Memory.cyclo ./App/Memory/W25Q_Memory.d ./App/Memory/W25Q_Memory.o ./App/Memory/W25Q_Memory.su

.PHONY: clean-App-2f-Memory

