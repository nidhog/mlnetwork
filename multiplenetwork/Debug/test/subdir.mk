################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/FailedUnitTestException.cpp \
../test/test_all.cpp \
../test/test_datastructures.cpp \
../test/test_evolution.cpp \
../test/test_io.cpp \
../test/test_measures.cpp \
../test/test_modularity.cpp \
../test/test_random.cpp \
../test/test_randomwalks.cpp \
../test/test_transformations.cpp 

OBJS += \
./test/FailedUnitTestException.o \
./test/test_all.o \
./test/test_datastructures.o \
./test/test_evolution.o \
./test/test_io.o \
./test/test_measures.o \
./test/test_modularity.o \
./test/test_random.o \
./test/test_randomwalks.o \
./test/test_transformations.o 

CPP_DEPS += \
./test/FailedUnitTestException.d \
./test/test_all.d \
./test/test_datastructures.d \
./test/test_evolution.d \
./test/test_io.d \
./test/test_measures.d \
./test/test_modularity.d \
./test/test_random.d \
./test/test_randomwalks.d \
./test/test_transformations.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


