################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
..\myrouterlift.ino 

CPP_SRCS += \
..\.ino.cpp 

LINK_OBJ += \
.\.ino.cpp.o 

INO_DEPS += \
.\myrouterlift.ino.d 

CPP_DEPS += \
.\.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega1284p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO_PRO -DARDUINO_ARCH_AVR   -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\Libraries\AccelStepper" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\EEPROMEx" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\LiquidCrystal" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\LiquidCrystal\src" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\Libraries\phi_interfaces" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\phi_prompt" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\MemoryFree" -I"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\cores\arduino" -I"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\variants\uno_pro" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall -Wl,-u,vfprintf -lprintf_flt -lm -Wl,-u,vfscanf -lscanf_flt -lm
	@echo 'Finished building: $<'
	@echo ' '

myrouterlift.o: ../myrouterlift.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega1284p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO_PRO -DARDUINO_ARCH_AVR   -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\Libraries\AccelStepper" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\EEPROMEx" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\LiquidCrystal" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\LiquidCrystal\src" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\Libraries\phi_interfaces" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\phi_prompt" -I"Z:\dev\mars_workspace\benjiz-router-lift\myrouterlift\libraries\MemoryFree" -I"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\cores\arduino" -I"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\variants\uno_pro" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall -Wl,-u,vfprintf -lprintf_flt -lm -Wl,-u,vfscanf -lscanf_flt -lm
	@echo 'Finished building: $<'
	@echo ' '


