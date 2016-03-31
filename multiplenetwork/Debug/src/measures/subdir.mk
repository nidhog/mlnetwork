################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/measures/degree.cpp \
../src/measures/distance_based.cpp \
../src/measures/layer_correlation.cpp \
../src/measures/neighborhood.cpp \
../src/measures/randomwalk_measures.cpp \
../src/measures/relevance.cpp 

OBJS += \
./src/measures/degree.o \
./src/measures/distance_based.o \
./src/measures/layer_correlation.o \
./src/measures/neighborhood.o \
./src/measures/randomwalk_measures.o \
./src/measures/relevance.o 

CPP_DEPS += \
./src/measures/degree.d \
./src/measures/distance_based.d \
./src/measures/layer_correlation.d \
./src/measures/neighborhood.d \
./src/measures/randomwalk_measures.d \
./src/measures/relevance.d 


# Each subdirectory must supply rules for building sources it contributes
src/measures/%.o: ../src/measures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


