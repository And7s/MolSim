################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Calculation.cpp \
../src/FileReader.cpp \
../src/MolSim.cpp \
../src/Particle.cpp \
../src/ParticleContainer.cpp \
../src/ParticleGenerator.cpp \
../src/Plotter.cpp 

OBJS += \
./src/Calculation.o \
./src/FileReader.o \
./src/MolSim.o \
./src/Particle.o \
./src/ParticleContainer.o \
./src/ParticleGenerator.o \
./src/Plotter.o 

CPP_DEPS += \
./src/Calculation.d \
./src/FileReader.d \
./src/MolSim.d \
./src/Particle.d \
./src/ParticleContainer.d \
./src/ParticleGenerator.d \
./src/Plotter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


