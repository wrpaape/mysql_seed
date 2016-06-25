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
define NEWLINE :=


endef


# SYSTEM CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# taken from user 'Trevor Robinson''s response to stackoverflow question:
#
# 	http://stackoverflow.com/questions/714100/os-detecting-makefile

ifeq ($(OS),Windows_NT)

        SYSTEM_WINDOWS 	:= T
        SYS_ENV_FLAGS 	:= -DWIN32

        ifeq      (AMD64,$(PROCESSOR_ARCHITECTURE))
                SYS_ARCH_FLAG	:= -arch x86_64
                SYS_ENV_FLAGS	+= -DAMD64
        else ifeq (x86,$(PROCESSOR_ARCHITECTURE))
                SYS_ARCH_FLAG	:= -arch i386
                SYS_ENV_FLAGS	+= -DIA32
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

        UNAME_P := $(shell uname -p)
        ifeq      (x86_64,$(UNAME_P))
                SYS_ARCH_FLAG	:= -arch i386
                SYS_ENV_FLAGS	+= -DAMD64
        else ifneq (,$(filter %86,$(UNAME_P)))
                SYS_ARCH_FLAG	:= -arch x86_64
                SYS_ENV_FLAGS 	+= -DIA32
        else ifneq (,$(filter arm%,$(UNAME_P)))
                SYS_ARCH_FLAG	:= -arch AArch64
                SYS_ENV_FLAGS 	+= -DARM
        endif
endif


# Path delimiter
# ──────────────────────────────────────────────────────────────────────────────
ifeq (T,$(SYSTEM_WINDOWS))
PATH_DELIM	:= \\
else
PATH_DELIM	:= /
endif

# Chain commands
# ──────────────────────────────────────────────────────────────────────────────
ifeq (T,$(SYSTEM_WINDOWS))
CMD_DELIM 	:= &
else
CMD_DELIM	:= ;
endif




# DIRECTORY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
PATH_JOIN		 = $(subst $(SPACE),$(PATH_DELIM),$(strip $1))

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

# Project Module
# ─────────────── source ───────────────────────────────────────────────────────
MODULE_SOURCE_PATH		= $(call SOURCE_PATH,$(PROJECT)_$1)# implementation
MODULE_HEADER_PATH		= $(call HEADER_PATH,$(PROJECT)_$1)# interface
# ─────────────── build ────────────────────────────────────────────────────────
MODULE_OBJECT_PATH   		= $(call OBJECT_PATH,$(PROJECT)_$1)# object files

# Module Testing
# ─────────────── source ───────────────────────────────────────────────────────
TEST_SOURCE_PATH		= $(call SOURCE_FILE_PATH,$(TEST_SOURCE_DIR),$(PROJECT)_$1_test)# Unity unit test implementation
TEST_HEADER_PATH		= $(call HEADER_FILE_PATH,$(TEST_HEADER_DIR),$(PROJECT)_$1_test)# Unity unit test interface
TEST_RUNNER_SOURCE_PATH		= $(call SOURCE_FILE_PATH,$(TEST_RUNNER_SOURCE_DIR),$(PROJECT)_$1_test_runner)# Unity test runners
# ─────────────── build ────────────────────────────────────────────────────────
TEST_OBJECT_PATH 		= $(call OBJECT_FILE_PATH,$(TEST_OBJECT_DIR),$(PROJECT)_$1_test)# Unity unit test object files
TEST_RUNNER_OBJECT_PATH		= $(call OBJECT_FILE_PATH,$(TEST_RUNNER_OBJECT_DIR),$(PROJECT)_$1_test_runner)# Unity test runner object files
TEST_BINARY_PATH 		= $(call BINARY_FILE_PATH,$(TEST_BINARY_DIR),$(PROJECT)_$1_test)# binary executable output

# Unity Test Framework
# ─────────────── source ───────────────────────────────────────────────────────
UNITY_SOURCE_PATH		= $(call SOURCE_FILE_PATH,$(UNITY_SOURCE_DIR),$1)# Unity framework implementation
UNITY_HEADER_PATH		= $(call HEADER_FILE_PATH,$(UNITY_HEADER_DIR),$1)# Unity framework interface
# ─────────────── build ────────────────────────────────────────────────────────
UNITY_SCRIPT_PATH		= $(call SCRIPT_FILE_PATH,$(UNITY_AUTO_DIR),$1)# Unity framework scripts
UNITY_OBJECT_PATH 		= $(call OBJECT_FILE_PATH,$(UNITY_OBJECT_DIR),$1)# Unity framework object files



# UTILITY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# C Compiler
# ──────────────────────────────────────────────────────────────────────────────
CC		:= gcc
CC_ENV_FLAGS	:= -D__USE_FIXED_PROTOTYPES__ $(SYS_ENV_FLAGS)
CC_FLAGS	:= -g -O2 -std=c99 -Wall $(CC_ENV_FLAGS) -I$(HEADER_DIR)
# Linker
# ──────────────────────────────────────────────────────────────────────────────
LD		:= ld
LD_FLAGS	:= -no_pie $(SYS_ARCH_FLAG)
LD_LIB_FLAGS	:= -lpthread -lc

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




## PROJECT COMPONENTS
# ══════════════════════════════════════════════════════════════════════════════
# unity (test framework)
# ──────────────────────────────────────────────────────────────────────────────
UNITY_SRC 		:= $(call UNITY_SOURCE_PATH,unity)
UNITY_HDR 		:= $(call UNITY_HEADER_PATH,unity)
UNITY_CONFIG_HDR 	:= $(call UNITY_HEADER_PATH,unity_config)
UNITY_INTERNALS_HDR 	:= $(call UNITY_HEADER_PATH,unity_internals)
UNITY_OBJ 		:= $(call UNITY_OBJECT_PATH,unity)
UNITY_GEN_TRNR_SCRIPT	:= $(call UNITY_SCRIPT_PATH,generate_test_runner)
UNITY_ENV_FLAGS 	:= -DUNITY_INCLUDE_CONFIG_H
UNITY_CC_FLAGS		:= $(CC_FLAGS) $(UNITY_ENV_FLAGS) -I$(UNITY_HEADER_DIR)
# ─────────────── run all tests ────────────────────────────────────────────────
TEST_FILES_GLOB	:= $(call TEST_BINARY_PATH,*)
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
MODE_HDR		:= $(call MODULE_HEADER_PATH,mode)
STRING_MACROS_HDR	:= $(call MODULE_HEADER_PATH,string_macros)


# mysql_seed_utils
# ──────────────────────────────────────────────────────────────────────────────
UTILS_SRC 		:= $(call MODULE_SOURCE_PATH,utils)
UTILS_HDR		:= $(call MODULE_HEADER_PATH,utils)
UTILS_OBJ 		:= $(call MODULE_OBJECT_PATH,utils)
UTILS_TEST_SRC		:= $(call TEST_SOURCE_PATH,utils)
UTILS_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,utils)
UTILS_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,utils)
UTILS_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,utils)
UTILS_TEST_OBJ		:= $(call TEST_OBJECT_PATH,utils)
UTILS_TEST_BIN		:= $(call TEST_BINARY_PATH,utils)
# ─────────────── target prequisites ───────────────────────────────────────────
UTILS_OBJ_PREQS		:= $(UTILS_SRC) 				\
			   $(UTILS_HDR)					\
			   $(STRING_MACROS_HDR)
UTILS_TRNR_SRC_PREQS	:= $(UTILS_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
UTILS_TEST_OBJ_PREQS	:= $(UTILS_TEST_SRC)				\
			   $(UTILS_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
UTILS_TRNR_OBJ_PREQS	:= $(UTILS_TRNR_SRC)				\
			   $(UTILS_TEST_OBJ_PREQS)
UTILS_TEST_BIN_PREQS	:= $(UTILS_TRNR_OBJ)				\
			   $(UTILS_TEST_OBJ)				\
			   $(UTILS_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(UTILS_TEST_BIN)
TARGETS			+= $(UTILS_OBJ)					\
			   $(UTILS_TRNR_SRC)				\
			   $(UTILS_TRNR_OBJ)				\
			   $(UTILS_TEST_OBJ)				\
			   $(UTILS_TEST_BIN)



# mysql_seed_exit
# ──────────────────────────────────────────────────────────────────────────────
EXIT_SRC 		:= $(call MODULE_SOURCE_PATH,exit)
EXIT_HDR		:= $(call MODULE_HEADER_PATH,exit)
EXIT_OBJ 		:= $(call MODULE_OBJECT_PATH,exit)
EXIT_TEST_SRC		:= $(call TEST_SOURCE_PATH,exit)
EXIT_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,exit)
EXIT_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,exit)
EXIT_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,exit)
EXIT_TEST_OBJ		:= $(call TEST_OBJECT_PATH,exit)
EXIT_TEST_BIN		:= $(call TEST_BINARY_PATH,exit)
# ─────────────── target prequisites ───────────────────────────────────────────
EXIT_OBJ_PREQS		:= $(EXIT_SRC) 					\
			   $(EXIT_HDR) 					\
			   $(MODE_HDR) 					\
			   $(STRING_MACROS_HDR)
EXIT_TRNR_SRC_PREQS	:= $(EXIT_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
EXIT_TEST_OBJ_PREQS	:= $(EXIT_TEST_SRC)				\
			   $(EXIT_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
EXIT_TRNR_OBJ_PREQS	:= $(EXIT_TRNR_SRC)				\
			   $(EXIT_TEST_OBJ_PREQS)
EXIT_TEST_BIN_PREQS	:= $(EXIT_TRNR_OBJ)				\
			   $(EXIT_TEST_OBJ)				\
			   $(EXIT_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(EXIT_TEST_BIN)
TARGETS			+= $(EXIT_OBJ)					\
			   $(EXIT_TRNR_SRC)				\
			   $(EXIT_TRNR_OBJ)				\
			   $(EXIT_TEST_OBJ)				\
			   $(EXIT_TEST_BIN)


# mysql_seed_parallel
# ──────────────────────────────────────────────────────────────────────────────
PARALLEL_SRC 		:= $(call MODULE_SOURCE_PATH,parallel)
PARALLEL_HDR		:= $(call MODULE_HEADER_PATH,parallel)
PARALLEL_OBJ 		:= $(call MODULE_OBJECT_PATH,parallel)
PARALLEL_TEST_SRC	:= $(call TEST_SOURCE_PATH,parallel)
PARALLEL_TRNR_SRC	:= $(call TEST_RUNNER_SOURCE_PATH,parallel)
PARALLEL_TEST_OBJ	:= $(call TEST_RUNNER_OBJECT_PATH,parallel)
PARALLEL_TRNR_OBJ	:= $(call TEST_RUNNER_OBJECT_PATH,parallel)
PARALLEL_TEST_OBJ	:= $(call TEST_OBJECT_PATH,parallel)
PARALLEL_TEST_BIN	:= $(call TEST_BINARY_PATH,parallel)
# ─────────────── target prequisites ───────────────────────────────────────────
PARALLEL_OBJ_PREQS	:= $(PARALLEL_SRC) 				\
			   $(PARALLEL_HDR)				\
			   $(EXIT_HDR)
PARALLEL_TRNR_SRC_PREQS	:= $(PARALLEL_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
PARALLEL_TEST_OBJ_PREQS	:= $(PARALLEL_TEST_SRC)				\
			   $(PARALLEL_OBJ_PREQS) 			\
			   $(UNITY_OBJ_PREQS)
PARALLEL_TRNR_OBJ_PREQS	:= $(PARALLEL_TRNR_SRC)				\
			   $(PARALLEL_TEST_OBJ_PREQS)
PARALLEL_TEST_BIN_PREQS	:= $(PARALLEL_TRNR_OBJ)				\
			   $(PARALLEL_TEST_OBJ)				\
			   $(PARALLEL_OBJ)				\
			   $(EXIT_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(PARALLEL_TEST_BIN)
TARGETS			+= $(PARALLEL_OBJ)				\
			   $(PARALLEL_TRNR_SRC)				\
			   $(PARALLEL_TRNR_OBJ)				\
			   $(PARALLEL_TEST_OBJ)				\
			   $(PARALLEL_TEST_BIN)



# mysql_seed_log
# ──────────────────────────────────────────────────────────────────────────────
LOG_SRC 		:= $(call MODULE_SOURCE_PATH,log)
LOG_HDR			:= $(call MODULE_HEADER_PATH,log)
LOG_OBJ 		:= $(call MODULE_OBJECT_PATH,log)
LOG_TEST_SRC		:= $(call TEST_SOURCE_PATH,log)
LOG_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,log)
LOG_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,log)
LOG_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,log)
LOG_TEST_OBJ		:= $(call TEST_OBJECT_PATH,log)
LOG_TEST_BIN		:= $(call TEST_BINARY_PATH,log)
# ─────────────── target prequisites ───────────────────────────────────────────
LOG_OBJ_PREQS		:= $(LOG_SRC) 					\
			   $(LOG_HDR) 					\
			   $(PARALLEL_HDR)				\
			   $(UTILS_HDR)
LOG_TRNR_SRC_PREQS	:= $(LOG_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
LOG_TEST_OBJ_PREQS	:= $(LOG_TEST_SRC)				\
			   $(LOG_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
LOG_TRNR_OBJ_PREQS	:= $(LOG_TRNR_SRC)				\
			   $(LOG_TEST_OBJ_PREQS)
LOG_TEST_BIN_PREQS	:= $(LOG_TRNR_OBJ)				\
			   $(LOG_TEST_OBJ)				\
			   $(LOG_OBJ)					\
			   $(PARALLEL_OBJ)				\
			   $(EXIT_OBJ)					\
			   $(UTILS_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(LOG_TEST_BIN)
TARGETS			+= $(LOG_OBJ)					\
			   $(LOG_TRNR_SRC)				\
			   $(LOG_TRNR_OBJ)				\
			   $(LOG_TEST_OBJ)				\
			   $(LOG_TEST_BIN)



# mysql_seed_create
# ──────────────────────────────────────────────────────────────────────────────
CREATE_SRC 		:= $(call MODULE_SOURCE_PATH,create)
CREATE_HDR		:= $(call MODULE_HEADER_PATH,create)
CREATE_OBJ 		:= $(call MODULE_OBJECT_PATH,create)
CREATE_TEST_SRC		:= $(call TEST_SOURCE_PATH,create)
CREATE_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,create)
CREATE_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,create)
CREATE_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,create)
CREATE_TEST_OBJ		:= $(call TEST_OBJECT_PATH,create)
CREATE_TEST_BIN		:= $(call TEST_BINARY_PATH,create)
# ─────────────── target prequisites ───────────────────────────────────────────
CREATE_OBJ_PREQS	:= $(CREATE_SRC) 				\
			   $(CREATE_HDR) 				\
			   $(MODE_HDR)
CREATE_TRNR_SRC_PREQS	:= $(CREATE_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
CREATE_TEST_OBJ_PREQS	:= $(CREATE_TEST_SRC)				\
			   $(CREATE_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
CREATE_TRNR_OBJ_PREQS	:= $(CREATE_TRNR_SRC)				\
			   $(CREATE_TEST_OBJ_PREQS)
CREATE_TEST_BIN_PREQS	:= $(CREATE_TRNR_OBJ)				\
			   $(CREATE_TEST_OBJ)				\
			   $(CREATE_OBJ)				\
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
RUN_SRC 		:= $(call MODULE_SOURCE_PATH,run)
RUN_HDR			:= $(call MODULE_HEADER_PATH,run)
RUN_OBJ 		:= $(call MODULE_OBJECT_PATH,run)
RUN_TEST_SRC		:= $(call TEST_SOURCE_PATH,run)
RUN_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,run)
RUN_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,run)
RUN_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,run)
RUN_TEST_OBJ		:= $(call TEST_OBJECT_PATH,run)
RUN_TEST_BIN		:= $(call TEST_BINARY_PATH,run)
# ─────────────── target prequisites ───────────────────────────────────────────
RUN_OBJ_PREQS		:= $(RUN_SRC) 					\
			   $(RUN_HDR) 					\
			   $(MODE_HDR)
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




# mysql_seed_count_string
# ──────────────────────────────────────────────────────────────────────────────
COUNT_STRING_SRC 	:= $(call MODULE_SOURCE_PATH,count_string)
COUNT_STRING_HDR	:= $(call MODULE_HEADER_PATH,count_string)
COUNT_STRING_OBJ 	:= $(call MODULE_OBJECT_PATH,count_string)
COUNT_STRING_TEST_SRC	:= $(call TEST_SOURCE_PATH,count_string)
COUNT_STRING_TRNR_SRC	:= $(call TEST_RUNNER_SOURCE_PATH,count_string)
COUNT_STRING_TEST_OBJ	:= $(call TEST_RUNNER_OBJECT_PATH,count_string)
COUNT_STRING_TRNR_OBJ	:= $(call TEST_RUNNER_OBJECT_PATH,count_string)
COUNT_STRING_TEST_OBJ	:= $(call TEST_OBJECT_PATH,count_string)
COUNT_STRING_TEST_BIN	:= $(call TEST_BINARY_PATH,count_string)
# ─────────────── target prequisites ───────────────────────────────────────────
COUNT_STRING_OBJ_PREQS		:= $(COUNT_STRING_SRC) 			\
				   $(COUNT_STRING_HDR) 			\
				   $(LOG_HDR)
COUNT_STRING_TRNR_SRC_PREQS	:= $(COUNT_STRING_TEST_SRC)		\
			   	   $(TEST_RUNNER_SOURCE_DIR)
COUNT_STRING_TEST_OBJ_PREQS	:= $(COUNT_STRING_TEST_SRC)		\
			   	   $(COUNT_STRING_OBJ_PREQS) 		\
			   	   $(UNITY_OBJ_PREQS)
COUNT_STRING_TRNR_OBJ_PREQS	:= $(COUNT_STRING_TRNR_SRC)		\
			   	   $(COUNT_STRING_TEST_OBJ_PREQS)
COUNT_STRING_TEST_BIN_PREQS	:= $(COUNT_STRING_TRNR_OBJ)		\
			   	   $(COUNT_STRING_TEST_OBJ)		\
			   	   $(COUNT_STRING_OBJ)			\
			   	   $(LOG_OBJ)				\
			   	   $(PARALLEL_OBJ)			\
			   	   $(EXIT_OBJ)				\
			   	   $(UTILS_OBJ)				\
			           $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(COUNT_STRING_TEST_BIN)
TARGETS			+= $(COUNT_STRING_OBJ)				\
			   $(COUNT_STRING_TRNR_SRC)			\
			   $(COUNT_STRING_TRNR_OBJ)			\
			   $(COUNT_STRING_TEST_OBJ)			\
			   $(COUNT_STRING_TEST_BIN)




# mysql_seed_cli
# ──────────────────────────────────────────────────────────────────────────────
CLI_SRC 		:= $(call MODULE_SOURCE_PATH,cli)
CLI_HDR			:= $(call MODULE_HEADER_PATH,cli)
CLI_OBJ 		:= $(call MODULE_OBJECT_PATH,cli)
CLI_TEST_SRC		:= $(call TEST_SOURCE_PATH,cli)
CLI_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,cli)
CLI_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,cli)
CLI_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,cli)
CLI_TEST_OBJ		:= $(call TEST_OBJECT_PATH,cli)
CLI_TEST_BIN		:= $(call TEST_BINARY_PATH,cli)
# ─────────────── target prequisites ───────────────────────────────────────────
CLI_OBJ_PREQS		:= $(CLI_SRC) 					\
			   $(CLI_HDR)					\
			   $(CREATE_HDR)				\
			   $(RUN_HDR)					\
			   $(EXIT_HDR)
CLI_TRNR_SRC_PREQS	:= $(CLI_TEST_SRC)				\
			   $(TEST_RUNNER_SOURCE_DIR)
CLI_TEST_OBJ_PREQS	:= $(CLI_TEST_SRC)				\
			   $(CLI_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
CLI_TRNR_OBJ_PREQS	:= $(CLI_TRNR_SRC)				\
			   $(CLI_TEST_OBJ_PREQS)
CLI_TEST_BIN_PREQS	:= $(CLI_TRNR_OBJ)				\
			   $(CLI_TEST_OBJ)				\
			   $(CLI_OBJ)					\
			   $(CREATE_OBJ)				\
			   $(RUN_OBJ)					\
			   $(LOG_OBJ)					\
			   $(PARALLEL_OBJ)				\
			   $(EXIT_OBJ)					\
			   $(UTILS_OBJ)					\
			   $(UNITY_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(CLI_TEST_BIN)
TARGETS			+= $(CLI_OBJ)					\
			   $(CLI_TRNR_SRC)				\
			   $(CLI_TRNR_OBJ)				\
			   $(CLI_TEST_OBJ)				\
			   $(CLI_TEST_BIN)



# mysql_seed (entry point)
# ──────────────────────────────────────────────────────────────────────────────
PROJECT_SRC 		:= $(call SOURCE_PATH,$(PROJECT))
PROJECT_HDR		:= $(call HEADER_PATH,$(PROJECT))
PROJECT_OBJ 		:= $(call OBJECT_PATH,$(PROJECT))
PROJECT_BIN 		:= $(call BINARY_PATH,$(PROJECT))
# ─────────────── target prequisites ───────────────────────────────────────────
PROJECT_BIN_PREQS	:= $(PROJECT_OBJ) 				\
			   $(CLI_OBJ) 					\
			   $(CREATE_OBJ) 				\
			   $(RUN_OBJ) 					\
			   $(COUNT_STRING_OBJ) 				\
			   $(LOG_OBJ) 					\
			   $(PARALLEL_OBJ)				\
			   $(EXIT_OBJ) 					\
			   $(UTILS_OBJ)
PROJECT_OBJ_PREQS	:= $(PROJECT_SRC) 				\
			   $(PROJECT_HDR) 				\
			   $(CLI_HDR)
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
test: $(TEST_BINARIES)
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

# make mysql_seed object
# ──────────────────────────────────────────────────────────────────────────────
$(PROJECT_OBJ): $(PROJECT_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_cli object
# ──────────────────────────────────────────────────────────────────────────────
$(CLI_OBJ): $(CLI_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_create object
# ──────────────────────────────────────────────────────────────────────────────
$(CREATE_OBJ): $(CREATE_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_run object
# ──────────────────────────────────────────────────────────────────────────────
$(RUN_OBJ): $(RUN_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_exit object
# ──────────────────────────────────────────────────────────────────────────────
$(EXIT_OBJ): $(EXIT_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_count_string object
# ──────────────────────────────────────────────────────────────────────────────
$(COUNT_STRING_OBJ): $(COUNT_STRING_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_log object
# ──────────────────────────────────────────────────────────────────────────────
$(LOG_OBJ): $(LOG_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_parallel object
# ──────────────────────────────────────────────────────────────────────────────
$(PARALLEL_OBJ): $(PARALLEL_OBJ_PREQS)
	$(CC) $(CC_FLAGS) -c $< -o $@

# make mysql_seed_utils object
# ──────────────────────────────────────────────────────────────────────────────
$(UTILS_OBJ): $(UTILS_OBJ_PREQS)
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
$(CLI_TEST_BIN): $(CLI_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(CLI_TRNR_OBJ): $(CLI_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(CLI_TEST_OBJ): $(CLI_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(CLI_TRNR_SRC): $(CLI_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_create
# make:
# 	mysql_seed_create_test		binary,
# 	mysql_seed_create_test_runner 	object,
# 	mysql_seed_create_test		object, and
# 	mysql_seed_create_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(CREATE_TEST_BIN): $(CREATE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

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
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(RUN_TRNR_OBJ): $(RUN_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RUN_TEST_OBJ): $(RUN_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RUN_TRNR_SRC): $(RUN_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_exit
# make:
# 	mysql_seed_exit_test		binary,
# 	mysql_seed_exit_test_runner 	object,
# 	mysql_seed_exit_test		object, and
# 	mysql_seed_exit_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(EXIT_TEST_BIN): $(EXIT_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(EXIT_TRNR_OBJ): $(EXIT_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(EXIT_TEST_OBJ): $(EXIT_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(EXIT_TRNR_SRC): $(EXIT_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_count_string
# make:
# 	mysql_seed_count_string_test		binary,
# 	mysql_seed_count_string_test_runner 	object,
# 	mysql_seed_count_string_test		object, and
# 	mysql_seed_count_string_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(COUNT_STRING_TEST_BIN): $(COUNT_STRING_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(COUNT_STRING_TRNR_OBJ): $(COUNT_STRING_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(COUNT_STRING_TEST_OBJ): $(COUNT_STRING_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(COUNT_STRING_TRNR_SRC): $(COUNT_STRING_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_log
# make:
# 	mysql_seed_log_test		binary,
# 	mysql_seed_log_test_runner 	object,
# 	mysql_seed_log_test		object, and
# 	mysql_seed_log_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(LOG_TEST_BIN): $(LOG_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(LOG_TRNR_OBJ): $(LOG_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(LOG_TEST_OBJ): $(LOG_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(LOG_TRNR_SRC): $(LOG_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_parallel
# make:
# 	mysql_seed_parallel_test		binary,
# 	mysql_seed_parallel_test_runner 	object,
# 	mysql_seed_parallel_test		object, and
# 	mysql_seed_parallel_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(PARALLEL_TEST_BIN): $(PARALLEL_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(PARALLEL_TRNR_OBJ): $(PARALLEL_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(PARALLEL_TEST_OBJ): $(PARALLEL_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(PARALLEL_TRNR_SRC): $(PARALLEL_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@


# for mysql_seed_utils
# make:
# 	mysql_seed_utils_test		binary,
# 	mysql_seed_utils_test_runner 	object,
# 	mysql_seed_utils_test		object, and
# 	mysql_seed_utils_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(UTILS_TEST_BIN): $(UTILS_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(UTILS_TRNR_OBJ): $(UTILS_TRNR_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_TEST_OBJ): $(UTILS_TEST_OBJ_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_TRNR_SRC): $(UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@
