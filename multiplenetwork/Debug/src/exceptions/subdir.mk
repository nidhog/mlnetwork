################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/exceptions/DuplicateElementException.cpp \
../src/exceptions/ElementNotFoundException.cpp \
../src/exceptions/FileNotFoundException.cpp \
../src/exceptions/OperationNotSupportedException.cpp \
../src/exceptions/WrongFormatException.cpp \
../src/exceptions/WrongParameterException.cpp 

OBJS += \
./src/exceptions/DuplicateElementException.o \
./src/exceptions/ElementNotFoundException.o \
./src/exceptions/FileNotFoundException.o \
./src/exceptions/OperationNotSupportedException.o \
./src/exceptions/WrongFormatException.o \
./src/exceptions/WrongParameterException.o 

CPP_DEPS += \
./src/exceptions/DuplicateElementException.d \
./src/exceptions/ElementNotFoundException.d \
./src/exceptions/FileNotFoundException.d \
./src/exceptions/OperationNotSupportedException.d \
./src/exceptions/WrongFormatException.d \
./src/exceptions/WrongParameterException.d 


# Each subdirectory must supply rules for building sources it contributes
src/exceptions/%.o: ../src/exceptions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


