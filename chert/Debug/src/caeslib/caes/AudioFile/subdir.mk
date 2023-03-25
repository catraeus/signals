################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/caeslib/caes/AudioFile/AudioFiler.cpp \
../src/caeslib/caes/AudioFile/CtlAudMsg.cpp \
../src/caeslib/caes/AudioFile/NumSys.cpp \
../src/caeslib/caes/AudioFile/RawFile.cpp \
../src/caeslib/caes/AudioFile/RiffCk.cpp \
../src/caeslib/caes/AudioFile/RiffMgr.cpp \
../src/caeslib/caes/AudioFile/Signal.cpp \
../src/caeslib/caes/AudioFile/WaveFiler.cpp \
../src/caeslib/caes/AudioFile/WaveFmt.cpp \
../src/caeslib/caes/AudioFile/WaveGUID.cpp 

CPP_DEPS += \
./src/caeslib/caes/AudioFile/AudioFiler.d \
./src/caeslib/caes/AudioFile/CtlAudMsg.d \
./src/caeslib/caes/AudioFile/NumSys.d \
./src/caeslib/caes/AudioFile/RawFile.d \
./src/caeslib/caes/AudioFile/RiffCk.d \
./src/caeslib/caes/AudioFile/RiffMgr.d \
./src/caeslib/caes/AudioFile/Signal.d \
./src/caeslib/caes/AudioFile/WaveFiler.d \
./src/caeslib/caes/AudioFile/WaveFmt.d \
./src/caeslib/caes/AudioFile/WaveGUID.d 

OBJS += \
./src/caeslib/caes/AudioFile/AudioFiler.o \
./src/caeslib/caes/AudioFile/CtlAudMsg.o \
./src/caeslib/caes/AudioFile/NumSys.o \
./src/caeslib/caes/AudioFile/RawFile.o \
./src/caeslib/caes/AudioFile/RiffCk.o \
./src/caeslib/caes/AudioFile/RiffMgr.o \
./src/caeslib/caes/AudioFile/Signal.o \
./src/caeslib/caes/AudioFile/WaveFiler.o \
./src/caeslib/caes/AudioFile/WaveFmt.o \
./src/caeslib/caes/AudioFile/WaveGUID.o 


# Each subdirectory must supply rules for building sources it contributes
src/caeslib/caes/AudioFile/%.o: ../src/caeslib/caes/AudioFile/%.cpp src/caeslib/caes/AudioFile/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/cairomm-1.0 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/caeslib -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-caeslib-2f-caes-2f-AudioFile

clean-src-2f-caeslib-2f-caes-2f-AudioFile:
	-$(RM) ./src/caeslib/caes/AudioFile/AudioFiler.d ./src/caeslib/caes/AudioFile/AudioFiler.o ./src/caeslib/caes/AudioFile/CtlAudMsg.d ./src/caeslib/caes/AudioFile/CtlAudMsg.o ./src/caeslib/caes/AudioFile/NumSys.d ./src/caeslib/caes/AudioFile/NumSys.o ./src/caeslib/caes/AudioFile/RawFile.d ./src/caeslib/caes/AudioFile/RawFile.o ./src/caeslib/caes/AudioFile/RiffCk.d ./src/caeslib/caes/AudioFile/RiffCk.o ./src/caeslib/caes/AudioFile/RiffMgr.d ./src/caeslib/caes/AudioFile/RiffMgr.o ./src/caeslib/caes/AudioFile/Signal.d ./src/caeslib/caes/AudioFile/Signal.o ./src/caeslib/caes/AudioFile/WaveFiler.d ./src/caeslib/caes/AudioFile/WaveFiler.o ./src/caeslib/caes/AudioFile/WaveFmt.d ./src/caeslib/caes/AudioFile/WaveFmt.o ./src/caeslib/caes/AudioFile/WaveGUID.d ./src/caeslib/caes/AudioFile/WaveGUID.o

.PHONY: clean-src-2f-caeslib-2f-caes-2f-AudioFile

