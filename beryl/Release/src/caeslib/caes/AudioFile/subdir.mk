################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/caes/AudioFile/AudioFiler.cpp \
../src/libs/caes/AudioFile/CtlAudMsg.cpp \
../src/libs/caes/AudioFile/NumSys.cpp \
../src/libs/caes/AudioFile/RiffCk.cpp \
../src/libs/caes/AudioFile/RiffMgr.cpp \
../src/libs/caes/AudioFile/Signal.cpp \
../src/libs/caes/AudioFile/WaveFiler.cpp \
../src/libs/caes/AudioFile/WaveFmt.cpp \
../src/libs/caes/AudioFile/WaveGUID.cpp 

CPP_DEPS += \
./src/libs/caes/AudioFile/AudioFiler.d \
./src/libs/caes/AudioFile/CtlAudMsg.d \
./src/libs/caes/AudioFile/NumSys.d \
./src/libs/caes/AudioFile/RiffCk.d \
./src/libs/caes/AudioFile/RiffMgr.d \
./src/libs/caes/AudioFile/Signal.d \
./src/libs/caes/AudioFile/WaveFiler.d \
./src/libs/caes/AudioFile/WaveFmt.d \
./src/libs/caes/AudioFile/WaveGUID.d 

OBJS += \
./src/libs/caes/AudioFile/AudioFiler.o \
./src/libs/caes/AudioFile/CtlAudMsg.o \
./src/libs/caes/AudioFile/NumSys.o \
./src/libs/caes/AudioFile/RiffCk.o \
./src/libs/caes/AudioFile/RiffMgr.o \
./src/libs/caes/AudioFile/Signal.o \
./src/libs/caes/AudioFile/WaveFiler.o \
./src/libs/caes/AudioFile/WaveFmt.o \
./src/libs/caes/AudioFile/WaveGUID.o 


# Each subdirectory must supply rules for building sources it contributes
src/libs/caes/AudioFile/%.o: ../src/libs/caes/AudioFile/%.cpp src/libs/caes/AudioFile/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/lib/arch/atkmm-1.6/include -I/usr/include/pangomm-1.4 -I/usr/include/harfbuzz -I/usr/include/cairomm-1.0 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/libs -O3 -Wall -c -fmessage-length=0 -std=c++11 -Wno-misleading-indentation -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-libs-2f-caes-2f-AudioFile

clean-src-2f-libs-2f-caes-2f-AudioFile:
	-$(RM) ./src/libs/caes/AudioFile/AudioFiler.d ./src/libs/caes/AudioFile/AudioFiler.o ./src/libs/caes/AudioFile/CtlAudMsg.d ./src/libs/caes/AudioFile/CtlAudMsg.o ./src/libs/caes/AudioFile/NumSys.d ./src/libs/caes/AudioFile/NumSys.o ./src/libs/caes/AudioFile/RiffCk.d ./src/libs/caes/AudioFile/RiffCk.o ./src/libs/caes/AudioFile/RiffMgr.d ./src/libs/caes/AudioFile/RiffMgr.o ./src/libs/caes/AudioFile/Signal.d ./src/libs/caes/AudioFile/Signal.o ./src/libs/caes/AudioFile/WaveFiler.d ./src/libs/caes/AudioFile/WaveFiler.o ./src/libs/caes/AudioFile/WaveFmt.d ./src/libs/caes/AudioFile/WaveFmt.o ./src/libs/caes/AudioFile/WaveGUID.d ./src/libs/caes/AudioFile/WaveGUID.o

.PHONY: clean-src-2f-libs-2f-caes-2f-AudioFile

