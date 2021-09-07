################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.c \
../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

OBJS += \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.o \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.d \
./Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.o: ../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.c Middlewares/Third_Party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/SEGGER/OS" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/SEGGER/SEGGER" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM3" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/SEGGER/Config" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_RTT.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.o: ../Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.c Middlewares/Third_Party/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu99 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/SEGGER/OS" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/SEGGER/SEGGER" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/FreeRTOS/org/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/FreeRTOS/org/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/FreeRTOS/org/Source/portable/GCC/ARM_CM3" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/SEGGER/Config" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/SEGGER/SEGGER/SEGGER_SYSVIEW.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

