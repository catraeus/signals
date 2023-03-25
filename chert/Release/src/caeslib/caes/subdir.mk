################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/caeslib/caes/CaesApodia.cpp \
../src/caeslib/caes/CaesFFT.cpp \
../src/caeslib/caes/CaesFunc.cpp \
../src/caeslib/caes/CaesMath.cpp \
../src/caeslib/caes/CaesSocket.cpp \
../src/caeslib/caes/CaesSpectrum.cpp \
../src/caeslib/caes/CaesStat.cpp \
../src/caeslib/caes/CaesString.cpp 

CPP_DEPS += \
./src/caeslib/caes/CaesApodia.d \
./src/caeslib/caes/CaesFFT.d \
./src/caeslib/caes/CaesFunc.d \
./src/caeslib/caes/CaesMath.d \
./src/caeslib/caes/CaesSocket.d \
./src/caeslib/caes/CaesSpectrum.d \
./src/caeslib/caes/CaesStat.d \
./src/caeslib/caes/CaesString.d 

OBJS += \
./src/caeslib/caes/CaesApodia.o \
./src/caeslib/caes/CaesFFT.o \
./src/caeslib/caes/CaesFunc.o \
./src/caeslib/caes/CaesMath.o \
./src/caeslib/caes/CaesSocket.o \
./src/caeslib/caes/CaesSpectrum.o \
./src/caeslib/caes/CaesStat.o \
./src/caeslib/caes/CaesString.o 


# Each subdirectory must supply rules for building sources it contributes
src/caeslib/caes/%.o: ../src/caeslib/caes/%.cpp src/caeslib/caes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/cairomm-1.0 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/caeslib -O0 -Wall -c -fmessage-length=0 -fprefetch-loop-arrays -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-caeslib-2f-caes

clean-src-2f-caeslib-2f-caes:
	-$(RM) ./src/caeslib/caes/CaesApodia.d ./src/caeslib/caes/CaesApodia.o ./src/caeslib/caes/CaesFFT.d ./src/caeslib/caes/CaesFFT.o ./src/caeslib/caes/CaesFunc.d ./src/caeslib/caes/CaesFunc.o ./src/caeslib/caes/CaesMath.d ./src/caeslib/caes/CaesMath.o ./src/caeslib/caes/CaesSocket.d ./src/caeslib/caes/CaesSocket.o ./src/caeslib/caes/CaesSpectrum.d ./src/caeslib/caes/CaesSpectrum.o ./src/caeslib/caes/CaesStat.d ./src/caeslib/caes/CaesStat.o ./src/caeslib/caes/CaesString.d ./src/caeslib/caes/CaesString.o

.PHONY: clean-src-2f-caeslib-2f-caes

