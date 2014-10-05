################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c \
C:/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c 

C_DEPS += \
./arduino/malloc.c.d \
./arduino/realloc.c.d 

AR_OBJ += \
./arduino/malloc.c.o \
./arduino/realloc.c.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/malloc.c.o: C:/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\MemoryFree" -I"C:\Arduino\hardware\arduino\avr\variants\standard" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\AccelStepper" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\EEPROMEx" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal\src" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\phi_interfaces" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\phi_prompt" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/realloc.c.o: C:/Arduino/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Arduino/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\MemoryFree" -I"C:\Arduino\hardware\arduino\avr\variants\standard" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\AccelStepper" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\EEPROMEx" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal\src" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\phi_interfaces" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\phi_prompt" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


