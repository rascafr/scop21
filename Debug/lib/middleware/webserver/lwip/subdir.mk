################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/middleware/webserver/lwip/fs.c \
../lib/middleware/webserver/lwip/fsdata.c \
../lib/middleware/webserver/lwip/httpd.c \
../lib/middleware/webserver/lwip/httpd_cgi_ssi.c \
../lib/middleware/webserver/lwip/netconf.c \
../lib/middleware/webserver/lwip/stm32f4x7_eth.c \
../lib/middleware/webserver/lwip/stm32f4x7_eth_bsp.c \
../lib/middleware/webserver/lwip/tcp_echoclient.c 

OBJS += \
./lib/middleware/webserver/lwip/fs.o \
./lib/middleware/webserver/lwip/fsdata.o \
./lib/middleware/webserver/lwip/httpd.o \
./lib/middleware/webserver/lwip/httpd_cgi_ssi.o \
./lib/middleware/webserver/lwip/netconf.o \
./lib/middleware/webserver/lwip/stm32f4x7_eth.o \
./lib/middleware/webserver/lwip/stm32f4x7_eth_bsp.o \
./lib/middleware/webserver/lwip/tcp_echoclient.o 

C_DEPS += \
./lib/middleware/webserver/lwip/fs.d \
./lib/middleware/webserver/lwip/fsdata.d \
./lib/middleware/webserver/lwip/httpd.d \
./lib/middleware/webserver/lwip/httpd_cgi_ssi.d \
./lib/middleware/webserver/lwip/netconf.d \
./lib/middleware/webserver/lwip/stm32f4x7_eth.d \
./lib/middleware/webserver/lwip/stm32f4x7_eth_bsp.d \
./lib/middleware/webserver/lwip/tcp_echoclient.d 


# Each subdirectory must supply rules for building sources it contributes
lib/middleware/webserver/lwip/%.o: ../lib/middleware/webserver/lwip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -I../appli -I../lib/hal/inc -I../lib/bsp -I../lib/bsp/Common -I../lib/bsp/lcd2x16 -I../lib/bsp/MatrixKeyboard -I../lib/bsp/lis302dl -I../lib/bsp/lis3dsh -I../lib/bsp/audio -I../lib/bsp/ov9655 -I../lib/bsp/stmpe811 -I../lib/bsp/LCD -I../lib/middleware/ -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I../lib/middleware/webserver -I../lib/middleware/webserver/lwip -I../lib/middleware/webserver/lwip/src/include -I../lib/middleware/webserver/lwip/system -I../lib/middleware/webserver/lwip/src/include/ipv4 -I../lib/middleware/webserver/lwip/src/include/lwip -I../lib/middleware/webserver/lwip/port -I../lib/middleware/webserver/STD_lib -I../lib/middleware/usb_device/Class/HID/Inc -I../lib/middleware/usb_device/Class/MSC/Inc -I../lib/middleware/usb_device/Core/Inc -I../lib/middleware/usb_host/Class/MSC/Inc -I../lib/middleware/usb_host/Core/Inc -I../lib/middleware/PDM -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


