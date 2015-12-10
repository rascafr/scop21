################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/middleware/webserver/lwip/src/core/def.c \
../lib/middleware/webserver/lwip/src/core/dhcp.c \
../lib/middleware/webserver/lwip/src/core/dns.c \
../lib/middleware/webserver/lwip/src/core/init.c \
../lib/middleware/webserver/lwip/src/core/mem.c \
../lib/middleware/webserver/lwip/src/core/memp.c \
../lib/middleware/webserver/lwip/src/core/netif.c \
../lib/middleware/webserver/lwip/src/core/pbuf.c \
../lib/middleware/webserver/lwip/src/core/raw.c \
../lib/middleware/webserver/lwip/src/core/stats.c \
../lib/middleware/webserver/lwip/src/core/sys.c \
../lib/middleware/webserver/lwip/src/core/tcp.c \
../lib/middleware/webserver/lwip/src/core/tcp_in.c \
../lib/middleware/webserver/lwip/src/core/tcp_out.c \
../lib/middleware/webserver/lwip/src/core/timers.c \
../lib/middleware/webserver/lwip/src/core/udp.c 

OBJS += \
./lib/middleware/webserver/lwip/src/core/def.o \
./lib/middleware/webserver/lwip/src/core/dhcp.o \
./lib/middleware/webserver/lwip/src/core/dns.o \
./lib/middleware/webserver/lwip/src/core/init.o \
./lib/middleware/webserver/lwip/src/core/mem.o \
./lib/middleware/webserver/lwip/src/core/memp.o \
./lib/middleware/webserver/lwip/src/core/netif.o \
./lib/middleware/webserver/lwip/src/core/pbuf.o \
./lib/middleware/webserver/lwip/src/core/raw.o \
./lib/middleware/webserver/lwip/src/core/stats.o \
./lib/middleware/webserver/lwip/src/core/sys.o \
./lib/middleware/webserver/lwip/src/core/tcp.o \
./lib/middleware/webserver/lwip/src/core/tcp_in.o \
./lib/middleware/webserver/lwip/src/core/tcp_out.o \
./lib/middleware/webserver/lwip/src/core/timers.o \
./lib/middleware/webserver/lwip/src/core/udp.o 

C_DEPS += \
./lib/middleware/webserver/lwip/src/core/def.d \
./lib/middleware/webserver/lwip/src/core/dhcp.d \
./lib/middleware/webserver/lwip/src/core/dns.d \
./lib/middleware/webserver/lwip/src/core/init.d \
./lib/middleware/webserver/lwip/src/core/mem.d \
./lib/middleware/webserver/lwip/src/core/memp.d \
./lib/middleware/webserver/lwip/src/core/netif.d \
./lib/middleware/webserver/lwip/src/core/pbuf.d \
./lib/middleware/webserver/lwip/src/core/raw.d \
./lib/middleware/webserver/lwip/src/core/stats.d \
./lib/middleware/webserver/lwip/src/core/sys.d \
./lib/middleware/webserver/lwip/src/core/tcp.d \
./lib/middleware/webserver/lwip/src/core/tcp_in.d \
./lib/middleware/webserver/lwip/src/core/tcp_out.d \
./lib/middleware/webserver/lwip/src/core/timers.d \
./lib/middleware/webserver/lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
lib/middleware/webserver/lwip/src/core/%.o: ../lib/middleware/webserver/lwip/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -I../appli -I../lib/hal/inc -I../lib/bsp -I../lib/bsp/Common -I../lib/bsp/lcd2x16 -I../lib/bsp/MatrixKeyboard -I../lib/bsp/lis302dl -I../lib/bsp/lis3dsh -I../lib/bsp/audio -I../lib/bsp/ov9655 -I../lib/bsp/stmpe811 -I../lib/bsp/LCD -I../lib/middleware/ -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I../lib/middleware/webserver -I../lib/middleware/webserver/lwip -I../lib/middleware/webserver/lwip/src/include -I../lib/middleware/webserver/lwip/system -I../lib/middleware/webserver/lwip/src/include/ipv4 -I../lib/middleware/webserver/lwip/src/include/lwip -I../lib/middleware/webserver/lwip/port -I../lib/middleware/webserver/STD_lib -I../lib/middleware/usb_device/Class/HID/Inc -I../lib/middleware/usb_device/Class/MSC/Inc -I../lib/middleware/usb_device/Core/Inc -I../lib/middleware/usb_host/Class/MSC/Inc -I../lib/middleware/usb_host/Core/Inc -I../lib/middleware/PDM -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


