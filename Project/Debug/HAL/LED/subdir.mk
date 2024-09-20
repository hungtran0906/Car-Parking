################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LED/LED.c 

OBJS += \
./HAL/LED/LED.o 

C_DEPS += \
./HAL/LED/LED.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LED/%.o HAL/LED/%.su HAL/LED/%.cyclo: ../HAL/LED/%.c HAL/LED/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/HAL/includes" -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-LED

clean-HAL-2f-LED:
	-$(RM) ./HAL/LED/LED.cyclo ./HAL/LED/LED.d ./HAL/LED/LED.o ./HAL/LED/LED.su

.PHONY: clean-HAL-2f-LED

