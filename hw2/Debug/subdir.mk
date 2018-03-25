################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPU_methods.c \
../MyPaint.c \
../pgmUtility.c 

OBJS += \
./CPU_methods.o \
./MyPaint.o \
./pgmUtility.o 

C_DEPS += \
./CPU_methods.d \
./MyPaint.d \
./pgmUtility.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


