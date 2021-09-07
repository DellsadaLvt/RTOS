################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/org/FreeRTOS/Source/croutine.c \
../Middlewares/Third_Party/org/FreeRTOS/Source/event_groups.c \
../Middlewares/Third_Party/org/FreeRTOS/Source/list.c \
../Middlewares/Third_Party/org/FreeRTOS/Source/queue.c \
../Middlewares/Third_Party/org/FreeRTOS/Source/stream_buffer.c \
../Middlewares/Third_Party/org/FreeRTOS/Source/tasks.c \
../Middlewares/Third_Party/org/FreeRTOS/Source/timers.c 

OBJS += \
./Middlewares/Third_Party/org/FreeRTOS/Source/croutine.o \
./Middlewares/Third_Party/org/FreeRTOS/Source/event_groups.o \
./Middlewares/Third_Party/org/FreeRTOS/Source/list.o \
./Middlewares/Third_Party/org/FreeRTOS/Source/queue.o \
./Middlewares/Third_Party/org/FreeRTOS/Source/stream_buffer.o \
./Middlewares/Third_Party/org/FreeRTOS/Source/tasks.o \
./Middlewares/Third_Party/org/FreeRTOS/Source/timers.o 

C_DEPS += \
./Middlewares/Third_Party/org/FreeRTOS/Source/croutine.d \
./Middlewares/Third_Party/org/FreeRTOS/Source/event_groups.d \
./Middlewares/Third_Party/org/FreeRTOS/Source/list.d \
./Middlewares/Third_Party/org/FreeRTOS/Source/queue.d \
./Middlewares/Third_Party/org/FreeRTOS/Source/stream_buffer.d \
./Middlewares/Third_Party/org/FreeRTOS/Source/tasks.d \
./Middlewares/Third_Party/org/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/org/FreeRTOS/Source/croutine.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/croutine.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/croutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/org/FreeRTOS/Source/event_groups.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/event_groups.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/event_groups.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/org/FreeRTOS/Source/list.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/list.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/list.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/org/FreeRTOS/Source/queue.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/queue.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/org/FreeRTOS/Source/stream_buffer.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/stream_buffer.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/stream_buffer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/org/FreeRTOS/Source/tasks.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/tasks.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/tasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/org/FreeRTOS/Source/timers.o: ../Middlewares/Third_Party/org/FreeRTOS/Source/timers.c Middlewares/Third_Party/org/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/CMSIS_RTOS_V2" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/include" -I"E:/Udemy/STM32_Course/MyLearning/Mastering RTOS Hands on FreeRTOS and STM32Fx with Debugging/Cube_IDE/RTOS_02/Middlewares/Third_Party/org/FreeRTOS/Source/portable/GCC/ARM_CM3" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/org/FreeRTOS/Source/timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
