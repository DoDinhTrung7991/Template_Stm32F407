#----------	INCLUDE_START	----------#
include prj_info.mk
include ../Source/Algorithm/module.mk
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
LDFLAGS = -mcpu=cortex-m4 -mthumb -Wall -T $(SRC_PATH)Linker/linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_RESULT_PATH)final.map
OBJ_LIST = \
	$(STATIC_INIT_OBJ_PATH)init_static.o \
	$(CONFIG_INIT_OBJ_PATH)init.o \
	$(INTERRUPT_OBJ_PATH)Interrupt.o \
	$(GPIO_OBJ_PATH)GPIO.o \
	$(TIMER_OBJ_PATH)Timer_Init.o \
	$(TIMER_OBJ_PATH)PWM.o \
	$(Communication_OBJ_PATH)$(UART_DIR)UART.o \
	$(CONTROL_OBJ_PATH)main.o \
	$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6.o \
	$(QUEUE_OBJ_PATH)queue.o

CFLAGS_GDB = -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 -ffunction-sections -fdata-sections -Wall -ggdb
LDFLAGS_GDB = -mcpu=cortex-m4 -mthumb -Wall -T $(SRC_PATH)Linker/linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_RESULT_PATH)final_gdb.map -ggdb
OBJ_LIST_GDB = \
	$(STATIC_INIT_OBJ_PATH)init_static_gdb.o \
	$(CONFIG_INIT_OBJ_PATH)init_gdb.o \
	$(INTERRUPT_OBJ_PATH)Interrupt_gdb.o \
	$(GPIO_OBJ_PATH)GPIO_gdb.o \
	$(TIMER_OBJ_PATH)Timer_Init_gdb.o \
	$(TIMER_OBJ_PATH)PWM_gdb.o \
	$(Communication_OBJ_PATH)$(UART_DIR)UART_gdb.o \
	$(CONTROL_OBJ_PATH)main_gdb.o \
	$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6_gdb.o \
	$(QUEUE_OBJ_PATH)queue_gdb.o
#----------	MACRO_END	----------#

#----------	MODULE_START	----------#
all: elf
	arm-none-eabi-objcopy -O binary $(BUILD_RESULT_PATH)/Hexapod_Robot.elf $(BUILD_RESULT_PATH)/Hexapod_Robot.bin
	@printf "Convert elf to bin done!!!\r\n"

elf: objects
	$(CC) $(LDFLAGS) -o $(BUILD_RESULT_PATH)/Hexapod_Robot.elf $(OBJ_LIST)
	@printf "Elf file created!!!\r\n"

objects: Driver_Init Interrupt GPIO Timer Control Communication StartupCode Algorithm
	@printf "Build objects done!!!\r\n"

Driver_Init: $(STATIC_INIT_OBJ_PATH)init_static.o $(CONFIG_INIT_OBJ_PATH)init.o
	@printf "Build Driver_Init done!!!\r\n\r\n"
Interrupt: $(INTERRUPT_OBJ_PATH)Interrupt.o
	@printf "Build Interrupt done!!!\r\n\r\n"
GPIO: $(GPIO_OBJ_PATH)GPIO.o
	@printf "Build GPIO done!!!\r\n\r\n"
Timer: $(TIMER_OBJ_PATH)Timer_Init.o $(TIMER_OBJ_PATH)PWM.o
	@printf "Build Timer done!!!\r\n\r\n"
Communication: $(Communication_OBJ_PATH)$(UART_DIR)UART.o
	@printf "Build Communication done!!!\r\n\r\n"
Control: $(CONTROL_OBJ_PATH)main.o
	@printf "Build Control done!!!\r\n\r\n"
StartupCode: $(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6.o
	@printf "Build StartupCode done!!!\r\n\r\n"
Algorithm: $(QUEUE_OBJ_PATH)queue.o
	@printf "Build Algorithm done!!!\r\n\r\n"

$(STATIC_INIT_OBJ_PATH)init_static.o: $(STATIC_INIT_PATH)init_static.c
	mkdir -p $(STATIC_INIT_OBJ_PATH)
	$(CC) $(CFLAGS) $(STATIC_INIT_INC) -o $@ $^
	@printf "\r\n"

$(CONFIG_INIT_OBJ_PATH)init.o: $(CONFIG_INIT_PATH)init.c
	mkdir -p $(CONFIG_INIT_OBJ_PATH)
	$(CC) $(CFLAGS) $(CONFIG_INIT_INC) -o $@ $^
	@printf "\r\n"

$(TIMER_OBJ_PATH)Timer_Init.o: $(TIMER_PATH)Timer_Init.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS) $(TIMER_INC) -o $@ $^
	@printf "\r\n"

$(TIMER_OBJ_PATH)PWM.o: $(PWM_PATH)/PWM.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS) $(TIMER_INC) -o $@ $^
	@printf "\r\n"

$(INTERRUPT_OBJ_PATH)Interrupt.o: $(INTERRUPT_PATH)Interrupt.c
	mkdir -p $(INTERRUPT_OBJ_PATH)
	$(CC) $(CFLAGS) $(INTERRUPT_INC) -o $@ $^
	@printf "\r\n"

$(GPIO_OBJ_PATH)GPIO.o: $(GPIO_PATH)GPIO.c
	mkdir -p $(GPIO_OBJ_PATH)
	$(CC) $(CFLAGS) $(GPIO_INC) -o $@ $^
	@printf "\r\n"

$(Communication_OBJ_PATH)$(UART_DIR)UART.o: $(UART_PATH)UART.c
	mkdir -p $(Communication_OBJ_PATH)$(UART_DIR)
	$(CC) $(CFLAGS) $(Communication_INC) -o $@ $^
	@printf "\r\n"

$(CONTROL_OBJ_PATH)main.o: $(CONTROL_PATH)main.c
	mkdir -p $(CONTROL_OBJ_PATH)
	$(CC) $(CFLAGS) $(CONTROL_INC) -o $@ $^
	@printf "\r\n"

$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6.o: $(STARTUP_CODE_PATH)startup__stm32f407vet6.c
	mkdir -p $(STARTUP_CODE_OBJ_PATH)
	$(CC) $(CFLAGS) $(STARTUP_CODE_INC) -o $@ $^
	@printf "\r\n"

$(QUEUE_OBJ_PATH)queue.o: $(QUEUE_PATH)queue.c
	mkdir -p $(QUEUE_OBJ_PATH)
	$(CC) $(CFLAGS) $(QUEUE_INC) -o $@ $^
	@printf "\r\n"
#----------	MODULE_END		----------#

#----------	MODULE_DEBUG_START	----------#
all_gdb: elf_gdb
	arm-none-eabi-objcopy -O binary $(BUILD_RESULT_PATH)/Hexapod_Robot_gdb.elf $(BUILD_RESULT_PATH)/Hexapod_Robot_gdb.bin
	@printf "Convert elf to bin done!!!\r\n"

elf_gdb: objects_gdb
	$(CC) $(LDFLAGS_GDB) -o $(BUILD_RESULT_PATH)/Hexapod_Robot_gdb.elf $(OBJ_LIST_GDB)
	@printf "Elf file created!!!\r\n"

objects_gdb: Driver_Init_gdb Interrupt_gdb GPIO_gdb Timer_gdb Control_gdb Communication_gdb StartupCode_gdb Algorithm_gdb
	@printf "Build objects done!!!\r\n"

Driver_Init_gdb: $(STATIC_INIT_OBJ_PATH)init_static_gdb.o $(CONFIG_INIT_OBJ_PATH)init_gdb.o
	@printf "Build Driver_Init_gdb done!!!\r\n\r\n"
Interrupt_gdb: $(INTERRUPT_OBJ_PATH)Interrupt_gdb.o
	@printf "Build Interrupt_gdb done!!!\r\n\r\n"
GPIO_gdb: $(GPIO_OBJ_PATH)GPIO_gdb.o
	@printf "Build GPIO_gdb done!!!\r\n\r\n"
Timer_gdb: $(TIMER_OBJ_PATH)Timer_Init_gdb.o $(TIMER_OBJ_PATH)PWM_gdb.o
	@printf "Build Timer_gdb done!!!\r\n\r\n"
Communication_gdb: $(Communication_OBJ_PATH)$(UART_DIR)UART_gdb.o
	@printf "Build Communication_gdb done!!!\r\n\r\n"
Control_gdb: $(CONTROL_OBJ_PATH)main_gdb.o
	@printf "Build Control_gdb done!!!\r\n\r\n"
StartupCode_gdb: $(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6_gdb.o
	@printf "Build StartupCode_gdb done!!!\r\n\r\n"
Algorithm_gdb: $(QUEUE_OBJ_PATH)queue_gdb.o
	@printf "Build Algorithm_gdb done!!!\r\n\r\n"

$(STATIC_INIT_OBJ_PATH)init_static_gdb.o: $(STATIC_INIT_PATH)init_static.c
	mkdir -p $(STATIC_INIT_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(STATIC_INIT_INC) -o $@ $^
	@printf "\r\n"

$(CONFIG_INIT_OBJ_PATH)init_gdb.o: $(CONFIG_INIT_PATH)init.c
	mkdir -p $(CONFIG_INIT_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(CONFIG_INIT_INC) -o $@ $^
	@printf "\r\n"

$(TIMER_OBJ_PATH)Timer_Init_gdb.o: $(TIMER_PATH)Timer_Init.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(TIMER_INC) -o $@ $^
	@printf "\r\n"

$(TIMER_OBJ_PATH)PWM_gdb.o: $(PWM_PATH)/PWM.c
	mkdir -p $(TIMER_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(TIMER_INC) -o $@ $^
	@printf "\r\n"

$(INTERRUPT_OBJ_PATH)Interrupt_gdb.o: $(INTERRUPT_PATH)Interrupt.c
	mkdir -p $(INTERRUPT_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(INTERRUPT_INC) -o $@ $^
	@printf "\r\n"

$(GPIO_OBJ_PATH)GPIO_gdb.o: $(GPIO_PATH)GPIO.c
	mkdir -p $(GPIO_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(GPIO_INC) -o $@ $^
	@printf "\r\n"

$(Communication_OBJ_PATH)$(UART_DIR)UART_gdb.o: $(UART_PATH)UART.c
	mkdir -p $(Communication_OBJ_PATH)$(UART_DIR)
	$(CC) $(CFLAGS_GDB) $(Communication_INC) -o $@ $^
	@printf "\r\n"

$(CONTROL_OBJ_PATH)main_gdb.o: $(CONTROL_PATH)main.c
	mkdir -p $(CONTROL_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(CONTROL_INC) -o $@ $^
	@printf "\r\n"

$(STARTUP_CODE_OBJ_PATH)startup__stm32f407vet6_gdb.o: $(STARTUP_CODE_PATH)startup__stm32f407vet6.c
	mkdir -p $(STARTUP_CODE_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(STARTUP_CODE_INC) -o $@ $^
	@printf "\r\n"

$(QUEUE_OBJ_PATH)queue_gdb.o: $(QUEUE_PATH)queue.c
	mkdir -p $(QUEUE_OBJ_PATH)
	$(CC) $(CFLAGS_GDB) $(QUEUE_INC) -o $@ $^
	@printf "\r\n"
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

# gdb-multiarch Hexapod_Robot_gdb.elf
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
