################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Platform/TM1637.c \
../Platform/buzzer.c 

OBJS += \
./Platform/TM1637.o \
./Platform/buzzer.o 

C_DEPS += \
./Platform/TM1637.d \
./Platform/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
Platform/%.o Platform/%.su Platform/%.cyclo: ../Platform/%.c Platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Common" -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Platform" -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/UserApp" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Platform

clean-Platform:
	-$(RM) ./Platform/TM1637.cyclo ./Platform/TM1637.d ./Platform/TM1637.o ./Platform/TM1637.su ./Platform/buzzer.cyclo ./Platform/buzzer.d ./Platform/buzzer.o ./Platform/buzzer.su

.PHONY: clean-Platform

