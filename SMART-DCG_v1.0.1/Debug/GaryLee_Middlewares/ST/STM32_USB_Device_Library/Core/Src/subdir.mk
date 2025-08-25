################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.c \
../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.o \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o 

C_DEPS += \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.d \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d \
./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.o GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.su GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.cyclo: ../GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.c GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/average filter" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/communication" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/data curve linearization" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/IO_ADC" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ModbusRTU/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ringbuffer" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/App" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/Target" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GaryLee_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

clean-GaryLee_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src:
	-$(RM) ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.cyclo ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.d ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.o ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_conf_template.su ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.cyclo ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.su ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.cyclo ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.su ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.cyclo ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o ./GaryLee_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.su

.PHONY: clean-GaryLee_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

