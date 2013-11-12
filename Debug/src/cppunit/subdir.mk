################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cppunit/Calculation_suite.cpp \
../src/cppunit/Calculation_test.cpp \
../src/cppunit/ParticleContainer_suite.cpp \
../src/cppunit/ParticleContainer_test.cpp \
../src/cppunit/Particle_suite.cpp \
../src/cppunit/Particle_test.cpp \
../src/cppunit/Tester.cpp 

OBJS += \
./src/cppunit/Calculation_suite.o \
./src/cppunit/Calculation_test.o \
./src/cppunit/ParticleContainer_suite.o \
./src/cppunit/ParticleContainer_test.o \
./src/cppunit/Particle_suite.o \
./src/cppunit/Particle_test.o \
./src/cppunit/Tester.o 

CPP_DEPS += \
./src/cppunit/Calculation_suite.d \
./src/cppunit/Calculation_test.d \
./src/cppunit/ParticleContainer_suite.d \
./src/cppunit/ParticleContainer_test.d \
./src/cppunit/Particle_suite.d \
./src/cppunit/Particle_test.d \
./src/cppunit/Tester.d 


# Each subdirectory must supply rules for building sources it contributes
src/cppunit/%.o: ../src/cppunit/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


