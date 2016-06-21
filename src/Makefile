# UTILITIES
# ══════════════════════════════════════════════════════════════════════════════
# C Compiler
# ──────────────────────────────────────────────────────────────────────────────
CC		:= gcc
CC_FLAGS	:= -I. -g -O2 -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__


# PATH CONFIGURATION
# ══════════════════════════════════════════════════════════════════════════════
# ─────────────── source ───────────────────────────────────────────────────────
HEADER_PATH		= $(call TRIM,./$1.h)# interface
SOURCE_PATH		= $(call TRIM,./$1.c)# implementation
# ─────────────── build ────────────────────────────────────────────────────────
OBJECT_PATH  		= $(call TRIM,../$obj/$1.o)# object files
BINARY_PATH 		= $(call TRIM,../$bin/$1)# executable output

# PROJECT CONFIGURATION
# ══════════════════════════════════════════════════════════════════════════════
PROJECT 	       := mysql_seed
MODULE_HEADER		= $(call HEADER_PATH,$(PROJECT)_$1)
MODULE_SOURCE		= $(call SOURCE_PATH,$(PROJECT)_$1)
MODULE_OBJECT		= $(call OBJECT_PATH,$(PROJECT)_$1)

# MISC
# ══════════════════════════════════════════════════════════════════════════════
EMPTY	:=
SPACE	:= $(EMPTY) $(EMPTY)
TAB	:= $(EMPTY)	$(EMPTY)
define NEWLINE :=


endef

TRIM = $(subst $(SPACE),$(EMPTY),$1)


define COMPILE_SOURCE
$(NEWLINE)
$(strip $1: $2)
	$(strip $(CC) $(CC_FLAGS) $3 -c $$< -o $$@)

OBJECTS += $1
$(NEWLINE)
endef

define COMPILE_MODE_MODULE
$(call COMPILE_SOURCE,$(call MODULE_OBJECT,$1),\
		      $(call MODULE_SOURCE,$1)
		      $(call MODULE_HEADER,$1)
		      $(MODE_MODULE_CC_PREQS))
endef

define COMPILE_MODE_MODULES
$(foreach mode,$(MODES),\
	       $(call COMPILE_MODE_MODULE,$(mode)))
endef


MODES := create run exit
MODE_MODULE_CC_PREQS :=	$(call MODULE_HEADER_PATH,mode)

all: compile_mode_modules link_mode_modules

compile_mode_modules: $


link_mode_modules: scratch.c
	$(CC) $(LIBS) -O2 -o $@ $^


clean:
	$(RM) scratch
