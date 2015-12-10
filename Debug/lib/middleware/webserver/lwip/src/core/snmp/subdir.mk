################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/middleware/webserver/lwip/src/core/snmp/asn1_dec.c \
../lib/middleware/webserver/lwip/src/core/snmp/asn1_enc.c \
../lib/middleware/webserver/lwip/src/core/snmp/mib2.c \
../lib/middleware/webserver/lwip/src/core/snmp/mib_structs.c \
../lib/middleware/webserver/lwip/src/core/snmp/msg_in.c \
../lib/middleware/webserver/lwip/src/core/snmp/msg_out.c 

OBJS += \
./lib/middleware/webserver/lwip/src/core/snmp/asn1_dec.o \
./lib/middleware/webserver/lwip/src/core/snmp/asn1_enc.o \
./lib/middleware/webserver/lwip/src/core/snmp/mib2.o \
./lib/middleware/webserver/lwip/src/core/snmp/mib_structs.o \
./lib/middleware/webserver/lwip/src/core/snmp/msg_in.o \
./lib/middleware/webserver/lwip/src/core/snmp/msg_out.o 

C_DEPS += \
./lib/middleware/webserver/lwip/src/core/snmp/asn1_dec.d \
./lib/middleware/webserver/lwip/src/core/snmp/asn1_enc.d \
./lib/middleware/webserver/lwip/src/core/snmp/mib2.d \
./lib/middleware/webserver/lwip/src/core/snmp/mib_structs.d \
./lib/middleware/webserver/lwip/src/core/snmp/msg_in.d \
./lib/middleware/webserver/lwip/src/core/snmp/msg_out.d 


# Each subdirectory must supply rules for building sources it contributes
lib/middleware/webserver/lwip/src/core/snmp/%.o: ../lib/middleware/webserver/lwip/src/core/snmp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -I../appli -I../lib/hal/inc -I../lib/bsp -I../lib/bsp/Common -I../lib/bsp/lcd2x16 -I../lib/bsp/MatrixKeyboard -I../lib/bsp/lis302dl -I../lib/bsp/lis3dsh -I../lib/bsp/audio -I../lib/bsp/ov9655 -I../lib/bsp/stmpe811 -I../lib/bsp/LCD -I../lib/middleware/ -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I../lib/middleware/webserver -I../lib/middleware/webserver/lwip -I../lib/middleware/webserver/lwip/src/include -I../lib/middleware/webserver/lwip/system -I../lib/middleware/webserver/lwip/src/include/ipv4 -I../lib/middleware/webserver/lwip/src/include/lwip -I../lib/middleware/webserver/lwip/port -I../lib/middleware/webserver/STD_lib -I../lib/middleware/usb_device/Class/HID/Inc -I../lib/middleware/usb_device/Class/MSC/Inc -I../lib/middleware/usb_device/Core/Inc -I../lib/middleware/usb_host/Class/MSC/Inc -I../lib/middleware/usb_host/Core/Inc -I../lib/middleware/PDM -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


