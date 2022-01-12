################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/lib_time/dst_pointer.c \
../Application/User/lib_time/gmtime.c \
../Application/User/lib_time/gmtime_r.c \
../Application/User/lib_time/mk_gmtime.c \
../Application/User/lib_time/mktime.c \
../Application/User/lib_time/tm_store.c \
../Application/User/lib_time/utc_offset.c 

C_DEPS += \
./Application/User/lib_time/dst_pointer.d \
./Application/User/lib_time/gmtime.d \
./Application/User/lib_time/gmtime_r.d \
./Application/User/lib_time/mk_gmtime.d \
./Application/User/lib_time/mktime.d \
./Application/User/lib_time/tm_store.d \
./Application/User/lib_time/utc_offset.d 

OBJS += \
./Application/User/lib_time/dst_pointer.o \
./Application/User/lib_time/gmtime.o \
./Application/User/lib_time/gmtime_r.o \
./Application/User/lib_time/mk_gmtime.o \
./Application/User/lib_time/mktime.o \
./Application/User/lib_time/tm_store.o \
./Application/User/lib_time/utc_offset.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/lib_time/%.o: ../Application/User/lib_time/%.c Application/User/lib_time/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F469xx -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Drivers/BSP/Components/Common -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-lib_time

clean-Application-2f-User-2f-lib_time:
	-$(RM) ./Application/User/lib_time/dst_pointer.d ./Application/User/lib_time/dst_pointer.o ./Application/User/lib_time/gmtime.d ./Application/User/lib_time/gmtime.o ./Application/User/lib_time/gmtime_r.d ./Application/User/lib_time/gmtime_r.o ./Application/User/lib_time/mk_gmtime.d ./Application/User/lib_time/mk_gmtime.o ./Application/User/lib_time/mktime.d ./Application/User/lib_time/mktime.o ./Application/User/lib_time/tm_store.d ./Application/User/lib_time/tm_store.o ./Application/User/lib_time/utc_offset.d ./Application/User/lib_time/utc_offset.o

.PHONY: clean-Application-2f-User-2f-lib_time

