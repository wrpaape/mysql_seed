# ══════════════════════════════════════════════════════════════════════════════
# ──────────────────────────────────────────────────────────────────────────────
#				CONFIGURATION
# ──────────────────────────────────────────────────────────────────────────────
# ══════════════════════════════════════════════════════════════════════════════
#
#
## MISC
# ══════════════════════════════════════════════════════════════════════════════
# Phony Targets
# ──────────────────────────────────────────────────────────────────────────────
.PHONY: all test clean


# String Utils
# ──────────────────────────────────────────────────────────────────────────────
EMPTY	       :=
SPACE	       := $(EMPTY) $(EMPTY)
TAB	       := $(EMPTY)	$(EMPTY)
TRIM		= $(subst $(SPACE),$(EMPTY),$1)
JOIN	        = $(subst $(SPACE),$2,$(strip $1))
define NEWLINE :=


endef


# Development Mode
# ──────────────────────────────────────────────────────────────────────────────
# toggles certain utility flags, make targets
DEVELOPMENT_MODE = T


# SYSTEM CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# extended from user 'Trevor Robinson''s response to stackoverflow question:
#
# 	http://stackoverflow.com/questions/714100/os-detecting-makefile

ifeq ($(OS),Windows_NT)

        SYSTEM_WINDOWS 	:= T
        SYS_ENV_FLAGS 	:= -DWIN32

        ifeq      (AMD64,$(PROCESSOR_ARCHITECTURE))
                ARCH_X86_64	:= T
                SYS_ARCH_FLAG	:= -arch x86_64
                SYS_ENV_FLAGS	+= -DAMD_64

        else ifeq (x86,$(PROCESSOR_ARCHITECTURE))
                ARCH_I386	:= T
                SYS_ARCH_FLAG	:= -arch i386
                SYS_ENV_FLAGS	+= -DIA_32
        endif
else
        UNAME_S := $(shell uname -s)

        ifeq      ($(UNAME_S),Linux)
                SYSTEM_LINUX 	:= T
                SYS_ENV_FLAGS 	:= -DLINUX

        else ifeq ($(UNAME_S),Darwin)
                SYSTEM_OSX 	:= T
                SYS_ENV_FLAGS 	:= -DOSX
        endif

        UNAME_M := $(shell uname -m)

        ifeq      (x86_64,$(UNAME_M))
                ARCH_X86_64	:= T
                SYS_ARCH_FLAG	:= -arch x86_64
                SYS_ENV_FLAGS	+= -DAMD_64

        else ifneq (,$(filter %86,$(UNAME_M)))
                ARCH_I386	:= T
                SYS_ARCH_FLAG	:= -arch i386
                SYS_ENV_FLAGS 	+= -DIA_32

        else ifneq (,$(filter arm%,$(UNAME_M)))

                ifneq (,$(filter %32%,$(UNAME_M)))
                        ARCH_ARM_32	:= T
                        SYS_ARCH_FLAG	:= -arch AArch32
                        SYS_ENV_FLAGS 	+= -DARM_32
                else
                        ARCH_ARM_64	:= T
                        SYS_ARCH_FLAG	:= -arch AArch64
                        SYS_ENV_FLAGS 	+= -DARM_64
                endif
        endif
endif

# Path delimiter and chain commands token
# ──────────────────────────────────────────────────────────────────────────────
ifeq (T,$(SYSTEM_WINDOWS))
PATH_DELIM	:= \\
CMD_DELIM 	:= &
else
PATH_DELIM	:= /
CMD_DELIM 	:= ;
endif



# DIRECTORY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
PATH_JOIN		 = $(call JOIN,$1,$(PATH_DELIM))
PROJECT 		:= mysql_seed
PROJECT_ROOT		:= ..
PROJECT_ROOT_ABSOLUTE	:= $(call TRIM,"\"$(realpath $(PROJECT_ROOT))\"")
SOURCE_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) src)
HEADER_DIR		:= $(SOURCE_DIR)
OBJECT_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) obj)
BINARY_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) bin)
TEST_SOURCE_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) test)
TEST_HEADER_DIR		:= $(TEST_SOURCE_DIR)
TEST_RUNNER_SOURCE_DIR	:= $(call PATH_JOIN,$(TEST_SOURCE_DIR) test_runners)
TEST_OBJECT_DIR		:= $(OBJECT_DIR)
TEST_RUNNER_OBJECT_DIR	:= $(TEST_OBJECT_DIR)
TEST_BINARY_DIR		:= $(TEST_SOURCE_DIR)
UNITY_ROOT		:= $(call PATH_JOIN,$(TEST_SOURCE_DIR) unity)
UNITY_SOURCE_DIR	:= $(call PATH_JOIN,$(UNITY_ROOT) src)
UNITY_HEADER_DIR	:= $(UNITY_SOURCE_DIR)
UNITY_OBJECT_DIR	:= $(call PATH_JOIN,$(UNITY_ROOT) obj)
UNITY_AUTO_DIR  	:= $(call PATH_JOIN,$(UNITY_ROOT) auto)

# 'windows' directory, library flags
# ──────────────────────────────────────────────────────────────────────────────
ifeq (T,$(SYSTEM_WINDOWS))
        WINDOWS_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) windows)
        THREADS_DIR		:= $(call PATH_JOIN,$(WINDOWS_DIR) pthreads_win32)
        THREADS_INC_DIR		:= $(call PATH_JOIN,$(THREADS_DIR) include)
        THREADS_LIB_ROOT	:= $(call PATH_JOIN,$(THREADS_DIR) dll)

        ifeq (T, ARCH_X86_64)
                        THREADS_LIB_DIR := $(call PATH_JOIN,$(THREADS_LIB_ROOT) x64)
        else
                        THREADS_LIB_DIR := $(call PATH_JOIN,$(THREADS_LIB_ROOT) x86)
        endif

        THREADS_LIB_FLAG	:= -L$(THREADS_LIB_DIR) -lpthreadGC2.dll
        THREADS_INC_FLAG	:= -I$(THREADS_INC_DIR)

        SYSTEM_LIB_FLAGS	:= -lWs2_32 -lKernel32
else
        THREADS_LIB_FLAG	:= -lpthread
        THREADS_INC_FLAG	:= $(EMPTY)

        SYSTEM_LIB_FLAGS	:= $(EMPTY)
endif


# PATH CONFIG
# ══════════════════════════════════════════════════════════════════════════════
FILE_PATH			= $(call PATH_JOIN,$1 $(call TRIM,$2))
SCRIPT_FILE_PATH		= $(call FILE_PATH,$1,$2.rb)
SOURCE_FILE_PATH		= $(call FILE_PATH,$1,$2.c)
HEADER_FILE_PATH		= $(call FILE_PATH,$1,$2.h)
OBJECT_FILE_PATH		= $(call FILE_PATH,$1,$2.o)
BINARY_FILE_PATH		= $(call FILE_PATH,$1,$2)

# Project
# ─────────────── source ───────────────────────────────────────────────────────
SOURCE_PATH			= $(call SOURCE_FILE_PATH,$(SOURCE_DIR),$1)# implementation
HEADER_PATH			= $(call HEADER_FILE_PATH,$(HEADER_DIR),$1)# interface
# ─────────────── build ────────────────────────────────────────────────────────
OBJECT_PATH   			= $(call OBJECT_FILE_PATH,$(OBJECT_DIR),$1)# object files
BINARY_PATH 			= $(call BINARY_FILE_PATH,$(BINARY_DIR),$1)# binary executable output

# Helper Project Module
# ─────────────── source ───────────────────────────────────────────────────────
HELPER_SOURCE_PATH		= $(call SOURCE_PATH,$(call PATH_JOIN,$1))# implementation
HELPER_HEADER_PATH		= $(call HEADER_PATH,$(call PATH_JOIN,$1))# interface
# ─────────────── build ────────────────────────────────────────────────────────
HELPER_OBJECT_PATH   		= $(call OBJECT_PATH,$(call JOIN,$1,_))# object files

# Helper Project Module Testing
# ─────────────── source ───────────────────────────────────────────────────────
HELPER_TEST_SOURCE_PATH		= $(call SOURCE_FILE_PATH,$(TEST_SOURCE_DIR),$(call JOIN,$1 test,_))# Unity unit test implementation
HELPER_TEST_HEADER_PATH		= $(call HEADER_FILE_PATH,$(TEST_HEADER_DIR),$(call JOIN,$1 test,_))# Unity unit test interface
HELPER_TEST_RUNNER_SOURCE_PATH	= $(call SOURCE_FILE_PATH,$(TEST_RUNNER_SOURCE_DIR),$(call JOIN,$1 test_runner,_))# Unity test runners
# ─────────────── build ────────────────────────────────────────────────────────
HELPER_TEST_OBJECT_PATH 	= $(call OBJECT_FILE_PATH,$(TEST_OBJECT_DIR),$(call JOIN,$1 test,_))# Unity unit test object files
HELPER_TEST_RUNNER_OBJECT_PATH	= $(call OBJECT_FILE_PATH,$(TEST_RUNNER_OBJECT_DIR),$(call JOIN,$1 test_runner,_))# Unity test runner object files
HELPER_TEST_BINARY_PATH 	= $(call BINARY_FILE_PATH,$(TEST_BINARY_DIR),$(call JOIN,$1 test,_))# binary executable output


# Main Project Module
# ─────────────── source ───────────────────────────────────────────────────────
PROJECT_SOURCE_PATH		= $(call SOURCE_PATH,$(PROJECT)_$1)# implementation
PROJECT_HEADER_PATH		= $(call HEADER_PATH,$(PROJECT)_$1)# interface
# ─────────────── build ────────────────────────────────────────────────────────
PROJECT_OBJECT_PATH   		= $(call OBJECT_PATH,$(PROJECT)_$1)# object files

# Main Project Module Testing
# ─────────────── source ───────────────────────────────────────────────────────
PROJECT_TEST_SOURCE_PATH	= $(call SOURCE_FILE_PATH,$(TEST_SOURCE_DIR),$(PROJECT)_$1_test)# Unity unit test implementation
PROJECT_TEST_HEADER_PATH	= $(call HEADER_FILE_PATH,$(TEST_HEADER_DIR),$(PROJECT)_$1_test)# Unity unit test interface
PROJECT_TEST_RUNNER_SOURCE_PATH	= $(call SOURCE_FILE_PATH,$(TEST_RUNNER_SOURCE_DIR),$(PROJECT)_$1_test_runner)# Unity test runners
# ─────────────── build ────────────────────────────────────────────────────────
PROJECT_TEST_OBJECT_PATH 	= $(call OBJECT_FILE_PATH,$(TEST_OBJECT_DIR),$(PROJECT)_$1_test)# Unity unit test object files
PROJECT_TEST_RUNNER_OBJECT_PATH	= $(call OBJECT_FILE_PATH,$(TEST_RUNNER_OBJECT_DIR),$(PROJECT)_$1_test_runner)# Unity test runner object files
PROJECT_TEST_BINARY_PATH 	= $(call BINARY_FILE_PATH,$(TEST_BINARY_DIR),$(PROJECT)_$1_test)# binary executable output



# Unity Test Framework
# ─────────────── source ───────────────────────────────────────────────────────
UNITY_SOURCE_PATH		= $(call SOURCE_FILE_PATH,$(UNITY_SOURCE_DIR),$1)# Unity framework implementation
UNITY_HEADER_PATH		= $(call HEADER_FILE_PATH,$(UNITY_HEADER_DIR),$1)# Uity framework interface
# ─────────────── build ────────────────────────────────────────────────────────
UNITY_SCRIPT_PATH		= $(call SCRIPT_FILE_PATH,$(UNITY_AUTO_DIR),$1)# Unity framework scripts
UNITY_OBJECT_PATH 		= $(call OBJECT_FILE_PATH,$(UNITY_OBJECT_DIR),$1)# Unity framework object files



# UTILITY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# C Compiler
# ──────────────────────────────────────────────────────────────────────────────
CC		:= gcc
CC_ENV_FLAGS	:= -D__USE_FIXED_PROTOTYPES__ -DROOT_ABSPATH=$(PROJECT_ROOT_ABSOLUTE) $(SYS_ENV_FLAGS)
CC_BASE_FLAGS	:= -std=c99 -march=native $(CC_ENV_FLAGS) -I$(HEADER_DIR) $(THREADS_INC_FLAG)

ifeq (T,$(DEVELOPMENT_MODE))
CC_FLAGS	:= -g -Wall $(CC_BASE_FLAGS)
else
CC_FLAGS	:= -O2 -funroll-loops $(CC_BASE_FLAGS)
endif
# Linker
# ──────────────────────────────────────────────────────────────────────────────
LD		:= ld
LD_FLAGS	:= -no_pie $(SYS_ARCH_FLAG)
LD_LIB_FLAGS	:= $(THREADS_LIB_FLAG) $(SYSTEM_LIB_FLAGS) -lc

ifeq (T,$(SYSTEM_OSX))
LD_FLAGS	+= -macosx_version_min 10.11
endif

# Make Directory
# ──────────────────────────────────────────────────────────────────────────────
MKDIR	    	:= mkdir
MKDIR_FLAGS 	:= $(EMPTY)
# Cleaner
# ──────────────────────────────────────────────────────────────────────────────
ifeq (T,$(SYSTEM_WINDOWS))
RM		:= del
RM_FLAGS	:= /F /Q
else
RM		:= rm
RM_FLAGS	:= -rf
endif
# Ruby
# ──────────────────────────────────────────────────────────────────────────────
RUBY		:= ruby
RUBY_FLAGS	:= $(EMPTY)




## UNITY TEST FRAMEWORK
# ══════════════════════════════════════════════════════════════════════════════
UNITY_SRC 		:= $(call UNITY_SOURCE_PATH,unity)
UNITY_HDR 		:= $(call UNITY_HEADER_PATH,unity)
UNITY_CONFIG_HDR 	:= $(call UNITY_HEADER_PATH,unity_config)
UNITY_INTERNALS_HDR 	:= $(call UNITY_HEADER_PATH,unity_internals)
UNITY_OBJ 		:= $(call UNITY_OBJECT_PATH,unity)
UNITY_GEN_TRNR_SCRIPT	:= $(call UNITY_SCRIPT_PATH,generate_test_runner)
UNITY_ENV_FLAGS 	:= -DUNITY_INCLUDE_CONFIG_H
UNITY_CC_FLAGS		:= $(CC_FLAGS) $(UNITY_ENV_FLAGS) -I$(UNITY_HEADER_DIR)
UNITY_LD_LIB_FLAGS	:= -lm
# ─────────────── run all tests ────────────────────────────────────────────────
TEST_FILES_GLOB	:= $(call BINARY_FILE_PATH,$(TEST_BINARY_DIR),*_test)
ifeq (T,$(SYSTEM_WINDOWS))
RUN_ALL_TESTS	:= FORFILES /M $(TEST_FILES_GLOB) /C "cmd /c @file"

else
RUN_ALL_TESTS	:= for test in $(TEST_FILES_GLOB); do "./$$test"; done
endif
# ─────────────── target prequisites ───────────────────────────────────────────
UNITY_OBJ_PREQS		:= $(UNITY_SRC)					\
			   $(UNITY_HDR)					\
			   $(UNITY_INTERNALS_HDR)			\
			   $(UNITY_CONFIG_HDR)
# ─────────────── targets ──────────────────────────────────────────────────────
TARGETS			+= $(UNITY_OBJ)					\
			   $(TEST_RUNNER_SOURCE_DIR)

# independent headers
# ──────────────────────────────────────────────────────────────────────────────
UTILS_TYPES_WORD_HDR		:= $(call HELPER_HEADER_PATH,utils types word)
UTILS_TYPES_OCTET_HDR		:= $(call HELPER_HEADER_PATH,utils types octet)
UTILS_TYPES_WIDTH_HDR		:= $(call HELPER_HEADER_PATH,utils types width)
UTILS_TYPES_ROUTINE_HDR		:= $(call HELPER_HEADER_PATH,utils types routine)
UTILS_TYPES_PROCEDURE_HDR	:= $(call HELPER_HEADER_PATH,utils types procedure)
UTILS_TYPES_HANDLER_HDR		:= $(call HELPER_HEADER_PATH,utils types handler)
UTILS_TYPES_WORD_PATTERN_HDR	:= $(call HELPER_HEADER_PATH,utils types word_pattern)
UTILS_TYPES_ACTION_HDR		:= $(call HELPER_HEADER_PATH,utils types action)
UTILS_CHAR_ATTRS_HDR		:= $(call HELPER_HEADER_PATH,utils char_attrs)
UTILS_WORD_ATTRS_HDR		:= $(call HELPER_HEADER_PATH,utils word_attrs)
UTILS_FAIL_SWITCH_HDR		:= $(call HELPER_HEADER_PATH,utils fail_switch)
MEMORY_MEMORY_SET_WIDTH_HDR	:= $(call HELPER_HEADER_PATH,memory memory_set_width)
MEMORY_MEMORY_GET_WIDTH_HDR	:= $(call HELPER_HEADER_PATH,memory memory_get_width)
MEMORY_MEMORY_PUT_WIDTH_HDR	:= $(call HELPER_HEADER_PATH,memory memory_put_width)
MEMORY_MEMORY_SWAP_WIDTH_HDR	:= $(call HELPER_HEADER_PATH,memory memory_swap_width)
MEMORY_WORD_REM_UTILS_HDR	:= $(call HELPER_HEADER_PATH,memory word_rem_utils)
STRING_INT_STRING_ATTRS_HDR	:= $(call HELPER_HEADER_PATH,string int_string_attrs)
STRING_PTR_STRING_ATTRS_HDR	:= $(call HELPER_HEADER_PATH,string ptr_string_attrs)
STRING_STRING_TOKEN_HDR		:= $(call HELPER_HEADER_PATH,string string_token)
STRING_STRING_MACROS_HDR	:= $(call HELPER_HEADER_PATH,string string_macros)
MODE_HDR			:= $(call PROJECT_HEADER_PATH,mode)

## HELPER MODULES
# ══════════════════════════════════════════════════════════════════════════════
# utils/utils
# ──────────────────────────────────────────────────────────────────────────────
UTILS_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,utils utils)
UTILS_UTILS_HDR			:= $(call HELPER_HEADER_PATH,utils utils)
UTILS_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,utils utils)
UTILS_UTILS_TEST_SRC		:= $(call HELPER_TEST_SOURCE_PATH,utils utils)
UTILS_UTILS_TRNR_SRC		:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,utils utils)
UTILS_UTILS_TRNR_OBJ		:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,utils utils)
UTILS_UTILS_TEST_OBJ		:= $(call HELPER_TEST_OBJECT_PATH,utils utils)
UTILS_UTILS_TEST_BIN		:= $(call HELPER_TEST_BINARY_PATH,utils utils)
# ─────────────── target prequisites ───────────────────────────────────────────
UTILS_UTILS_OBJ_PREQS		:= $(UTILS_UTILS_SRC) 			\
			   	   $(UTILS_UTILS_HDR)
UTILS_UTILS_OBJ_GROUP		:= $(UTILS_UTILS_OBJ)
UTILS_UTILS_TRNR_SRC_PREQS	:= $(UTILS_UTILS_TEST_SRC)		\
				   $(TEST_RUNNER_SOURCE_DIR)
UTILS_UTILS_TEST_OBJ_PREQS	:= $(UTILS_UTILS_TEST_SRC)		\
			   	   $(UTILS_UTILS_OBJ_PREQS) 		\
			   	   $(UNITY_OBJ_PREQS)
UTILS_UTILS_TRNR_OBJ_PREQS	:= $(UTILS_UTILS_TRNR_SRC)		\
			   	   $(UTILS_UTILS_TEST_OBJ_PREQS)
UTILS_UTILS_TEST_BIN_PREQS	:= $(UTILS_UTILS_TRNR_OBJ)		\
				   $(UTILS_UTILS_TEST_OBJ)		\
			   	   $(UTILS_UTILS_OBJ_GROUP)		\
			   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(UTILS_UTILS_TEST_BIN)
TARGETS			+= $(UTILS_UTILS_OBJ)				\
			   $(UTILS_UTILS_TRNR_SRC)			\
			   $(UTILS_UTILS_TRNR_OBJ)			\
			   $(UTILS_UTILS_TEST_OBJ)			\
			   $(UTILS_UTILS_TEST_BIN)


# utils/closure
# ──────────────────────────────────────────────────────────────────────────────
UTILS_CLOSURE_SRC 		:= $(call HELPER_SOURCE_PATH,utils closure)
UTILS_CLOSURE_HDR		:= $(call HELPER_HEADER_PATH,utils closure)
UTILS_CLOSURE_OBJ 		:= $(call HELPER_OBJECT_PATH,utils closure)
UTILS_CLOSURE_TEST_SRC		:= $(call HELPER_TEST_SOURCE_PATH,utils closure)
UTILS_CLOSURE_TRNR_SRC		:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,utils closure)
UTILS_CLOSURE_TRNR_OBJ		:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,utils closure)
UTILS_CLOSURE_TEST_OBJ		:= $(call HELPER_TEST_OBJECT_PATH,utils closure)
UTILS_CLOSURE_TEST_BIN		:= $(call HELPER_TEST_BINARY_PATH,utils closure)
# ─────────────── target prequisites ───────────────────────────────────────────
UTILS_CLOSURE_OBJ_PREQS		:= $(UTILS_CLOSURE_SRC) 		\
			   	   $(UTILS_CLOSURE_HDR)			\
			   	   $(UTILS_TYPES_ROUTINE_HDR)		\
				   $(UTILS_TYPES_PROCEDURE_HDR)		\
				   $(UTILS_TYPES_HANDLER_HDR)
UTILS_CLOSURE_OBJ_GROUP		:= $(UTILS_CLOSURE_OBJ)
UTILS_CLOSURE_TRNR_SRC_PREQS	:= $(UTILS_CLOSURE_TEST_SRC)		\
				   $(TEST_RUNNER_SOURCE_DIR)
UTILS_CLOSURE_TEST_OBJ_PREQS	:= $(UTILS_CLOSURE_TEST_SRC)		\
			   	   $(UTILS_CLOSURE_OBJ_PREQS) 		\
			   	   $(UNITY_OBJ_PREQS)
UTILS_CLOSURE_TRNR_OBJ_PREQS	:= $(UTILS_CLOSURE_TRNR_SRC)		\
			   	   $(UTILS_CLOSURE_TEST_OBJ_PREQS)
UTILS_CLOSURE_TEST_BIN_PREQS	:= $(UTILS_CLOSURE_TRNR_OBJ)		\
				   $(UTILS_CLOSURE_TEST_OBJ)		\
			   	   $(UTILS_CLOSURE_OBJ_GROUP)		\
			   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(UTILS_CLOSURE_TEST_BIN)
TARGETS			+= $(UTILS_CLOSURE_OBJ)				\
			   $(UTILS_CLOSURE_TRNR_SRC)			\
			   $(UTILS_CLOSURE_TRNR_OBJ)			\
			   $(UTILS_CLOSURE_TEST_OBJ)			\
			   $(UTILS_CLOSURE_TEST_BIN)

# time/time_utils
# ──────────────────────────────────────────────────────────────────────────────
TIME_TIME_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,time time_utils)
TIME_TIME_UTILS_HDR		:= $(call HELPER_HEADER_PATH,time time_utils)
TIME_TIME_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,time time_utils)
TIME_TIME_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,time time_utils)
TIME_TIME_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,time time_utils)
TIME_TIME_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,time time_utils)
TIME_TIME_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,time time_utils)
TIME_TIME_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,time time_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
TIME_TIME_UTILS_OBJ_PREQS	:= $(TIME_TIME_UTILS_SRC) 		\
			   	   $(TIME_TIME_UTILS_HDR)		\
				   $(UTILS_FAIL_SWITCH_HDR)		\
				   $(UTILS_CLOSURE_HDR)
TIME_TIME_UTILS_OBJ_GROUP	:= $(TIME_TIME_UTILS_OBJ)		\
				   $(UTILS_CLOSURE_OBJ_GROUP)
TIME_TIME_UTILS_TRNR_SRC_PREQS	:= $(TIME_TIME_UTILS_TEST_SRC)		\
				   $(TEST_RUNNER_SOURCE_DIR)
TIME_TIME_UTILS_TEST_OBJ_PREQS	:= $(TIME_TIME_UTILS_TEST_SRC)		\
			   	   $(TIME_TIME_UTILS_OBJ_PREQS) 	\
			   	   $(UNITY_OBJ_PREQS)
TIME_TIME_UTILS_TRNR_OBJ_PREQS	:= $(TIME_TIME_UTILS_TRNR_SRC)		\
			   	   $(TIME_TIME_UTILS_TEST_OBJ_PREQS)
TIME_TIME_UTILS_TEST_BIN_PREQS	:= $(TIME_TIME_UTILS_TRNR_OBJ)		\
				   $(TIME_TIME_UTILS_TEST_OBJ)		\
			   	   $(TIME_TIME_UTILS_OBJ_GROUP)		\
			   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(TIME_TIME_UTILS_TEST_BIN)
TARGETS			+= $(TIME_TIME_UTILS_OBJ)			\
			   $(TIME_TIME_UTILS_TRNR_SRC)			\
			   $(TIME_TIME_UTILS_TRNR_OBJ)			\
			   $(TIME_TIME_UTILS_TEST_OBJ)			\
			   $(TIME_TIME_UTILS_TEST_BIN)

# memory/memory_utils
# ──────────────────────────────────────────────────────────────────────────────
MEMORY_MEMORY_UTILS_SRC 	:= $(call HELPER_SOURCE_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_HDR		:= $(call HELPER_HEADER_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_OBJ 	:= $(call HELPER_OBJECT_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,memory memory_utils)
MEMORY_MEMORY_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,memory memory_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
MEMORY_MEMORY_UTILS_OBJ_PREQS		:= $(MEMORY_MEMORY_UTILS_SRC) 		\
			   	   	   $(MEMORY_MEMORY_UTILS_HDR)		\
			   	   	   $(UTILS_UTILS_HDR)			\
			   	   	   $(UTILS_TYPES_WIDTH_HDR)
MEMORY_MEMORY_UTILS_OBJ_GROUP		:= $(MEMORY_MEMORY_UTILS_OBJ) 		\
					   $(UTILS_UTILS_OBJ_GROUP)
MEMORY_MEMORY_UTILS_TRNR_SRC_PREQS	:= $(MEMORY_MEMORY_UTILS_TEST_SRC)	\
					   $(TEST_RUNNER_SOURCE_DIR)
MEMORY_MEMORY_UTILS_TEST_OBJ_PREQS	:= $(MEMORY_MEMORY_UTILS_TEST_SRC)	\
					   $(MEMORY_MEMORY_UTILS_OBJ_PREQS) 	\
					   $(UNITY_OBJ_PREQS)
MEMORY_MEMORY_UTILS_TRNR_OBJ_PREQS	:= $(MEMORY_MEMORY_UTILS_TRNR_SRC)	\
					   $(MEMORY_MEMORY_UTILS_TEST_OBJ_PREQS)
MEMORY_MEMORY_UTILS_TEST_BIN_PREQS	:= $(MEMORY_MEMORY_UTILS_TRNR_OBJ)	\
					   $(MEMORY_MEMORY_UTILS_TEST_OBJ)	\
					   $(MEMORY_MEMORY_UTILS_OBJ_GROUP)	\
					   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(MEMORY_MEMORY_UTILS_TEST_BIN)
TARGETS			+= $(MEMORY_MEMORY_UTILS_OBJ)			\
			   $(MEMORY_MEMORY_UTILS_TRNR_SRC)		\
			   $(MEMORY_MEMORY_UTILS_TRNR_OBJ)		\
			   $(MEMORY_MEMORY_UTILS_TEST_OBJ)		\
			   $(MEMORY_MEMORY_UTILS_TEST_BIN)


# memory/memory_zero
# ──────────────────────────────────────────────────────────────────────────────
MEMORY_MEMORY_ZERO_SRC 		:= $(call HELPER_SOURCE_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_HDR		:= $(call HELPER_HEADER_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_OBJ 		:= $(call HELPER_OBJECT_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,memory memory_zero)
MEMORY_MEMORY_ZERO_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,memory memory_zero)
# ─────────────── target prequisites ───────────────────────────────────────────
MEMORY_MEMORY_ZERO_OBJ_PREQS		:= $(MEMORY_MEMORY_ZERO_SRC) 		\
			   	   	   $(MEMORY_MEMORY_ZERO_HDR)		\
			   	   	   $(MEMORY_WORD_REM_UTILS_HDR)
MEMORY_MEMORY_ZERO_OBJ_GROUP		:= $(MEMORY_MEMORY_ZERO_OBJ)		\
					   $(MEMORY_MEMORY_UTILS_OBJ_GROUP)
MEMORY_MEMORY_ZERO_TRNR_SRC_PREQS	:= $(MEMORY_MEMORY_ZERO_TEST_SRC)	\
					   $(TEST_RUNNER_SOURCE_DIR)
MEMORY_MEMORY_ZERO_TEST_OBJ_PREQS	:= $(MEMORY_MEMORY_ZERO_TEST_SRC)	\
					   $(MEMORY_MEMORY_ZERO_OBJ_PREQS) 	\
					   $(UNITY_OBJ_PREQS)
MEMORY_MEMORY_ZERO_TRNR_OBJ_PREQS	:= $(MEMORY_MEMORY_ZERO_TRNR_SRC)	\
					   $(MEMORY_MEMORY_ZERO_TEST_OBJ_PREQS)
MEMORY_MEMORY_ZERO_TEST_BIN_PREQS	:= $(MEMORY_MEMORY_ZERO_TRNR_OBJ)	\
					   $(MEMORY_MEMORY_ZERO_TEST_OBJ)	\
					   $(MEMORY_MEMORY_ZERO_OBJ_GROUP)	\
					   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(MEMORY_MEMORY_ZERO_TEST_BIN)
TARGETS			+= $(MEMORY_MEMORY_ZERO_OBJ)		\
			   $(MEMORY_MEMORY_ZERO_TRNR_SRC)	\
			   $(MEMORY_MEMORY_ZERO_TRNR_OBJ)	\
			   $(MEMORY_MEMORY_ZERO_TEST_OBJ)	\
			   $(MEMORY_MEMORY_ZERO_TEST_BIN)



# memory/memory_copy_array
# ──────────────────────────────────────────────────────────────────────────────
MEMORY_MEMORY_COPY_ARRAY_SRC 		:= $(call HELPER_SOURCE_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_HDR		:= $(call HELPER_HEADER_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_OBJ 		:= $(call HELPER_OBJECT_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,memory memory_copy_array)
MEMORY_MEMORY_COPY_ARRAY_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,memory memory_copy_array)
# ─────────────── target prequisites ───────────────────────────────────────────
MEMORY_MEMORY_COPY_ARRAY_OBJ_PREQS	:= $(MEMORY_MEMORY_COPY_ARRAY_SRC) 		\
			   	   	   $(MEMORY_MEMORY_COPY_ARRAY_HDR)		\
			   	   	   $(MEMORY_MEMORY_SET_WIDTH_HDR)		\
			   	   	   $(MEMORY_WORD_REM_UTILS_HDR)
MEMORY_MEMORY_COPY_ARRAY_OBJ_GROUP	:= $(MEMORY_MEMORY_COPY_ARRAY_OBJ)		\
					   $(MEMORY_MEMORY_UTILS_OBJ_GROUP)
MEMORY_MEMORY_COPY_ARRAY_TRNR_SRC_PREQS	:= $(MEMORY_MEMORY_COPY_ARRAY_TEST_SRC)		\
					   $(TEST_RUNNER_SOURCE_DIR)
MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ_PREQS	:= $(MEMORY_MEMORY_COPY_ARRAY_TEST_SRC)		\
					   $(MEMORY_MEMORY_COPY_ARRAY_OBJ_PREQS) 	\
					   $(UNITY_OBJ_PREQS)
MEMORY_MEMORY_COPY_ARRAY_TRNR_OBJ_PREQS	:= $(MEMORY_MEMORY_COPY_ARRAY_TRNR_SRC)		\
					   $(MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ_PREQS)
MEMORY_MEMORY_COPY_ARRAY_TEST_BIN_PREQS	:= $(MEMORY_MEMORY_COPY_ARRAY_TRNR_OBJ)		\
					   $(MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ)		\
					   $(MEMORY_MEMORY_COPY_ARRAY_OBJ_GROUP)	\
					   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(MEMORY_MEMORY_COPY_ARRAY_TEST_BIN)
TARGETS			+= $(MEMORY_MEMORY_COPY_ARRAY_OBJ)		\
			   $(MEMORY_MEMORY_COPY_ARRAY_TRNR_SRC)		\
			   $(MEMORY_MEMORY_COPY_ARRAY_TRNR_OBJ)		\
			   $(MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ)		\
			   $(MEMORY_MEMORY_COPY_ARRAY_TEST_BIN)


# memory/memory_put_array
# ──────────────────────────────────────────────────────────────────────────────
MEMORY_MEMORY_PUT_ARRAY_SRC 		:= $(call HELPER_SOURCE_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_HDR		:= $(call HELPER_HEADER_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_OBJ 		:= $(call HELPER_OBJECT_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,memory memory_put_array)
MEMORY_MEMORY_PUT_ARRAY_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,memory memory_put_array)
# ─────────────── target prequisites ───────────────────────────────────────────
MEMORY_MEMORY_PUT_ARRAY_OBJ_PREQS	:= $(MEMORY_MEMORY_PUT_ARRAY_SRC) 		\
			   	   	   $(MEMORY_MEMORY_PUT_ARRAY_HDR)		\
			   	   	   $(MEMORY_MEMORY_PUT_WIDTH_HDR)		\
			   	   	   $(MEMORY_WORD_REM_UTILS_HDR)
MEMORY_MEMORY_PUT_ARRAY_OBJ_GROUP	:= $(MEMORY_MEMORY_PUT_ARRAY_OBJ)		\
					   $(MEMORY_MEMORY_UTILS_OBJ_GROUP)
MEMORY_MEMORY_PUT_ARRAY_TRNR_SRC_PREQS	:= $(MEMORY_MEMORY_PUT_ARRAY_TEST_SRC)		\
					   $(TEST_RUNNER_SOURCE_DIR)
MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ_PREQS	:= $(MEMORY_MEMORY_PUT_ARRAY_TEST_SRC)		\
					   $(MEMORY_MEMORY_PUT_ARRAY_OBJ_PREQS) 	\
					   $(UNITY_OBJ_PREQS)
MEMORY_MEMORY_PUT_ARRAY_TRNR_OBJ_PREQS	:= $(MEMORY_MEMORY_PUT_ARRAY_TRNR_SRC)		\
					   $(MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ_PREQS)
MEMORY_MEMORY_PUT_ARRAY_TEST_BIN_PREQS	:= $(MEMORY_MEMORY_PUT_ARRAY_TRNR_OBJ)		\
					   $(MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ)		\
					   $(MEMORY_MEMORY_PUT_ARRAY_OBJ_GROUP)		\
					   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(MEMORY_MEMORY_PUT_ARRAY_TEST_BIN)
TARGETS			+= $(MEMORY_MEMORY_PUT_ARRAY_OBJ)		\
			   $(MEMORY_MEMORY_PUT_ARRAY_TRNR_SRC)		\
			   $(MEMORY_MEMORY_PUT_ARRAY_TRNR_OBJ)		\
			   $(MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ)		\
			   $(MEMORY_MEMORY_PUT_ARRAY_TEST_BIN)


# memory/memory_swap
# ──────────────────────────────────────────────────────────────────────────────
MEMORY_MEMORY_SWAP_SRC 		:= $(call HELPER_SOURCE_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_HDR		:= $(call HELPER_HEADER_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_OBJ 		:= $(call HELPER_OBJECT_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,memory memory_swap)
# ─────────────── target prequisites ───────────────────────────────────────────
MEMORY_MEMORY_SWAP_OBJ_PREQS		:= $(MEMORY_MEMORY_SWAP_SRC) 		\
			   	   	   $(MEMORY_MEMORY_SWAP_HDR)		\
			   	   	   $(MEMORY_MEMORY_SWAP_WIDTH_HDR)	\
					   $(MEMORY_MEMORY_COPY_ARRAY_HDR)
MEMORY_MEMORY_SWAP_OBJ_GROUP		:= $(MEMORY_MEMORY_SWAP_OBJ)		\
					   $(MEMORY_MEMORY_COPY_ARRAY_OBJ_GROUP)
MEMORY_MEMORY_SWAP_TRNR_SRC_PREQS	:= $(MEMORY_MEMORY_SWAP_TEST_SRC)	\
					   $(TEST_RUNNER_SOURCE_DIR)
MEMORY_MEMORY_SWAP_TEST_OBJ_PREQS	:= $(MEMORY_MEMORY_SWAP_TEST_SRC)	\
					   $(MEMORY_MEMORY_SWAP_OBJ_PREQS) 	\
					   $(UNITY_OBJ_PREQS)
MEMORY_MEMORY_SWAP_TRNR_OBJ_PREQS	:= $(MEMORY_MEMORY_SWAP_TRNR_SRC)	\
					   $(MEMORY_MEMORY_SWAP_TEST_OBJ_PREQS)
MEMORY_MEMORY_SWAP_TEST_BIN_PREQS	:= $(MEMORY_MEMORY_SWAP_TRNR_OBJ)	\
					   $(MEMORY_MEMORY_SWAP_TEST_OBJ)	\
					   $(MEMORY_MEMORY_SWAP_OBJ_GROUP)	\
					   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(MEMORY_MEMORY_SWAP_TEST_BIN)
TARGETS			+= $(MEMORY_MEMORY_SWAP_OBJ)			\
			   $(MEMORY_MEMORY_SWAP_TRNR_SRC)		\
			   $(MEMORY_MEMORY_SWAP_TRNR_OBJ)		\
			   $(MEMORY_MEMORY_SWAP_TEST_OBJ)		\
			   $(MEMORY_MEMORY_SWAP_TEST_BIN)

# random/pcg_basic
# ──────────────────────────────────────────────────────────────────────────────
RANDOM_PCG_BASIC_SRC 		:= $(call HELPER_SOURCE_PATH,random pcg_basic)
RANDOM_PCG_BASIC_HDR		:= $(call HELPER_HEADER_PATH,random pcg_basic)
RANDOM_PCG_BASIC_OBJ 		:= $(call HELPER_OBJECT_PATH,random pcg_basic)
RANDOM_PCG_BASIC_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,random pcg_basic)
RANDOM_PCG_BASIC_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,random pcg_basic)
RANDOM_PCG_BASIC_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,random pcg_basic)
RANDOM_PCG_BASIC_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,random pcg_basic)
RANDOM_PCG_BASIC_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,random pcg_basic)
# ─────────────── target prequisites ───────────────────────────────────────────
RANDOM_PCG_BASIC_OBJ_PREQS	:= $(RANDOM_PCG_BASIC_SRC) 		\
			   	   $(RANDOM_PCG_BASIC_HDR)
RANDOM_PCG_BASIC_OBJ_GROUP	:= $(RANDOM_PCG_BASIC_OBJ)
RANDOM_PCG_BASIC_TRNR_SRC_PREQS	:= $(RANDOM_PCG_BASIC_TEST_SRC)		\
				   $(TEST_RUNNER_SOURCE_DIR)
RANDOM_PCG_BASIC_TEST_OBJ_PREQS	:= $(RANDOM_PCG_BASIC_TEST_SRC)		\
			   	   $(RANDOM_PCG_BASIC_OBJ_PREQS) 	\
			   	   $(UNITY_OBJ_PREQS)
RANDOM_PCG_BASIC_TRNR_OBJ_PREQS	:= $(RANDOM_PCG_BASIC_TRNR_SRC)		\
			   	   $(RANDOM_PCG_BASIC_TEST_OBJ_PREQS)
RANDOM_PCG_BASIC_TEST_BIN_PREQS	:= $(RANDOM_PCG_BASIC_TRNR_OBJ)		\
				   $(RANDOM_PCG_BASIC_TEST_OBJ)		\
			   	   $(RANDOM_PCG_BASIC_OBJ_GROUP)	\
			   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(RANDOM_PCG_BASIC_TEST_BIN)
TARGETS			+= $(RANDOM_PCG_BASIC_OBJ)			\
			   $(RANDOM_PCG_BASIC_TRNR_SRC)			\
			   $(RANDOM_PCG_BASIC_TRNR_OBJ)			\
			   $(RANDOM_PCG_BASIC_TEST_OBJ)			\
			   $(RANDOM_PCG_BASIC_TEST_BIN)


# random/random
# ──────────────────────────────────────────────────────────────────────────────
RANDOM_RANDOM_SRC 		:= $(call HELPER_SOURCE_PATH,random random)
RANDOM_RANDOM_HDR		:= $(call HELPER_HEADER_PATH,random random)
RANDOM_RANDOM_TYPES_HDR		:= $(call HELPER_HEADER_PATH,random random_types)
RANDOM_RANDOM_OBJ 		:= $(call HELPER_OBJECT_PATH,random random)
RANDOM_RANDOM_TEST_SRC		:= $(call HELPER_TEST_SOURCE_PATH,random random)
RANDOM_RANDOM_TRNR_SRC		:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,random random)
RANDOM_RANDOM_TRNR_OBJ		:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,random random)
RANDOM_RANDOM_TEST_OBJ		:= $(call HELPER_TEST_OBJECT_PATH,random random)
RANDOM_RANDOM_TEST_BIN		:= $(call HELPER_TEST_BINARY_PATH,random random)
# ─────────────── target prequisites ───────────────────────────────────────────
RANDOM_RANDOM_OBJ_PREQS		:= $(RANDOM_RANDOM_SRC) 		\
			   	   $(RANDOM_RANDOM_HDR)			\
			   	   $(RANDOM_RANDOM_TYPES_HDR)		\
			   	   $(MEMORY_MEMORY_SWAP_HDR)
RANDOM_RANDOM_OBJ_GROUP		:= $(RANDOM_RANDOM_OBJ)			\
			   	   $(RANDOM_PCG_BASIC_OBJ)		\
			   	   $(MEMORY_MEMORY_SWAP_OBJ_GROUP)
RANDOM_RANDOM_TRNR_SRC_PREQS	:= $(RANDOM_RANDOM_TEST_SRC)		\
				   $(TEST_RUNNER_SOURCE_DIR)
RANDOM_RANDOM_TEST_OBJ_PREQS	:= $(RANDOM_RANDOM_TEST_SRC)		\
			   	   $(RANDOM_RANDOM_OBJ_PREQS) 		\
			   	   $(UNITY_OBJ_PREQS)
RANDOM_RANDOM_TRNR_OBJ_PREQS	:= $(RANDOM_RANDOM_TRNR_SRC)		\
			   	   $(RANDOM_RANDOM_TEST_OBJ_PREQS)
RANDOM_RANDOM_TEST_BIN_PREQS	:= $(RANDOM_RANDOM_TRNR_OBJ)		\
				   $(RANDOM_RANDOM_TEST_OBJ)		\
			   	   $(RANDOM_RANDOM_OBJ_GROUP)		\
			   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(RANDOM_RANDOM_TEST_BIN)
TARGETS			+= $(RANDOM_RANDOM_OBJ)				\
			   $(RANDOM_RANDOM_TRNR_SRC)			\
			   $(RANDOM_RANDOM_TRNR_OBJ)			\
			   $(RANDOM_RANDOM_TEST_OBJ)			\
			   $(RANDOM_RANDOM_TEST_BIN)


# string/ascii_utils
# ──────────────────────────────────────────────────────────────────────────────
STRING_ASCII_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,string ascii_utils)
STRING_ASCII_UTILS_HDR		:= $(call HELPER_HEADER_PATH,string ascii_utils)
STRING_ASCII_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,string ascii_utils)
STRING_ASCII_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,string ascii_utils)
STRING_ASCII_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,string ascii_utils)
STRING_ASCII_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,string ascii_utils)
STRING_ASCII_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,string ascii_utils)
STRING_ASCII_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,string ascii_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
STRING_ASCII_UTILS_OBJ_PREQS		:= $(STRING_ASCII_UTILS_SRC) 			\
			   		   $(STRING_ASCII_UTILS_HDR)			\
					   $(UTILS_TYPES_OCTET_HDR)
STRING_ASCII_UTILS_OBJ_GROUP		:= $(STRING_ASCII_UTILS_OBJ)
STRING_ASCII_UTILS_TRNR_SRC_PREQS	:= $(STRING_ASCII_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
STRING_ASCII_UTILS_TEST_OBJ_PREQS	:= $(STRING_ASCII_UTILS_TEST_SRC)		\
			   		   $(STRING_ASCII_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
STRING_ASCII_UTILS_TRNR_OBJ_PREQS	:= $(STRING_ASCII_UTILS_TRNR_SRC)		\
			   		   $(STRING_ASCII_UTILS_TEST_OBJ_PREQS)
STRING_ASCII_UTILS_TEST_BIN_PREQS	:= $(STRING_ASCII_UTILS_TRNR_OBJ)		\
			   		   $(STRING_ASCII_UTILS_TEST_OBJ)		\
			   		   $(STRING_ASCII_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(STRING_ASCII_UTILS_TEST_BIN)
TARGETS			+= $(STRING_ASCII_UTILS_OBJ)					\
			   $(STRING_ASCII_UTILS_TRNR_SRC)				\
			   $(STRING_ASCII_UTILS_TRNR_OBJ)				\
			   $(STRING_ASCII_UTILS_TEST_OBJ)				\
			   $(STRING_ASCII_UTILS_TEST_BIN)


# string/utf8_utils
# ──────────────────────────────────────────────────────────────────────────────
STRING_UTF8_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,string utf8_utils)
STRING_UTF8_UTILS_HDR		:= $(call HELPER_HEADER_PATH,string utf8_utils)
STRING_UTF8_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,string utf8_utils)
STRING_UTF8_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,string utf8_utils)
STRING_UTF8_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,string utf8_utils)
STRING_UTF8_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,string utf8_utils)
STRING_UTF8_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,string utf8_utils)
STRING_UTF8_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,string utf8_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
STRING_UTF8_UTILS_OBJ_PREQS		:= $(STRING_UTF8_UTILS_SRC) 			\
			   		   $(STRING_UTF8_UTILS_HDR)			\
					   $(STRING_STRING_MACROS_HDR)			\
					   $(UTILS_CLOSURE_HDR)				\
					   $(UTILS_TYPES_OCTET_HDR)			\
					   $(UTILS_CHAR_ATTRS_HDR)
STRING_UTF8_UTILS_OBJ_GROUP		:= $(STRING_UTF8_UTILS_OBJ)			\
					   $(UTILS_CLOSURE_OBJ_GROUP)
STRING_UTF8_UTILS_TRNR_SRC_PREQS	:= $(STRING_UTF8_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
STRING_UTF8_UTILS_TEST_OBJ_PREQS	:= $(STRING_UTF8_UTILS_TEST_SRC)		\
			   		   $(STRING_UTF8_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
STRING_UTF8_UTILS_TRNR_OBJ_PREQS	:= $(STRING_UTF8_UTILS_TRNR_SRC)		\
			   		   $(STRING_UTF8_UTILS_TEST_OBJ_PREQS)
STRING_UTF8_UTILS_TEST_BIN_PREQS	:= $(STRING_UTF8_UTILS_TRNR_OBJ)		\
			   		   $(STRING_UTF8_UTILS_TEST_OBJ)		\
			   		   $(STRING_UTF8_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(STRING_UTF8_UTILS_TEST_BIN)
TARGETS			+= $(STRING_UTF8_UTILS_OBJ)					\
			   $(STRING_UTF8_UTILS_TRNR_SRC)				\
			   $(STRING_UTF8_UTILS_TRNR_OBJ)				\
			   $(STRING_UTF8_UTILS_TEST_OBJ)				\
			   $(STRING_UTF8_UTILS_TEST_BIN)


# string/string_utils
# ──────────────────────────────────────────────────────────────────────────────
STRING_STRING_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,string string_utils)
STRING_STRING_UTILS_HDR			:= $(call HELPER_HEADER_PATH,string string_utils)
STRING_STRING_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,string string_utils)
STRING_STRING_UTILS_TEST_SRC		:= $(call HELPER_TEST_SOURCE_PATH,string string_utils)
STRING_STRING_UTILS_TRNR_SRC		:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,string string_utils)
STRING_STRING_UTILS_TRNR_OBJ		:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,string string_utils)
STRING_STRING_UTILS_TEST_OBJ		:= $(call HELPER_TEST_OBJECT_PATH,string string_utils)
STRING_STRING_UTILS_TEST_BIN		:= $(call HELPER_TEST_BINARY_PATH,string string_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
STRING_STRING_UTILS_OBJ_PREQS		:= $(STRING_STRING_UTILS_SRC) 			\
			   		   $(STRING_STRING_UTILS_HDR)			\
			   		   $(MEMORY_MEMORY_PUT_ARRAY_HDR)		\
			   		   $(UTILS_TYPES_WORD_PATTERN_HDR)		\
			   		   $(STRING_INT_STRING_ATTRS_HDR)		\
			   		   $(STRING_PTR_STRING_ATTRS_HDR)		\
			   		   $(STRING_ASCII_UTILS_HDR)			\
			   		   $(STRING_UTF8_UTILS_HDR)			\
			   		   $(STRING_STRING_MACROS_HDR)
STRING_STRING_UTILS_OBJ_GROUP		:= $(STRING_STRING_UTILS_OBJ)			\
			   		   $(MEMORY_MEMORY_PUT_ARRAY_OBJ_GROUP)		\
					   $(STRING_ASCII_UTILS_OBJ_GROUP)		\
					   $(STRING_UTF8_UTILS_OBJ_GROUP)
STRING_STRING_UTILS_TRNR_SRC_PREQS	:= $(STRING_STRING_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
STRING_STRING_UTILS_TEST_OBJ_PREQS	:= $(STRING_STRING_UTILS_TEST_SRC)		\
			   		   $(STRING_STRING_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
STRING_STRING_UTILS_TRNR_OBJ_PREQS	:= $(STRING_STRING_UTILS_TRNR_SRC)		\
			   		   $(STRING_STRING_UTILS_TEST_OBJ_PREQS)
STRING_STRING_UTILS_TEST_BIN_PREQS	:= $(STRING_STRING_UTILS_TRNR_OBJ)		\
			   		   $(STRING_STRING_UTILS_TEST_OBJ)		\
			   		   $(STRING_STRING_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(STRING_STRING_UTILS_TEST_BIN)
TARGETS			+= $(STRING_STRING_UTILS_OBJ)					\
			   $(STRING_STRING_UTILS_TRNR_SRC)				\
			   $(STRING_STRING_UTILS_TRNR_OBJ)				\
			   $(STRING_STRING_UTILS_TEST_OBJ)				\
			   $(STRING_STRING_UTILS_TEST_BIN)


# system/system_utils
# ──────────────────────────────────────────────────────────────────────────────
SYSTEM_SYSTEM_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_HDR			:= $(call HELPER_HEADER_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_TEST_SRC		:= $(call HELPER_TEST_SOURCE_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_TRNR_SRC		:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_TRNR_OBJ		:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_TEST_OBJ		:= $(call HELPER_TEST_OBJECT_PATH,system system_utils)
SYSTEM_SYSTEM_UTILS_TEST_BIN		:= $(call HELPER_TEST_BINARY_PATH,system system_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
SYSTEM_SYSTEM_UTILS_OBJ_PREQS		:= $(SYSTEM_SYSTEM_UTILS_SRC) 			\
			   		   $(SYSTEM_SYSTEM_UTILS_HDR)			\
			   		   $(UTILS_CLOSURE_HDR)				\
			   		   $(UTILS_FAIL_SWITCH_HDR)
SYSTEM_SYSTEM_UTILS_OBJ_GROUP		:= $(SYSTEM_SYSTEM_UTILS_OBJ)			\
					   $(UTILS_CLOSURE_OBJ_GROUP)
SYSTEM_SYSTEM_UTILS_TRNR_SRC_PREQS	:= $(SYSTEM_SYSTEM_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
SYSTEM_SYSTEM_UTILS_TEST_OBJ_PREQS	:= $(SYSTEM_SYSTEM_UTILS_TEST_SRC)		\
			   		   $(SYSTEM_SYSTEM_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
SYSTEM_SYSTEM_UTILS_TRNR_OBJ_PREQS	:= $(SYSTEM_SYSTEM_UTILS_TRNR_SRC)		\
			   		   $(SYSTEM_SYSTEM_UTILS_TEST_OBJ_PREQS)
SYSTEM_SYSTEM_UTILS_TEST_BIN_PREQS	:= $(SYSTEM_SYSTEM_UTILS_TRNR_OBJ)		\
			   		   $(SYSTEM_SYSTEM_UTILS_TEST_OBJ)		\
			   		   $(SYSTEM_SYSTEM_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(SYSTEM_SYSTEM_UTILS_TEST_BIN)
TARGETS			+= $(SYSTEM_SYSTEM_UTILS_OBJ)					\
			   $(SYSTEM_SYSTEM_UTILS_TRNR_SRC)				\
			   $(SYSTEM_SYSTEM_UTILS_TRNR_OBJ)				\
			   $(SYSTEM_SYSTEM_UTILS_TEST_OBJ)				\
			   $(SYSTEM_SYSTEM_UTILS_TEST_BIN)


# system/file_utils
# ──────────────────────────────────────────────────────────────────────────────
SYSTEM_FILE_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,system file_utils)
SYSTEM_FILE_UTILS_HDR		:= $(call HELPER_HEADER_PATH,system file_utils)
SYSTEM_FILE_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,system file_utils)
SYSTEM_FILE_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,system file_utils)
SYSTEM_FILE_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,system file_utils)
SYSTEM_FILE_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,system file_utils)
SYSTEM_FILE_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,system file_utils)
SYSTEM_FILE_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,system file_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
SYSTEM_FILE_UTILS_OBJ_PREQS		:= $(SYSTEM_FILE_UTILS_SRC) 			\
			   		   $(SYSTEM_FILE_UTILS_HDR)			\
			   		   $(UTILS_UTILS_HDR)				\
			   		   $(SYSTEM_SYSTEM_UTILS_HDR)			\
					   $(STRING_STRING_UTILS_HDR)
SYSTEM_FILE_UTILS_OBJ_GROUP		:= $(SYSTEM_FILE_UTILS_OBJ)			\
			   		   $(UTILS_UTILS_OBJ_GROUP)			\
					   $(SYSTEM_SYSTEM_UTILS_OBJ_GROUP)		\
					   $(STRING_STRING_UTILS_OBJ_GROUP)
SYSTEM_FILE_UTILS_TRNR_SRC_PREQS	:= $(SYSTEM_FILE_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
SYSTEM_FILE_UTILS_TEST_OBJ_PREQS	:= $(SYSTEM_FILE_UTILS_TEST_SRC)		\
			   		   $(SYSTEM_FILE_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
SYSTEM_FILE_UTILS_TRNR_OBJ_PREQS	:= $(SYSTEM_FILE_UTILS_TRNR_SRC)		\
			   		   $(SYSTEM_FILE_UTILS_TEST_OBJ_PREQS)
SYSTEM_FILE_UTILS_TEST_BIN_PREQS	:= $(SYSTEM_FILE_UTILS_TRNR_OBJ)		\
			   		   $(SYSTEM_FILE_UTILS_TEST_OBJ)		\
			   		   $(SYSTEM_FILE_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(SYSTEM_FILE_UTILS_TEST_BIN)
TARGETS			+= $(SYSTEM_FILE_UTILS_OBJ)					\
			   $(SYSTEM_FILE_UTILS_TRNR_SRC)				\
			   $(SYSTEM_FILE_UTILS_TRNR_OBJ)				\
			   $(SYSTEM_FILE_UTILS_TEST_OBJ)				\
			   $(SYSTEM_FILE_UTILS_TEST_BIN)


# system/exit_utils
# ──────────────────────────────────────────────────────────────────────────────
SYSTEM_EXIT_UTILS_SRC 		:= $(call HELPER_SOURCE_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_HDR		:= $(call HELPER_HEADER_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_OBJ 		:= $(call HELPER_OBJECT_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,system exit_utils)
SYSTEM_EXIT_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,system exit_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
SYSTEM_EXIT_UTILS_OBJ_PREQS		:= $(SYSTEM_EXIT_UTILS_SRC) 			\
			   		   $(SYSTEM_EXIT_UTILS_HDR)			\
			   		   $(SYSTEM_FILE_UTILS_HDR)			\
					   $(UTILS_TYPES_ACTION_HDR)
SYSTEM_EXIT_UTILS_OBJ_GROUP		:= $(SYSTEM_EXIT_UTILS_OBJ)			\
					   $(SYSTEM_FILE_UTILS_OBJ_GROUP)
SYSTEM_EXIT_UTILS_TRNR_SRC_PREQS	:= $(SYSTEM_EXIT_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
SYSTEM_EXIT_UTILS_TEST_OBJ_PREQS	:= $(SYSTEM_EXIT_UTILS_TEST_SRC)		\
			   		   $(SYSTEM_EXIT_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
SYSTEM_EXIT_UTILS_TRNR_OBJ_PREQS	:= $(SYSTEM_EXIT_UTILS_TRNR_SRC)		\
			   		   $(SYSTEM_EXIT_UTILS_TEST_OBJ_PREQS)
SYSTEM_EXIT_UTILS_TEST_BIN_PREQS	:= $(SYSTEM_EXIT_UTILS_TRNR_OBJ)		\
			   		   $(SYSTEM_EXIT_UTILS_TEST_OBJ)		\
			   		   $(SYSTEM_EXIT_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(SYSTEM_EXIT_UTILS_TEST_BIN)
TARGETS			+= $(SYSTEM_EXIT_UTILS_OBJ)					\
			   $(SYSTEM_EXIT_UTILS_TRNR_SRC)				\
			   $(SYSTEM_EXIT_UTILS_TRNR_OBJ)				\
			   $(SYSTEM_EXIT_UTILS_TEST_OBJ)				\
			   $(SYSTEM_EXIT_UTILS_TEST_BIN)


# thread/thread_utils
# ──────────────────────────────────────────────────────────────────────────────
THREAD_THREAD_UTILS_SRC 	:= $(call HELPER_SOURCE_PATH,thread thread_utils)
THREAD_THREAD_UTILS_HDR		:= $(call HELPER_HEADER_PATH,thread thread_utils)
THREAD_THREAD_UTILS_OBJ 	:= $(call HELPER_OBJECT_PATH,thread thread_utils)
THREAD_THREAD_UTILS_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,thread thread_utils)
THREAD_THREAD_UTILS_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,thread thread_utils)
THREAD_THREAD_UTILS_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,thread thread_utils)
THREAD_THREAD_UTILS_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,thread thread_utils)
THREAD_THREAD_UTILS_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,thread thread_utils)
# ─────────────── target prequisites ───────────────────────────────────────────
THREAD_THREAD_UTILS_OBJ_PREQS		:= $(THREAD_THREAD_UTILS_SRC)			\
			   	   	   $(THREAD_THREAD_UTILS_HDR)			\
			   	   	   $(MEMORY_MEMORY_COPY_ARRAY_HDR)		\
			   	   	   $(TIME_TIME_UTILS_HDR)			\
			   	   	   $(UTILS_CLOSURE_HDR)				\
			   	   	   $(UTILS_FAIL_SWITCH_HDR)
THREAD_THREAD_UTILS_OBJ_GROUP		:= $(THREAD_THREAD_UTILS_OBJ)			\
			   	   	   $(MEMORY_MEMORY_COPY_ARRAY_OBJ_GROUP)	\
			   	   	   $(TIME_TIME_UTILS_OBJ_GROUP)			\
			   	   	   $(UTILS_CLOSURE_OBJ_GROUP)
THREAD_THREAD_UTILS_TRNR_SRC_PREQS	:= $(THREAD_THREAD_UTILS_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
THREAD_THREAD_UTILS_TEST_OBJ_PREQS	:= $(THREAD_THREAD_UTILS_TEST_SRC)		\
			   		   $(THREAD_THREAD_UTILS_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
THREAD_THREAD_UTILS_TRNR_OBJ_PREQS	:= $(THREAD_THREAD_UTILS_TRNR_SRC)		\
			   		   $(THREAD_THREAD_UTILS_TEST_OBJ_PREQS)
THREAD_THREAD_UTILS_TEST_BIN_PREQS	:= $(THREAD_THREAD_UTILS_TRNR_OBJ)		\
			   		   $(THREAD_THREAD_UTILS_TEST_OBJ)		\
			   		   $(THREAD_THREAD_UTILS_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(THREAD_THREAD_UTILS_TEST_BIN)
TARGETS			+= $(THREAD_THREAD_UTILS_OBJ)			\
			   $(THREAD_THREAD_UTILS_TRNR_SRC)		\
			   $(THREAD_THREAD_UTILS_TRNR_OBJ)		\
			   $(THREAD_THREAD_UTILS_TEST_OBJ)		\
			   $(THREAD_THREAD_UTILS_TEST_BIN)


# thread/task_queue
# ──────────────────────────────────────────────────────────────────────────────
THREAD_TASK_QUEUE_SRC 	:= $(call HELPER_SOURCE_PATH,thread task_queue)
THREAD_TASK_QUEUE_HDR		:= $(call HELPER_HEADER_PATH,thread task_queue)
THREAD_TASK_QUEUE_OBJ 	:= $(call HELPER_OBJECT_PATH,thread task_queue)
THREAD_TASK_QUEUE_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,thread task_queue)
THREAD_TASK_QUEUE_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,thread task_queue)
THREAD_TASK_QUEUE_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,thread task_queue)
THREAD_TASK_QUEUE_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,thread task_queue)
THREAD_TASK_QUEUE_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,thread task_queue)
# ─────────────── target prequisites ───────────────────────────────────────────
THREAD_TASK_QUEUE_OBJ_PREQS		:= $(THREAD_TASK_QUEUE_SRC) 		\
			   		   $(THREAD_TASK_QUEUE_HDR) 		\
			   		   $(THREAD_THREAD_UTILS_HDR)
THREAD_TASK_QUEUE_OBJ_GROUP		:= $(THREAD_TASK_QUEUE_OBJ)		\
					   $(THREAD_THREAD_UTILS_OBJ_GROUP)
THREAD_TASK_QUEUE_TRNR_SRC_PREQS	:= $(THREAD_TASK_QUEUE_TEST_SRC)	\
			   		   $(TEST_RUNNER_SOURCE_DIR)
THREAD_TASK_QUEUE_TEST_OBJ_PREQS	:= $(THREAD_TASK_QUEUE_TEST_SRC)	\
			   		   $(THREAD_TASK_QUEUE_OBJ_PREQS) 	\
			   		   $(UNITY_OBJ_PREQS)
THREAD_TASK_QUEUE_TRNR_OBJ_PREQS	:= $(THREAD_TASK_QUEUE_TRNR_SRC)	\
			   		   $(THREAD_TASK_QUEUE_TEST_OBJ_PREQS)
THREAD_TASK_QUEUE_TEST_BIN_PREQS	:= $(THREAD_TASK_QUEUE_TRNR_OBJ)	\
			   		   $(THREAD_TASK_QUEUE_TEST_OBJ)	\
			   		   $(THREAD_TASK_QUEUE_OBJ_GROUP)	\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(THREAD_TASK_QUEUE_TEST_BIN)
TARGETS			+= $(THREAD_TASK_QUEUE_OBJ)			\
			   $(THREAD_TASK_QUEUE_TRNR_SRC)		\
			   $(THREAD_TASK_QUEUE_TRNR_OBJ)		\
			   $(THREAD_TASK_QUEUE_TEST_OBJ)		\
			   $(THREAD_TASK_QUEUE_TEST_BIN)


# thread/thread_log
# ──────────────────────────────────────────────────────────────────────────────
THREAD_THREAD_LOG_SRC 		:= $(call HELPER_SOURCE_PATH,thread thread_log)
THREAD_THREAD_LOG_HDR		:= $(call HELPER_HEADER_PATH,thread thread_log)
THREAD_THREAD_LOG_OBJ 		:= $(call HELPER_OBJECT_PATH,thread thread_log)
THREAD_THREAD_LOG_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,thread thread_log)
THREAD_THREAD_LOG_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,thread thread_log)
THREAD_THREAD_LOG_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,thread thread_log)
THREAD_THREAD_LOG_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,thread thread_log)
THREAD_THREAD_LOG_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,thread thread_log)
# ─────────────── target prequisites ───────────────────────────────────────────
THREAD_THREAD_LOG_OBJ_PREQS		:= $(THREAD_THREAD_LOG_SRC) 		\
			   		   $(THREAD_THREAD_LOG_HDR) 		\
			   		   $(THREAD_THREAD_UTILS_HDR)		\
			   		   $(STRING_STRING_UTILS_HDR)		\
			   		   $(SYSTEM_FILE_UTILS_HDR)
THREAD_THREAD_LOG_OBJ_GROUP		:= $(THREAD_THREAD_LOG_OBJ)		\
					   $(THREAD_THREAD_UTILS_OBJ_GROUP)	\
					   $(STRING_STRING_UTILS_OBJ_GROUP)	\
					   $(SYSTEM_FILE_UTILS_OBJ_GROUP)
THREAD_THREAD_LOG_TRNR_SRC_PREQS	:= $(THREAD_THREAD_LOG_TEST_SRC)	\
			   		   $(TEST_RUNNER_SOURCE_DIR)
THREAD_THREAD_LOG_TEST_OBJ_PREQS	:= $(THREAD_THREAD_LOG_TEST_SRC)	\
			   		   $(THREAD_THREAD_LOG_OBJ_PREQS) 	\
			   		   $(UNITY_OBJ_PREQS)
THREAD_THREAD_LOG_TRNR_OBJ_PREQS	:= $(THREAD_THREAD_LOG_TRNR_SRC)	\
			   		   $(THREAD_THREAD_LOG_TEST_OBJ_PREQS)
THREAD_THREAD_LOG_TEST_BIN_PREQS	:= $(THREAD_THREAD_LOG_TRNR_OBJ)	\
			   		   $(THREAD_THREAD_LOG_TEST_OBJ)	\
			   		   $(THREAD_THREAD_LOG_OBJ_GROUP)	\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(THREAD_THREAD_LOG_TEST_BIN)
TARGETS			+= $(THREAD_THREAD_LOG_OBJ)		\
			   $(THREAD_THREAD_LOG_TRNR_SRC)	\
			   $(THREAD_THREAD_LOG_TRNR_OBJ)	\
			   $(THREAD_THREAD_LOG_TEST_OBJ)	\
			   $(THREAD_THREAD_LOG_TEST_BIN)


# thread/thread_pool
# ──────────────────────────────────────────────────────────────────────────────
THREAD_THREAD_POOL_SRC 		:= $(call HELPER_SOURCE_PATH,thread thread_pool)
THREAD_THREAD_POOL_HDR		:= $(call HELPER_HEADER_PATH,thread thread_pool)
THREAD_THREAD_POOL_OBJ 		:= $(call HELPER_OBJECT_PATH,thread thread_pool)
THREAD_THREAD_POOL_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,thread thread_pool)
THREAD_THREAD_POOL_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,thread thread_pool)
THREAD_THREAD_POOL_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,thread thread_pool)
THREAD_THREAD_POOL_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,thread thread_pool)
THREAD_THREAD_POOL_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,thread thread_pool)
# ─────────────── target prequisites ───────────────────────────────────────────
THREAD_THREAD_POOL_OBJ_PREQS		:= $(THREAD_THREAD_POOL_SRC) 		\
			   		   $(THREAD_THREAD_POOL_HDR) 		\
			   		   $(THREAD_THREAD_UTILS_HDR)		\
			   		   $(THREAD_THREAD_LOG_HDR)
THREAD_THREAD_POOL_OBJ_GROUP		:= $(THREAD_THREAD_POOL_OBJ)		\
					   $(THREAD_THREAD_LOG_OBJ_GROUP)	\
					   $(THREAD_TASK_QUEUE_OBJ_GROUP)
THREAD_THREAD_POOL_TRNR_SRC_PREQS	:= $(THREAD_THREAD_POOL_TEST_SRC)	\
			   		   $(TEST_RUNNER_SOURCE_DIR)
THREAD_THREAD_POOL_TEST_OBJ_PREQS	:= $(THREAD_THREAD_POOL_TEST_SRC)	\
			   		   $(THREAD_THREAD_POOL_OBJ_PREQS) 	\
			   		   $(UNITY_OBJ_PREQS)
THREAD_THREAD_POOL_TRNR_OBJ_PREQS	:= $(THREAD_THREAD_POOL_TRNR_SRC)	\
			   		   $(THREAD_THREAD_POOL_TEST_OBJ_PREQS)
THREAD_THREAD_POOL_TEST_BIN_PREQS	:= $(THREAD_THREAD_POOL_TRNR_OBJ)	\
			   		   $(THREAD_THREAD_POOL_TEST_OBJ)	\
			   		   $(THREAD_THREAD_POOL_OBJ_GROUP)	\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(THREAD_THREAD_POOL_TEST_BIN)
TARGETS			+= $(THREAD_THREAD_POOL_OBJ)			\
			   $(THREAD_THREAD_POOL_TRNR_SRC)		\
			   $(THREAD_THREAD_POOL_TRNR_OBJ)		\
			   $(THREAD_THREAD_POOL_TEST_OBJ)		\
			   $(THREAD_THREAD_POOL_TEST_BIN)

## PROJECT-HELPER MODULES
# ══════════════════════════════════════════════════════════════════════════════
# mysql_seed_file
# ──────────────────────────────────────────────────────────────────────────────
FILE_SRC 		:= $(call PROJECT_SOURCE_PATH,file)
FILE_HDR		:= $(call PROJECT_HEADER_PATH,file)
FILE_OBJ 		:= $(call PROJECT_OBJECT_PATH,file)
FILE_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,file)
FILE_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,file)
FILE_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,file)
FILE_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,file)
FILE_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,file)
# ─────────────── target prequisites ───────────────────────────────────────────
FILE_OBJ_PREQS		:= $(FILE_SRC) 					\
			   $(FILE_HDR) 					\
			   $(SYSTEM_EXIT_UTILS_HDR)			\
			   $(THREAD_THREAD_UTILS_HDR)
FILE_OBJ_GROUP		:= $(FILE_OBJ)					\
			   $(SYSTEM_EXIT_UTILS_OBJ_GROUP)		\
			   $(THREAD_THREAD_UTILS_OBJ_GROUP)
FILE_TRNR_SRC_PREQS	:= $(FILE_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
FILE_TEST_OBJ_PREQS	:= $(FILE_TEST_SRC)				\
			   $(FILE_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
FILE_TRNR_OBJ_PREQS	:= $(FILE_TRNR_SRC)				\
			   $(FILE_TEST_OBJ_PREQS)
FILE_TEST_BIN_PREQS	:= $(FILE_TRNR_OBJ)				\
			   $(FILE_TEST_OBJ)				\
			   $(FILE_OBJ_GROUP)				\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(FILE_TEST_BIN)
TARGETS			+= $(FILE_OBJ)					\
			   $(FILE_TRNR_SRC)				\
			   $(FILE_TRNR_OBJ)				\
			   $(FILE_TEST_OBJ)				\
			   $(FILE_TEST_BIN)




## GENERATE MODULES
# ══════════════════════════════════════════════════════════════════════════════
# generate/generator
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_GENERATOR_SRC 		:= $(call HELPER_SOURCE_PATH,generate generator)
GENERATE_GENERATOR_HDR		:= $(call HELPER_HEADER_PATH,generate generator)
GENERATE_GENERATOR_OBJ 		:= $(call HELPER_OBJECT_PATH,generate generator)
GENERATE_GENERATOR_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate generator)
GENERATE_GENERATOR_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate generator)
GENERATE_GENERATOR_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate generator)
GENERATE_GENERATOR_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate generator)
GENERATE_GENERATOR_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate generator)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_GENERATOR_OBJ_PREQS		:= $(GENERATE_GENERATOR_SRC) 		\
			     	   	   $(GENERATE_GENERATOR_HDR)		\
			     	   	   $(FILE_HDR)				\
			      	   	   $(THREAD_THREAD_POOL_HDR)
GENERATE_GENERATOR_OBJ_GROUP		:= $(GENERATE_GENERATOR_OBJ) 		\
				   	   $(FILE_OBJ_GROUP)			\
				   	   $(THREAD_THREAD_POOL_OBJ_GROUP)
GENERATE_GENERATOR_TRNR_SRC_PREQS	:= $(GENERATE_GENERATOR_TEST_SRC)	\
				   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_GENERATOR_TEST_OBJ_PREQS	:= $(GENERATE_GENERATOR_TEST_SRC)	\
			   	   	   $(GENERATE_GENERATOR_OBJ_PREQS)	\
			   	   	   $(UNITY_OBJ_PREQS)
GENERATE_GENERATOR_TRNR_OBJ_PREQS	:= $(GENERATE_GENERATOR_TRNR_SRC)	\
			   	   	   $(GENERATE_GENERATOR_TEST_OBJ_PREQS)
GENERATE_GENERATOR_TEST_BIN_PREQS	:= $(GENERATE_GENERATOR_TRNR_OBJ)	\
				   	   $(GENERATE_GENERATOR_TEST_OBJ)	\
			   	   	   $(GENERATE_GENERATOR_OBJ_GROUP)	\
			   	   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_GENERATOR_TEST_BIN)
TARGETS			+= $(GENERATE_GENERATOR_OBJ)			\
			   $(GENERATE_GENERATOR_TRNR_SRC)		\
			   $(GENERATE_GENERATOR_TRNR_OBJ)		\
			   $(GENERATE_GENERATOR_TEST_OBJ)		\
			   $(GENERATE_GENERATOR_TEST_BIN)


# generate/counter
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_COUNTER_SRC 		:= $(call HELPER_SOURCE_PATH,generate counter)
GENERATE_COUNTER_HDR		:= $(call HELPER_HEADER_PATH,generate counter)
GENERATE_COUNTER_OBJ 		:= $(call HELPER_OBJECT_PATH,generate counter)
GENERATE_COUNTER_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate counter)
GENERATE_COUNTER_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate counter)
GENERATE_COUNTER_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate counter)
GENERATE_COUNTER_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate counter)
GENERATE_COUNTER_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate counter)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_COUNTER_OBJ_PREQS	:= $(GENERATE_COUNTER_SRC) 		\
				   $(GENERATE_COUNTER_HDR) 		\
				   $(GENERATE_GENERATOR_HDR)
GENERATE_COUNTER_OBJ_GROUP	:= $(GENERATE_COUNTER_OBJ) 		\
				   $(GENERATE_GENERATOR_OBJ_GROUP)
GENERATE_COUNTER_TRNR_SRC_PREQS	:= $(GENERATE_COUNTER_TEST_SRC)		\
			   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_COUNTER_TEST_OBJ_PREQS	:= $(GENERATE_COUNTER_TEST_SRC)		\
			   	   $(GENERATE_COUNTER_OBJ_PREQS) 	\
			   	   $(UNITY_OBJ_PREQS)
GENERATE_COUNTER_TRNR_OBJ_PREQS	:= $(GENERATE_COUNTER_TRNR_SRC)		\
			   	   $(GENERATE_COUNTER_TEST_OBJ_PREQS)
GENERATE_COUNTER_TEST_BIN_PREQS	:= $(GENERATE_COUNTER_TRNR_OBJ)		\
			   	   $(GENERATE_COUNTER_TEST_OBJ)		\
			   	   $(GENERATE_COUNTER_OBJ_GROUP)	\
			           $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_COUNTER_TEST_BIN)
TARGETS			+= $(GENERATE_COUNTER_OBJ)			\
			   $(GENERATE_COUNTER_TRNR_SRC)			\
			   $(GENERATE_COUNTER_TRNR_OBJ)			\
			   $(GENERATE_COUNTER_TEST_OBJ)			\
			   $(GENERATE_COUNTER_TEST_BIN)


# generate/column_string_names
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_COLUMN_STRING_NAMES_SRC 	:= $(call HELPER_SOURCE_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_HDR	:= $(call HELPER_HEADER_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_OBJ 	:= $(call HELPER_OBJECT_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate column_string_names)
GENERATE_COLUMN_STRING_NAMES_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate column_string_names)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_COLUMN_STRING_NAMES_OBJ_PREQS		:= $(GENERATE_COLUMN_STRING_NAMES_SRC) 			\
			     	   		   $(GENERATE_COLUMN_STRING_NAMES_HDR)			\
			      	   	   	   $(RANDOM_RANDOM_HDR)
GENERATE_COLUMN_STRING_NAMES_OBJ_GROUP		:= $(GENERATE_COLUMN_STRING_NAMES_OBJ) 			\
				   	   	   $(RANDOM_RANDOM_OBJ_GROUP)				\
				   	   	   $(GENERATE_GENERATOR_OBJ_GROUP)
GENERATE_COLUMN_STRING_NAMES_TRNR_SRC_PREQS	:= $(GENERATE_COLUMN_STRING_NAMES_TEST_SRC)		\
				   	   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_COLUMN_STRING_NAMES_TEST_OBJ_PREQS	:= $(GENERATE_COLUMN_STRING_NAMES_TEST_SRC)		\
			   	   	   	   $(GENERATE_COLUMN_STRING_NAMES_OBJ_PREQS)		\
			   	   	   	   $(UNITY_OBJ_PREQS)
GENERATE_COLUMN_STRING_NAMES_TRNR_OBJ_PREQS	:= $(GENERATE_COLUMN_STRING_NAMES_TRNR_SRC)		\
			   	   	   	   $(GENERATE_COLUMN_STRING_NAMES_TEST_OBJ_PREQS)
GENERATE_COLUMN_STRING_NAMES_TEST_BIN_PREQS	:= $(GENERATE_COLUMN_STRING_NAMES_TRNR_OBJ)		\
				   	   	   $(GENERATE_COLUMN_STRING_NAMES_TEST_OBJ)		\
			   	   	   	   $(GENERATE_COLUMN_STRING_NAMES_OBJ_GROUP)		\
			   	   	   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_COLUMN_STRING_NAMES_TEST_BIN)
TARGETS			+= $(GENERATE_COLUMN_STRING_NAMES_OBJ)			\
			   $(GENERATE_COLUMN_STRING_NAMES_TRNR_SRC)		\
			   $(GENERATE_COLUMN_STRING_NAMES_TRNR_OBJ)		\
			   $(GENERATE_COLUMN_STRING_NAMES_TEST_OBJ)		\
			   $(GENERATE_COLUMN_STRING_NAMES_TEST_BIN)


# generate/column_string
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_COLUMN_STRING_SRC 	:= $(call HELPER_SOURCE_PATH,generate column_string)
GENERATE_COLUMN_STRING_HDR	:= $(call HELPER_HEADER_PATH,generate column_string)
GENERATE_COLUMN_STRING_OBJ 	:= $(call HELPER_OBJECT_PATH,generate column_string)
GENERATE_COLUMN_STRING_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate column_string)
GENERATE_COLUMN_STRING_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate column_string)
GENERATE_COLUMN_STRING_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate column_string)
GENERATE_COLUMN_STRING_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate column_string)
GENERATE_COLUMN_STRING_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate column_string)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_COLUMN_STRING_OBJ_PREQS	:= $(GENERATE_COLUMN_STRING_SRC) 		\
			     	   	   $(GENERATE_COLUMN_STRING_HDR)		\
			      	   	   $(GENERATE_COUNTER_HDR)			\
			      	   	   $(GENERATE_COLUMN_STRING_NAMES_HDR)
GENERATE_COLUMN_STRING_OBJ_GROUP	:= $(GENERATE_COLUMN_STRING_OBJ) 		\
				   	   $(GENERATE_COUNTER_OBJ_GROUP)		\
				   	   $(GENERATE_COLUMN_STRING_NAMES_OBJ_GROUP)
GENERATE_COLUMN_STRING_TRNR_SRC_PREQS	:= $(GENERATE_COLUMN_STRING_TEST_SRC)		\
				   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_COLUMN_STRING_TEST_OBJ_PREQS	:= $(GENERATE_COLUMN_STRING_TEST_SRC)		\
			   	   	   $(GENERATE_COLUMN_STRING_OBJ_PREQS)		\
			   	   	   $(UNITY_OBJ_PREQS)
GENERATE_COLUMN_STRING_TRNR_OBJ_PREQS	:= $(GENERATE_COLUMN_STRING_TRNR_SRC)		\
			   	   	   $(GENERATE_COLUMN_STRING_TEST_OBJ_PREQS)
GENERATE_COLUMN_STRING_TEST_BIN_PREQS	:= $(GENERATE_COLUMN_STRING_TRNR_OBJ)		\
				   	   $(GENERATE_COLUMN_STRING_TEST_OBJ)		\
			   	   	   $(GENERATE_COLUMN_STRING_OBJ_GROUP)		\
			   	   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_COLUMN_STRING_TEST_BIN)
TARGETS			+= $(GENERATE_COLUMN_STRING_OBJ)		\
			   $(GENERATE_COLUMN_STRING_TRNR_SRC)		\
			   $(GENERATE_COLUMN_STRING_TRNR_OBJ)		\
			   $(GENERATE_COLUMN_STRING_TEST_OBJ)		\
			   $(GENERATE_COLUMN_STRING_TEST_BIN)


# generate/column_id
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_COLUMN_ID_SRC 		:= $(call HELPER_SOURCE_PATH,generate column_id)
GENERATE_COLUMN_ID_HDR		:= $(call HELPER_HEADER_PATH,generate column_id)
GENERATE_COLUMN_ID_OBJ 		:= $(call HELPER_OBJECT_PATH,generate column_id)
GENERATE_COLUMN_ID_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate column_id)
GENERATE_COLUMN_ID_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate column_id)
GENERATE_COLUMN_ID_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate column_id)
GENERATE_COLUMN_ID_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate column_id)
GENERATE_COLUMN_ID_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate column_id)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_COLUMN_ID_OBJ_PREQS		:= $(GENERATE_COLUMN_ID_SRC) 			\
			     	   	   $(GENERATE_COLUMN_ID_HDR)			\
			      	   	   $(GENERATE_COUNTER_HDR)
GENERATE_COLUMN_ID_OBJ_GROUP		:= $(GENERATE_COLUMN_ID_OBJ) 			\
				   	   $(GENERATE_COUNTER_OBJ_GROUP)
GENERATE_COLUMN_ID_TRNR_SRC_PREQS	:= $(GENERATE_COLUMN_ID_TEST_SRC)		\
				   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_COLUMN_ID_TEST_OBJ_PREQS	:= $(GENERATE_COLUMN_ID_TEST_SRC)		\
			   	   	   $(GENERATE_COLUMN_ID_OBJ_PREQS)		\
			   	   	   $(UNITY_OBJ_PREQS)
GENERATE_COLUMN_ID_TRNR_OBJ_PREQS	:= $(GENERATE_COLUMN_ID_TRNR_SRC)		\
			   	   	   $(GENERATE_COLUMN_ID_TEST_OBJ_PREQS)
GENERATE_COLUMN_ID_TEST_BIN_PREQS	:= $(GENERATE_COLUMN_ID_TRNR_OBJ)		\
				   	   $(GENERATE_COLUMN_ID_TEST_OBJ)		\
			   	   	   $(GENERATE_COLUMN_ID_OBJ_GROUP)		\
			   	   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_COLUMN_ID_TEST_BIN)
TARGETS			+= $(GENERATE_COLUMN_ID_OBJ)		\
			   $(GENERATE_COLUMN_ID_TRNR_SRC)	\
			   $(GENERATE_COLUMN_ID_TRNR_OBJ)	\
			   $(GENERATE_COLUMN_ID_TEST_OBJ)	\
			   $(GENERATE_COLUMN_ID_TEST_BIN)


# generate/column_timestamp
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_COLUMN_TIMESTAMP_SRC 		:= $(call HELPER_SOURCE_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_HDR		:= $(call HELPER_HEADER_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_OBJ 		:= $(call HELPER_OBJECT_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate column_timestamp)
GENERATE_COLUMN_TIMESTAMP_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate column_timestamp)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_COLUMN_TIMESTAMP_OBJ_PREQS		:= $(GENERATE_COLUMN_TIMESTAMP_SRC) 			\
			     	   	   	   $(GENERATE_COLUMN_TIMESTAMP_HDR)			\
			      	   	   	   $(GENERATE_GENERATOR_HDR)
GENERATE_COLUMN_TIMESTAMP_OBJ_GROUP		:= $(GENERATE_COLUMN_TIMESTAMP_OBJ) 			\
						   $(GENERATE_GENERATOR_OBJ_GROUP)
GENERATE_COLUMN_TIMESTAMP_TRNR_SRC_PREQS	:= $(GENERATE_COLUMN_TIMESTAMP_TEST_SRC)		\
				   	   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_COLUMN_TIMESTAMP_TEST_OBJ_PREQS	:= $(GENERATE_COLUMN_TIMESTAMP_TEST_SRC)		\
			   	   	   	   $(GENERATE_COLUMN_TIMESTAMP_OBJ_PREQS)		\
			   	   	   	   $(UNITY_OBJ_PREQS)
GENERATE_COLUMN_TIMESTAMP_TRNR_OBJ_PREQS	:= $(GENERATE_COLUMN_TIMESTAMP_TRNR_SRC)		\
			   	   	   	   $(GENERATE_COLUMN_TIMESTAMP_TEST_OBJ_PREQS)
GENERATE_COLUMN_TIMESTAMP_TEST_BIN_PREQS	:= $(GENERATE_COLUMN_TIMESTAMP_TRNR_OBJ)		\
						   $(GENERATE_COLUMN_TIMESTAMP_TEST_OBJ)		\
			   	   	   	   $(GENERATE_COLUMN_TIMESTAMP_OBJ_GROUP)		\
			   	   	   	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_COLUMN_TIMESTAMP_TEST_BIN)
TARGETS			+= $(GENERATE_COLUMN_TIMESTAMP_OBJ)		\
			   $(GENERATE_COLUMN_TIMESTAMP_TRNR_SRC)	\
			   $(GENERATE_COLUMN_TIMESTAMP_TRNR_OBJ)	\
			   $(GENERATE_COLUMN_TIMESTAMP_TEST_OBJ)	\
			   $(GENERATE_COLUMN_TIMESTAMP_TEST_BIN)


# generate/loader
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_LOADER_SRC 		:= $(call HELPER_SOURCE_PATH,generate loader)
GENERATE_LOADER_HDR		:= $(call HELPER_HEADER_PATH,generate loader)
GENERATE_LOADER_OBJ 		:= $(call HELPER_OBJECT_PATH,generate loader)
GENERATE_LOADER_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate loader)
GENERATE_LOADER_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate loader)
GENERATE_LOADER_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate loader)
GENERATE_LOADER_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate loader)
GENERATE_LOADER_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate loader)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_LOADER_OBJ_PREQS	:= $(GENERATE_LOADER_SRC) 		\
				   $(GENERATE_LOADER_HDR) 		\
				   $(GENERATE_GENERATOR_HDR)
GENERATE_LOADER_OBJ_GROUP	:= $(GENERATE_LOADER_OBJ)		\
				   $(GENERATE_GENERATOR_OBJ) 		\
				   $(GENERATE_GENERATOR_OBJ_GROUP)
GENERATE_LOADER_TRNR_SRC_PREQS	:= $(GENERATE_LOADER_TEST_SRC)		\
			   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_LOADER_TEST_OBJ_PREQS	:= $(GENERATE_LOADER_TEST_SRC)		\
			   	   $(GENERATE_LOADER_OBJ_PREQS) 	\
			   	   $(UNITY_OBJ_PREQS)
GENERATE_LOADER_TRNR_OBJ_PREQS	:= $(GENERATE_LOADER_TRNR_SRC)		\
			   	   $(GENERATE_LOADER_TEST_OBJ_PREQS)
GENERATE_LOADER_TEST_BIN_PREQS	:= $(GENERATE_LOADER_TRNR_OBJ)		\
			   	   $(GENERATE_LOADER_TEST_OBJ)		\
			   	   $(GENERATE_LOADER_OBJ_GROUP)		\
			           $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_LOADER_TEST_BIN)
TARGETS			+= $(GENERATE_LOADER_OBJ)			\
			   $(GENERATE_LOADER_TRNR_SRC)			\
			   $(GENERATE_LOADER_TRNR_OBJ)			\
			   $(GENERATE_LOADER_TEST_OBJ)			\
			   $(GENERATE_LOADER_TEST_BIN)


# generate/row_block
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_ROW_BLOCK_SRC 		:= $(call HELPER_SOURCE_PATH,generate row_block)
GENERATE_ROW_BLOCK_HDR		:= $(call HELPER_HEADER_PATH,generate row_block)
GENERATE_ROW_BLOCK_OBJ 		:= $(call HELPER_OBJECT_PATH,generate row_block)
GENERATE_ROW_BLOCK_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate row_block)
GENERATE_ROW_BLOCK_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate row_block)
GENERATE_ROW_BLOCK_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate row_block)
GENERATE_ROW_BLOCK_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate row_block)
GENERATE_ROW_BLOCK_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate row_block)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_ROW_BLOCK_OBJ_PREQS		:= $(GENERATE_ROW_BLOCK_SRC) 		\
				   	   $(GENERATE_ROW_BLOCK_HDR) 		\
				   	   $(GENERATE_GENERATOR_HDR)
GENERATE_ROW_BLOCK_OBJ_GROUP		:= $(GENERATE_ROW_BLOCK_OBJ)		\
				   	   $(GENERATE_GENERATOR_OBJ_GROUP)
GENERATE_ROW_BLOCK_TRNR_SRC_PREQS	:= $(GENERATE_ROW_BLOCK_TEST_SRC)	\
			   	   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_ROW_BLOCK_TEST_OBJ_PREQS	:= $(GENERATE_ROW_BLOCK_TEST_SRC)	\
			   	   	   $(GENERATE_ROW_BLOCK_OBJ_PREQS) 	\
			   	   	   $(UNITY_OBJ_PREQS)
GENERATE_ROW_BLOCK_TRNR_OBJ_PREQS	:= $(GENERATE_ROW_BLOCK_TRNR_SRC)	\
			   	   	   $(GENERATE_ROW_BLOCK_TEST_OBJ_PREQS)
GENERATE_ROW_BLOCK_TEST_BIN_PREQS	:= $(GENERATE_ROW_BLOCK_TRNR_OBJ)	\
			   	   	   $(GENERATE_ROW_BLOCK_TEST_OBJ)	\
			   	   	   $(GENERATE_ROW_BLOCK_OBJ_GROUP)	\
			           	   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_ROW_BLOCK_TEST_BIN)
TARGETS			+= $(GENERATE_ROW_BLOCK_OBJ)			\
			   $(GENERATE_ROW_BLOCK_TRNR_SRC)		\
			   $(GENERATE_ROW_BLOCK_TRNR_OBJ)		\
			   $(GENERATE_ROW_BLOCK_TEST_OBJ)		\
			   $(GENERATE_ROW_BLOCK_TEST_BIN)


# generate/table
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_TABLE_SRC 	:= $(call HELPER_SOURCE_PATH,generate table)
GENERATE_TABLE_HDR	:= $(call HELPER_HEADER_PATH,generate table)
GENERATE_TABLE_OBJ 	:= $(call HELPER_OBJECT_PATH,generate table)
GENERATE_TABLE_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate table)
GENERATE_TABLE_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate table)
GENERATE_TABLE_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate table)
GENERATE_TABLE_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate table)
GENERATE_TABLE_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate table)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_TABLE_OBJ_PREQS	:= $(GENERATE_TABLE_SRC) 		\
				   $(GENERATE_TABLE_HDR) 		\
				   $(GENERATE_ROW_BLOCK_HDR)
GENERATE_TABLE_OBJ_GROUP	:= $(GENERATE_TABLE_OBJ) 		\
				   $(GENERATE_ROW_BLOCK_OBJ_GROUP)
GENERATE_TABLE_TRNR_SRC_PREQS	:= $(GENERATE_TABLE_TEST_SRC)		\
			   	   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_TABLE_TEST_OBJ_PREQS	:= $(GENERATE_TABLE_TEST_SRC)		\
			   	   $(GENERATE_TABLE_OBJ_PREQS) 		\
			   	   $(UNITY_OBJ_PREQS)
GENERATE_TABLE_TRNR_OBJ_PREQS	:= $(GENERATE_TABLE_TRNR_SRC)		\
			   	   $(GENERATE_TABLE_TEST_OBJ_PREQS)
GENERATE_TABLE_TEST_BIN_PREQS	:= $(GENERATE_TABLE_TRNR_OBJ)		\
			   	   $(GENERATE_TABLE_TEST_OBJ)		\
			   	   $(GENERATE_TABLE_OBJ_GROUP)		\
			           $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_TABLE_TEST_BIN)
TARGETS			+= $(GENERATE_TABLE_OBJ)			\
			   $(GENERATE_TABLE_TRNR_SRC)			\
			   $(GENERATE_TABLE_TRNR_OBJ)			\
			   $(GENERATE_TABLE_TEST_OBJ)			\
			   $(GENERATE_TABLE_TEST_BIN)


# generate/generate
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_GENERATE_SRC 		:= $(call HELPER_SOURCE_PATH,generate generate)
GENERATE_GENERATE_HDR		:= $(call HELPER_HEADER_PATH,generate generate)
GENERATE_GENERATE_OBJ 		:= $(call HELPER_OBJECT_PATH,generate generate)
GENERATE_GENERATE_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,generate generate)
GENERATE_GENERATE_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,generate generate)
GENERATE_GENERATE_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,generate generate)
GENERATE_GENERATE_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,generate generate)
GENERATE_GENERATE_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,generate generate)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_GENERATE_OBJ_PREQS		:= $(GENERATE_GENERATE_SRC) 			\
			   		   $(GENERATE_GENERATE_HDR) 			\
			   		   $(GENERATE_LOADER_HDR)			\
			   		   $(GENERATE_COLUMN_ID_HDR)			\
			   		   $(GENERATE_COLUMN_STRING_HDR)		\
			   		   $(GENERATE_COLUMN_TIMESTAMP_HDR)		\
			   		   $(GENERATE_TABLE_HDR)
GENERATE_GENERATE_OBJ_GROUP		:= $(GENERATE_GENERATE_OBJ)			\
			   		   $(GENERATE_LOADER_OBJ_GROUP)			\
			   		   $(GENERATE_COLUMN_ID_OBJ_GROUP)		\
			   		   $(GENERATE_COLUMN_STRING_OBJ_GROUP)		\
			   		   $(GENERATE_COLUMN_TIMESTAMP_OBJ_GROUP)		\
			   		   $(GENERATE_TABLE_OBJ_GROUP)
GENERATE_GENERATE_TRNR_SRC_PREQS	:= $(GENERATE_GENERATE_TEST_SRC)		\
			   		   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_GENERATE_TEST_OBJ_PREQS	:= $(GENERATE_GENERATE_TEST_SRC)		\
			   		   $(GENERATE_GENERATE_OBJ_PREQS) 		\
			   		   $(UNITY_OBJ_PREQS)
GENERATE_GENERATE_TRNR_OBJ_PREQS	:= $(GENERATE_GENERATE_TRNR_SRC)		\
			   		   $(GENERATE_GENERATE_TEST_OBJ_PREQS)
GENERATE_GENERATE_TEST_BIN_PREQS	:= $(GENERATE_GENERATE_TRNR_OBJ)		\
			   		   $(GENERATE_GENERATE_TEST_OBJ)		\
			   		   $(GENERATE_GENERATE_OBJ_GROUP)		\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_GENERATE_TEST_BIN)
TARGETS			+= $(GENERATE_GENERATE_OBJ)			\
			   $(GENERATE_GENERATE_TRNR_SRC)		\
			   $(GENERATE_GENERATE_TRNR_OBJ)		\
			   $(GENERATE_GENERATE_TEST_OBJ)		\
			   $(GENERATE_GENERATE_TEST_BIN)



## PROJECT MODULES
# ══════════════════════════════════════════════════════════════════════════════
# mysql_seed_generate
# ──────────────────────────────────────────────────────────────────────────────
GENERATE_SRC 		:= $(call PROJECT_SOURCE_PATH,generate)
GENERATE_HDR		:= $(call PROJECT_HEADER_PATH,generate)
GENERATE_OBJ 		:= $(call PROJECT_OBJECT_PATH,generate)
GENERATE_TEST_SRC	:= $(call PROJECT_TEST_SOURCE_PATH,generate)
GENERATE_TRNR_SRC	:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,generate)
GENERATE_TRNR_OBJ	:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,generate)
GENERATE_TEST_OBJ	:= $(call PROJECT_TEST_OBJECT_PATH,generate)
GENERATE_TEST_BIN	:= $(call PROJECT_TEST_BINARY_PATH,generate)
# ─────────────── target prequisites ───────────────────────────────────────────
GENERATE_OBJ_PREQS	:= $(GENERATE_SRC) 				\
			   $(GENERATE_HDR) 				\
			   $(GENERATE_GENERATE_HDR)
GENERATE_OBJ_GROUP	:= $(GENERATE_OBJ)				\
			   $(GENERATE_GENERATE_OBJ_GROUP)
GENERATE_TRNR_SRC_PREQS	:= $(GENERATE_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
GENERATE_TEST_OBJ_PREQS	:= $(GENERATE_TEST_SRC)				\
			   $(GENERATE_OBJ_PREQS) 			\
			   $(UNITY_OBJ_PREQS)
GENERATE_TRNR_OBJ_PREQS	:= $(GENERATE_TRNR_SRC)				\
			   $(GENERATE_TEST_OBJ_PREQS)
GENERATE_TEST_BIN_PREQS	:= $(GENERATE_TRNR_OBJ)				\
			   $(GENERATE_TEST_OBJ)				\
			   $(GENERATE_OBJ_GROUP)			\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(GENERATE_TEST_BIN)
TARGETS			+= $(GENERATE_OBJ)				\
			   $(GENERATE_TRNR_SRC)				\
			   $(GENERATE_TRNR_OBJ)				\
			   $(GENERATE_TEST_OBJ)				\
			   $(GENERATE_TEST_BIN)


# mysql_seed_load
# ──────────────────────────────────────────────────────────────────────────────
LOAD_SRC 		:= $(call PROJECT_SOURCE_PATH,load)
LOAD_HDR		:= $(call PROJECT_HEADER_PATH,load)
LOAD_OBJ 		:= $(call PROJECT_OBJECT_PATH,load)
LOAD_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,load)
LOAD_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,load)
LOAD_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,load)
LOAD_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,load)
LOAD_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,load)
# ─────────────── target prequisites ───────────────────────────────────────────
LOAD_OBJ_PREQS		:= $(LOAD_SRC) 					\
			   $(LOAD_HDR) 					\
			   $(FILE_HDR)
LOAD_OBJ_GROUP		:= $(LOAD_OBJ)					\
			   $(FILE_OBJ_GROUP)
LOAD_TRNR_SRC_PREQS	:= $(LOAD_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
LOAD_TEST_OBJ_PREQS	:= $(LOAD_TEST_SRC)				\
			   $(LOAD_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
LOAD_TRNR_OBJ_PREQS	:= $(LOAD_TRNR_SRC)				\
			   $(LOAD_TEST_OBJ_PREQS)
LOAD_TEST_BIN_PREQS	:= $(LOAD_TRNR_OBJ)				\
			   $(LOAD_TEST_OBJ)				\
			   $(LOAD_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(LOAD_TEST_BIN)
TARGETS			+= $(LOAD_OBJ)					\
			   $(LOAD_TRNR_SRC)				\
			   $(LOAD_TRNR_OBJ)				\
			   $(LOAD_TEST_OBJ)				\
			   $(LOAD_TEST_BIN)


# mysql_seed_remove
# ──────────────────────────────────────────────────────────────────────────────
REMOVE_SRC 		:= $(call PROJECT_SOURCE_PATH,remove)
REMOVE_HDR		:= $(call PROJECT_HEADER_PATH,remove)
REMOVE_OBJ 		:= $(call PROJECT_OBJECT_PATH,remove)
REMOVE_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,remove)
REMOVE_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,remove)
REMOVE_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,remove)
REMOVE_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,remove)
REMOVE_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,remove)
# ─────────────── target prequisites ───────────────────────────────────────────
REMOVE_OBJ_PREQS	:= $(REMOVE_SRC) 				\
			   $(REMOVE_HDR) 				\
			   $(FILE_HDR)
REMOVE_OBJ_GROUP	:= $(REMOVE_OBJ)				\
			   $(FILE_OBJ_GROUP)
REMOVE_TRNR_SRC_PREQS	:= $(REMOVE_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
REMOVE_TEST_OBJ_PREQS	:= $(REMOVE_TEST_SRC)				\
			   $(REMOVE_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
REMOVE_TRNR_OBJ_PREQS	:= $(REMOVE_TRNR_SRC)				\
			   $(REMOVE_TEST_OBJ_PREQS)
REMOVE_TEST_BIN_PREQS	:= $(REMOVE_TRNR_OBJ)				\
			   $(REMOVE_TEST_OBJ)				\
			   $(REMOVE_OBJ_GROUP)				\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(REMOVE_TEST_BIN)
TARGETS			+= $(REMOVE_OBJ)				\
			   $(REMOVE_TRNR_SRC)				\
			   $(REMOVE_TRNR_OBJ)				\
			   $(REMOVE_TEST_OBJ)				\
			   $(REMOVE_TEST_BIN)


# mysql_seed_help
# ──────────────────────────────────────────────────────────────────────────────
HELP_SRC 		:= $(call PROJECT_SOURCE_PATH,help)
HELP_HDR		:= $(call PROJECT_HEADER_PATH,help)
HELP_OBJ 		:= $(call PROJECT_OBJECT_PATH,help)
HELP_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,help)
HELP_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,help)
HELP_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,help)
HELP_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,help)
HELP_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,help)
# ─────────────── target prequisites ───────────────────────────────────────────
HELP_OBJ_PREQS		:= $(HELP_SRC) 					\
			   $(HELP_HDR) 					\
			   $(FILE_HDR)
HELP_OBJ_GROUP		:= $(HELP_OBJ)					\
			   $(FILE_OBJ_GROUP)
HELP_TRNR_SRC_PREQS	:= $(HELP_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
HELP_TEST_OBJ_PREQS	:= $(HELP_TEST_SRC)				\
			   $(HELP_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
HELP_TRNR_OBJ_PREQS	:= $(HELP_TRNR_SRC)				\
			   $(HELP_TEST_OBJ_PREQS)
HELP_TEST_BIN_PREQS	:= $(HELP_TRNR_OBJ)				\
			   $(HELP_TEST_OBJ)				\
			   $(HELP_OBJ_GROUP)				\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(HELP_TEST_BIN)
TARGETS			+= $(HELP_OBJ)					\
			   $(HELP_TRNR_SRC)				\
			   $(HELP_TRNR_OBJ)				\
			   $(HELP_TEST_OBJ)				\
			   $(HELP_TEST_BIN)



# mysql_seed (entry point)
# ──────────────────────────────────────────────────────────────────────────────
PROJECT_SRC 		:= $(call SOURCE_PATH,$(PROJECT))
PROJECT_HDR		:= $(call HEADER_PATH,$(PROJECT))
PROJECT_OBJ 		:= $(call OBJECT_PATH,$(PROJECT))
PROJECT_BIN 		:= $(call BINARY_PATH,$(PROJECT))
# ─────────────── target prequisites ───────────────────────────────────────────
PROJECT_BIN_PREQS	:= $(PROJECT_OBJ) 				\
			   $(HELP_OBJ_GROUP) 				\
			   $(REMOVE_OBJ_GROUP) 				\
			   $(GENERATE_OBJ_GROUP) 			\
			   $(LOAD_OBJ_GROUP)

PROJECT_OBJ_PREQS	:= $(PROJECT_SRC) 				\
			   $(PROJECT_HDR) 				\
			   $(HELP_HDR)					\
			   $(REMOVE_HDR)				\
			   $(GENERATE_HDR)				\
			   $(LOAD_HDR)
# ─────────────── targets ──────────────────────────────────────────────────────
TARGETS			+= $(PROJECT_OBJ)				\
			   $(PROJECT_BIN)




# ══════════════════════════════════════════════════════════════════════════════
# ──────────────────────────────────────────────────────────────────────────────
# 				MAKE RULES
# ──────────────────────────────────────────────────────────────────────────────
# ══════════════════════════════════════════════════════════════════════════════
#
#
## COMPOSITE RULES
# ══════════════════════════════════════════════════════════════════════════════
# make all targets
# ──────────────────────────────────────────────────────────────────────────────
all: $(TARGETS)

# run all unit tests
# ──────────────────────────────────────────────────────────────────────────────
run_tests: $(TEST_BINARIES)
	$(RUN_ALL_TESTS)

# remove all targets
# ──────────────────────────────────────────────────────────────────────────────
clean:
	$(RM) $(RM_FLAGS) $(TARGETS)


## MAKE PROJECT
# ══════════════════════════════════════════════════════════════════════════════
# make mysql_seed binary
# ──────────────────────────────────────────────────────────────────────────────
$(PROJECT_BIN): $(PROJECT_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

# # make mysql_seed object
# # ──────────────────────────────────────────────────────────────────────────────
$(PROJECT_OBJ): $(PROJECT_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_generate object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_OBJ): $(GENERATE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_load object
# ──────────────────────────────────────────────────────────────────────────────
$(LOAD_OBJ): $(LOAD_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_remove object
# ──────────────────────────────────────────────────────────────────────────────
$(REMOVE_OBJ): $(REMOVE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_help object
# ──────────────────────────────────────────────────────────────────────────────
$(HELP_OBJ): $(HELP_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_file object
# ──────────────────────────────────────────────────────────────────────────────
$(FILE_OBJ): $(FILE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_pool object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_POOL_OBJ): $(THREAD_THREAD_POOL_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_log object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_LOG_OBJ): $(THREAD_THREAD_LOG_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/task_queue object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_TASK_QUEUE_OBJ): $(THREAD_TASK_QUEUE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_UTILS_OBJ): $(THREAD_THREAD_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/generate object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_GENERATE_OBJ): $(GENERATE_GENERATE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/generator object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_GENERATOR_OBJ): $(GENERATE_GENERATOR_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/counter object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COUNTER_OBJ): $(GENERATE_COUNTER_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/loader object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_LOADER_OBJ): $(GENERATE_LOADER_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/table object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_TABLE_OBJ): $(GENERATE_TABLE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/row_block object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_ROW_BLOCK_OBJ): $(GENERATE_ROW_BLOCK_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/column_timestamp object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_TIMESTAMP_OBJ): $(GENERATE_COLUMN_TIMESTAMP_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/column_id object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_ID_OBJ): $(GENERATE_COLUMN_ID_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/column_string object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_STRING_OBJ): $(GENERATE_COLUMN_STRING_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make generate/column_string_names object
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_STRING_NAMES_OBJ): $(GENERATE_COLUMN_STRING_NAMES_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make system/system_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(SYSTEM_SYSTEM_UTILS_OBJ): $(SYSTEM_SYSTEM_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make system/file_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(SYSTEM_FILE_UTILS_OBJ): $(SYSTEM_FILE_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make system/exit_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(SYSTEM_EXIT_UTILS_OBJ): $(SYSTEM_EXIT_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make string/string_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(STRING_STRING_UTILS_OBJ): $(STRING_STRING_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make string/ascii_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(STRING_ASCII_UTILS_OBJ): $(STRING_ASCII_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make string/utf8_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(STRING_UTF8_UTILS_OBJ): $(STRING_UTF8_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make random/random object
# ──────────────────────────────────────────────────────────────────────────────
$(RANDOM_RANDOM_OBJ): $(RANDOM_RANDOM_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make random/pcg_basic object
# ──────────────────────────────────────────────────────────────────────────────
$(RANDOM_PCG_BASIC_OBJ): $(RANDOM_PCG_BASIC_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_put_array object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_PUT_ARRAY_OBJ): $(MEMORY_MEMORY_PUT_ARRAY_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_copy_array object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_COPY_ARRAY_OBJ): $(MEMORY_MEMORY_COPY_ARRAY_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_swap object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_SWAP_OBJ): $(MEMORY_MEMORY_SWAP_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_zero object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_ZERO_OBJ): $(MEMORY_MEMORY_ZERO_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_UTILS_OBJ): $(MEMORY_MEMORY_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make time/time_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(TIME_TIME_UTILS_OBJ): $(TIME_TIME_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make utils/closure object
# ──────────────────────────────────────────────────────────────────────────────
$(UTILS_CLOSURE_OBJ): $(UTILS_CLOSURE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make utils/utils object
# ──────────────────────────────────────────────────────────────────────────────
$(UTILS_UTILS_OBJ): $(UTILS_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@





## MAKE UNITY TEST FRAMEWORK
# ══════════════════════════════════════════════════════════════════════════════
# make unity object
# ──────────────────────────────────────────────────────────────────────────────
$(UNITY_OBJ): $(UNITY_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# make test_runners directory
# ──────────────────────────────────────────────────────────────────────────────
$(TEST_RUNNER_SOURCE_DIR):
	$(MKDIR) $(MKDIR_FLAGS) $@



# for mysql_seed_generate
# make:
# 	mysql_seed_generate_test		binary,
# 	mysql_seed_generate_test_runner 	object,
# 	mysql_seed_generate_test		object, and
# 	mysql_seed_generate_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_TEST_BIN): $(GENERATE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_TRNR_OBJ): $(GENERATE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_TEST_OBJ): $(GENERATE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_TRNR_SRC): $(GENERATE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_load
# make:
# 	mysql_seed_load_test		binary,
# 	mysql_seed_load_test_runner 	object,
# 	mysql_seed_load_test		object, and
# 	mysql_seed_load_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(LOAD_TEST_BIN): $(LOAD_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(LOAD_TRNR_OBJ): $(LOAD_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(LOAD_TEST_OBJ): $(LOAD_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(LOAD_TRNR_SRC): $(LOAD_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_remove
# make:
# 	mysql_seed_remove_test		binary,
# 	mysql_seed_remove_test_runner 	object,
# 	mysql_seed_remove_test		object, and
# 	mysql_seed_remove_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(REMOVE_TEST_BIN): $(REMOVE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(REMOVE_TRNR_OBJ): $(REMOVE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(REMOVE_TEST_OBJ): $(REMOVE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(REMOVE_TRNR_SRC): $(REMOVE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_help
# make:
# 	mysql_seed_help_test		binary,
# 	mysql_seed_help_test_runner 	object,
# 	mysql_seed_help_test		object, and
# 	mysql_seed_help_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(HELP_TEST_BIN): $(HELP_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(HELP_TRNR_OBJ): $(HELP_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(HELP_TEST_OBJ): $(HELP_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(HELP_TRNR_SRC): $(HELP_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_file
# make:
# 	mysql_seed_file_test		binary,
# 	mysql_seed_file_test_runner 	object,
# 	mysql_seed_file_test		object, and
# 	mysql_seed_file_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(FILE_TEST_BIN): $(FILE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(FILE_TRNR_OBJ): $(FILE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(FILE_TEST_OBJ): $(FILE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(FILE_TRNR_SRC): $(FILE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for thread/thread_pool
# make:
# 	thread_thread_pool_test		binary,
# 	thread_thread_pool_test_runner 	object,
# 	thread_thread_pool_test		object, and
# 	thread_thread_pool_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_POOL_TEST_BIN): $(THREAD_THREAD_POOL_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(THREAD_THREAD_POOL_TRNR_OBJ): $(THREAD_THREAD_POOL_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_POOL_TEST_OBJ): $(THREAD_THREAD_POOL_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_POOL_TRNR_SRC): $(THREAD_THREAD_POOL_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for thread/thread_log
# make:
# 	thread_thread_log_test		binary,
# 	thread_thread_log_test_runner 	object,
# 	thread_thread_log_test		object, and
# 	thread_thread_log_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_LOG_TEST_BIN): $(THREAD_THREAD_LOG_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(THREAD_THREAD_LOG_TRNR_OBJ): $(THREAD_THREAD_LOG_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_LOG_TEST_OBJ): $(THREAD_THREAD_LOG_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_LOG_TRNR_SRC): $(THREAD_THREAD_LOG_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for thread/task_queue
# make:
# 	thread_task_queue_test		binary,
# 	thread_task_queue_test_runner 	object,
# 	thread_task_queue_test		object, and
# 	thread_task_queue_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_TASK_QUEUE_TEST_BIN): $(THREAD_TASK_QUEUE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(THREAD_TASK_QUEUE_TRNR_OBJ): $(THREAD_TASK_QUEUE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_TASK_QUEUE_TEST_OBJ): $(THREAD_TASK_QUEUE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_TASK_QUEUE_TRNR_SRC): $(THREAD_TASK_QUEUE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for thread/thread_utils
# make:
# 	thread_thread_utils_test		binary,
# 	thread_thread_utils_test_runner 	object,
# 	thread_thread_utils_test		object, and
# 	thread_thread_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_UTILS_TEST_BIN): $(THREAD_THREAD_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(THREAD_THREAD_UTILS_TRNR_OBJ): $(THREAD_THREAD_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_UTILS_TEST_OBJ): $(THREAD_THREAD_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_UTILS_TRNR_SRC): $(THREAD_THREAD_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for system/system_utils
# make:
# 	system_system_utils_test		binary,
# 	system_system_utils_test_runner 	object,
# 	system_system_utils_test		object, and
# 	system_system_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(SYSTEM_SYSTEM_UTILS_TEST_BIN): $(SYSTEM_SYSTEM_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(SYSTEM_SYSTEM_UTILS_TRNR_OBJ): $(SYSTEM_SYSTEM_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(SYSTEM_SYSTEM_UTILS_TEST_OBJ): $(SYSTEM_SYSTEM_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(SYSTEM_SYSTEM_UTILS_TRNR_SRC): $(SYSTEM_SYSTEM_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for system/file_utils
# make:
# 	system_file_utils_test		binary,
# 	system_file_utils_test_runner 	object,
# 	system_file_utils_test		object, and
# 	system_file_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(SYSTEM_FILE_UTILS_TEST_BIN): $(SYSTEM_FILE_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(SYSTEM_FILE_UTILS_TRNR_OBJ): $(SYSTEM_FILE_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(SYSTEM_FILE_UTILS_TEST_OBJ): $(SYSTEM_FILE_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(SYSTEM_FILE_UTILS_TRNR_SRC): $(SYSTEM_FILE_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for system/exit_utils
# make:
# 	system_exit_utils_test		binary,
# 	system_exit_utils_test_runner 	object,
# 	system_exit_utils_test		object, and
# 	system_exit_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(SYSTEM_EXIT_UTILS_TEST_BIN): $(SYSTEM_EXIT_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(SYSTEM_EXIT_UTILS_TRNR_OBJ): $(SYSTEM_EXIT_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(SYSTEM_EXIT_UTILS_TEST_OBJ): $(SYSTEM_EXIT_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(SYSTEM_EXIT_UTILS_TRNR_SRC): $(SYSTEM_EXIT_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for string/string_utils
# make:
# 	string_string_utils_test		binary,
# 	string_string_utils_test_runner 	object,
# 	string_string_utils_test		object, and
# 	string_string_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(STRING_STRING_UTILS_TEST_BIN): $(STRING_STRING_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(STRING_STRING_UTILS_TRNR_OBJ): $(STRING_STRING_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(STRING_STRING_UTILS_TEST_OBJ): $(STRING_STRING_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(STRING_STRING_UTILS_TRNR_SRC): $(STRING_STRING_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for string/ascii_utils
# make:
# 	string_ascii_utils_test		binary,
# 	string_ascii_utils_test_runner 	object,
# 	string_ascii_utils_test		object, and
# 	string_ascii_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(STRING_ASCII_UTILS_TEST_BIN): $(STRING_ASCII_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(STRING_ASCII_UTILS_TRNR_OBJ): $(STRING_ASCII_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(STRING_ASCII_UTILS_TEST_OBJ): $(STRING_ASCII_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(STRING_ASCII_UTILS_TRNR_SRC): $(STRING_ASCII_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for string/utf8_utils
# make:
# 	string_utf8_utils_test		binary,
# 	string_utf8_utils_test_runner 	object,
# 	string_utf8_utils_test		object, and
# 	string_utf8_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(STRING_UTF8_UTILS_TEST_BIN): $(STRING_UTF8_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(STRING_UTF8_UTILS_TRNR_OBJ): $(STRING_UTF8_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(STRING_UTF8_UTILS_TEST_OBJ): $(STRING_UTF8_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(STRING_UTF8_UTILS_TRNR_SRC): $(STRING_UTF8_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/loader
# make:
# 	generate_loader_test		binary,
# 	generate_loader_test_runner 	object,
# 	generate_loader_test		object, and
# 	generate_loader_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_LOADER_TEST_BIN): $(GENERATE_LOADER_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_LOADER_TRNR_OBJ): $(GENERATE_LOADER_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_LOADER_TEST_OBJ): $(GENERATE_LOADER_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_LOADER_TRNR_SRC): $(GENERATE_LOADER_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/table
# make:
# 	generate_table_test		binary,
# 	generate_table_test_runner 	object,
# 	generate_table_test		object, and
# 	generate_table_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_TABLE_TEST_BIN): $(GENERATE_TABLE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_TABLE_TRNR_OBJ): $(GENERATE_TABLE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_TABLE_TEST_OBJ): $(GENERATE_TABLE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_TABLE_TRNR_SRC): $(GENERATE_TABLE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/row_block
# make:
# 	generate_row_block_test		binary,
# 	generate_row_block_test_runner 	object,
# 	generate_row_block_test		object, and
# 	generate_row_block_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_ROW_BLOCK_TEST_BIN): $(GENERATE_ROW_BLOCK_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_ROW_BLOCK_TRNR_OBJ): $(GENERATE_ROW_BLOCK_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_ROW_BLOCK_TEST_OBJ): $(GENERATE_ROW_BLOCK_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_ROW_BLOCK_TRNR_SRC): $(GENERATE_ROW_BLOCK_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/counter
# make:
# 	generate_counter_test		binary,
# 	generate_counter_test_runner 	object,
# 	generate_counter_test		object, and
# 	generate_counter_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COUNTER_TEST_BIN): $(GENERATE_COUNTER_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_COUNTER_TRNR_OBJ): $(GENERATE_COUNTER_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COUNTER_TEST_OBJ): $(GENERATE_COUNTER_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COUNTER_TRNR_SRC): $(GENERATE_COUNTER_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/column_timestamp
# make:
# 	generate_column_timestamp_test		binary,
# 	generate_column_timestamp_test_runner 	object,
# 	generate_column_timestamp_test		object, and
# 	generate_column_timestamp_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_TIMESTAMP_TEST_BIN): $(GENERATE_COLUMN_TIMESTAMP_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_COLUMN_TIMESTAMP_TRNR_OBJ): $(GENERATE_COLUMN_TIMESTAMP_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_TIMESTAMP_TEST_OBJ): $(GENERATE_COLUMN_TIMESTAMP_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_TIMESTAMP_TRNR_SRC): $(GENERATE_COLUMN_TIMESTAMP_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/column_id
# make:
# 	generate_column_id_test		binary,
# 	generate_column_id_test_runner 	object,
# 	generate_column_id_test		object, and
# 	generate_column_id_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_ID_TEST_BIN): $(GENERATE_COLUMN_ID_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_COLUMN_ID_TRNR_OBJ): $(GENERATE_COLUMN_ID_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_ID_TEST_OBJ): $(GENERATE_COLUMN_ID_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_ID_TRNR_SRC): $(GENERATE_COLUMN_ID_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/column_string
# make:
# 	generate_column_string_test		binary,
# 	generate_column_string_test_runner 	object,
# 	generate_column_string_test		object, and
# 	generate_column_string_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_STRING_TEST_BIN): $(GENERATE_COLUMN_STRING_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_COLUMN_STRING_TRNR_OBJ): $(GENERATE_COLUMN_STRING_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_STRING_TEST_OBJ): $(GENERATE_COLUMN_STRING_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_STRING_TRNR_SRC): $(GENERATE_COLUMN_STRING_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/column_string_names
# make:
# 	generate_column_string_names_test		binary,
# 	generate_column_string_names_test_runner 	object,
# 	generate_column_string_names_test		object, and
# 	generate_column_string_names_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_COLUMN_STRING_NAMES_TEST_BIN): $(GENERATE_COLUMN_STRING_NAMES_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_COLUMN_STRING_NAMES_TRNR_OBJ): $(GENERATE_COLUMN_STRING_NAMES_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_STRING_NAMES_TEST_OBJ): $(GENERATE_COLUMN_STRING_NAMES_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_COLUMN_STRING_NAMES_TRNR_SRC): $(GENERATE_COLUMN_STRING_NAMES_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for generate/generator
# make:
# 	generate_generator_test		binary,
# 	generate_generator_test_runner 	object,
# 	generate_generator_test		object, and
# 	generate_generator_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_GENERATOR_TEST_BIN): $(GENERATE_GENERATOR_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_GENERATOR_TRNR_OBJ): $(GENERATE_GENERATOR_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_GENERATOR_TEST_OBJ): $(GENERATE_GENERATOR_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_GENERATOR_TRNR_SRC): $(GENERATE_GENERATOR_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@

# for generate/generate
# make:
# 	generate_generate_test		binary,
# 	generate_generate_test_runner 	object,
# 	generate_generate_test		object, and
# 	generate_generate_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(GENERATE_GENERATE_TEST_BIN): $(GENERATE_GENERATE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(GENERATE_GENERATE_TRNR_OBJ): $(GENERATE_GENERATE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_GENERATE_TEST_OBJ): $(GENERATE_GENERATE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(GENERATE_GENERATE_TRNR_SRC): $(GENERATE_GENERATE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for random/random
# make:
# 	random_random_test		binary,
# 	random_random_test_runner 	object,
# 	random_random_test		object, and
# 	random_random_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(RANDOM_RANDOM_TEST_BIN): $(RANDOM_RANDOM_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(RANDOM_RANDOM_TRNR_OBJ): $(RANDOM_RANDOM_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RANDOM_RANDOM_TEST_OBJ): $(RANDOM_RANDOM_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RANDOM_RANDOM_TRNR_SRC): $(RANDOM_RANDOM_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for random/pcg_basic
# make:
# 	random_pcg_basic_test		binary,
# 	random_pcg_basic_test_runner 	object,
# 	random_pcg_basic_test		object, and
# 	random_pcg_basic_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(RANDOM_PCG_BASIC_TEST_BIN): $(RANDOM_PCG_BASIC_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(RANDOM_PCG_BASIC_TRNR_OBJ): $(RANDOM_PCG_BASIC_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RANDOM_PCG_BASIC_TEST_OBJ): $(RANDOM_PCG_BASIC_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RANDOM_PCG_BASIC_TRNR_SRC): $(RANDOM_PCG_BASIC_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for memory/memory_put_array
# make:
# 	memory_memory_put_array_test		binary,
# 	memory_memory_put_array_test_runner 	object,
# 	memory_memory_put_array_test		object, and
# 	memory_memory_put_array_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_PUT_ARRAY_TEST_BIN): $(MEMORY_MEMORY_PUT_ARRAY_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(MEMORY_MEMORY_PUT_ARRAY_TRNR_OBJ): $(MEMORY_MEMORY_PUT_ARRAY_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ): $(MEMORY_MEMORY_PUT_ARRAY_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_PUT_ARRAY_TRNR_SRC): $(MEMORY_MEMORY_PUT_ARRAY_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for memory/memory_copy_array
# make:
# 	memory_memory_copy_array_test		binary,
# 	memory_memory_copy_array_test_runner 	object,
# 	memory_memory_copy_array_test		object, and
# 	memory_memory_copy_array_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_COPY_ARRAY_TEST_BIN): $(MEMORY_MEMORY_COPY_ARRAY_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(MEMORY_MEMORY_COPY_ARRAY_TRNR_OBJ): $(MEMORY_MEMORY_COPY_ARRAY_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ): $(MEMORY_MEMORY_COPY_ARRAY_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_COPY_ARRAY_TRNR_SRC): $(MEMORY_MEMORY_COPY_ARRAY_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for memory/memory_swap
# make:
# 	memory_memory_swap_test		binary,
# 	memory_memory_swap_test_runner 	object,
# 	memory_memory_swap_test		object, and
# 	memory_memory_swap_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_SWAP_TEST_BIN): $(MEMORY_MEMORY_SWAP_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(MEMORY_MEMORY_SWAP_TRNR_OBJ): $(MEMORY_MEMORY_SWAP_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_SWAP_TEST_OBJ): $(MEMORY_MEMORY_SWAP_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_SWAP_TRNR_SRC): $(MEMORY_MEMORY_SWAP_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for memory/memory_zero
# make:
# 	memory_memory_zero_test		binary,
# 	memory_memory_zero_test_runner 	object,
# 	memory_memory_zero_test		object, and
# 	memory_memory_zero_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_ZERO_TEST_BIN): $(MEMORY_MEMORY_ZERO_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(MEMORY_MEMORY_ZERO_TRNR_OBJ): $(MEMORY_MEMORY_ZERO_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_ZERO_TEST_OBJ): $(MEMORY_MEMORY_ZERO_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_ZERO_TRNR_SRC): $(MEMORY_MEMORY_ZERO_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for memory/memory_utils
# make:
# 	memory_memory_utils_test		binary,
# 	memory_memory_utils_test_runner 	object,
# 	memory_memory_utils_test		object, and
# 	memory_memory_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_UTILS_TEST_BIN): $(MEMORY_MEMORY_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(MEMORY_MEMORY_UTILS_TRNR_OBJ): $(MEMORY_MEMORY_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_UTILS_TEST_OBJ): $(MEMORY_MEMORY_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(MEMORY_MEMORY_UTILS_TRNR_SRC): $(MEMORY_MEMORY_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for time/time_utils
# make:
# 	time_time_utils_test		binary,
# 	time_time_utils_test_runner 	object,
# 	time_time_utils_test		object, and
# 	time_time_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(TIME_TIME_UTILS_TEST_BIN): $(TIME_TIME_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(TIME_TIME_UTILS_TRNR_OBJ): $(TIME_TIME_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(TIME_TIME_UTILS_TEST_OBJ): $(TIME_TIME_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(TIME_TIME_UTILS_TRNR_SRC): $(TIME_TIME_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for utils/closure
# make:
# 	utils_closure_test		binary,
# 	utils_closure_test_runner 	object,
# 	utils_closure_test		object, and
# 	utils_closure_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(UTILS_CLOSURE_TEST_BIN): $(UTILS_CLOSURE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(UTILS_CLOSURE_TRNR_OBJ): $(UTILS_CLOSURE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_CLOSURE_TEST_OBJ): $(UTILS_CLOSURE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_CLOSURE_TRNR_SRC): $(UTILS_CLOSURE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for utils/utils
# make:
# 	utils_utils_test		binary,
# 	utils_utils_test_runner 	object,
# 	utils_utils_test		object, and
# 	utils_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(UTILS_UTILS_TEST_BIN): $(UTILS_UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(UTILS_UTILS_TRNR_OBJ): $(UTILS_UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_UTILS_TEST_OBJ): $(UTILS_UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_UTILS_TRNR_SRC): $(UTILS_UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@
