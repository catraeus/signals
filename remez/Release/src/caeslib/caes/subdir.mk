################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/caeslib/caes/CaesHpNum.cpp \
../src/caeslib/caes/CaesMath.cpp \
../src/caeslib/caes/CaesRemez.cpp 

CPP_DEPS += \
./src/caeslib/caes/CaesHpNum.d \
./src/caeslib/caes/CaesMath.d \
./src/caeslib/caes/CaesRemez.d 

OBJS += \
./src/caeslib/caes/CaesHpNum.o \
./src/caeslib/caes/CaesMath.o \
./src/caeslib/caes/CaesRemez.o 


# Each subdirectory must supply rules for building sources it contributes
src/caeslib/caes/%.o: ../src/caeslib/caes/%.cpp src/caeslib/caes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/way/dev/SW/caeslib -I/usr/include/sigc++-2.0 -I/usr/lib/arch/sigc++-2.0/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-caeslib-2f-caes

clean-src-2f-caeslib-2f-caes:
	-$(RM) ./src/caeslib/caes/CaesHpNum.d ./src/caeslib/caes/CaesHpNum.o ./src/caeslib/caes/CaesMath.d ./src/caeslib/caes/CaesMath.o ./src/caeslib/caes/CaesRemez.d ./src/caeslib/caes/CaesRemez.o

.PHONY: clean-src-2f-caeslib-2f-caes

