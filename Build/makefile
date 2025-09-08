#----------	INCLUDE_START	----------#
include prj_info.mk
include ../Driver/Static/Driver_Init/module.mk
include ../Driver/Config/Driver_Init/module.mk
include ../Driver/Config/Timer/module.mk
include ../Driver/Config/Interrupt/module.mk
include ../Driver/Config/GPIO/module.mk
include ../Driver/Config/Communication/module.mk
include ../Hardware_Abstraction/Control/module.mk
#----------	INCLUDE_END		----------#

#----------	MACRO_START	----------#
CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 -ffunction-sections -fdata-sections -Wall
LDFLAGS = -Wall -nostdlib -T ../Linker/linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_RESULT_PATH)/final.map
OBJ_LIST = \
	$(INTERRUPT_OBJ_PATH)stm32_startup.o \
	$(STATIC_INIT_OBJ_PATH)init_conf.o \
	$(CONFIG_INIT_OBJ_PATH)init.o \
	$(INTERRUPT_OBJ_PATH)Interrupt.o \
	$(GPIO_OBJ_PATH)GPIO.o \
	$(TIMER_OBJ_PATH)Timer_Init.o \
	$(TIMER_OBJ_PATH)PWM.o \
	$(Communication_OBJ_PATH)$(UART_MODULE)/UART.o \
	$(CONTROL_OBJ_PATH)main.o
#----------	MACRO_END	----------#

#----------	MODULE_START	----------#
all: elf
	arm-none-eabi-objcopy -O binary $(BUILD_RESULT_PATH)/Hexapod_Robot.elf $(BUILD_RESULT_PATH)/Hexapod_Robot.bin

elf: objects
	$(CC) $(LDFLAGS) -o $(BUILD_RESULT_PATH)/Hexapod_Robot.elf $(OBJ_LIST)

objects: Driver_Init Interrupt GPIO Timer Control Communication

Driver_Init: $(STATIC_INIT_OBJ_PATH)init_conf.o $(CONFIG_INIT_OBJ_PATH)init.o
Interrupt: $(INTERRUPT_OBJ_PATH)stm32_startup.o $(INTERRUPT_OBJ_PATH)Interrupt.o
GPIO: $(GPIO_OBJ_PATH)GPIO.o
Timer: $(TIMER_OBJ_PATH)Timer_Init.o $(TIMER_OBJ_PATH)PWM.o
Communication: $(Communication_OBJ_PATH)$(UART_MODULE)/UART.o
Control: $(CONTROL_OBJ_PATH)main.o

$(STATIC_INIT_OBJ_PATH)init_conf.o: $(STATIC_INIT_PATH)init_conf.c
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

$(INTERRUPT_OBJ_PATH)stm32_startup.o: $(INTERRUPT_PATH)stm32_startup.c
	mkdir -p $(INTERRUPT_OBJ_PATH)
	$(CC) $(CFLAGS) $(INTERRUPT_INC) -o $@ $^

$(INTERRUPT_OBJ_PATH)Interrupt.o: $(INTERRUPT_PATH)Interrupt.c
	mkdir -p $(INTERRUPT_OBJ_PATH)
	$(CC) $(CFLAGS) $(INTERRUPT_INC) -o $@ $^

$(GPIO_OBJ_PATH)GPIO.o: $(GPIO_PATH)GPIO.c
	mkdir -p $(GPIO_OBJ_PATH)
	$(CC) $(CFLAGS) $(GPIO_INC) -o $@ $^

$(Communication_OBJ_PATH)$(UART_MODULE)/UART.o: $(UART_PATH)UART.c
	mkdir -p $(Communication_OBJ_PATH)$(UART_MODULE)
	$(CC) $(CFLAGS) $(Communication_INC) -o $@ $^

$(CONTROL_OBJ_PATH)main.o: $(CONTROL_PATH)main.c
	mkdir -p $(CONTROL_OBJ_PATH)
	$(CC) $(CFLAGS) $(CONTROL_INC) -o $@ $^
#----------	MODULE_END		----------#

clean: $(BUILD_RESULT_PATH)
	rm -r $(BUILD_RESULT_PATH)*
