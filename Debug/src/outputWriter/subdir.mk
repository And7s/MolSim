################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/outputWriter/VTKWriter.cpp \
../src/outputWriter/XYZWriter.cpp \
../src/outputWriter/vtk-unstructured.cpp 

OBJS += \
./src/outputWriter/VTKWriter.o \
./src/outputWriter/XYZWriter.o \
./src/outputWriter/vtk-unstructured.o 

CPP_DEPS += \
./src/outputWriter/VTKWriter.d \
./src/outputWriter/XYZWriter.d \
./src/outputWriter/vtk-unstructured.d 


# Each subdirectory must supply rules for building sources it contributes
src/outputWriter/%.o: ../src/outputWriter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


