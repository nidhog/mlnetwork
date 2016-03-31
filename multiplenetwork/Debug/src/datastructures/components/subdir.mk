################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/datastructures/components/actor.cpp \
../src/datastructures/components/basic.cpp \
../src/datastructures/components/edge.cpp \
../src/datastructures/components/layer.cpp \
../src/datastructures/components/node.cpp 

OBJS += \
./src/datastructures/components/actor.o \
./src/datastructures/components/basic.o \
./src/datastructures/components/edge.o \
./src/datastructures/components/layer.o \
./src/datastructures/components/node.o 

CPP_DEPS += \
./src/datastructures/components/actor.d \
./src/datastructures/components/basic.d \
./src/datastructures/components/edge.d \
./src/datastructures/components/layer.d \
./src/datastructures/components/node.d 


# Each subdirectory must supply rules for building sources it contributes
src/datastructures/components/%.o: ../src/datastructures/components/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


