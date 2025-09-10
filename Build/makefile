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
LDFLAGS = -Wall -nostdlib -T ../Linker/linker.ld -Wl,--gc-sections -Wl,-Map=$(BUILD_RESULT_PATH)/final.map
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

clean: $(BUILD_RESULT_PATH)
	rm -rf $(BUILD_RESULT_PATH)*
