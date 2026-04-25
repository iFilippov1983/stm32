################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/ascii/mbascii.c 

C_DEPS += \
./modbus/ascii/mbascii.d 

OBJS += \
./modbus/ascii/mbascii.o 


# Each subdirectory must supply rules for building sources it contributes
modbus/ascii/%.o modbus/ascii/%.su: ../modbus/ascii/%.c modbus/ascii/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../simple_math -I../lab_works -I../modbus/ascii -I../modbus/functions -I../modbus/include -I../modbus/rtu -I../modbus/port -I../modbus/tcp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modbus-2f-ascii

clean-modbus-2f-ascii:
	-$(RM) ./modbus/ascii/mbascii.d ./modbus/ascii/mbascii.o ./modbus/ascii/mbascii.su

.PHONY: clean-modbus-2f-ascii

