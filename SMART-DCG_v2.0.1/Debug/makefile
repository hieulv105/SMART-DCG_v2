################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include App/ModbusRTU/subdir.mk
-include App/Memory/subdir.mk
-include App/Measurement/subdir.mk
-include App/Communicate/subdir.mk
-include App/Common/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SMART-DCG_v2.0.1
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SMART-DCG_v2.0.1.elf \

MAP_FILES += \
SMART-DCG_v2.0.1.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SMART-DCG_v2.0.1.list \

OBJCOPY_HEX += \
SMART-DCG_v2.0.1.hex \

OBJCOPY_BIN += \
SMART-DCG_v2.0.1.bin \


# All Target
all: main-build

# Main-build Target
main-build: SMART-DCG_v2.0.1.elf secondary-outputs

# Tool invocations
SMART-DCG_v2.0.1.elf SMART-DCG_v2.0.1.map: $(OBJS) $(USER_OBJS) Z:\OneDrive\ -\ ATS\ JSC\01_PROJECT\SMART\ DCG\ v2\04_SOFTWARE\01_MCU\SMART-DCG_v2.0.1\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SMART-DCG_v2.0.1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"Z:\OneDrive - ATS JSC\01_PROJECT\SMART DCG v2\04_SOFTWARE\01_MCU\SMART-DCG_v2.0.1\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SMART-DCG_v2.0.1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SMART-DCG_v2.0.1.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SMART-DCG_v2.0.1.list"
	@echo 'Finished building: $@'
	@echo ' '

SMART-DCG_v2.0.1.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "SMART-DCG_v2.0.1.hex"
	@echo 'Finished building: $@'
	@echo ' '

SMART-DCG_v2.0.1.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SMART-DCG_v2.0.1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SMART-DCG_v2.0.1.bin SMART-DCG_v2.0.1.elf SMART-DCG_v2.0.1.hex SMART-DCG_v2.0.1.list SMART-DCG_v2.0.1.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
