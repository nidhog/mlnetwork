################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/datastructures/MLNetwork.cpp \
../src/datastructures/distance.cpp \
../src/datastructures/path.cpp 

OBJS += \
./src/datastructures/MLNetwork.o \
./src/datastructures/distance.o \
./src/datastructures/path.o 

CPP_DEPS += \
./src/datastructures/MLNetwork.d \
./src/datastructures/distance.d \
./src/datastructures/path.d 


# Each subdirectory must supply rules for building sources it contributes
src/datastructures/%.o: ../src/datastructures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


