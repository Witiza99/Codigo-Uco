################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MQKPEvaluator.cpp \
../src/MQKPInstance.cpp \
../src/MQKPSolGenerator.cpp \
../src/MQKPSolution.cpp \
../src/Timer.cpp \
../src/main.cpp \
../src/seeds.cpp 

OBJS += \
./src/MQKPEvaluator.o \
./src/MQKPInstance.o \
./src/MQKPSolGenerator.o \
./src/MQKPSolution.o \
./src/Timer.o \
./src/main.o \
./src/seeds.o 

CPP_DEPS += \
./src/MQKPEvaluator.d \
./src/MQKPInstance.d \
./src/MQKPSolGenerator.d \
./src/MQKPSolution.d \
./src/Timer.d \
./src/main.d \
./src/seeds.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


