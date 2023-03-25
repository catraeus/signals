################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Arb/WaveIn.cpp \
../src/Arb/WaveOut.cpp 

OBJS += \
./src/Arb/WaveIn.o \
./src/Arb/WaveOut.o 

CPP_DEPS += \
./src/Arb/WaveIn.d \
./src/Arb/WaveOut.d 


# Each subdirectory must supply rules for building sources it contributes
src/Arb/%.o: ../src/Arb/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/srv/dev/svn/SW/libraries/particles/icon -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/glibmm-2.4 -I/usr/lib/gdkmm-3.0/include -I/usr/include/gdkmm-3.0 -I/usr/include/gtk-3.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/sigc++-2.0 -I/usr/lib/gtkmm-3.0/include -I/usr/include/gtkmm-3.0 -I/usr/include/cairo -I/usr/include/cairomm-1.0 -I/usr/include/pango-1.0 -I/usr/include/pangomm-1.4 -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/giomm-2.4 -I/usr/include/atk-1.0 -I/usr/include/atkmm-1.6 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-unix-print-2.0 -O0 -g3 -pedantic -pedantic-errors -Wall -Werror -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


