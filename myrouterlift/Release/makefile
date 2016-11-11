################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include core\core/subdir.mk
-include Libraries\phi_prompt/subdir.mk
-include Libraries\phi_interfaces/subdir.mk
-include Libraries\MemoryFree/subdir.mk
-include Libraries\LiquidCrystal\src/subdir.mk
-include Libraries\EEPROMEx/subdir.mk
-include Libraries\AccelStepper/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
myrouterlift.elf \

HEX += \
myrouterlift.hex \


# All Target
all: myrouterlift

# Tool invocations
myrouterlift: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-size" -A "Z:/dev/mars_workspace/benjiz-router-lift/myrouterlift/Release/myrouterlift.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-gcc-ar" rcs "Z:/dev/mars_workspace/benjiz-router-lift/myrouterlift/Release/arduino.ar"  arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

myrouterlift.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\Dev\eclipse-cpp-mars-2-win32-x86_64\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-gcc" -Os -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -Wl,-u,vfprintf -lprintf_flt -lm -Wl,-u,vfscanf -lscanf_flt -lm -o "Z:/dev/mars_workspace/benjiz-router-lift/myrouterlift/Release/myrouterlift.elf"  $(LINK_OBJ) $(AR)  "-LZ:/dev/mars_workspace/benjiz-router-lift/myrouterlift/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

myrouterlift.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
