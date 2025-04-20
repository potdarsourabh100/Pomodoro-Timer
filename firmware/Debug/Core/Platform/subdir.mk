################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Platform/TM1637.c 

OBJS += \
./Core/Platform/TM1637.o 

C_DEPS += \
./Core/Platform/TM1637.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Platform/%.o Core/Platform/%.su Core/Platform/%.cyclo: ../Core/Platform/%.c Core/Platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Core/Common" -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Core/Platform" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Platform

clean-Core-2f-Platform:
	-$(RM) ./Core/Platform/TM1637.cyclo ./Core/Platform/TM1637.d ./Core/Platform/TM1637.o ./Core/Platform/TM1637.su

.PHONY: clean-Core-2f-Platform

