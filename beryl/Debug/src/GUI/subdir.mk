################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GUI/PageApod.cpp \
../src/GUI/PageFileWr.cpp \
../src/GUI/PageNoise.cpp \
../src/GUI/PageRemez.cpp \
../src/GUI/PageSinc.cpp \
../src/GUI/PageSine.cpp \
../src/GUI/WinMain.cpp 

CPP_DEPS += \
./src/GUI/PageApod.d \
./src/GUI/PageFileWr.d \
./src/GUI/PageNoise.d \
./src/GUI/PageRemez.d \
./src/GUI/PageSinc.d \
./src/GUI/PageSine.d \
./src/GUI/WinMain.d 

OBJS += \
./src/GUI/PageApod.o \
./src/GUI/PageFileWr.o \
./src/GUI/PageNoise.o \
./src/GUI/PageRemez.o \
./src/GUI/PageSinc.o \
./src/GUI/PageSine.o \
./src/GUI/WinMain.o 


# Each subdirectory must supply rules for building sources it contributes
src/GUI/%.o: ../src/GUI/%.cpp src/GUI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/cairomm-1.0 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/caeslib -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -Wno-misleading-indentation -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-GUI

clean-src-2f-GUI:
	-$(RM) ./src/GUI/PageApod.d ./src/GUI/PageApod.o ./src/GUI/PageFileWr.d ./src/GUI/PageFileWr.o ./src/GUI/PageNoise.d ./src/GUI/PageNoise.o ./src/GUI/PageRemez.d ./src/GUI/PageRemez.o ./src/GUI/PageSinc.d ./src/GUI/PageSinc.o ./src/GUI/PageSine.d ./src/GUI/PageSine.o ./src/GUI/WinMain.d ./src/GUI/WinMain.o

.PHONY: clean-src-2f-GUI

