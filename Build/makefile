#----------	INCLUDE_START	----------#
include prj_info.mk
include ../Source/Driver/Static/Driver_Init/module.mk
include ../Source/Driver/Config/Driver_Init/module.mk
include ../Source/Driver/Config/Timer/module.mk
include ../Source/Driver/Config/Interrupt/module.mk
include ../Source/Driver/Config/GPIO/module.mk
include ../Source/Driver/Config/Communication/module.mk
include ../Source/Control/module.mk
include ../Source/StartupCode/module.mk
#----------	INCLUDE_END		----------#

#----------	MACRO_START	----------#
CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 -ffunction-sections -fdata-sections -Wall
LDFLAGS = -Wall -nostdlib -T $(SRC_PATH)Linker/linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_RESULT_PATH)final.map
OBJ_LIST = \
	$(STATIC_INIT_OBJ_PATH)init_static.o \
	$(CONFIG_INIT_OBJ_PATH)init.o \
	$(INTERRUPT_OBJ_PATH)Interrupt.o \
	$(GPIO_OBJ_PATH)GPIO.o \
	$(TIMER_OBJ_PATH)Timer_Init.o \
	$(TIMER_OBJ_PATH)PWM.o \
	$(Communication_OBJ_PATH)$(UART_DIR)UART.o \
	$(CONTROL_OBJ_PATH)main.o \
	$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6.o

CFLAGS_GDB = -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 -ffunction-sections -fdata-sections -Wall -ggdb
LDFLAGS_GDB = -Wall -nostdlib -T $(SRC_PATH)Linker/linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_RESULT_PATH)final_gdb.map -ggdb
OBJ_LIST_GDB = \
	$(STATIC_INIT_OBJ_PATH)init_static_gdb.o \
	$(CONFIG_INIT_OBJ_PATH)init_gdb.o \
	$(INTERRUPT_OBJ_PATH)Interrupt_gdb.o \
	$(GPIO_OBJ_PATH)GPIO_gdb.o \
	$(TIMER_OBJ_PATH)Timer_Init_gdb.o \
	$(TIMER_OBJ_PATH)PWM_gdb.o \
	$(Communication_OBJ_PATH)$(UART_DIR)UART_gdb.o \
	$(CONTROL_OBJ_PATH)main_gdb.o \
	$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6_gdb.o
#----------	MACRO_END	----------#

#----------	MODULE_START	----------#
all: elf
	arm-none-eabi-objcopy -O binary $(BUILD_RESULT_PATH)/Hexapod_Robot.elf $(BUILD_RESULT_PATH)/Hexapod_Robot.bin

elf: objects
	$(CC) $(LDFLAGS) -o $(BUILD_RESULT_PATH)/Hexapod_Robot.elf $(OBJ_LIST)

objects: Driver_Init Interrupt GPIO Timer Control Communication StartupCode

Driver_Init: $(STATIC_INIT_OBJ_PATH)init_static.o $(CONFIG_INIT_OBJ_PATH)init.o
Interrupt: $(INTERRUPT_OBJ_PATH)Interrupt.o
GPIO: $(GPIO_OBJ_PATH)GPIO.o
Timer: $(TIMER_OBJ_PATH)Timer_Init.o $(TIMER_OBJ_PATH)PWM.o
Communication: $(Communication_OBJ_PATH)$(UART_DIR)UART.o
Control: $(CONTROL_OBJ_PATH)main.o
StartupCode: $(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6.o

$(STATIC_INIT_OBJ_PATH)init_static.o: $(STATIC_INIT_PATH)init_static.c
	mkdir -p $(STATIC_INIT_OBJ_PATH)
	$(CC) $(CFLAGS) $(STATIC_INIT_INC) -o $@ $^

$(CONFIG_INIT_OBJ_PATH)init.o: $(CONFIG_INIT_PATH)init.c
	mkdir -p $(CONFIG_INIT_OBJ_PATH)
	$(CC) $(CFLAGS) $(CONFIG_INIT_INC) -o $@ $^

$(TIMER_OBJ_PATH)Timer_Init.o: $(TIMER_PATH)Timer_Init.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS) $(TIMER_INC) -o $@ $^

$(TIMER_OBJ_PATH)PWM.o: $(PWM_PATH)/PWM.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS) $(TIMER_INC) -o $@ $^

$(INTERRUPT_OBJ_PATH)Interrupt.o: $(INTERRUPT_PATH)Interrupt.c
	mkdir -p $(INTERRUPT_OBJ_PATH)
	$(CC) $(CFLAGS) $(INTERRUPT_INC) -o $@ $^

$(GPIO_OBJ_PATH)GPIO.o: $(GPIO_PATH)GPIO.c
	mkdir -p $(GPIO_OBJ_PATH)
	$(CC) $(CFLAGS) $(GPIO_INC) -o $@ $^

$(Communication_OBJ_PATH)$(UART_DIR)UART.o: $(UART_PATH)UART.c
	mkdir -p $(Communication_OBJ_PATH)$(UART_DIR)
	$(CC) $(CFLAGS) $(Communication_INC) -o $@ $^

$(CONTROL_OBJ_PATH)main.o: $(CONTROL_PATH)main.c
	mkdir -p $(CONTROL_OBJ_PATH)
	$(CC) $(CFLAGS) $(CONTROL_INC) -o $@ $^

$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6.o: $(STARTUP_CODE_PATH)startup__stm32f407vet6.c
	mkdir -p $(STARTUP_CODE_OBJ_PATH)
	$(CC) $(CFLAGS) $(STARTUP_CODE_INC) -o $@ $^
#----------	MODULE_END		----------#

#----------	MODULE_DEBUG_START	----------#
all_gdb: elf_gdb
	arm-none-eabi-objcopy -O binary $(BUILD_RESULT_PATH)/Hexapod_Robot_gdb.elf $(BUILD_RESULT_PATH)/Hexapod_Robot_gdb.bin

elf_gdb: objects_gdb
	$(CC) $(LDFLAGS_GDB) -o $(BUILD_RESULT_PATH)/Hexapod_Robot_gdb.elf $(OBJ_LIST_GDB)

objects_gdb: Driver_Init_gdb Interrupt_gdb GPIO_gdb Timer_gdb Control_gdb Communication_gdb StartupCode_gdb

Driver_Init_gdb: $(STATIC_INIT_OBJ_PATH)init_static_gdb.o $(CONFIG_INIT_OBJ_PATH)init_gdb.o
Interrupt_gdb: $(INTERRUPT_OBJ_PATH)Interrupt_gdb.o
GPIO_gdb: $(GPIO_OBJ_PATH)GPIO_gdb.o
Timer_gdb: $(TIMER_OBJ_PATH)Timer_Init_gdb.o $(TIMER_OBJ_PATH)PWM_gdb.o
Communication_gdb: $(Communication_OBJ_PATH)$(UART_DIR)UART_gdb.o
Control_gdb: $(CONTROL_OBJ_PATH)main_gdb.o
StartupCode_gdb: $(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6_gdb.o

$(STATIC_INIT_OBJ_PATH)init_static_gdb.o: $(STATIC_INIT_PATH)init_static.c
	mkdir -p $(STATIC_INIT_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(STATIC_INIT_INC) -o $@ $^

$(CONFIG_INIT_OBJ_PATH)init_gdb.o: $(CONFIG_INIT_PATH)init.c
	mkdir -p $(CONFIG_INIT_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(CONFIG_INIT_INC) -o $@ $^

$(TIMER_OBJ_PATH)Timer_Init_gdb.o: $(TIMER_PATH)Timer_Init.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(TIMER_INC) -o $@ $^

$(TIMER_OBJ_PATH)PWM_gdb.o: $(PWM_PATH)/PWM.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(TIMER_INC) -o $@ $^

$(INTERRUPT_OBJ_PATH)Interrupt_gdb.o: $(INTERRUPT_PATH)Interrupt.c
	mkdir -p $(INTERRUPT_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(INTERRUPT_INC) -o $@ $^

$(GPIO_OBJ_PATH)GPIO_gdb.o: $(GPIO_PATH)GPIO.c
	mkdir -p $(GPIO_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(GPIO_INC) -o $@ $^

$(Communication_OBJ_PATH)$(UART_DIR)UART_gdb.o: $(UART_PATH)UART.c
	mkdir -p $(Communication_OBJ_PATH)$(UART_DIR)
	$(CC) $(CFLAGS_GDB) $(Communication_INC) -o $@ $^

$(CONTROL_OBJ_PATH)main_gdb.o: $(CONTROL_PATH)main.c
	mkdir -p $(CONTROL_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(CONTROL_INC) -o $@ $^

$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6_gdb.o: $(STARTUP_CODE_PATH)startup__stm32f407vet6.c
	mkdir -p $(STARTUP_CODE_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(STARTUP_CODE_INC) -o $@ $^
#----------	MODULE_DEBUG_END		----------#

#----------	FLASH_AND_DEBUG_START	----------#
clean: $(BUILD_RESULT_PATH)
	rm -rf $(BUILD_RESULT_PATH)*

erase:
	st-flash erase

flash: $(BUILD_RESULT_PATH)Hexapod_Robot.bin
	st-flash write $(BUILD_RESULT_PATH)Hexapod_Robot.bin 0x08000000

debug: $(BUILD_RESULT_PATH)Hexapod_Robot_gdb.elf
	openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg

# gdb-multiarch Hexapod_Robot.elf
# 	target extended-remote :3333	#Connect to stlink port 3333
# 	monitor reset halt				#Reset and halt
# 	load							# Nạp chương trình vào Flash của STM32.
# 	break function
# 	continue
# 	next: Chạy dòng tiếp theo (không nhảy vào hàm).
# 	step: Nhảy vào bên trong hàm.
# 	print variable_name
# 	info registers: Xem giá trị các thanh ghi CPU.
# 	quit: Thoát khỏi gdb
# 	break main.c:55       # Dòng 55 của file main.c
# 	break *0x08000abc     # Set breakpoint theo địa chỉ bộ nhớ
# 	break main.c:55 if temp > 30 # Set breakpoint có điều kiện
# 	condition 1 counter == 100 # Add condition to available breakpoint
# 	disable [ID]	Tạm thời vô hiệu hóa breakpoint nhưng không xóa
# 	enable [ID]	Kích hoạt lại breakpoint đã bị disable
# 	delete [ID]	Xóa breakpoint
# 	info breakpoints: Xem danh sách breakpoint
# 	info source: xem địa chỉ source và flags build
# 	symbol-file your_project.elf  # Đảm bảo GDB đã nạp symbol
# 	info functions: Kiểm tra cấu trúc File ELF
#	directory: Xóa toàn bộ danh sách để làm lại từ đầu
#----------	FLASH_AND_DEBUG_END	----------#
