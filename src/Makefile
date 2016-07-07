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
PATH_DELIM		:= \\
CMD_DELIM 		:= &
else
PATH_DELIM		:= /
CMD_DELIM 		:= ;
endif



# DIRECTORY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
PATH_JOIN		 = $(call JOIN,$1,$(PATH_DELIM))

PROJECT 		:= mysql_seed
PROJECT_ROOT		:= ..
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
else
        THREADS_LIB_FLAG	:= -lpthread
        THREADS_INC_FLAG	:= $(EMPTY)
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


# Generator Module
GEN_PREFIX			= $(call PATH_JOIN,gen $(call TRIM,gen_$1))
# ─────────────── source ───────────────────────────────────────────────────────
GEN_SOURCE_PATH			= $(call SOURCE_PATH,$(call GEN_PREFIX,$1))# implementation
GEN_HEADER_PATH			= $(call HEADER_PATH,$(call GEN_PREFIX,$1))# interface
# ─────────────── build ────────────────────────────────────────────────────────
GEN_OBJECT_PATH   		= $(call OBJECT_PATH,gen_gen_$1)# object files

# Generator Module Testing
# ─────────────── source ───────────────────────────────────────────────────────
GEN_TEST_SOURCE_PATH		= $(call SOURCE_FILE_PATH,$(TEST_SOURCE_DIR),gen_gen_$1_test)# Unity unit test implementation
GEN_TEST_HEADER_PATH		= $(call HEADER_FILE_PATH,$(TEST_HEADER_DIR),gen_gen_$1_test)# Unity unit test interface
GEN_TEST_RUNNER_SOURCE_PATH	= $(call SOURCE_FILE_PATH,$(TEST_RUNNER_SOURCE_DIR),gen_gen_$1_test_runner)# Unity test runners
# ─────────────── build ────────────────────────────────────────────────────────
GEN_TEST_OBJECT_PATH 		= $(call OBJECT_FILE_PATH,$(TEST_OBJECT_DIR),gen_gen_$1_test)# Unity unit test object files
GEN_TEST_RUNNER_OBJECT_PATH	= $(call OBJECT_FILE_PATH,$(TEST_RUNNER_OBJECT_DIR),gen_gen_$1_test_runner)# Unity test runner object files
GEN_TEST_BINARY_PATH 		= $(call BINARY_FILE_PATH,$(TEST_BINARY_DIR),gen_gen_$1_test)# binary executable output

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
CC_ENV_FLAGS	:= -D__USE_FIXED_PROTOTYPES__ $(SYS_ENV_FLAGS)
CC_FLAGS	:= -g -O2 -std=c99 -Wall -march=native $(CC_ENV_FLAGS) -I$(HEADER_DIR) $(THREADS_INC_FLAG)
# Linker
# ──────────────────────────────────────────────────────────────────────────────
LD		:= ld
LD_FLAGS	:= -no_pie $(SYS_ARCH_FLAG)
LD_LIB_FLAGS	:= $(THREADS_LIB_FLAG) -lc

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
UTILS_TYPES_WORD_PATTERN_HDR	:= $(call HELPER_HEADER_PATH,utils types word_pattern)
UTILS_TYPES_ACTION_HDR		:= $(call HELPER_HEADER_PATH,utils types action)
UTILS_WORD_ATTRS_HDR		:= $(call HELPER_HEADER_PATH,utils word_attrs)
UTILS_HANDLE_UTILS_HDR		:= $(call HELPER_HEADER_PATH,utils handle_utils)
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
UTILS_UTILS_OBJ_GROUP		:= $(UTILS_OBJ)
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
			   	   $(TIME_TIME_UTILS_HDR)
TIME_TIME_UTILS_OBJ_GROUP	:= $(TIME_TIME_UTILS_OBJ)
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


# memory/memory_swap
# ──────────────────────────────────────────────────────────────────────────────
MEMORY_MEMORY_SWAP_SRC 		:= $(call HELPER_SOURCE_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_HDR		:= $(call HELPER_HEADER_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_WIDTH_HDR	:= $(call HELPER_HEADER_PATH,memory memory_swap_width)
MEMORY_MEMORY_SWAP_OBJ 		:= $(call HELPER_OBJECT_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,memory memory_swap)
MEMORY_MEMORY_SWAP_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,memory memory_swap)
# ─────────────── target prequisites ───────────────────────────────────────────
MEMORY_MEMORY_SWAP_OBJ_PREQS		:= $(MEMORY_MEMORY_SWAP_SRC) 		\
			   	   	   $(MEMORY_MEMORY_SWAP_HDR)		\
			   	   	   $(MEMORY_MEMORY_SWAP_WIDTH_HDR)
MEMORY_MEMORY_SWAP_OBJ_GROUP		:= $(MEMORY_MEMORY_SWAP_OBJ)		\
					   $(MEMORY_MEMORY_UTILS_OBJ_GROUP)
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
			   		   $(UTILS_TYPES_WORD_PATTERN_HDR)		\
			   		   $(STRING_INT_STRING_ATTRS_HDR)		\
			   		   $(STRING_PTR_STRING_ATTRS_HDR)		\
			   		   $(STRING_ASCII_UTILS_HDR)			\
			   		   $(STRING_STRING_MACROS_HDR)
STRING_STRING_UTILS_OBJ_GROUP		:= $(STRING_STRING_UTILS_OBJ)			\
					   $(STRING_ASCII_UTILS_OBJ_GROUP)
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
			   		   $(UTILS_HANDLE_UTILS_HDR)
SYSTEM_SYSTEM_UTILS_OBJ_GROUP		:= $(SYSTEM_SYSTEM_UTILS_OBJ)
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
			   		   $(SYSTEM_SYSTEM_UTILS_HDR)
SYSTEM_FILE_UTILS_OBJ_GROUP		:= $(SYSTEM_FILE_UTILS_OBJ)			\
					   $(SYSTEM_SYSTEM_UTILS_OBJ_GROUP)
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
			   		   $(STRING_STRING_UTILS_HDR)			\
					   $(UTILS_TYPES_ACTION_HDR)
SYSTEM_EXIT_UTILS_OBJ_GROUP		:= $(SYSTEM_EXIT_UTILS_OBJ)			\
					   $(SYSTEM_FILE_UTILS_OBJ_GROUP)		\
					   $(STRING_STRING_UTILS_OBJ_GROUP)
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
			   	   	   $(TIME_TIME_UTILS_HDR)			\
			   	   	   $(UTILS_HANDLE_UTILS_HDR)			\
			   	   	   $(UTILS_FAIL_SWITCH_CLOSE_HDR)
THREAD_THREAD_UTILS_OBJ_GROUP		:= $(THREAD_THREAD_UTILS_OBJ)			\
			   	   	   $(TIME_TIME_UTILS_OBJ)
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


# thread/thread_queue
# ──────────────────────────────────────────────────────────────────────────────
THREAD_THREAD_QUEUE_SRC 	:= $(call HELPER_SOURCE_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_HDR		:= $(call HELPER_HEADER_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_OBJ 	:= $(call HELPER_OBJECT_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_TEST_SRC	:= $(call HELPER_TEST_SOURCE_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_TRNR_SRC	:= $(call HELPER_TEST_RUNNER_SOURCE_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_TRNR_OBJ	:= $(call HELPER_TEST_RUNNER_OBJECT_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_TEST_OBJ	:= $(call HELPER_TEST_OBJECT_PATH,thread thread_queue)
THREAD_THREAD_QUEUE_TEST_BIN	:= $(call HELPER_TEST_BINARY_PATH,thread thread_queue)
# ─────────────── target prequisites ───────────────────────────────────────────
THREAD_THREAD_QUEUE_OBJ_PREQS		:= $(THREAD_THREAD_QUEUE_SRC) 		\
			   		   $(THREAD_THREAD_QUEUE_HDR) 		\
			   		   $(THREAD_THREAD_UTILS_HDR)
THREAD_THREAD_QUEUE_OBJ_GROUP		:= $(THREAD_THREAD_QUEUE_OBJ)		\
					   $(THREAD_THREAD_UTILS_OBJ_GROUP)
THREAD_THREAD_QUEUE_TRNR_SRC_PREQS	:= $(THREAD_THREAD_QUEUE_TEST_SRC)	\
			   		   $(TEST_RUNNER_SOURCE_DIR)
THREAD_THREAD_QUEUE_TEST_OBJ_PREQS	:= $(THREAD_THREAD_QUEUE_TEST_SRC)	\
			   		   $(THREAD_THREAD_QUEUE_OBJ_PREQS) 	\
			   		   $(UNITY_OBJ_PREQS)
THREAD_THREAD_QUEUE_TRNR_OBJ_PREQS	:= $(THREAD_THREAD_QUEUE_TRNR_SRC)	\
			   		   $(THREAD_THREAD_QUEUE_TEST_OBJ_PREQS)
THREAD_THREAD_QUEUE_TEST_BIN_PREQS	:= $(THREAD_THREAD_QUEUE_TRNR_OBJ)	\
			   		   $(THREAD_THREAD_QUEUE_TEST_OBJ)	\
			   		   $(THREAD_THREAD_QUEUE_OBJ_GROUP)	\
			   		   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(THREAD_THREAD_QUEUE_TEST_BIN)
TARGETS			+= $(THREAD_THREAD_QUEUE_OBJ)			\
			   $(THREAD_THREAD_QUEUE_TRNR_SRC)		\
			   $(THREAD_THREAD_QUEUE_TRNR_OBJ)		\
			   $(THREAD_THREAD_QUEUE_TEST_OBJ)		\
			   $(THREAD_THREAD_QUEUE_TEST_BIN)


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
TARGETS			+= $(THREAD_THREAD_LOG_OBJ)			\
			   $(THREAD_THREAD_LOG_TRNR_SRC)		\
			   $(THREAD_THREAD_LOG_TRNR_OBJ)		\
			   $(THREAD_THREAD_LOG_TEST_OBJ)		\
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
					   $(THREAD_THREAD_QUEUE_OBJ_GROUP)
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



# ## GENERATOR MODULES
# # ══════════════════════════════════════════════════════════════════════════════
# # gen/gen_strings
# # ──────────────────────────────────────────────────────────────────────────────
# GEN_GEN_STRINGS_SRC 		:= $(call GEN_SOURCE_PATH,strings)
# GEN_GEN_STRINGS_HDR		:= $(call GEN_HEADER_PATH,strings)
# GEN_GEN_STRINGS_OBJ 		:= $(call GEN_OBJECT_PATH,strings)
# GEN_GEN_STRINGS_TEST_SRC	:= $(call GEN_TEST_SOURCE_PATH,strings)
# GEN_GEN_STRINGS_TRNR_SRC	:= $(call GEN_TEST_RUNNER_SOURCE_PATH,strings)
# GEN_GEN_STRINGS_TRNR_OBJ	:= $(call GEN_TEST_RUNNER_OBJECT_PATH,strings)
# GEN_GEN_STRINGS_TEST_OBJ	:= $(call GEN_TEST_OBJECT_PATH,strings)
# GEN_GEN_STRINGS_TEST_BIN	:= $(call GEN_TEST_BINARY_PATH,strings)
# # ─────────────── target prequisites ───────────────────────────────────────────
# GEN_GEN_STRINGS_OBJ_PREQS	:= $(GEN_GEN_STRINGS_SRC) 		\
# 			   	   $(GEN_GEN_STRINGS_HDR)		\
# 			   	   $(THREAD_THREAD_LOG_HDR)
# GEN_GEN_STRINGS_TRNR_SRC_PREQS	:= $(GEN_GEN_STRINGS_TEST_SRC)		\
# 				   $(TEST_RUNNER_SOURCE_DIR)
# GEN_GEN_STRINGS_TEST_OBJ_PREQS	:= $(GEN_GEN_STRINGS_TEST_SRC)		\
# 			   	   $(GEN_GEN_STRINGS_OBJ_PREQS) 	\
# 			   	   $(UNITY_OBJ_PREQS)
# GEN_GEN_STRINGS_TRNR_OBJ_PREQS	:= $(GEN_GEN_STRINGS_TRNR_SRC)		\
# 			   	   $(GEN_GEN_STRINGS_TEST_OBJ_PREQS)
# GEN_GEN_STRINGS_TEST_BIN_PREQS	:= $(GEN_GEN_STRINGS_TRNR_OBJ)		\
# 				   $(GEN_GEN_STRINGS_TEST_OBJ)		\
# 			   	   $(GEN_GEN_STRINGS_OBJ)		\
# 			   	   $(THREAD_THREAD_LOG_OBJ)				\
# 			   	   $(THREAD_THREAD_UTILS_OBJ)			\
# 			   	   $(HELP_OBJ)				\
# 			   	   $(TIME_TIME_UTILS_OBJ)		\
# 			   	   $(STRING_STRING_UTILS_OBJ)				\
# 			   	   $(UNITY_OBJ)
# # ─────────────── targets ──────────────────────────────────────────────────────
# TEST_BINARIES		+= $(GEN_GEN_STRINGS_TEST_BIN)
# TARGETS			+= $(GEN_GEN_STRINGS_OBJ)		\
# 			   $(GEN_GEN_STRINGS_TRNR_SRC)		\
# 			   $(GEN_GEN_STRINGS_TRNR_OBJ)		\
# 			   $(GEN_GEN_STRINGS_TEST_OBJ)		\
# 			   $(GEN_GEN_STRINGS_TEST_BIN)


# # gen/gen_names
# # ──────────────────────────────────────────────────────────────────────────────
# GEN_GEN_NAMES_SRC 		:= $(call GEN_SOURCE_PATH,names)
# GEN_GEN_NAMES_HDR		:= $(call GEN_HEADER_PATH,names)
# GEN_GEN_NAMES_OBJ 		:= $(call GEN_OBJECT_PATH,names)
# GEN_GEN_NAMES_TEST_SRC		:= $(call GEN_TEST_SOURCE_PATH,names)
# GEN_GEN_NAMES_TRNR_SRC		:= $(call GEN_TEST_RUNNER_SOURCE_PATH,names)
# GEN_GEN_NAMES_TRNR_OBJ		:= $(call GEN_TEST_RUNNER_OBJECT_PATH,names)
# GEN_GEN_NAMES_TEST_OBJ		:= $(call GEN_TEST_OBJECT_PATH,names)
# GEN_GEN_NAMES_TEST_BIN		:= $(call GEN_TEST_BINARY_PATH,names)
# # ─────────────── target prequisites ───────────────────────────────────────────
# GEN_GEN_NAMES_OBJ_PREQS		:= $(GEN_GEN_NAMES_SRC) 		\
# 			     	   $(GEN_GEN_NAMES_HDR)			\
# 			     	   $(GEN_GEN_STRINGS_HDR)		\
# 			      	   $(RANDOM_RANDOM_HDR)
# GEN_GEN_NAMES_TRNR_SRC_PREQS	:= $(GEN_GEN_NAMES_TEST_SRC)		\
# 				   $(TEST_RUNNER_SOURCE_DIR)
# GEN_GEN_NAMES_TEST_OBJ_PREQS	:= $(GEN_GEN_NAMES_TEST_SRC)		\
# 			   	   $(GEN_GEN_NAMES_OBJ_PREQS)		\
# 			   	   $(UNITY_OBJ_PREQS)
# GEN_GEN_NAMES_TRNR_OBJ_PREQS	:= $(GEN_GEN_NAMES_TRNR_SRC)		\
# 			   	   $(GEN_GEN_NAMES_TEST_OBJ_PREQS)
# GEN_GEN_NAMES_TEST_BIN_PREQS	:= $(GEN_GEN_NAMES_TRNR_OBJ)		\
# 				   $(GEN_GEN_NAMES_TEST_OBJ)		\
# 			   	   $(GEN_GEN_NAMES_OBJ)			\
# 			   	   $(GEN_GEN_STRINGS_OBJ)		\
# 			   	   $(THREAD_THREAD_LOG_OBJ)				\
# 			   	   $(THREAD_THREAD_UTILS_OBJ)			\
# 			   	   $(HELP_OBJ)				\
# 			   	   $(TIME_TIME_UTILS_OBJ)		\
# 			   	   $(STRING_STRING_UTILS_OBJ)				\
# 			   	   $(RANDOM_RANDOM_OBJ)			\
# 			   	   $(RANDOM_PCG_BASIC_OBJ)		\
# 			   	   $(MEMORY_MEMORY_SWAP_OBJ)		\
# 			   	   $(MEMORY_MEMORY_UTILS_OBJ)		\
# 				   $(UTILS_UTILS_OBJ_GROUP)		\
# 			   	   $(UNITY_OBJ)
# # ─────────────── targets ──────────────────────────────────────────────────────
# TEST_BINARIES		+= $(GEN_GEN_NAMES_TEST_BIN)
# TARGETS			+= $(GEN_GEN_NAMES_OBJ)			\
# 			   $(GEN_GEN_NAMES_TRNR_SRC)		\
# 			   $(GEN_GEN_NAMES_TRNR_OBJ)		\
# 			   $(GEN_GEN_NAMES_TEST_OBJ)		\
# 			   $(GEN_GEN_NAMES_TEST_BIN)


# # gen/gen_count_string
# # ──────────────────────────────────────────────────────────────────────────────
# GEN_GEN_COUNT_STRING_SRC 	:= $(call GEN_SOURCE_PATH,count_string)
# GEN_GEN_COUNT_STRING_HDR	:= $(call GEN_HEADER_PATH,count_string)
# GEN_GEN_COUNT_STRING_OBJ 	:= $(call GEN_OBJECT_PATH,count_string)
# GEN_GEN_COUNT_STRING_TEST_SRC	:= $(call GEN_TEST_SOURCE_PATH,count_string)
# GEN_GEN_COUNT_STRING_TRNR_SRC	:= $(call GEN_TEST_RUNNER_SOURCE_PATH,count_string)
# GEN_GEN_COUNT_STRING_TRNR_OBJ	:= $(call GEN_TEST_RUNNER_OBJECT_PATH,count_string)
# GEN_GEN_COUNT_STRING_TEST_OBJ	:= $(call GEN_TEST_OBJECT_PATH,count_string)
# GEN_GEN_COUNT_STRING_TEST_BIN	:= $(call GEN_TEST_BINARY_PATH,count_string)
# # ─────────────── target prequisites ───────────────────────────────────────────
# GEN_GEN_COUNT_STRING_OBJ_PREQS		:= $(GEN_GEN_COUNT_STRING_SRC) 		\
# 				   	   $(GEN_GEN_COUNT_STRING_HDR) 		\
# 				   	   $(GEN_GEN_STRINGS_HDR)
# GEN_GEN_COUNT_STRING_TRNR_SRC_PREQS	:= $(GEN_GEN_COUNT_STRING_TEST_SRC)	\
# 			   	   	   $(TEST_RUNNER_SOURCE_DIR)
# GEN_GEN_COUNT_STRING_TEST_OBJ_PREQS	:= $(GEN_GEN_COUNT_STRING_TEST_SRC)	\
# 			   	   	   $(GEN_GEN_COUNT_STRING_OBJ_PREQS) 	\
# 			   	   	   $(UNITY_OBJ_PREQS)
# GEN_GEN_COUNT_STRING_TRNR_OBJ_PREQS	:= $(GEN_GEN_COUNT_STRING_TRNR_SRC)	\
# 			   	   	   $(GEN_GEN_COUNT_STRING_TEST_OBJ_PREQS)
# GEN_GEN_COUNT_STRING_TEST_BIN_PREQS	:= $(GEN_GEN_COUNT_STRING_TRNR_OBJ)	\
# 			   	   	   $(GEN_GEN_COUNT_STRING_TEST_OBJ)	\
# 			   	   	   $(GEN_GEN_COUNT_STRING_OBJ)		\
# 			   	   	   $(GEN_GEN_STRINGS_OBJ)		\
# 			   	   	   $(THREAD_THREAD_LOG_OBJ)				\
# 			   	   	   $(THREAD_THREAD_UTILS_OBJ)			\
# 			   	   	   $(HELP_OBJ)				\
# 			   	   	   $(TIME_TIME_UTILS_OBJ)		\
# 			   	   	   $(STRING_STRING_UTILS_OBJ)				\
# 			           	   $(UNITY_OBJ)
# # ─────────────── targets ──────────────────────────────────────────────────────
# TEST_BINARIES		+= $(GEN_GEN_COUNT_STRING_TEST_BIN)
# TARGETS			+= $(GEN_GEN_COUNT_STRING_OBJ)			\
# 			   $(GEN_GEN_COUNT_STRING_TRNR_SRC)		\
# 			   $(GEN_GEN_COUNT_STRING_TRNR_OBJ)		\
# 			   $(GEN_GEN_COUNT_STRING_TEST_OBJ)		\
# 			   $(GEN_GEN_COUNT_STRING_TEST_BIN)


## PROJECT MODULES
# ══════════════════════════════════════════════════════════════════════════════
# mysql_seed_create
# ──────────────────────────────────────────────────────────────────────────────
CREATE_SRC 		:= $(call PROJECT_SOURCE_PATH,create)
CREATE_HDR		:= $(call PROJECT_HEADER_PATH,create)
CREATE_OBJ 		:= $(call PROJECT_OBJECT_PATH,create)
CREATE_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,create)
CREATE_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,create)
CREATE_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,create)
CREATE_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,create)
CREATE_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,create)
# ─────────────── target prequisites ───────────────────────────────────────────
CREATE_OBJ_PREQS	:= $(CREATE_SRC) 				\
			   $(CREATE_HDR) 				\
			   $(MODE_HDR)
CREATE_OBJ_GROUP	:= $(CREATE_OBJ)
CREATE_TRNR_SRC_PREQS	:= $(CREATE_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
CREATE_TEST_OBJ_PREQS	:= $(CREATE_TEST_SRC)				\
			   $(CREATE_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
CREATE_TRNR_OBJ_PREQS	:= $(CREATE_TRNR_SRC)				\
			   $(CREATE_TEST_OBJ_PREQS)
CREATE_TEST_BIN_PREQS	:= $(CREATE_TRNR_OBJ)				\
			   $(CREATE_TEST_OBJ)				\
			   $(CREATE_OBJ_GROUP)				\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(CREATE_TEST_BIN)
TARGETS			+= $(CREATE_OBJ)				\
			   $(CREATE_TRNR_SRC)				\
			   $(CREATE_TRNR_OBJ)				\
			   $(CREATE_TEST_OBJ)				\
			   $(CREATE_TEST_BIN)


# mysql_seed_run
# ──────────────────────────────────────────────────────────────────────────────
RUN_SRC 		:= $(call PROJECT_SOURCE_PATH,run)
RUN_HDR			:= $(call PROJECT_HEADER_PATH,run)
RUN_OBJ 		:= $(call PROJECT_OBJECT_PATH,run)
RUN_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,run)
RUN_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,run)
RUN_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,run)
RUN_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,run)
RUN_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,run)
# ─────────────── target prequisites ───────────────────────────────────────────
RUN_OBJ_PREQS		:= $(RUN_SRC) 					\
			   $(RUN_HDR) 					\
			   $(MODE_HDR)
RUN_OBJ_GROUP		:= $(RUN_OBJ)
RUN_TRNR_SRC_PREQS	:= $(RUN_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
RUN_TEST_OBJ_PREQS	:= $(RUN_TEST_SRC)				\
			   $(RUN_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
RUN_TRNR_OBJ_PREQS	:= $(RUN_TRNR_SRC)				\
			   $(RUN_TEST_OBJ_PREQS)
RUN_TEST_BIN_PREQS	:= $(RUN_TRNR_OBJ)				\
			   $(RUN_TEST_OBJ)				\
			   $(RUN_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(RUN_TEST_BIN)
TARGETS			+= $(RUN_OBJ)					\
			   $(RUN_TRNR_SRC)				\
			   $(RUN_TRNR_OBJ)				\
			   $(RUN_TEST_OBJ)				\
			   $(RUN_TEST_BIN)


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
			   $(MODE_HDR) 					\
			   $(STRING_STRING_MACROS_HDR)
HELP_OBJ_GROUP		:= $(HELP_OBJ)
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



# mysql_seed_cli
# ──────────────────────────────────────────────────────────────────────────────
CLI_SRC 		:= $(call PROJECT_SOURCE_PATH,cli)
CLI_HDR			:= $(call PROJECT_HEADER_PATH,cli)
CLI_OBJ 		:= $(call PROJECT_OBJECT_PATH,cli)
CLI_TEST_SRC		:= $(call PROJECT_TEST_SOURCE_PATH,cli)
CLI_TRNR_SRC		:= $(call PROJECT_TEST_RUNNER_SOURCE_PATH,cli)
CLI_TRNR_OBJ		:= $(call PROJECT_TEST_RUNNER_OBJECT_PATH,cli)
CLI_TEST_OBJ		:= $(call PROJECT_TEST_OBJECT_PATH,cli)
CLI_TEST_BIN		:= $(call PROJECT_TEST_BINARY_PATH,cli)
# # ─────────────── target prequisites ───────────────────────────────────────────
# CLI_OBJ_PREQS		:= $(CLI_SRC) 					\
# 			   $(CLI_HDR)					\
# 			   $(CREATE_HDR)				\
# 			   $(RUN_HDR)					\
# 			   $(HELP_HDR)
# CLI_OBJ_GROUP		:= $(CREATE_OBJ_GROUP)				\
# 			   $(RUN_OBJ_GROUP)				\
# 			   $(HELP_OBJ_GROUP)
# CLI_TRNR_SRC_PREQS	:= $(CLI_TEST_SRC)				\
# 			   $(TEST_RUNNER_SOURCE_DIR)
# CLI_TEST_OBJ_PREQS	:= $(CLI_TEST_SRC)				\
# 			   $(CLI_OBJ_PREQS) 				\
# 			   $(UNITY_OBJ_PREQS)
# CLI_TRNR_OBJ_PREQS	:= $(CLI_TRNR_SRC)				\
# 			   $(CLI_TEST_OBJ_PREQS)
# CLI_TEST_BIN_PREQS	:= $(CLI_TRNR_OBJ)				\
# 			   $(CLI_TEST_OBJ)				\
# 			   $(CLI_OBJ)					\
# 			   $(CREATE_OBJ)				\
# 			   $(RUN_OBJ)					\
# 			   $(THREAD_THREAD_LOG_OBJ)					\
# 			   $(THREAD_THREAD_UTILS_OBJ)				\
# 			   $(HELP_OBJ)					\
# 			   $(TIME_TIME_UTILS_OBJ)			\
# 			   $(STRING_STRING_UTILS_OBJ)					\
# 			   $(UNITY_OBJ)
# # ─────────────── targets ──────────────────────────────────────────────────────
# TEST_BINARIES		+= $(CLI_TEST_BIN)
# TARGETS			+= $(CLI_OBJ)					\
# 			   $(CLI_TRNR_SRC)				\
# 			   $(CLI_TRNR_OBJ)				\
# 			   $(CLI_TEST_OBJ)				\
# 			   $(CLI_TEST_BIN)



# mysql_seed (entry point)
# ──────────────────────────────────────────────────────────────────────────────
# PROJECT_SRC 		:= $(call SOURCE_PATH,$(PROJECT))
# PROJECT_HDR		:= $(call HEADER_PATH,$(PROJECT))
# PROJECT_OBJ 		:= $(call OBJECT_PATH,$(PROJECT))
# PROJECT_BIN 		:= $(call BINARY_PATH,$(PROJECT))
# # ─────────────── target prequisites ───────────────────────────────────────────
# PROJECT_BIN_PREQS	:= $(PROJECT_OBJ) 				\
# 			   $(CREATE_OBJ_GROUP) 				\
# 			   $(RUN_OBJ_GROUP)				\
# 			   $(HELP_OBJ_GROUP)
# 			   $(GEN_GEN_COUNT_STRING_OBJ) 			\
# 			   $(GEN_GEN_NAMES_OBJ) 			\
# 			   $(GEN_GEN_STRINGS_OBJ) 			\
# 			   $(THREAD_THREAD_LOG_OBJ) 					\
# 			   $(THREAD_THREAD_UTILS_OBJ)				\
# 			   $(HELP_OBJ) 					\
# 			   $(STRING_STRING_UTILS_OBJ)					\
# 			   $(RANDOM_RANDOM_OBJ)				\
# 			   $(RANDOM_PCG_BASIC_OBJ)			\
# 			   $(MEMORY_MEMORY_SWAP_OBJ)			\
# 			   $(MEMORY_MEMORY_UTILS_OBJ)			\
# 			   $(TIME_TIME_UTILS_OBJ)			\
# 			   $(UTILS_UTILS_OBJ)

# PROJECT_OBJ_PREQS	:= $(PROJECT_SRC) 				\
# 			   $(PROJECT_HDR) 				\
# 			   $(CLI_HDR)
# # ─────────────── targets ──────────────────────────────────────────────────────
# TARGETS			+= $(PROJECT_OBJ)				\
# 			   $(PROJECT_BIN)




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
# $(PROJECT_OBJ): $(PROJECT_OBJ_PREQS)
# 	$(CC) $(CC_FLAGS) -c $< -o $@

# # make mysql_seed_cli object
# # ──────────────────────────────────────────────────────────────────────────────
# $(CLI_OBJ): $(CLI_OBJ_PREQS)
# 	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_create object
# ──────────────────────────────────────────────────────────────────────────────
$(CREATE_OBJ): $(CREATE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_run object
# ──────────────────────────────────────────────────────────────────────────────
$(RUN_OBJ): $(RUN_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_help object
# ──────────────────────────────────────────────────────────────────────────────
$(HELP_OBJ): $(HELP_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_pool object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_POOL_OBJ): $(THREAD_THREAD_POOL_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_log object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_LOG_OBJ): $(THREAD_THREAD_LOG_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_queue object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_QUEUE_OBJ): $(THREAD_THREAD_QUEUE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make thread/thread_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_UTILS_OBJ): $(THREAD_THREAD_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# # make gen/gen_count_string object
# # ──────────────────────────────────────────────────────────────────────────────
# $(GEN_GEN_COUNT_STRING_OBJ): $(GEN_GEN_COUNT_STRING_OBJ_PREQS)
# 	$(CC) $(CC_FLAGS) -c $< -o $@

# # make gen/gen_names object
# # ──────────────────────────────────────────────────────────────────────────────
# $(GEN_GEN_NAMES_OBJ): $(GEN_GEN_NAMES_OBJ_PREQS)
# 	$(CC) $(CC_FLAGS) -c $< -o $@

# # make gen/gen_strings object
# # ──────────────────────────────────────────────────────────────────────────────
# $(GEN_GEN_STRINGS_OBJ): $(GEN_GEN_STRINGS_OBJ_PREQS)
# 	$(CC) $(CC_FLAGS) -c $< -o $@

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

# make random/random object
# ──────────────────────────────────────────────────────────────────────────────
$(RANDOM_RANDOM_OBJ): $(RANDOM_RANDOM_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make random/pcg_basic object
# ──────────────────────────────────────────────────────────────────────────────
$(RANDOM_PCG_BASIC_OBJ): $(RANDOM_PCG_BASIC_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_swap object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_SWAP_OBJ): $(MEMORY_MEMORY_SWAP_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make memory/memory_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(MEMORY_MEMORY_UTILS_OBJ): $(MEMORY_MEMORY_UTILS_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make time/time_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(TIME_TIME_UTILS_OBJ): $(TIME_TIME_UTILS_OBJ_PREQS)
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



## MAKE UNIT TESTS
# ══════════════════════════════════════════════════════════════════════════════
# for mysql_seed_cli
# make:
# 	mysql_seed_cli_test		binary,
# 	mysql_seed_cli_test_runner 	object,
# 	mysql_seed_cli_test		object, and
# 	mysql_seed_cli_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
# $(CLI_TEST_BIN): $(CLI_TEST_BIN_PREQS)
# 	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

# $(CLI_TRNR_OBJ): $(CLI_TRNR_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(CLI_TEST_OBJ): $(CLI_TEST_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(CLI_TRNR_SRC): $(CLI_TRNR_SRC_PREQS)
# 	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_create
# make:
# 	mysql_seed_create_test		binary,
# 	mysql_seed_create_test_runner 	object,
# 	mysql_seed_create_test		object, and
# 	mysql_seed_create_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(CREATE_TEST_BIN): $(CREATE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(CREATE_TRNR_OBJ): $(CREATE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(CREATE_TEST_OBJ): $(CREATE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(CREATE_TRNR_SRC): $(CREATE_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_run
# make:
# 	mysql_seed_run_test		binary,
# 	mysql_seed_run_test_runner 	object,
# 	mysql_seed_run_test		object, and
# 	mysql_seed_run_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(RUN_TEST_BIN): $(RUN_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(RUN_TRNR_OBJ): $(RUN_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RUN_TEST_OBJ): $(RUN_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RUN_TRNR_SRC): $(RUN_TRNR_SRC_PREQS)
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


# for thread/thread_queue
# make:
# 	thread_thread_queue_test		binary,
# 	thread_thread_queue_test_runner 	object,
# 	thread_thread_queue_test		object, and
# 	thread_thread_queue_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(THREAD_THREAD_QUEUE_TEST_BIN): $(THREAD_THREAD_QUEUE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

$(THREAD_THREAD_QUEUE_TRNR_OBJ): $(THREAD_THREAD_QUEUE_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_QUEUE_TEST_OBJ): $(THREAD_THREAD_QUEUE_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(THREAD_THREAD_QUEUE_TRNR_SRC): $(THREAD_THREAD_QUEUE_TRNR_SRC_PREQS)
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


# # for gen/gen_count_string
# # make:
# # 	gen_gen_count_string_test		binary,
# # 	gen_gen_count_string_test_runner 	object,
# # 	gen_gen_count_string_test		object, and
# # 	gen_gen_count_string_test_runner	source
# # ──────────────────────────────────────────────────────────────────────────────
# $(GEN_GEN_COUNT_STRING_TEST_BIN): $(GEN_GEN_COUNT_STRING_TEST_BIN_PREQS)
# 	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

# $(GEN_GEN_COUNT_STRING_TRNR_OBJ): $(GEN_GEN_COUNT_STRING_TRNR_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(GEN_GEN_COUNT_STRING_TEST_OBJ): $(GEN_GEN_COUNT_STRING_TEST_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(GEN_GEN_COUNT_STRING_TRNR_SRC): $(GEN_GEN_COUNT_STRING_TRNR_SRC_PREQS)
# 	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@

# # for gen/gen_names
# # make:
# # 	gen_gen_names_test		binary,
# # 	gen_gen_names_test_runner 	object,
# # 	gen_gen_names_test		object, and
# # 	gen_gen_names_test_runner	source
# # ──────────────────────────────────────────────────────────────────────────────
# $(GEN_GEN_NAMES_TEST_BIN): $(GEN_GEN_NAMES_TEST_BIN_PREQS)
# 	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

# $(GEN_GEN_NAMES_TRNR_OBJ): $(GEN_GEN_NAMES_TRNR_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(GEN_GEN_NAMES_TEST_OBJ): $(GEN_GEN_NAMES_TEST_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(GEN_GEN_NAMES_TRNR_SRC): $(GEN_GEN_NAMES_TRNR_SRC_PREQS)
# 	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# # for gen/gen_strings
# # make:
# # 	gen_gen_strings_test		binary,
# # 	gen_gen_strings_test_runner 	object,
# # 	gen_gen_strings_test		object, and
# # 	gen_gen_strings_test_runner	source
# # ──────────────────────────────────────────────────────────────────────────────
# $(GEN_GEN_STRINGS_TEST_BIN): $(GEN_GEN_STRINGS_TEST_BIN_PREQS)
# 	$(LD) $(LD_FLAGS) $^ $(UNITY_LD_LIB_FLAGS) $(LD_LIB_FLAGS) -o $@

# $(GEN_GEN_STRINGS_TRNR_OBJ): $(GEN_GEN_STRINGS_TRNR_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(GEN_GEN_STRINGS_TEST_OBJ): $(GEN_GEN_STRINGS_TEST_OBJ_PREQS)
# 	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

# $(GEN_GEN_STRINGS_TRNR_SRC): $(GEN_GEN_STRINGS_TRNR_SRC_PREQS)
# 	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@



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
