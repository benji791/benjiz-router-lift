################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../myrouterlift.ino 

CPP_SRCS += \
../.ino.cpp 

LINK_OBJ += \
./.ino.cpp.o 

INO_DEPS += \
./myrouterlift.ino.d 

CPP_DEPS += \
./.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\standard" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\AccelStepper" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\EEPROMEx" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal\src" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\phi_interfaces" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\phi_prompt" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\MemoryFree" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

myrouterlift.o: ../myrouterlift.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Arduino/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=156-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\standard" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\AccelStepper" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\EEPROMEx" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\LiquidCrystal\src" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\Libraries\phi_interfaces" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\phi_prompt" -I"Z:\dev\github.com_benji791_benjiz-router-lift.git\myrouterlift\libraries\MemoryFree" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


