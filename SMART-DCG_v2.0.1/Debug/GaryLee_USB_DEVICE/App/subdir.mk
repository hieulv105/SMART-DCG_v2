################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GaryLee_USB_DEVICE/App/usb_device.c \
../GaryLee_USB_DEVICE/App/usbd_cdc_if.c \
../GaryLee_USB_DEVICE/App/usbd_desc.c 

OBJS += \
./GaryLee_USB_DEVICE/App/usb_device.o \
./GaryLee_USB_DEVICE/App/usbd_cdc_if.o \
./GaryLee_USB_DEVICE/App/usbd_desc.o 

C_DEPS += \
./GaryLee_USB_DEVICE/App/usb_device.d \
./GaryLee_USB_DEVICE/App/usbd_cdc_if.d \
./GaryLee_USB_DEVICE/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
GaryLee_USB_DEVICE/App/%.o GaryLee_USB_DEVICE/App/%.su GaryLee_USB_DEVICE/App/%.cyclo: ../GaryLee_USB_DEVICE/App/%.c GaryLee_USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/average filter" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/communication" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/data curve linearization" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/IO_ADC" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ModbusRTU/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/App/ringbuffer" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/App" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_USB_DEVICE/Target" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/manhl/OneDrive - ATS JSC/Projects/Smart modem/Smart modem v2022/Firmware/SmartModem2022/Smart_modem_v2022.2/My_Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GaryLee_USB_DEVICE-2f-App

clean-GaryLee_USB_DEVICE-2f-App:
	-$(RM) ./GaryLee_USB_DEVICE/App/usb_device.cyclo ./GaryLee_USB_DEVICE/App/usb_device.d ./GaryLee_USB_DEVICE/App/usb_device.o ./GaryLee_USB_DEVICE/App/usb_device.su ./GaryLee_USB_DEVICE/App/usbd_cdc_if.cyclo ./GaryLee_USB_DEVICE/App/usbd_cdc_if.d ./GaryLee_USB_DEVICE/App/usbd_cdc_if.o ./GaryLee_USB_DEVICE/App/usbd_cdc_if.su ./GaryLee_USB_DEVICE/App/usbd_desc.cyclo ./GaryLee_USB_DEVICE/App/usbd_desc.d ./GaryLee_USB_DEVICE/App/usbd_desc.o ./GaryLee_USB_DEVICE/App/usbd_desc.su

.PHONY: clean-GaryLee_USB_DEVICE-2f-App

