################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/rtu/mbcrc.c \
../modbus/rtu/mbrtu.c 

C_DEPS += \
./modbus/rtu/mbcrc.d \
./modbus/rtu/mbrtu.d 

OBJS += \
./modbus/rtu/mbcrc.o \
./modbus/rtu/mbrtu.o 


# Each subdirectory must supply rules for building sources it contributes
modbus/rtu/%.o modbus/rtu/%.su: ../modbus/rtu/%.c modbus/rtu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../simple_math -I../lab_works -I../modbus/ascii -I../modbus/functions -I../modbus/include -I../modbus/rtu -I../modbus/port -I../modbus/tcp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modbus-2f-rtu

clean-modbus-2f-rtu:
	-$(RM) ./modbus/rtu/mbcrc.d ./modbus/rtu/mbcrc.o ./modbus/rtu/mbcrc.su ./modbus/rtu/mbrtu.d ./modbus/rtu/mbrtu.o ./modbus/rtu/mbrtu.su

.PHONY: clean-modbus-2f-rtu

