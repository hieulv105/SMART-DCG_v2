################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
../My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
../My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o \
./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o \
./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o 

C_DEPS += \
./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d \
./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d \
./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.o My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.su My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.cyclo: ../My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.c My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/average filter" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/communication" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/data curve linearization" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/IO_ADC" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ModbusRTU/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ringbuffer" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/App" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/Target" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

clean-My_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src:
	-$(RM) ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.cyclo ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.su ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.cyclo ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.su ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.cyclo ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o ./My_Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.su

.PHONY: clean-My_Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

