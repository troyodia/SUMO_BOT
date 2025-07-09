.PHONY: all clean flash cppcheck format
######################################
# target
######################################
TARGET = SUMO_ROBOT


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
CPPCHECK = cppcheck 
FORMAT = clang-format
CPPCHECK_INCLUDES = \
	./Src/app \
	./Src/common \
	./Src/drivers \
	./Src/test


CPPCHECK_FLAGS = \
	--quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude \
	--suppress=unmatchedSuppression \
	--suppress=unusedFunction \
	$(addprefix -I,$(CPPCHECK_INCLUDES)) 	


######################################
# source
######################################
# C sources
C_SOURCES =  \
	Src/main.c \
	Src/app/drive.c \
	Src/app/enemy.c \
	Src/drivers/io.c \
	Src/drivers/mcu_init.c \
	Src/drivers/led.c \
	Src/common/assert_handler.c \
	Src/system_stm32l4xx.c \

C_SOURCES_WITH_HEADERS = \
	Src/app/drive.c \
	Src/app/enemy.c \
	Src/drivers/io.c \
	Src/drivers/mcu_init.c \
	Src/drivers/led.c \
	Src/common/assert_handler.c \

CPP_CHECK_C_SOURCES =  \
	Src/main.c \
	$(C_SOURCES_WITH_HEADERS) \

HEADERS = \
	$(C_SOURCES_WITH_HEADERS:.c=.h) \
	Src/common/defines.h \

# ASM sources
ASM_SOURCES =  \
	Startup/startup_stm32l476rgtx.s

# ASM sources
ASMM_SOURCES = 


#######################################
# binaries
#######################################
GCC_DIR = $(GCC_PATH)
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_DIR variable (> make GCC_DIR=xxx)
# The gcc compiler bin path can be either defined in make command via GCC_DIR variable (> make GCC_DIR=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_DIR
CC = $(GCC_DIR)/$(PREFIX)gcc
AS = $(GCC_DIR)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_DIR)/$(PREFIX)objcopy
SZ = $(GCC_DIR)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
# HEX = $(CP) -O ihex
# BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
  
# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32L476xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
	Drivers/CMSIS/Device/ST/STM32L4xx/Include \
	Drivers/CMSIS/Include \
	Src/app \
	Src/common \
	Src/drivers \
	Src/test \
	external/printf \



# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(addprefix -I,$(C_INCLUDES)) $(OPT) -Wall -Wextra -Werror -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32L476RGTX_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,--gc-sections

# default action: build all
all: $(BIN_DIR)/$(TARGET).elf 


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(OBJ_DIR)/, $(C_SOURCES:.c=.o))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(OBJ_DIR)/,$(ASM_SOURCES:.s=.o))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(OBJ_DIR)/,$(ASMM_SOURCES:.S=.o))
vpath %.S $(sort $(dir $(ASMM_SOURCES)))
	

$(OBJ_DIR)/%.o: %.c Makefile 
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.s Makefile
	@mkdir -p $(dir $@)
	$(AS) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.S Makefile
	@mkdir -p $(dir $@)
	$(AS) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/$(TARGET).elf: $(OBJECTS) $(HEADERS) 
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@
	$(SZ) $@

	
#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
# openocd
#######################################
flash: all
	openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program $(BIN_DIR)/$(TARGET).elf verify reset exit"
#######################################
cppcheck: 
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(CPP_CHECK_C_SOURCES)
#######################################
format:
	@$(FORMAT) -i $(C_SOURCES) $(HEADERS)
# *** EOF ***