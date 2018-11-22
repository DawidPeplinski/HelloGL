################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/display.cpp \
../src/main.cpp \
../src/mesh.cpp \
../src/shader.cpp 

OBJS += \
./src/display.o \
./src/main.o \
./src/mesh.o \
./src/shader.o 

CPP_DEPS += \
./src/display.d \
./src/main.d \
./src/mesh.d \
./src/shader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


