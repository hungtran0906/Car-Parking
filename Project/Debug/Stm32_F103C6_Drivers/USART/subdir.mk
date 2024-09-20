################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.c 

OBJS += \
./Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/USART/%.o Stm32_F103C6_Drivers/USART/%.su Stm32_F103C6_Drivers/USART/%.cyclo: ../Stm32_F103C6_Drivers/USART/%.c Stm32_F103C6_Drivers/USART/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -c -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/HAL/includes" -I"C:/Intern_HCL/1_LEARN_GIT/Car_parking/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-USART

clean-Stm32_F103C6_Drivers-2f-USART:
	-$(RM) ./Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.cyclo ./Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.d ./Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.o ./Stm32_F103C6_Drivers/USART/Stm32_F103C6_USART_driver.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-USART

