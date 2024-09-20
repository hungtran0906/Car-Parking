################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Servo/Servo.c 

OBJS += \
./HAL/Servo/Servo.o 

C_DEPS += \
./HAL/Servo/Servo.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Servo/%.o HAL/Servo/%.su HAL/Servo/%.cyclo: ../HAL/Servo/%.c HAL/Servo/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/HAL/includes" -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-Servo

clean-HAL-2f-Servo:
	-$(RM) ./HAL/Servo/Servo.cyclo ./HAL/Servo/Servo.d ./HAL/Servo/Servo.o ./HAL/Servo/Servo.su

.PHONY: clean-HAL-2f-Servo

