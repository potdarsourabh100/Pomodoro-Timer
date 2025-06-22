################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/pomodorotimer.c 

OBJS += \
./Application/pomodorotimer.o 

C_DEPS += \
./Application/pomodorotimer.d 


# Each subdirectory must supply rules for building sources it contributes
Application/%.o Application/%.su Application/%.cyclo: ../Application/%.c Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Common" -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Platform" -I"D:/Sourabh_Workspace/My_Personal_Project_Workspaces/Pomodoro-Timer/firmware/Application" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application

clean-Application:
	-$(RM) ./Application/pomodorotimer.cyclo ./Application/pomodorotimer.d ./Application/pomodorotimer.o ./Application/pomodorotimer.su

.PHONY: clean-Application

