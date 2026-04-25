################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/functions/mbfunccoils.c \
../modbus/functions/mbfuncdiag.c \
../modbus/functions/mbfuncdisc.c \
../modbus/functions/mbfuncfile.c \
../modbus/functions/mbfuncholding.c \
../modbus/functions/mbfuncinput.c \
../modbus/functions/mbfuncother.c \
../modbus/functions/mbutils.c 

C_DEPS += \
./modbus/functions/mbfunccoils.d \
./modbus/functions/mbfuncdiag.d \
./modbus/functions/mbfuncdisc.d \
./modbus/functions/mbfuncfile.d \
./modbus/functions/mbfuncholding.d \
./modbus/functions/mbfuncinput.d \
./modbus/functions/mbfuncother.d \
./modbus/functions/mbutils.d 

OBJS += \
./modbus/functions/mbfunccoils.o \
./modbus/functions/mbfuncdiag.o \
./modbus/functions/mbfuncdisc.o \
./modbus/functions/mbfuncfile.o \
./modbus/functions/mbfuncholding.o \
./modbus/functions/mbfuncinput.o \
./modbus/functions/mbfuncother.o \
./modbus/functions/mbutils.o 


# Each subdirectory must supply rules for building sources it contributes
modbus/functions/%.o modbus/functions/%.su: ../modbus/functions/%.c modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../simple_math -I../lab_works -I../modbus/ascii -I../modbus/functions -I../modbus/include -I../modbus/rtu -I../modbus/port -I../modbus/tcp -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-modbus-2f-functions

clean-modbus-2f-functions:
	-$(RM) ./modbus/functions/mbfunccoils.d ./modbus/functions/mbfunccoils.o ./modbus/functions/mbfunccoils.su ./modbus/functions/mbfuncdiag.d ./modbus/functions/mbfuncdiag.o ./modbus/functions/mbfuncdiag.su ./modbus/functions/mbfuncdisc.d ./modbus/functions/mbfuncdisc.o ./modbus/functions/mbfuncdisc.su ./modbus/functions/mbfuncfile.d ./modbus/functions/mbfuncfile.o ./modbus/functions/mbfuncfile.su ./modbus/functions/mbfuncholding.d ./modbus/functions/mbfuncholding.o ./modbus/functions/mbfuncholding.su ./modbus/functions/mbfuncinput.d ./modbus/functions/mbfuncinput.o ./modbus/functions/mbfuncinput.su ./modbus/functions/mbfuncother.d ./modbus/functions/mbfuncother.o ./modbus/functions/mbfuncother.su ./modbus/functions/mbutils.d ./modbus/functions/mbutils.o ./modbus/functions/mbutils.su

.PHONY: clean-modbus-2f-functions

