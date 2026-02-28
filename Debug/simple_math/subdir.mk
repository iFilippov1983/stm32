################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../simple_math/simple_math.c 

C_DEPS += \
./simple_math/simple_math.d 

OBJS += \
./simple_math/simple_math.o 


# Each subdirectory must supply rules for building sources it contributes
simple_math/%.o simple_math/%.su: ../simple_math/%.c simple_math/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../simple_math -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-simple_math

clean-simple_math:
	-$(RM) ./simple_math/simple_math.d ./simple_math/simple_math.o ./simple_math/simple_math.su

.PHONY: clean-simple_math

