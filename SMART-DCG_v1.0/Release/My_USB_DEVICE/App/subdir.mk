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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My_USB_DEVICE-2f-App

clean-My_USB_DEVICE-2f-App:
	-$(RM) ./My_USB_DEVICE/App/usb_device.cyclo ./My_USB_DEVICE/App/usb_device.d ./My_USB_DEVICE/App/usb_device.o ./My_USB_DEVICE/App/usb_device.su ./My_USB_DEVICE/App/usbd_cdc_if.cyclo ./My_USB_DEVICE/App/usbd_cdc_if.d ./My_USB_DEVICE/App/usbd_cdc_if.o ./My_USB_DEVICE/App/usbd_cdc_if.su ./My_USB_DEVICE/App/usbd_desc.cyclo ./My_USB_DEVICE/App/usbd_desc.d ./My_USB_DEVICE/App/usbd_desc.o ./My_USB_DEVICE/App/usbd_desc.su

.PHONY: clean-My_USB_DEVICE-2f-App

