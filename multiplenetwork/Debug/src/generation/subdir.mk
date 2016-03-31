################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/generation/BAEvolutionModel.cpp \
../src/generation/EvolutionModel.cpp \
../src/generation/UniformEvolutionModel.cpp \
../src/generation/evolution.cpp \
../src/generation/evolution_strategies.cpp 

OBJS += \
./src/generation/BAEvolutionModel.o \
./src/generation/EvolutionModel.o \
./src/generation/UniformEvolutionModel.o \
./src/generation/evolution.o \
./src/generation/evolution_strategies.o 

CPP_DEPS += \
./src/generation/BAEvolutionModel.d \
./src/generation/EvolutionModel.d \
./src/generation/UniformEvolutionModel.d \
./src/generation/evolution.d \
./src/generation/evolution_strategies.d 


# Each subdirectory must supply rules for building sources it contributes
src/generation/%.o: ../src/generation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


