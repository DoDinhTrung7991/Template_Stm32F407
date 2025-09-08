UART_MODULE = UART
Communication_PATH = $(PRJ_PATH)Driver/Config/Communication/
UART_PATH = $(Communication_PATH)$(UART_MODULE)/
Communication_OBJ_PATH = $(BUILD_RESULT_PATH_DRIVER)Communication/
Communication_INC = \
	-I$(UART_PATH) \
	-I$(GPIO_PATH) \
	-I$(STATIC_INIT_PATH) \
	-I$(STATIC_INIT_PATH)../Registers \
	-I$(STATIC_INIT_PATH)../Other_headers \
	-I$(INTERRUPT_PATH)
