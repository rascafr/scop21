################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/middleware/webserver/lwip/src/netif/ppp/subdir.mk
-include lib/middleware/webserver/lwip/src/netif/subdir.mk
-include lib/middleware/webserver/lwip/src/core/snmp/subdir.mk
-include lib/middleware/webserver/lwip/src/core/ipv4/subdir.mk
-include lib/middleware/webserver/lwip/src/core/subdir.mk
-include lib/middleware/webserver/lwip/src/api/subdir.mk
-include lib/middleware/webserver/lwip/subdir.mk
-include lib/middleware/webserver/subdir.mk
-include lib/middleware/usb_host/Core/Src/subdir.mk
-include lib/middleware/usb_host/Class/MSC/Src/subdir.mk
-include lib/middleware/FatFs/src/drivers/subdir.mk
-include lib/middleware/FatFs/src/subdir.mk
-include lib/hal/src/subdir.mk
-include lib/bsp/stmpe811/subdir.mk
-include lib/bsp/ov9655/subdir.mk
-include lib/bsp/lis3dsh/subdir.mk
-include lib/bsp/lis302dl/subdir.mk
-include lib/bsp/lcd2x16/subdir.mk
-include lib/bsp/audio/subdir.mk
-include lib/bsp/MatrixKeyboard/subdir.mk
-include lib/bsp/LCD/subdir.mk
-include lib/bsp/subdir.mk
-include lib/subdir.mk
-include appli/mylibs/subdir.mk
-include appli/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: projet-oscillo-numerique.elf

# Tool invocations
projet-oscillo-numerique.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -T"../lib/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "projet-oscillo-numerique.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "projet-oscillo-numerique.elf" "projet-oscillo-numerique.bin"
	arm-none-eabi-size "projet-oscillo-numerique.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
