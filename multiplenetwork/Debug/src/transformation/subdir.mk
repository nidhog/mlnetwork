################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/transformation/flattening.cpp 

OBJS += \
./src/transformation/flattening.o 

CPP_DEPS += \
./src/transformation/flattening.d 


# Each subdirectory must supply rules for building sources it contributes
src/transformation/%.o: ../src/transformation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


