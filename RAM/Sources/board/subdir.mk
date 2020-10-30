################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/board/dcfg.c" 

C_SRCS += \
../Sources/board/dcfg.c 

OBJS += \
./Sources/board/dcfg.o 

C_DEPS += \
./Sources/board/dcfg.d 

OBJS_QUOTED += \
"./Sources/board/dcfg.o" 

OBJS_OS_FORMAT += \
./Sources/board/dcfg.o 

C_DEPS_QUOTED += \
"./Sources/board/dcfg.d" 


# Each subdirectory must supply rules for building sources it contributes
Sources/board/dcfg.o: ../Sources/board/dcfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC AEABI e6500 C Compiler'
	"$(PAGccAeabiE6500DirEnv)/powerpc-aeabi-gcc" "$<" @"Sources/board/dcfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/board/dcfg.o"
	@echo 'Finished building: $<'
	@echo ' '


