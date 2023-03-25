################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/libs/pcg/test-high/subdir.mk
-include src/libs/pcg/sample/subdir.mk
-include src/libs/caes/AudioFile/subdir.mk
-include src/libs/caes/subdir.mk
-include src/GUI/subdir.mk
-include src/Ctl/subdir.mk
-include src/Cfg/subdir.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := rutile
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory pre-build && $(MAKE) --no-print-directory main-build

# Main-build Target
main-build: rutile

# Tool invocations
rutile: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -no-pie -o "rutile" $(OBJS) $(USER_OBJS) $(LIBS) -lgtkmm-3.0 -lgtk-3 -lgdkmm-3.0 -latkmm-1.6 -lglibmm-2.4 -lcairomm-1.0 -lpangomm-1.4 -lsigc-2.0 -lgsl -lgslcblas
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) rutile
	-@echo ' '

pre-build:
	-svnmark ../src/Cfg/CfgVersion.hpp
	-@echo ' '

.PHONY: all clean dependents main-build pre-build

-include ../makefile.targets
