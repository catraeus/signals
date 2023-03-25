################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/caes/Alsa/Alsa.cpp \
../src/libs/caes/Alsa/AlsaCard.cpp \
../src/libs/caes/Alsa/AlsaDevice.cpp \
../src/libs/caes/Alsa/AlsaFormat.cpp \
../src/libs/caes/Alsa/AlsaIfTypes.cpp \
../src/libs/caes/Alsa/AlsaInterface.cpp \
../src/libs/caes/Alsa/AlsaStream.cpp \
../src/libs/caes/Alsa/AlsaStreamIn.cpp \
../src/libs/caes/Alsa/AlsaStreamOut.cpp 

CPP_DEPS += \
./src/libs/caes/Alsa/Alsa.d \
./src/libs/caes/Alsa/AlsaCard.d \
./src/libs/caes/Alsa/AlsaDevice.d \
./src/libs/caes/Alsa/AlsaFormat.d \
./src/libs/caes/Alsa/AlsaIfTypes.d \
./src/libs/caes/Alsa/AlsaInterface.d \
./src/libs/caes/Alsa/AlsaStream.d \
./src/libs/caes/Alsa/AlsaStreamIn.d \
./src/libs/caes/Alsa/AlsaStreamOut.d 

OBJS += \
./src/libs/caes/Alsa/Alsa.o \
./src/libs/caes/Alsa/AlsaCard.o \
./src/libs/caes/Alsa/AlsaDevice.o \
./src/libs/caes/Alsa/AlsaFormat.o \
./src/libs/caes/Alsa/AlsaIfTypes.o \
./src/libs/caes/Alsa/AlsaInterface.o \
./src/libs/caes/Alsa/AlsaStream.o \
./src/libs/caes/Alsa/AlsaStreamIn.o \
./src/libs/caes/Alsa/AlsaStreamOut.o 


# Each subdirectory must supply rules for building sources it contributes
src/libs/caes/Alsa/%.o: ../src/libs/caes/Alsa/%.cpp src/libs/caes/Alsa/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/include/giomm-2.4 -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/include/glib-2.0 -I/usr/include/glibmm-2.4 -I/usr/include/gdkmm-3.0 -I/usr/include/gtk-3.0 -I/usr/include/sigc++-2.0 -I/usr/include/gtkmm-3.0 -I/usr/include/cairo -I/usr/include/cairomm-1.0 -I/usr/include/pango-1.0 -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/giomm-2.4 -I/usr/include/atk-1.0 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng -I/way/dev/SW/libs -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-libs-2f-caes-2f-Alsa

clean-src-2f-libs-2f-caes-2f-Alsa:
	-$(RM) ./src/libs/caes/Alsa/Alsa.d ./src/libs/caes/Alsa/Alsa.o ./src/libs/caes/Alsa/AlsaCard.d ./src/libs/caes/Alsa/AlsaCard.o ./src/libs/caes/Alsa/AlsaDevice.d ./src/libs/caes/Alsa/AlsaDevice.o ./src/libs/caes/Alsa/AlsaFormat.d ./src/libs/caes/Alsa/AlsaFormat.o ./src/libs/caes/Alsa/AlsaIfTypes.d ./src/libs/caes/Alsa/AlsaIfTypes.o ./src/libs/caes/Alsa/AlsaInterface.d ./src/libs/caes/Alsa/AlsaInterface.o ./src/libs/caes/Alsa/AlsaStream.d ./src/libs/caes/Alsa/AlsaStream.o ./src/libs/caes/Alsa/AlsaStreamIn.d ./src/libs/caes/Alsa/AlsaStreamIn.o ./src/libs/caes/Alsa/AlsaStreamOut.d ./src/libs/caes/Alsa/AlsaStreamOut.o

.PHONY: clean-src-2f-libs-2f-caes-2f-Alsa

