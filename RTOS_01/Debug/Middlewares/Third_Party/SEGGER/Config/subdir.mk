################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o: ../Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c Middlewares/Third_Party/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_01/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_01/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM3" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_01/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_01/Middlewares/Third_Party/SEGGER/Config" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_01/Middlewares/Third_Party/SEGGER/OS" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_01/Middlewares/Third_Party/SEGGER/SEGGER" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
