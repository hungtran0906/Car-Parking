################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad/KPD_program.c 

OBJS += \
./HAL/KeyPad/KPD_program.o 

C_DEPS += \
./HAL/KeyPad/KPD_program.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KeyPad/%.o HAL/KeyPad/%.su HAL/KeyPad/%.cyclo: ../HAL/KeyPad/%.c HAL/KeyPad/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/HAL/includes" -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-KeyPad

clean-HAL-2f-KeyPad:
	-$(RM) ./HAL/KeyPad/KPD_program.cyclo ./HAL/KeyPad/KPD_program.d ./HAL/KeyPad/KPD_program.o ./HAL/KeyPad/KPD_program.su

.PHONY: clean-HAL-2f-KeyPad

