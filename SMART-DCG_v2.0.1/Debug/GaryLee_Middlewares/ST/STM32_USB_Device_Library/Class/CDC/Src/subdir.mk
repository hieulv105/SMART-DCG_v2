################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.c 

OBJS += \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.o 

C_DEPS += \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.d 


# Each subdirectory must supply rules for building sources it contributes
GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.o GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.su GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.cyclo: ../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.c GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/average filter" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/communication" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/data curve linearization" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/IO_ADC" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ModbusRTU/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ringbuffer" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/App" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/Target" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GaryLee_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-CDC-2f-Src

clean-GaryLee_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-CDC-2f-Src:
	-$(RM) ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.cyclo ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.su ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.cyclo ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.d ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.o ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc_if_template.su

.PHONY: clean-GaryLee_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Class-2f-CDC-2f-Src

