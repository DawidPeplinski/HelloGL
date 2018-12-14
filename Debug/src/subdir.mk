################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/stb_image.c 

CPP_SRCS += \
../src/display.cpp \
../src/main.cpp \
../src/mesh.cpp \
../src/obj_loader.cpp \
../src/shader.cpp \
../src/text.cpp \
../src/texture.cpp 

OBJS += \
./src/display.o \
./src/main.o \
./src/mesh.o \
./src/obj_loader.o \
./src/shader.o \
./src/stb_image.o \
./src/text.o \
./src/texture.o 

C_DEPS += \
./src/stb_image.d 

CPP_DEPS += \
./src/display.d \
./src/main.d \
./src/mesh.d \
./src/obj_loader.d \
./src/shader.d \
./src/text.d \
./src/texture.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


