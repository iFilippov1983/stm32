################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab_works/AdDaFunctions.c \
../lab_works/I2cFinctions.c \
../lab_works/LabWorks.c \
../lab_works/SpiFunctions.c \
../lab_works/UsartFunctions.c 

C_DEPS += \
./lab_works/AdDaFunctions.d \
./lab_works/I2cFinctions.d \
./lab_works/LabWorks.d \
./lab_works/SpiFunctions.d \
./lab_works/UsartFunctions.d 

OBJS += \
./lab_works/AdDaFunctions.o \
./lab_works/I2cFinctions.o \
./lab_works/LabWorks.o \
./lab_works/SpiFunctions.o \
./lab_works/UsartFunctions.o 


# Each subdirectory must supply rules for building sources it contributes
lab_works/%.o lab_works/%.su: ../lab_works/%.c lab_works/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../simple_math -I../lab_works -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lab_works

clean-lab_works:
	-$(RM) ./lab_works/AdDaFunctions.d ./lab_works/AdDaFunctions.o ./lab_works/AdDaFunctions.su ./lab_works/I2cFinctions.d ./lab_works/I2cFinctions.o ./lab_works/I2cFinctions.su ./lab_works/LabWorks.d ./lab_works/LabWorks.o ./lab_works/LabWorks.su ./lab_works/SpiFunctions.d ./lab_works/SpiFunctions.o ./lab_works/SpiFunctions.su ./lab_works/UsartFunctions.d ./lab_works/UsartFunctions.o ./lab_works/UsartFunctions.su

.PHONY: clean-lab_works

