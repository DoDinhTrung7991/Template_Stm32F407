UART_DIR = UART/
Communication_PATH = $(SRC_PATH)Driver/Config/Communication/
UART_PATH = $(Communication_PATH)$(UART_DIR)
Communication_OBJ_PATH = $(BUILD_RESULT_PATH_DRIVER)Communication/
Communication_INC = \
	-I$(UART_PATH) \
	-I$(GPIO_PATH) \
	-I$(STATIC_INIT_PATH) \
	-I$(STATIC_INIT_PATH)../Registers \
	-I$(STATIC_INIT_PATH)../General_headers \
	-I$(INTERRUPT_PATH)
