################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/core/avr-libc/subdir.mk
-include arduino/core/subdir.mk
-include Libraries/phi_prompt/subdir.mk
-include Libraries/phi_interfaces/subdir.mk
-include Libraries/MemoryFree/subdir.mk
-include Libraries/LiquidCrystal/src/subdir.mk
-include Libraries/EEPROMEx/subdir.mk
-include Libraries/AccelStepper/subdir.mk
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
Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/arduino.ar \

ELF += \
myrouterlift.elf \

EEP += \
myrouterlift.eep \

FLASH_IMAGE += \
myrouterlift.hex \


# All Target
all: myrouterlift

# Tool invocations
myrouterlift: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Arduino/hardware/tools/avr/bin/avr-size" -A "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/myrouterlift.elf"
	@echo 'Finished building target: $@'
	@echo ' '

Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Arduino/hardware/tools/avr/bin/avr-ar" rcs "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

myrouterlift.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Arduino/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p -o "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/myrouterlift.elf"   $(LINK_OBJ) $(AR)  "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/arduino.ar" "-LZ:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

myrouterlift.eep: $(ELF)
	@echo 'Create eeprom image'
	"C:/Arduino/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/myrouterlift.elf" "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/myrouterlift.eep"
	@echo 'Finished building: $@'
	@echo ' '

myrouterlift.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Arduino/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/myrouterlift.elf" "Z:/dev/github.com_benji791_benjiz-router-lift.git/myrouterlift/Release/myrouterlift.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) myrouterlift
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
