################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/datastructures/attributes/Attribute.cpp \
../src/datastructures/attributes/AttributeStore.cpp 

OBJS += \
./src/datastructures/attributes/Attribute.o \
./src/datastructures/attributes/AttributeStore.o 

CPP_DEPS += \
./src/datastructures/attributes/Attribute.d \
./src/datastructures/attributes/AttributeStore.d 


# Each subdirectory must supply rules for building sources it contributes
src/datastructures/attributes/%.o: ../src/datastructures/attributes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


