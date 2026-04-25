################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/port/portevent.c \
../modbus/port/portserial.c \
../modbus/port/porttimer.c 

C_DEPS += \
./modbus/port/portevent.d \
./modbus/port/portserial.d \
./modbus/port/porttimer.d 

OBJS += \
./modbus/port/portevent.o \
./modbus/port/portserial.o \
./modbus/port/porttimer.o 


# Each subdirectory must supply rules for building sources it contributes
modbus/port/%.o modbus/port/%.su: ../modbus/port/%.c modbus/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../simple_math -I../lab_works -I../modbus/ascii -I../modbus/functions -I../modbus/include -I../modbus/rtu -I../modbus/port -I../modbus/tcp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modbus-2f-port

clean-modbus-2f-port:
	-$(RM) ./modbus/port/portevent.d ./modbus/port/portevent.o ./modbus/port/portevent.su ./modbus/port/portserial.d ./modbus/port/portserial.o ./modbus/port/portserial.su ./modbus/port/porttimer.d ./modbus/port/porttimer.o ./modbus/port/porttimer.su

.PHONY: clean-modbus-2f-port

