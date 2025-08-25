################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/IO_ADC/IO_ADC.c 

OBJS += \
./App/IO_ADC/IO_ADC.o 

C_DEPS += \
./App/IO_ADC/IO_ADC.d 


# Each subdirectory must supply rules for building sources it contributes
App/IO_ADC/%.o App/IO_ADC/%.su App/IO_ADC/%.cyclo: ../App/IO_ADC/%.c App/IO_ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/Common" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/IO_ADC" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/ModbusRTU" -I"E:/OneDrive - ATS JSC/[02]_PROJECT/SMART-DCG/[04] SOFTWARE/SMART-DCG_v1.0/App/communication" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-IO_ADC

clean-App-2f-IO_ADC:
	-$(RM) ./App/IO_ADC/IO_ADC.cyclo ./App/IO_ADC/IO_ADC.d ./App/IO_ADC/IO_ADC.o ./App/IO_ADC/IO_ADC.su

.PHONY: clean-App-2f-IO_ADC

