################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/cpu/cache.c" \
"../Sources/cpu/monitor.c" \
"../Sources/cpu/prediction.c" 

C_SRCS += \
../Sources/cpu/cache.c \
../Sources/cpu/monitor.c \
../Sources/cpu/prediction.c 

OBJS += \
./Sources/cpu/cache.o \
./Sources/cpu/monitor.o \
./Sources/cpu/prediction.o 

C_DEPS += \
./Sources/cpu/cache.d \
./Sources/cpu/monitor.d \
./Sources/cpu/prediction.d 

OBJS_QUOTED += \
"./Sources/cpu/cache.o" \
"./Sources/cpu/monitor.o" \
"./Sources/cpu/prediction.o" 

OBJS_OS_FORMAT += \
./Sources/cpu/cache.o \
./Sources/cpu/monitor.o \
./Sources/cpu/prediction.o 

C_DEPS_QUOTED += \
"./Sources/cpu/cache.d" \
"./Sources/cpu/monitor.d" \
"./Sources/cpu/prediction.d" 


# Each subdirectory must supply rules for building sources it contributes
Sources/cpu/cache.o: ../Sources/cpu/cache.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC AEABI e6500 C Compiler'
	"$(PAGccAeabiE6500DirEnv)/powerpc-aeabi-gcc" "$<" @"Sources/cpu/cache.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/cpu/cache.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/monitor.o: ../Sources/cpu/monitor.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC AEABI e6500 C Compiler'
	"$(PAGccAeabiE6500DirEnv)/powerpc-aeabi-gcc" "$<" @"Sources/cpu/monitor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/cpu/monitor.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/prediction.o: ../Sources/cpu/prediction.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: PowerPC AEABI e6500 C Compiler'
	"$(PAGccAeabiE6500DirEnv)/powerpc-aeabi-gcc" "$<" @"Sources/cpu/prediction.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/cpu/prediction.o"
	@echo 'Finished building: $<'
	@echo ' '


