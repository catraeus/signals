################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Ana/AnBulk.cpp \
../src/Ana/AnSinus.cpp 

CPP_DEPS += \
./src/Ana/AnBulk.d \
./src/Ana/AnSinus.d 

OBJS += \
./src/Ana/AnBulk.o \
./src/Ana/AnSinus.o 


# Each subdirectory must supply rules for building sources it contributes
src/Ana/%.o: ../src/Ana/%.cpp src/Ana/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/include/harfbuzz -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/cairomm-1.0 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/caeslib -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Ana

clean-src-2f-Ana:
	-$(RM) ./src/Ana/AnBulk.d ./src/Ana/AnBulk.o ./src/Ana/AnSinus.d ./src/Ana/AnSinus.o

.PHONY: clean-src-2f-Ana

