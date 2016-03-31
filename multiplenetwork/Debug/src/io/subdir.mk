################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/io/graphml.cpp \
../src/io/multilayer.cpp 

OBJS += \
./src/io/graphml.o \
./src/io/multilayer.o 

CPP_DEPS += \
./src/io/graphml.d \
./src/io/multilayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/io/%.o: ../src/io/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


