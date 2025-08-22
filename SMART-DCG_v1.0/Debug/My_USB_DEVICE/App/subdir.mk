################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My_USB_DEVICE/App/usb_device.c \
../My_USB_DEVICE/App/usbd_cdc_if.c \
../My_USB_DEVICE/App/usbd_desc.c 

OBJS += \
./My_USB_DEVICE/App/usb_device.o \
./My_USB_DEVICE/App/usbd_cdc_if.o \
./My_USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./My_USB_DEVICE/App/usb_device.d \
./My_USB_DEVICE/App/usbd_cdc_if.d \
./My_USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
My_USB_DEVICE/App/%.o My_USB_DEVICE/App/%.su My_USB_DEVICE/App/%.cyclo: ../My_USB_DEVICE/App/%.c My_USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/average filter" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/communication" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/data curve linearization" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/IO_ADC" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ModbusRTU/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ringbuffer" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/App" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/Target" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My_USB_DEVICE-2f-App

clean-My_USB_DEVICE-2f-App:
	-$(RM) ./My_USB_DEVICE/App/usb_device.cyclo ./My_USB_DEVICE/App/usb_device.d ./My_USB_DEVICE/App/usb_device.o ./My_USB_DEVICE/App/usb_device.su ./My_USB_DEVICE/App/usbd_cdc_if.cyclo ./My_USB_DEVICE/App/usbd_cdc_if.d ./My_USB_DEVICE/App/usbd_cdc_if.o ./My_USB_DEVICE/App/usbd_cdc_if.su ./My_USB_DEVICE/App/usbd_desc.cyclo ./My_USB_DEVICE/App/usbd_desc.d ./My_USB_DEVICE/App/usbd_desc.o ./My_USB_DEVICE/App/usbd_desc.su

.PHONY: clean-My_USB_DEVICE-2f-App

