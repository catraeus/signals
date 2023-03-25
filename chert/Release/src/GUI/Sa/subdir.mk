################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GUI/Sa/DrwSa.cpp \
../src/GUI/Sa/FrmAp.cpp \
../src/GUI/Sa/FrmSaAp.cpp \
../src/GUI/Sa/FrmSaAxisH.cpp \
../src/GUI/Sa/FrmSaAxisV.cpp \
../src/GUI/Sa/FrmSaHor.cpp \
../src/GUI/Sa/FrmSaMode.cpp \
../src/GUI/Sa/FrmSaVrt.cpp \
../src/GUI/Sa/WinSa.cpp 

CPP_DEPS += \
./src/GUI/Sa/DrwSa.d \
./src/GUI/Sa/FrmAp.d \
./src/GUI/Sa/FrmSaAp.d \
./src/GUI/Sa/FrmSaAxisH.d \
./src/GUI/Sa/FrmSaAxisV.d \
./src/GUI/Sa/FrmSaHor.d \
./src/GUI/Sa/FrmSaMode.d \
./src/GUI/Sa/FrmSaVrt.d \
./src/GUI/Sa/WinSa.d 

OBJS += \
./src/GUI/Sa/DrwSa.o \
./src/GUI/Sa/FrmAp.o \
./src/GUI/Sa/FrmSaAp.o \
./src/GUI/Sa/FrmSaAxisH.o \
./src/GUI/Sa/FrmSaAxisV.o \
./src/GUI/Sa/FrmSaHor.o \
./src/GUI/Sa/FrmSaMode.o \
./src/GUI/Sa/FrmSaVrt.o \
./src/GUI/Sa/WinSa.o 


# Each subdirectory must supply rules for building sources it contributes
src/GUI/Sa/%.o: ../src/GUI/Sa/%.cpp src/GUI/Sa/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/cairomm-1.0 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/caeslib -O0 -Wall -c -fmessage-length=0 -fprefetch-loop-arrays -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-GUI-2f-Sa

clean-src-2f-GUI-2f-Sa:
	-$(RM) ./src/GUI/Sa/DrwSa.d ./src/GUI/Sa/DrwSa.o ./src/GUI/Sa/FrmAp.d ./src/GUI/Sa/FrmAp.o ./src/GUI/Sa/FrmSaAp.d ./src/GUI/Sa/FrmSaAp.o ./src/GUI/Sa/FrmSaAxisH.d ./src/GUI/Sa/FrmSaAxisH.o ./src/GUI/Sa/FrmSaAxisV.d ./src/GUI/Sa/FrmSaAxisV.o ./src/GUI/Sa/FrmSaHor.d ./src/GUI/Sa/FrmSaHor.o ./src/GUI/Sa/FrmSaMode.d ./src/GUI/Sa/FrmSaMode.o ./src/GUI/Sa/FrmSaVrt.d ./src/GUI/Sa/FrmSaVrt.o ./src/GUI/Sa/WinSa.d ./src/GUI/Sa/WinSa.o

.PHONY: clean-src-2f-GUI-2f-Sa

