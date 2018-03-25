################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../GPU-Programming/cryptMD5.cu \
../GPU-Programming/hostmd5.cu \
../GPU-Programming/main.cu \
../GPU-Programming/md5.cu \
../GPU-Programming/tester.cu 

C_SRCS += \
../GPU-Programming/charTest.c 

O_SRCS += \
../GPU-Programming/cryptCall.o \
../GPU-Programming/hostCrypt.o 

OBJS += \
./GPU-Programming/charTest.o \
./GPU-Programming/cryptMD5.o \
./GPU-Programming/hostmd5.o \
./GPU-Programming/main.o \
./GPU-Programming/md5.o \
./GPU-Programming/tester.o 

CU_DEPS += \
./GPU-Programming/cryptMD5.d \
./GPU-Programming/hostmd5.d \
./GPU-Programming/main.d \
./GPU-Programming/md5.d \
./GPU-Programming/tester.d 

C_DEPS += \
./GPU-Programming/charTest.d 


# Each subdirectory must supply rules for building sources it contributes
GPU-Programming/%.o: ../GPU-Programming/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/bin/nvcc -G -g -O0 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35  -odir "GPU-Programming" -M -o "$(@:%.o=%.d)" "$<"
	/usr/bin/nvcc -G -g -O0 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

GPU-Programming/%.o: ../GPU-Programming/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/bin/nvcc -G -g -O0 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35  -odir "GPU-Programming" -M -o "$(@:%.o=%.d)" "$<"
	/usr/bin/nvcc -G -g -O0 --compile --relocatable-device-code=false -gencode arch=compute_20,code=compute_20 -gencode arch=compute_30,code=compute_30 -gencode arch=compute_35,code=compute_35 -gencode arch=compute_20,code=sm_20 -gencode arch=compute_20,code=sm_21 -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


