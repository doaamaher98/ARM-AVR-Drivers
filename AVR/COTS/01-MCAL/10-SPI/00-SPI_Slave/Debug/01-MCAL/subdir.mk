################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../01-MCAL/DIO.c \
../01-MCAL/DIO_Cfg.c \
../01-MCAL/GIE.c \
../01-MCAL/GIE_Cfg.c \
../01-MCAL/SPI.c \
../01-MCAL/TIMER0.c 

OBJS += \
./01-MCAL/DIO.o \
./01-MCAL/DIO_Cfg.o \
./01-MCAL/GIE.o \
./01-MCAL/GIE_Cfg.o \
./01-MCAL/SPI.o \
./01-MCAL/TIMER0.o 

C_DEPS += \
./01-MCAL/DIO.d \
./01-MCAL/DIO_Cfg.d \
./01-MCAL/GIE.d \
./01-MCAL/GIE_Cfg.d \
./01-MCAL/SPI.d \
./01-MCAL/TIMER0.d 


# Each subdirectory must supply rules for building sources it contributes
01-MCAL/%.o: ../01-MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


