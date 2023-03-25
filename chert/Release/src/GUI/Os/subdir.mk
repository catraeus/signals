################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GUI/Os/DrwOs.cpp \
../src/GUI/Os/FrmOsAxisH.cpp \
../src/GUI/Os/FrmOsAxisV.cpp \
../src/GUI/Os/FrmOsHor.cpp \
../src/GUI/Os/FrmOsVrt.cpp \
../src/GUI/Os/WinOs.cpp 

CPP_DEPS += \
./src/GUI/Os/DrwOs.d \
./src/GUI/Os/FrmOsAxisH.d \
./src/GUI/Os/FrmOsAxisV.d \
./src/GUI/Os/FrmOsHor.d \
./src/GUI/Os/FrmOsVrt.d \
./src/GUI/Os/WinOs.d 

OBJS += \
./src/GUI/Os/DrwOs.o \
./src/GUI/Os/FrmOsAxisH.o \
./src/GUI/Os/FrmOsAxisV.o \
./src/GUI/Os/FrmOsHor.o \
./src/GUI/Os/FrmOsVrt.o \
./src/GUI/Os/WinOs.o 


# Each subdirectory must supply rules for building sources it contributes
src/GUI/Os/%.o: ../src/GUI/Os/%.cpp src/GUI/Os/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/cairomm-1.0 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/caeslib -O0 -Wall -c -fmessage-length=0 -fprefetch-loop-arrays -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-GUI-2f-Os

clean-src-2f-GUI-2f-Os:
	-$(RM) ./src/GUI/Os/DrwOs.d ./src/GUI/Os/DrwOs.o ./src/GUI/Os/FrmOsAxisH.d ./src/GUI/Os/FrmOsAxisH.o ./src/GUI/Os/FrmOsAxisV.d ./src/GUI/Os/FrmOsAxisV.o ./src/GUI/Os/FrmOsHor.d ./src/GUI/Os/FrmOsHor.o ./src/GUI/Os/FrmOsVrt.d ./src/GUI/Os/FrmOsVrt.o ./src/GUI/Os/WinOs.d ./src/GUI/Os/WinOs.o

.PHONY: clean-src-2f-GUI-2f-Os

