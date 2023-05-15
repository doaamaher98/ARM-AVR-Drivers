################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../03-HAL/LED.c \
../03-HAL/LED_Cfg.c 

OBJS += \
./03-HAL/LED.o \
./03-HAL/LED_Cfg.o 

C_DEPS += \
./03-HAL/LED.d \
./03-HAL/LED_Cfg.d 


# Each subdirectory must supply rules for building sources it contributes
03-HAL/%.o: ../03-HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


