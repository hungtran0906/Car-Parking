################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32_F103C6_Drivers/USART/subdir.mk
-include Stm32_F103C6_Drivers/TIMER/subdir.mk
-include Stm32_F103C6_Drivers/RCC/subdir.mk
-include Stm32_F103C6_Drivers/GPIO/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include HAL/Servo/subdir.mk
-include HAL/PIR/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KeyPad/subdir.mk
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


BUILD_ARTIFACT_NAME := AutomatedSmartParkingProject
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
AutomatedSmartParkingProject.elf \

MAP_FILES += \
AutomatedSmartParkingProject.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
AutomatedSmartParkingProject.list \

OBJCOPY_HEX += \
AutomatedSmartParkingProject.hex \


# All Target
all: main-build

# Main-build Target
main-build: AutomatedSmartParkingProject.elf secondary-outputs

# Tool invocations
AutomatedSmartParkingProject.elf AutomatedSmartParkingProject.map: $(OBJS) $(USER_OBJS) C:\Intern_HCL\1_LEARN_GIT\Car_parking\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "AutomatedSmartParkingProject.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Intern_HCL\1_LEARN_GIT\Car_parking\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="AutomatedSmartParkingProject.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

AutomatedSmartParkingProject.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "AutomatedSmartParkingProject.list"
	@echo 'Finished building: $@'
	@echo ' '

AutomatedSmartParkingProject.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "AutomatedSmartParkingProject.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) AutomatedSmartParkingProject.elf AutomatedSmartParkingProject.hex AutomatedSmartParkingProject.list AutomatedSmartParkingProject.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
