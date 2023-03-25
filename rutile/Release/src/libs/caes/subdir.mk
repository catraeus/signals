################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/caes/CaesApodia.cpp \
../src/libs/caes/CaesFunc.cpp \
../src/libs/caes/CaesIpps.cpp \
../src/libs/caes/CaesMath.cpp \
../src/libs/caes/CaesRemez.cpp \
../src/libs/caes/CaesString.cpp 

OBJS += \
./src/libs/caes/CaesApodia.o \
./src/libs/caes/CaesFunc.o \
./src/libs/caes/CaesIpps.o \
./src/libs/caes/CaesMath.o \
./src/libs/caes/CaesRemez.o \
./src/libs/caes/CaesString.o 

CPP_DEPS += \
./src/libs/caes/CaesApodia.d \
./src/libs/caes/CaesFunc.d \
./src/libs/caes/CaesIpps.d \
./src/libs/caes/CaesMath.d \
./src/libs/caes/CaesRemez.d \
./src/libs/caes/CaesString.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/caes/%.o: ../src/libs/caes/%.cpp src/libs/caes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/include/pangomm-1.4 -I/usr/include/cairomm-1.0 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/libs -O3 -Wall -c -fmessage-length=0 -std=c++11 -Wno-misleading-indentation -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


