################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Calculation.cpp \
../src/Card.cpp \
../src/Pack.cpp \
../src/bank.cpp \
../src/player.cpp \
../src/test.cpp 

OBJS += \
./src/Calculation.o \
./src/Card.o \
./src/Pack.o \
./src/bank.o \
./src/player.o \
./src/test.o 

CPP_DEPS += \
./src/Calculation.d \
./src/Card.d \
./src/Pack.d \
./src/bank.d \
./src/player.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


