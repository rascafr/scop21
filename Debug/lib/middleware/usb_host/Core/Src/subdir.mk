################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/middleware/usb_host/Core/Src/usbh_conf.c \
../lib/middleware/usb_host/Core/Src/usbh_core.c \
../lib/middleware/usb_host/Core/Src/usbh_ctlreq.c \
../lib/middleware/usb_host/Core/Src/usbh_ioreq.c \
../lib/middleware/usb_host/Core/Src/usbh_pipes.c 

OBJS += \
./lib/middleware/usb_host/Core/Src/usbh_conf.o \
./lib/middleware/usb_host/Core/Src/usbh_core.o \
./lib/middleware/usb_host/Core/Src/usbh_ctlreq.o \
./lib/middleware/usb_host/Core/Src/usbh_ioreq.o \
./lib/middleware/usb_host/Core/Src/usbh_pipes.o 

C_DEPS += \
./lib/middleware/usb_host/Core/Src/usbh_conf.d \
./lib/middleware/usb_host/Core/Src/usbh_core.d \
./lib/middleware/usb_host/Core/Src/usbh_ctlreq.d \
./lib/middleware/usb_host/Core/Src/usbh_ioreq.d \
./lib/middleware/usb_host/Core/Src/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
lib/middleware/usb_host/Core/Src/%.o: ../lib/middleware/usb_host/Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -I../appli -I../lib/hal/inc -I../lib/bsp -I../lib/bsp/Common -I../lib/bsp/lcd2x16 -I../lib/bsp/MatrixKeyboard -I../lib/bsp/lis302dl -I../lib/bsp/lis3dsh -I../lib/bsp/audio -I../lib/bsp/ov9655 -I../lib/bsp/stmpe811 -I../lib/bsp/LCD -I../lib/middleware/ -I../lib/middleware/FatFs/src -I../lib/middleware/FatFs/src/drivers -I../lib/middleware/webserver -I../lib/middleware/webserver/lwip -I../lib/middleware/webserver/lwip/src/include -I../lib/middleware/webserver/lwip/system -I../lib/middleware/webserver/lwip/src/include/ipv4 -I../lib/middleware/webserver/lwip/src/include/lwip -I../lib/middleware/webserver/lwip/port -I../lib/middleware/webserver/STD_lib -I../lib/middleware/usb_device/Class/HID/Inc -I../lib/middleware/usb_device/Class/MSC/Inc -I../lib/middleware/usb_device/Core/Inc -I../lib/middleware/usb_host/Class/MSC/Inc -I../lib/middleware/usb_host/Core/Inc -I../lib/middleware/PDM -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


