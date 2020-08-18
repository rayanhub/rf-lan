################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rng.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_spi.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c 

OBJS += \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rng.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_spi.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.o 

C_DEPS += \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_adc_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rng.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_spi.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F2xx_HAL_Driver/Src/%.o: ../Drivers/STM32F2xx_HAL_Driver/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32F205xx -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/Delay_DWT/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/enc28j60/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/si4463/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/STM32F2xx_HAL_Driver/Inc" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/STM32F2xx_HAL_Driver/Inc/Legacy" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"/home/rayan/Documents/modem_proj/modem_rf+lan/Drivers/CMSIS/Include"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


