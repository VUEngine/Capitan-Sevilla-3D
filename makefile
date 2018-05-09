# Makefile taken from Wikipedia.org

# Default build type
TYPE = debug
#TYPE = release
#TYPE = beta
#TYPE = tools
#TYPE = preprocessor

# Where I live
GAME_HOME = $(shell pwd)
WORKING_FOLDER = $(GAME_HOME)/./$(BUILD_DIR)/compiler

# output dir
BUILD_DIR = build

# target's needed steps
ALL_TARGET_PREREQUISITES = dirs $(TARGET).vb $(PAD) $(DUMP_TARGET)

# compiler
COMPILER_VERSION = 4.7
COMPILER_OUTPUT = c
COMPILER_NAME = v810

GCC = $(COMPILER_NAME)-gcc
AS = $(COMPILER_NAME)-as
LD = $(COMPILER_NAME)-ld
OBJCOPY = $(COMPILER_NAME)-objcopy
OBJDUMP = $(COMPILER_NAME)-objdump


# Small data sections' usage
MSDA_SIZE                       = 0
MEMORY_POOL_SECTION             =
NON_INITIALIZED_DATA_SECTION    =
INITIALIZED_DATA_SECTION        =
STATIC_SINGLETONS_DATA_SECTION  =
VIRTUAL_TABLES_DATA_SECTION     =

MEMORY_POOL_SECTION_ATTRIBUTE               = __MEMORY_POOL_SECTION_ATTRIBUTE=
NON_INITIALIZED_DATA_SECTION_ATTRIBUTE      = __NON_INITIALIZED_DATA_SECTION_ATTRIBUTE=
INITIALIZED_DATA_SECTION_ATTRIBUTE          = __INITIALIZED_DATA_SECTION_ATTRIBUTE=
STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE    = __STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE=
VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE       = __VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE=


# include overrides
CONFIG_MAKE_FILE = $(shell pwd)/config.make
include $(CONFIG_MAKE_FILE)

ifneq ($(BUILD_MODE),)
TYPE = $(BUILD_MODE)
endif

OPTIMIZATION_OPTION = -O0
ifneq ($(OPTIMIZATION),)
OPTIMIZATION_OPTION = -$(OPTIMIZATION)
endif

PEDANTIC_WARNINGS_FLAG =
ifeq ($(PRINT_PEDANTIC_WARNINGS), 1)
PEDANTIC_WARNINGS_FLAG = -pedantic
endif

DUMP_TARGET =
ifeq ($(DUMP_ELF), 1)
DUMP_TARGET = dump
endif

PAD =
ifeq ($(PAD_ROM), 1)
PAD = pad
endif

STORE_SUFIX =
PROLOG_FUNCTIONS_FLAG =
ifeq ($(USE_PROLOG_FUNCTIONS), 1)
PROLOG_FUNCTIONS_FLAG = -mprolog-function
STORE_SUFIX = -pf
endif

FRAME_POINTER_USAGE_FLAG = -fomit-frame-pointer
ifeq ($(USE_FRAME_POINTER), 1)
FRAME_POINTER_USAGE_FLAG = -fno-omit-frame-pointer
endif

USE_CUSTOM_LINKER_SCRIPT =

ifneq ($(MEMORY_POOL_SECTION),)
MEMORY_POOL_SECTION_ATTRIBUTE = __MEMORY_POOL_SECTION_ATTRIBUTE="__attribute__((section(\"$(MEMORY_POOL_SECTION)\")))"
USE_CUSTOM_LINKER_SCRIPT = 1
endif

ifneq ($(NON_INITIALIZED_DATA_SECTION),)
NON_INITIALIZED_DATA_SECTION_ATTRIBUTE = __NON_INITIALIZED_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(NON_INITIALIZED_DATA_SECTION)\")))"
USE_CUSTOM_LINKER_SCRIPT = 1
endif

ifneq ($(INITIALIZED_DATA_SECTION),)
INITIALIZED_DATA_SECTION_ATTRIBUTE = __INITIALIZED_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(INITIALIZED_DATA_SECTION)\")))"
USE_CUSTOM_LINKER_SCRIPT = 1
endif

ifneq ($(STATIC_SINGLETONS_DATA_SECTION),)
STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE = __STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(STATIC_SINGLETONS_DATA_SECTION)\")))"
USE_CUSTOM_LINKER_SCRIPT = 1
endif

ifneq ($(VIRTUAL_TABLES_DATA_SECTION),)
VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE = __VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE="__attribute__((section(\"$(VIRTUAL_TABLES_DATA_SECTION)\")))"
USE_CUSTOM_LINKER_SCRIPT = 1
endif

DATA_SECTION_ATTRIBUTES = $(MEMORY_POOL_SECTION_ATTRIBUTE) $(NON_INITIALIZED_DATA_SECTION_ATTRIBUTE) $(INITIALIZED_DATA_SECTION_ATTRIBUTE) $(STATIC_SINGLETONS_DATA_SECTION_ATTRIBUTE) $(VIRTUAL_TABLES_DATA_SECTION_ATTRIBUTE)

# linker script
LINKER_SCRIPT = $(VUENGINE_HOME)/lib/compiler/linker/vb.ld
ifneq ($(USE_CUSTOM_LINKER_SCRIPT),)
LINKER_SCRIPT = $(shell pwd)/lib/compiler/linker/vb.ld
endif

# engine's home
VUENGINE_HOME = $(VBDE)libs/vuengine

# Which directories contain source files
DIRS = $(shell find source assets -type d -print)
HEADER_DIRS = $(shell find $(VUENGINE_HOME)/source source -type d -print)

# Which libraries are linked
LIBS = vuengine

# Obligatory headers
CONFIG_FILE =       $(shell pwd)/config.h
ESSENTIAL_HEADERS = -include $(CONFIG_FILE) \
					-include $(VUENGINE_HOME)/libvuengine.h

# Common macros for all build types
COMMON_MACROS = $(DATA_SECTION_ATTRIBUTES)

# The next blocks changes some variables depending on the build type
ifeq ($(TYPE),debug)
LD_PARAMS = -T$(LINKER_SCRIPT) -lm
C_PARAMS = $(ESSENTIAL_HEADERS) $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) $(PEDANTIC_WARNINGS_FLAG) $(OPTIMIZATION_OPTION) -std=gnu99 -mv810 -nodefaultlibs -Wall -Wextra
MACROS = __DEBUG __TOOLS $(COMMON_MACROS)
endif

ifeq ($(TYPE), release)
LD_PARAMS = -T$(LINKER_SCRIPT) -lm
C_PARAMS = $(ESSENTIAL_HEADERS) $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) $(PEDANTIC_WARNINGS_FLAG) $(OPTIMIZATION_OPTION) -std=gnu99 -mv810 -nodefaultlibs -Wall -Wextra -finline-functions -Winline
MACROS = __RELEASE $(COMMON_MACROS)
endif

ifeq ($(TYPE), beta)
LD_PARAMS = -T$(LINKER_SCRIPT) -lm
C_PARAMS = $(ESSENTIAL_HEADERS) $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) $(PEDANTIC_WARNINGS_FLAG) $(OPTIMIZATION_OPTION) -std=gnu99 -mv810 -nodefaultlibs -Wall -Wextra -finline-functions -Winline
MACROS = __BETA $(COMMON_MACROS)
endif

ifeq ($(TYPE), tools)
LD_PARAMS = -T$(LINKER_SCRIPT) -lm
C_PARAMS = $(ESSENTIAL_HEADERS) $(PROLOG_FUNCTIONS_FLAG) $(FRAME_POINTER_USAGE_FLAG) $(PEDANTIC_WARNINGS_FLAG) $(OPTIMIZATION_OPTION) -std=gnu99 -mv810 -nodefaultlibs -Wall -Wextra -finline-functions -Winline
MACROS = __TOOLS $(COMMON_MACROS)
endif

ifeq ($(TYPE),preprocessor)
ALL_TARGET_PREREQUISITES = dirs $(VUENGINE) $(C_OBJECTS) printPostPreprocessorInfo
LD_PARAMS =
C_PARAMS = -std=gnu99 -mv810 -nodefaultlibs -Wall -Wextra -E
MACROS = $(COMMON_MACROS)
endif

# Add directories to the include and library paths
VUENGINE_INCLUDE_PATHS = $(VUENGINE_HOME) $(shell find $(VUENGINE_HOME)/source -type d -print)
GAME_INCLUDE_PATHS = $(shell find assets source -type d -print)
GAME_INCLUDE_PATHS += .

# linked engine's home
VUENGINE_LIBRARY_PATH = $(BUILD_DIR)

# Where to store object and dependency files.
STORE = $(BUILD_DIR)/$(TYPE)$(STORE_SUFIX)

# Makefs a list of the source (.cpp) files.
C_SOURCE = $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.c))

# Makes a list of the source (.s) files.
ASSEMBLY_SOURCE = $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.s))

# List of header files.
HEADERS = $(foreach DIR,$(HEADER_DIRS),$(wildcard $(DIR)/*.h))

# Makes a list of the header files that will have to be created.
H_FILES = $(addprefix $(WORKING_FOLDER)/sources/, $(HEADERS:.h=.h))

# Makes a list of the object files that will have to be created.
C_OBJECTS = $(addprefix $(STORE)/, $(C_SOURCE:.c=.o))
C_INTERMEDIATE_SOURCES = $(addprefix $(WORKING_FOLDER)/sources/, $(C_SOURCE:.c=.c))

# Makes a list of the object files that will have to be created.
ASSEMBLY_OBJECTS = $(addprefix $(STORE)/, $(ASSEMBLY_SOURCE:.s=.o))

# Same for the .d (dependency) files.
D_FILES = $(addprefix $(STORE)/,$(C_SOURCE:.c=.d))

HELPERS_PREFIX=game

# Class setup file
FINAL_SETUP_CLASSES = setupClasses
FINAL_SETUP_CLASSES_OBJECT = $(STORE)/$(FINAL_SETUP_CLASSES)

SETUP_CLASSES = $(HELPERS_PREFIX)SetupClasses
SETUP_CLASSES_OBJECT = $(STORE)/$(SETUP_CLASSES)

# Virtual methods preprocessor file
VIRTUAL_METHODS_HELPER=$(WORKING_FOLDER)/preprocessor/$(HELPERS_PREFIX)VirtualMethods.txt

# Main target. The @ in front of a command prevents make from displaying it to the standard output.

# first build the engine
ENGINE = libvuengine.a

# the target file
TARGET_FILE = output
TARGET = $(STORE)/$(TARGET_FILE)-$(TYPE)

# define the engine
VUENGINE = $(BUILD_DIR)/libvuengine.a

all: printBuildingInfo $(ALL_TARGET_PREREQUISITES)

printBuildingInfo:
	@echo Building $(TARGET).vb
	@echo Build type: $(TYPE)
	@echo Compiler: $(COMPILER_NAME) $(COMPILER_VERSION)
	@echo Compiler\'s output: $(COMPILER_OUTPUT)
#	@sh $(VUENGINE_HOME)/lib/compiler/preprocessor/cleanSyntax.sh $(GAME_HOME)/source

printPostPreprocessorInfo:
	@echo Done compiling in $(TYPE) mode with GCC $(COMPILER_VERSION)

setupClasses:
	@sh $(VUENGINE_HOME)/lib/compiler/preprocessor/setupClasses.sh -h $(GAME_HOME) -o $(SETUP_CLASSES).c -w $(WORKING_FOLDER)/preprocessor
	@echo Classes processing done

dump: $(TARGET).elf
	@echo Dumping elf
	@$(OBJDUMP) -t $(TARGET).elf > $(STORE)/sections-$(TYPE).txt
	@$(OBJDUMP) -S $(TARGET).elf > $(STORE)/machine-$(TYPE).asm
	@echo Dumping elf done

pad: $(TARGET).vb
	@echo Padding $(BUILD_DIR)/$(TARGET_FILE).vb
	@$(VUENGINE_HOME)/lib/utilities/padder $(BUILD_DIR)/$(TARGET_FILE).vb 3
	@echo " "

$(TARGET).vb: $(TARGET).elf
	@echo Creating $@
	@$(OBJCOPY) -O binary $(TARGET).elf $@
	@cp $(TARGET).vb $(BUILD_DIR)/$(TARGET_FILE).vb
	@echo Done creating $(BUILD_DIR)/$(TARGET_FILE).vb in $(TYPE) mode with GCC $(COMPILER_VERSION)

$(TARGET).elf: $(VUENGINE) $(VIRTUAL_METHODS_HELPER) $(C_OBJECTS) $(C_INTERMEDIATE_SOURCES) $(ASSEMBLY_OBJECTS) $(SETUP_CLASSES_OBJECT).o $(FINAL_SETUP_CLASSES_OBJECT).o
	@echo Linking $(TARGET).elf
	@$(GCC) -o $@ -nostartfiles $(C_OBJECTS) $(ASSEMBLY_OBJECTS) $(FINAL_SETUP_CLASSES_OBJECT).o $(SETUP_CLASSES_OBJECT).o $(LD_PARAMS) \
		$(foreach LIBRARY, $(LIBS),-l$(LIBRARY)) $(foreach LIB,$(VUENGINE_LIBRARY_PATH),-L$(LIB)) -Wl,-Map=$(TARGET).map

$(VIRTUAL_METHODS_HELPER): $(H_FILES)
	@echo "Preparing virtual methods in game"
	@sh $(VUENGINE_HOME)/lib/compiler/preprocessor/prepareVirtualMethods.sh -w $(WORKING_FOLDER)/preprocessor -h $(GAME_HOME)/source -p $(HELPERS_PREFIX) -d

$(SETUP_CLASSES_OBJECT).o: $(WORKING_FOLDER)/preprocessor/$(SETUP_CLASSES).c
	@echo Compiling $<
	@echo to $@
	@$(GCC) $(foreach INC,$(VUENGINE_INCLUDE_PATHS) $(GAME_INCLUDE_PATHS),-I$(INC))\
        $(foreach MACRO,$(MACROS),-D$(MACRO)) $(C_PARAMS) -$(COMPILER_OUTPUT) $< -o $@

$(WORKING_FOLDER)/preprocessor/$(SETUP_CLASSES).c: setupClasses

$(FINAL_SETUP_CLASSES_OBJECT).o: $(WORKING_FOLDER)/preprocessor/$(FINAL_SETUP_CLASSES).c
	@echo Compiling $<
	@echo to $@
	@$(GCC) $(foreach INC,$(VUENGINE_INCLUDE_PATHS) $(GAME_INCLUDE_PATHS),-I$(INC))\
        $(foreach MACRO,$(MACROS),-D$(MACRO)) $(C_PARAMS) -$(COMPILER_OUTPUT) $< -o $@

$(FINAL_SETUP_CLASSES)/preprocessor/$(SETUP_CLASSES).c: setupClasses

# Rule for creating object file and .d file, the sed magic is to add the object path at the start of the file
# because the files gcc outputs assume it will be in the same dir as the source file.
$(STORE)/%.o: $(WORKING_FOLDER)/sources/%.c
	@$(GCC) -Wp,-MD,$(STORE)/$*.dd $(foreach INC,$(VUENGINE_INCLUDE_PATHS) $(GAME_INCLUDE_PATHS),-I$(INC))\
        $(foreach MACRO,$(MACROS),-D$(MACRO)) $(C_PARAMS)  -$(COMPILER_OUTPUT) $< -o $@
	@sed -e '1s/^\(.*\)$$/$(subst /,\/,$(dir $@))\1/' $(STORE)/$*.dd > $(STORE)/$*.d
	@rm -f $(STORE)/$*.dd

$(WORKING_FOLDER)/sources/%.c: %.c
	@echo Compiling $<
	@sh $(VUENGINE_HOME)/lib/compiler/preprocessor/processVirtualCalls.sh -i $< -o $@ -d -w $(WORKING_FOLDER)/preprocessor -p engine -p $(HELPERS_PREFIX)

$(STORE)/%.o: %.s
	@echo Creating object file for $*
	@$(AS) -o $@ $<

$(WORKING_FOLDER)/sources/%.h: %.h
	@cp $< $@

$(VUENGINE): deleteEngine
	@echo Building VUEngine...
	@$(MAKE) all -f $(VUENGINE_HOME)/makefile $@ -e TYPE=$(TYPE) -e CONFIG_FILE=$(CONFIG_FILE) -e CONFIG_MAKE_FILE=$(CONFIG_MAKE_FILE) -e GAME_HOME=$(GAME_HOME)
	@echo VUEngine built into libvuengine.a

deleteEngine:
	@rm -f $(VUENGINE)

# Empty rule to prevent problems when a header is deleted.
%.h: ;

# Cleans up the objects, .d files and executables.
clean:
	@echo Cleaning $(TYPE)...
	@find $(BUILD_DIR) -maxdepth 1 -type f -exec rm -f {} \;
	@rm -f $(foreach DIR,$(DIRS),$(STORE)/$(DIR)/*.d $(STORE)/$(DIR)/*.o)
	@rm -Rf $(STORE)
	@echo Cleaning done.

# Create necessary directories
dirs:
	@echo Checking working dirs..
	@-if [ ! -e $(STORE) ]; then mkdir -p $(STORE); fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(STORE)/$(DIR) ]; \
         then mkdir -p $(STORE)/$(DIR); fi; )
	@-if [ ! -e $(WORKING_FOLDER)/sources ]; then mkdir -p $(WORKING_FOLDER)/sources; fi;
	@-$(foreach DIR,$(DIRS), if [ ! -e $(WORKING_FOLDER)/sources/$(DIR) ]; \
         then mkdir -p $(WORKING_FOLDER)/sources/$(DIR); fi; )

# Includes the .d files so it knows the exact dependencies for every source
-include $(D_FILES)
