# Target architecture for the build. Use avr32 if you are unsure.
TARGET_ARCH_AVR32 ?= avr32
TARGET_ARCH ?= $(TARGET_ARCH_AVR32)

CFLAGS_CPU   = -mpart=$(PART) $(CFLAGS_FPU)
CFLAGS_LINK  = -ffunction-sections -fdata-sections -fno-builtin -fshort-enums
#~ CFLAGS_DBG  ?= -ggdb -g3
CFLAGS_OPT  ?= -Os
CFLAGS_CPU += -msoft-float
CFLAGS_CPU += -muse-rodata-section
CFLAGS_CPU += -fdata-sections
CFLAGS_CPU += -ffunction-sections
CFLAGS_CPU += -I$(PATH_AVR32_INCLUDE)

CFLAGS    += $(CFLAGS_CPU) $(CFLAGS_LINK) $(CFLAGS_DBG) $(CFLAGS_OPT)

ASFLAGS   += $(CFLAGS_CPU) $(CFLAGS_DBG)
LINKFLAGS += $(CFLAGS_CPU) $(CFLAGS_DBG) $(CFLAGS_OPT) -static -lgcc -e _start -Wl,--gc-sections  --direct-data
OFLAGS    += -j .text -j .data

# Use ROM_LEN and RAM_LEN during link
$(if $(ROM_LEN),,$(error ROM_LEN is not defined))
$(if $(RAM_LEN),,$(error RAM_LEN is not defined))
LINKFLAGS += $(LINKFLAGPREFIX)--defsym=__TEXT_REGION_LENGTH__=$(ROM_LEN)$(if $(ROM_RESERVED),-$(ROM_RESERVED))
LINKFLAGS += $(LINKFLAGPREFIX)--defsym=__DATA_REGION_LENGTH__=$(RAM_LEN)

# Use newer linker script to have ROM/RAM configuration symbols in binutils<2.26
LDSCRIPT_COMPAT = $(if $(shell $(TARGET_ARCH)-ld --verbose | grep __TEXT_REGION_LENGTH__),,\
                    -T$(RIOTCPU)/$(CPU)/ldscripts/link_uc3a0512.lds)
LINKFLAGS += $(LDSCRIPT_COMPAT)

# use the wrapper functions for following avr-libc functions
#~ LINKFLAGS += -Wl,-wrap=malloc -Wl,-wrap=calloc -Wl,-wrap=realloc -Wl,-wrap=free

#~ ifeq ($(LTO),1)
  # avr-gcc <4.8.3 has a bug when using LTO which causes a warning to be printed always:
  # '_vector_25' appears to be a misspelled signal handler [enabled by default]
  # See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59396
#~   LINKFLAGS += -Wno-error
#~ endif

OPTIONAL_CFLAGS_BLACKLIST += -gz
OPTIONAL_CFLAGS_BLACKLIST += -Wformat-overflow
OPTIONAL_CFLAGS_BLACKLIST += -Wformat-truncation
OPTIONAL_CFLAGS_BLACKLIST += -fdiagnostics-color
