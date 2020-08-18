################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/si4463/Src/si4463.c 

OBJS += \
./Drivers/si4463/Src/si4463.o 

C_DEPS += \
./Drivers/si4463/Src/si4463.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/si4463/Src/%.o: ../Drivers/si4463/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32F205xx -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/Delay_DWT/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/enc28j60/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/si4463/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/STM32F2xx_HAL_Driver/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/STM32F2xx_HAL_Driver/Inc/Legacy" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/CMSIS/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


