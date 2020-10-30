################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 30
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Sources/kernel/subdir.mk
-include Sources/cpu/subdir.mk
-include Sources/bench/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
cw_naught.elf \

EXECUTABLES_QUOTED += \
"cw_naught.elf" \

EXECUTABLES_OS_FORMAT += \
cw_naught.elf \


# All Target
all: warning-messages explicit-dependencies cw_naught.elf

# Tool invocations
cw_naught.elf: $(OBJS) $(USER_OBJS) ../LCF/T4240QDS_gcc-aeabi_SMP.lcf
	@echo 'Building target: $@'
	@echo 'Executing target #31 $@'
	@echo 'Invoking: PowerPC AEABI e6500 C Linker'
	"$(PAGccAeabiE6500DirEnv)/powerpc-aeabi-gcc"  $(USER_OBJS_QUOTED)  @"cw_naught.args" -o"cw_naught.elf"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) "./*/*/*.o" "./*/*.o"  $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) $(S_UPPER_DEPS_QUOTED) "./*/*/*.d" "./*/*.d"  $(ProjDirPath)/RAM/cw_naught.elf
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../LCF/T4240QDS_gcc-aeabi_SMP.lcf 

warning-messages: 

