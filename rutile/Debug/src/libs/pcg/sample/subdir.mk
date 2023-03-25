################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/pcg/sample/codebook.cpp \
../src/libs/pcg/sample/cppref-sample.cpp \
../src/libs/pcg/sample/make-partytrick.cpp \
../src/libs/pcg/sample/pcg-demo.cpp \
../src/libs/pcg/sample/spew.cpp \
../src/libs/pcg/sample/use-partytrick.cpp 

CPP_DEPS += \
./src/libs/pcg/sample/codebook.d \
./src/libs/pcg/sample/cppref-sample.d \
./src/libs/pcg/sample/make-partytrick.d \
./src/libs/pcg/sample/pcg-demo.d \
./src/libs/pcg/sample/spew.d \
./src/libs/pcg/sample/use-partytrick.d 

OBJS += \
./src/libs/pcg/sample/codebook.o \
./src/libs/pcg/sample/cppref-sample.o \
./src/libs/pcg/sample/make-partytrick.o \
./src/libs/pcg/sample/pcg-demo.o \
./src/libs/pcg/sample/spew.o \
./src/libs/pcg/sample/use-partytrick.o 


# Each subdirectory must supply rules for building sources it contributes
src/libs/pcg/sample/%.o: ../src/libs/pcg/sample/%.cpp src/libs/pcg/sample/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/lib/arch/gtkmm-3.0/include -I/usr/lib/arch/gdkmm-3.0/include -I/usr/lib/arch/glib-2.0/include -I/usr/lib/arch/glibmm-2.4/include -I/usr/lib/arch/giomm-2.4/include -I/usr/lib/arch/pangomm-1.4/include -I/usr/lib/arch/cairomm-1.0/include -I/usr/lib/arch/sigc++-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/libpng -I/usr/include/gtkmm-3.0 -I/usr/include/gdkmm-3.0 -I/usr/include/glibmm-2.4 -I/usr/include/giomm-2.4 -I/usr/include/atkmm-1.6 -I/usr/include/pangomm-1.4 -I/usr/include/cairomm-1.0 -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/sigc++-2.0 -I/way/dev/SW/libs -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -Wno-misleading-indentation -Wno-unused-result -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-libs-2f-pcg-2f-sample

clean-src-2f-libs-2f-pcg-2f-sample:
	-$(RM) ./src/libs/pcg/sample/codebook.d ./src/libs/pcg/sample/codebook.o ./src/libs/pcg/sample/cppref-sample.d ./src/libs/pcg/sample/cppref-sample.o ./src/libs/pcg/sample/make-partytrick.d ./src/libs/pcg/sample/make-partytrick.o ./src/libs/pcg/sample/pcg-demo.d ./src/libs/pcg/sample/pcg-demo.o ./src/libs/pcg/sample/spew.d ./src/libs/pcg/sample/spew.o ./src/libs/pcg/sample/use-partytrick.d ./src/libs/pcg/sample/use-partytrick.o

.PHONY: clean-src-2f-libs-2f-pcg-2f-sample

