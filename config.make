# VUEngine based plugins that the project uses
PLUGINS =	vuengine/plugins/entities/LowPowerEntity 														\
			vuengine/plugins/other/AutomaticPause															\
			vuengine/plugins/other/SaveDataManager															\
			vuengine/plugins/states/SplashScreens															\

# Compiler's output
COMPILER_OUTPUT         = c

# Compilation type
# preprocessor:			The .o files are preprocessor's output instead of compiler's.
# debug:				Adds lots of runtime assertions. Enables debugging tools too.
# 						It is recommended to use the sram sections for the memory pools
# 						when debugging in order to avoid stack overflows
# 						(SRAM as WRAM only works on emulators).
# tools:				Adds debugging tools without all the debug checking.
# beta:					Removes most asserts. For testing the performance on hardware.
# release:				Removes all asserts. For shipping only!
TYPE                    = release

# Optimization level
OPTIMIZATION            = O3

# Enable pedantic warnings
# 0:                    Omit.
# 1:                    Use.
PRINT_PEDANTIC_WARNINGS = 0

# Frame pointer's usage
# 0:                    Omit.
# 1:                    Use.
USE_FRAME_POINTER       = 0

# Prolog functions' usage
# 0:                    Omit.
# 1:                    Use.
USE_PROLOG_FUNCTIONS    = 0

# Pad ROM for hardware testing
# 0:                    No padding.
# 1:                    Pad the ROM for hardware testing.
PAD_ROM                 = 0

# Dump elf
# 0:                    No dumping.
# 1:                    Dump the assembly code and the memory sections.
DUMP_ELF                = 0

# Sections' usage
# SRAM's usage
# You can use SRAM as WRAM. It adds, theoretically, 16MB of WRAM where all non initialized variables can be allocated.
# This feature is experimental and only works properly on emulators.
# Since only 8KB of SRAM is available on real carts, more than that will only work on emulators.
# To make effective any change to these options, the whole project needs to be recompiled.
# DRAM can be used as WRAM too, you must edit the linker script vb.ld to accommodate this
# taking into account that the Param Table's last address normally is 0x0003D800, where
# the WORLD attributes start.

# valid options are [/.bss/.sbss/.dram_bss/.sram_bss]
MEMORY_POOL_SECTION             = .sbss
# valid options are [/.bss/.sbss/.dram_bss/.sram_bss]
NON_INITIALIZED_DATA_SECTION    = .sbss
# valid options are [/.data/.sdata/.dram_data/.sram_data]
INITIALIZED_DATA_SECTION        = .sdata
# valid options are [/.bss/.sbss/.dram_bss/.sram_bss]
STATIC_SINGLETONS_DATA_SECTION  = .dram_bss
# valid options are [/.bss/.sbss/.dram_bss/.sram_bss]
VIRTUAL_TABLES_DATA_SECTION     = .dram_bss

# Size of variables to be loaded in the .sdata section
# Not working properly because rosdata is used instead of rodata section
# MSDA_SIZE             = 0
