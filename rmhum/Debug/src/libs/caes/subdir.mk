################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/caes/CaesApodia.cpp \
../src/libs/caes/CaesFunc.cpp \
../src/libs/caes/CaesMath.cpp 

OBJS += \
./src/libs/caes/CaesApodia.o \
./src/libs/caes/CaesFunc.o \
./src/libs/caes/CaesMath.o 

CPP_DEPS += \
./src/libs/caes/CaesApodia.d \
./src/libs/caes/CaesFunc.d \
./src/libs/caes/CaesMath.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/caes/%.o: ../src/libs/caes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../../../libs -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


