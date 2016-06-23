.PHONY: all test clean

# ══════════════════════════════════════════════════════════════════════════════
# ──────────────────────────────────────────────────────────────────────────────
#				CONFIGURATION
# ──────────────────────────────────────────────────────────────────────────────
# ══════════════════════════════════════════════════════════════════════════════
#
#
# SYSTEM CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# taken from user 'Trevor Robinson''s response to stackoverflow question:
#
# 	http://stackoverflow.com/questions/714100/os-detecting-makefile
ifeq ($(OS),Windows_NT)
        SYSTEM_WINDOWS 	:= T
        SYS_ENV_FLAGS 	:= -DWIN32

        ifeq      (AMD64,$(PROCESSOR_ARCHITECTURE))
                SYS_ENV_FLAGS	+= -DAMD64
        else ifeq (x86,$(PROCESSOR_ARCHITECTURE))
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
                SYS_ENV_FLAGS	+= -DAMD64
        else ifneq (,$(filter %86,$(UNAME_P)))
                SYS_ENV_FLAGS 	+= -DIA32
        else ifneq (,$(filter arm%,$(UNAME_P)))
                SYS_ENV_FLAGS 	+= -DARM
        endif
endif
# Path delimiter
# ──────────────────────────────────────────────────────────────────────────────
ifdef $(SYSTEM_WINDOWS)
PATH_DELIM	:= \\
else
PATH_DELIM	:= /
endif
# Chain commands
# ──────────────────────────────────────────────────────────────────────────────
ifdef $(SYSTEM_WINDOWS)
CMD_DELIM 	:= &
else
CMD_DELIM	:= ;
endif




# DIRECTORY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
PATH_JOIN	 	 = $(subst $(SPACE),$(PATH_DELIM),$(strip $1))

PROJECT 		:= mysql_seed
PROJECT_ROOT		:= ..
SOURCE_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) src)
HEADER_DIR		:= $(SOURCE_DIR)
OBJECT_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) obj)
BINARY_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) bin)
TEST_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) test)
TEST_RUNNER_DIR		:= $(call PATH_JOIN,$(TEST_DIR) test_runners)
UNITY_DIR		:= $(call PATH_JOIN,$(TEST_DIR) unity)
UNITY_SOURCE_DIR	:= $(call PATH_JOIN,$(UNITY_DIR) src)
UNITY_HEADER_DIR	:= $(UNITY_SOURCE_DIR)
UNITY_AUTO_DIR  	:= $(call PATH_JOIN,$(UNITY_DIR) auto)



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
LD_FLAGS	:= -no_pie
LD_LIB_FLAGS	:= -lpthread -lc
# Make Directory
# ──────────────────────────────────────────────────────────────────────────────
MKDIR	    	:= mkdir
MKDIR_FLAGS 	:= $(EMPTY)
# Cleaner
# ──────────────────────────────────────────────────────────────────────────────
ifdef $(SYSTEM_WINDOWS)
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



# PATH CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# Project File
# ──────────────────────────────────────────────────────────────────────────────
PROJECT_FILE			= $(call PATH_JOIN,$1 $(call TRIM,$(PROJECT)$2$3))
# Project Module
# ─────────────── source ───────────────────────────────────────────────────────
HEADER_PATH			= $(call PROJECT_FILE,$(HEADER_DIR),$1,.h)# interface
SOURCE_PATH			= $(call PROJECT_FILE,$(SOURCE_DIR),$1,.c)# implementation
# ─────────────── build ────────────────────────────────────────────────────────
OBJECT_PATH   			= $(call PROJECT_FILE,$(OBJECT_DIR),$1,.o)# object files
BINARY_PATH 			= $(call PROJECT_FILE,$(BINARY_DIR),$1,$(EMPTY))# binary executable output
# Module Testing
# ─────────────── scripts ──────────────────────────────────────────────────────
UNITY_AUTO_PATH			= $(call PATH_JOIN,$(UNITY_AUTO_DIR)$1.rb)
# ─────────────── source ───────────────────────────────────────────────────────
UNITY_SOURCE_PATH		= $(call PATH_JOIN,$(UNITY_SOURCE_DIR)$1.c)
UNITY_HEADER_PATH		= $(call PATH_JOIN,$(UNITY_HEADER_DIR)$1.h)
TEST_SOURCE_PATH		= $(call PROJECT_FILE,$(TEST_DIR),$1,_test.c)# Unity unit tests
TEST_RUNNER_SOURCE_PATH		= $(call PROJECT_FILE,$(TEST_RUNNER_DIR),$1,_test_runner.c)# Unity test runners
# ─────────────── build ────────────────────────────────────────────────────────
UNITY_OBJECT_PATH 		= $(call PROJECT_FILE,$(OBJECT_DIR),$1,.o)# Unity framework object files
TEST_OBJECT_PATH 		= $(call PROJECT_FILE,$(OBJECT_DIR),$1,_test.o)# Unity unit test object files
TEST_RUNNER_OBJECT_PATH		= $(call PROJECT_FILE,$(OBJECT_DIR),$1,_test_runner.o)# Unity test runner object files
TEST_BINARY_PATH 		= $(call PROJECT_FILE,$(TEST_DIR),$1,_test)# binary executable output


## MISC
# ══════════════════════════════════════════════════════════════════════════════
# String Utils
# ──────────────────────────────────────────────────────────────────────────────
EMPTY	:=
SPACE	:= $(EMPTY) $(EMPTY)
TAB	:= $(EMPTY)	$(EMPTY)
TRIM	 = $(subst $(SPACE),$(EMPTY),$1)
define NEWLINE :=


endef
# Run all Tests
# ──────────────────────────────────────────────────────────────────────────────
TEST_FILES_GLOB	:= $(call TEST_BINARY_PATH,*)

ifdef $(SYSTEM_WINDOWS)
RUN_ALL_TESTS	:= FORFILES /M $(TEST_FILES_GLOB) /C "cmd /c @file"

else
RUN_ALL_TESTS	:= for test in $(TEST_FILES_GLOB); do "./$$test"; done
endif



## PROJECT COMPONENTS
# ══════════════════════════════════════════════════════════════════════════════
# unity (test framework)
# ──────────────────────────────────────────────────────────────────────────────
UNITY_SRC 		:= $(call UNITY_SOURCE_PATH,unity)
UNITY_HDR 		:= $(call UNITY_HEADER_PATH,unity)
UNITY_CONFIG_HDR 	:= $(call UNITY_HEADER_PATH,unity_config)
UNITY_INTERNALS_HDR 	:= $(call UNITY_HEADER_PATH,unity_internals)
UNITY_OBJ 		:= $(call UNITY_OBJECT_PATH,unity)
UNITY_GEN_TRNR_SCRIPT	:= $(call UNITY_AUTO_PATH,generate_test_runner)
UNITY_ENV_FLAGS 	:= -DUNITY_INCLUDE_CONFIG_H
UNITY_CC_FLAGS		:= $(CC_FLAGS) $(UNITY_ENV_FLAGS) -I$(UNITY_HEADER_DIR)
# ─────────────── target prequisites ───────────────────────────────────────────
UNITY_OBJ_PREQS		:= $(UNITY_SRC)					\
			   $(UNITY_HDR)					\
			   $(UNITY_INTERNALS_HDR)			\
			   $(UNITY_CONFIG_HDR)
# ─────────────── targets ──────────────────────────────────────────────────────
TARGETS			+= $(UNITY_OBJ)					\
			   $(TEST_RUNNER_DIR)


# mysql_seed (entry point)
# ──────────────────────────────────────────────────────────────────────────────
PROJECT_SRC 		:= $(call SOURCE_PATH,$(EMPTY))
PROJECT_HDR		:= $(call HEADER_PATH,$(EMPTY))
PROJECT_OBJ 		:= $(call OBJECT_PATH,$(EMPTY))
PROJECT_BIN 		:= $(call BINARY_PATH,$(EMPTY))
# ─────────────── target prequisites ───────────────────────────────────────────
PROJECT_BIN_PREQS	:= $(PROJECT_OBJ) 				\
			   $(CREATE_OBJ) 				\
			   $(RUN_OBJ) 					\
			   $(EXIT_OBJ) 					\
			   $(COUNT_STRING_OBJ) 				\
			   $(LOG_OBJ) 					\
			   $(PARALLEL_OBJ)				\
			   $(UTILS_OBJ)
PROJECT_OBJ_PREQS	:= $(PROJECT_SRC) 				\
			   $(PROJECT_HDR) 				\
			   $(CREATE_HDR) 				\
			   $(RUN_HDR) 					\
			   $(EXIT_HDR)
# ─────────────── targets ──────────────────────────────────────────────────────
TARGETS			+= $(PROJECT_OBJ)				\
			   $(PROJECT_BIN)


# mysql_seed_mode
# ──────────────────────────────────────────────────────────────────────────────
MODE_HDR		:= $(call HEADER_PATH,mode)


# mysql_seed_create
# ──────────────────────────────────────────────────────────────────────────────
CREATE_SRC 		:= $(call SOURCE_PATH,create)
CREATE_HDR		:= $(call HEADER_PATH,create)
CREATE_OBJ 		:= $(call OBJECT_PATH,create)
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
			   $(TEST_RUNNER_DIR)
CREATE_TEST_OBJ_PREQS	:= $(CREATE_TEST_SRC)				\
			   $(CREATE_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
CREATE_TRNR_OBJ_PREQS	:= $(CREATE_TRNR_SRC)				\
			   $(CREATE_TEST_OBJ_PREQS)
CREATE_TEST_BIN_PREQS	:= $(CREATE_TRNR_OBJ)				\
			   $(CREATE_TEST_OBJ)				\
			   $(CREATE_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(CREATE_TEST_BIN)
TARGETS			+= $(CREATE_OBJ)				\
			   $(CREATE_TRNR_SRC)				\
			   $(CREATE_TRNR_OBJ)				\
			   $(CREATE_TEST_OBJ)				\
			   $(CREATE_TEST_BIN)


# mysql_seed_run
# ──────────────────────────────────────────────────────────────────────────────
RUN_SRC 		:= $(call SOURCE_PATH,run)
RUN_HDR			:= $(call HEADER_PATH,run)
RUN_OBJ 		:= $(call OBJECT_PATH,run)
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
RUN_TRNR_SRC_PREQS	:= $(RUN_TEST_SRC)
			   $(TEST_RUNNER_DIR)
RUN_TEST_OBJ_PREQS	:= $(RUN_TEST_SRC)				\
			   $(RUN_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
RUN_TRNR_OBJ_PREQS	:= $(RUN_TRNR_SRC)				\
			   $(RUN_TEST_OBJ_PREQS)
RUN_TEST_BIN_PREQS	:= $(RUN_TRNR_OBJ)				\
			   $(RUN_TEST_OBJ)				\
			   $(RUN_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(RUN_TEST_BIN)
TARGETS			+= $(RUN_OBJ)					\
			   $(RUN_TRNR_SRC)				\
			   $(RUN_TRNR_OBJ)				\
			   $(RUN_TEST_OBJ)				\
			   $(RUN_TEST_BIN)


# mysql_seed_exit
# ──────────────────────────────────────────────────────────────────────────────
EXIT_SRC 		:= $(call SOURCE_PATH,exit)
EXIT_HDR		:= $(call HEADER_PATH,exit)
EXIT_OBJ 		:= $(call OBJECT_PATH,exit)
EXIT_TEST_SRC		:= $(call TEST_SOURCE_PATH,exit)
EXIT_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,exit)
EXIT_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,exit)
EXIT_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,exit)
EXIT_TEST_OBJ		:= $(call TEST_OBJECT_PATH,exit)
EXIT_TEST_BIN		:= $(call TEST_BINARY_PATH,exit)
# ─────────────── target prequisites ───────────────────────────────────────────
EXIT_OBJ_PREQS		:= $(EXIT_SRC) 					\
			   $(EXIT_HDR) 					\
			   $(MODE_HDR)
EXIT_TRNR_SRC_PREQS	:= $(EXIT_TEST_SRC)
			   $(TEST_RUNNER_DIR)
EXIT_TEST_OBJ_PREQS	:= $(EXIT_TEST_SRC)				\
			   $(EXIT_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
EXIT_TRNR_OBJ_PREQS	:= $(EXIT_TRNR_SRC)				\
			   $(EXIT_TEST_OBJ_PREQS)
EXIT_TEST_BIN_PREQS	:= $(EXIT_TRNR_OBJ)				\
			   $(EXIT_TEST_OBJ)				\
			   $(EXIT_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(EXIT_TEST_BIN)
TARGETS			+= $(EXIT_OBJ)					\
			   $(EXIT_TRNR_SRC)				\
			   $(EXIT_TRNR_OBJ)				\
			   $(EXIT_TEST_OBJ)				\
			   $(EXIT_TEST_BIN)


# mysql_seed_count_string
# ──────────────────────────────────────────────────────────────────────────────
COUNT_STRING_SRC 	:= $(call SOURCE_PATH,count_string)
COUNT_STRING_HDR	:= $(call HEADER_PATH,count_string)
COUNT_STRING_OBJ 	:= $(call OBJECT_PATH,count_string)
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
COUNT_STRING_TRNR_SRC_PREQS	:= $(COUNT_STRING_TEST_SRC)
			   	   $(TEST_RUNNER_DIR)
COUNT_STRING_TEST_OBJ_PREQS	:= $(COUNT_STRING_TEST_SRC)		\
			   	   $(COUNT_STRING_OBJ_PREQS) 		\
			   	   $(UNITY_OBJ_PREQS)
COUNT_STRING_TRNR_OBJ_PREQS	:= $(COUNT_STRING_TRNR_SRC)		\
			   	   $(COUNT_STRING_TEST_OBJ_PREQS)
COUNT_STRING_TEST_BIN_PREQS	:= $(COUNT_STRING_TRNR_OBJ)		\
			   	   $(COUNT_STRING_TEST_OBJ)		\
			   	   $(COUNT_STRING_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(COUNT_STRING_TEST_BIN)
TARGETS			+= $(COUNT_STRING_OBJ)				\
			   $(COUNT_STRING_TRNR_SRC)			\
			   $(COUNT_STRING_TRNR_OBJ)			\
			   $(COUNT_STRING_TEST_OBJ)			\
			   $(COUNT_STRING_TEST_BIN)


# mysql_seed_log
# ──────────────────────────────────────────────────────────────────────────────
LOG_SRC 		:= $(call SOURCE_PATH,log)
LOG_HDR			:= $(call HEADER_PATH,log)
LOG_OBJ 		:= $(call OBJECT_PATH,log)
LOG_TEST_SRC		:= $(call TEST_SOURCE_PATH,log)
LOG_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,log)
LOG_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,log)
LOG_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,log)
LOG_TEST_OBJ		:= $(call TEST_OBJECT_PATH,log)
LOG_TEST_BIN		:= $(call TEST_BINARY_PATH,log)
# ─────────────── target prequisites ───────────────────────────────────────────
LOG_OBJ_PREQS		:= $(LOG_SRC) 					\
			   $(LOG_HDR) 					\
			   $(UTILS_HDR)					\
			   $(PARALLEL_HDR)
LOG_TRNR_SRC_PREQS	:= $(LOG_TEST_SRC)
			   $(TEST_RUNNER_DIR)
LOG_TEST_OBJ_PREQS	:= $(LOG_TEST_SRC)				\
			   $(LOG_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
LOG_TRNR_OBJ_PREQS	:= $(LOG_TRNR_SRC)				\
			   $(LOG_TEST_OBJ_PREQS)
LOG_TEST_BIN_PREQS	:= $(LOG_TRNR_OBJ)				\
			   $(LOG_TEST_OBJ)				\
			   $(LOG_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(LOG_TEST_BIN)
TARGETS			+= $(LOG_OBJ)					\
			   $(LOG_TRNR_SRC)				\
			   $(LOG_TRNR_OBJ)				\
			   $(LOG_TEST_OBJ)				\
			   $(LOG_TEST_BIN)


# mysql_seed_parallel
# ──────────────────────────────────────────────────────────────────────────────
PARALLEL_SRC 		:= $(call SOURCE_PATH,parallel)
PARALLEL_HDR		:= $(call HEADER_PATH,parallel)
PARALLEL_OBJ 		:= $(call OBJECT_PATH,parallel)
PARALLEL_TEST_SRC	:= $(call TEST_SOURCE_PATH,parallel)
PARALLEL_TRNR_SRC	:= $(call TEST_RUNNER_SOURCE_PATH,parallel)
PARALLEL_TEST_OBJ	:= $(call TEST_RUNNER_OBJECT_PATH,parallel)
PARALLEL_TRNR_OBJ	:= $(call TEST_RUNNER_OBJECT_PATH,parallel)
PARALLEL_TEST_OBJ	:= $(call TEST_OBJECT_PATH,parallel)
PARALLEL_TEST_BIN	:= $(call TEST_BINARY_PATH,parallel)
# ─────────────── target prequisites ───────────────────────────────────────────
PARALLEL_OBJ_PREQS	:= $(PARALLEL_SRC) 				\
			   $(PARALLEL_HDR)
PARALLEL_TRNR_SRC_PREQS	:= $(PARALLEL_TEST_SRC)
			   $(TEST_RUNNER_DIR)
PARALLEL_TEST_OBJ_PREQS	:= $(PARALLEL_TEST_SRC)				\
			   $(PARALLEL_OBJ_PREQS) 			\
			   $(UNITY_OBJ_PREQS)
PARALLEL_TRNR_OBJ_PREQS	:= $(PARALLEL_TRNR_SRC)				\
			   $(PARALLEL_TEST_OBJ_PREQS)
PARALLEL_TEST_BIN_PREQS	:= $(PARALLEL_TRNR_OBJ)				\
			   $(PARALLEL_TEST_OBJ)				\
			   $(PARALLEL_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(PARALLEL_TEST_BIN)
TARGETS			+= $(PARALLEL_OBJ)				\
			   $(PARALLEL_TRNR_SRC)				\
			   $(PARALLEL_TRNR_OBJ)				\
			   $(PARALLEL_TEST_OBJ)				\
			   $(PARALLEL_TEST_BIN)


# mysql_seed_utils
# ──────────────────────────────────────────────────────────────────────────────
UTILS_SRC 		:= $(call SOURCE_PATH,utils)
UTILS_HDR		:= $(call HEADER_PATH,utils)
UTILS_OBJ 		:= $(call OBJECT_PATH,utils)
UTILS_TEST_SRC		:= $(call TEST_SOURCE_PATH,utils)
UTILS_TRNR_SRC		:= $(call TEST_RUNNER_SOURCE_PATH,utils)
UTILS_TEST_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,utils)
UTILS_TRNR_OBJ		:= $(call TEST_RUNNER_OBJECT_PATH,utils)
UTILS_TEST_OBJ		:= $(call TEST_OBJECT_PATH,utils)
UTILS_TEST_BIN		:= $(call TEST_BINARY_PATH,utils)
# ─────────────── target prequisites ───────────────────────────────────────────
UTILS_OBJ_PREQS		:= $(UTILS_SRC) 				\
			   $(UTILS_HDR)
UTILS_TRNR_SRC_PREQS	:= $(UTILS_TEST_SRC)
			   $(TEST_RUNNER_DIR)
UTILS_TEST_OBJ_PREQS	:= $(UTILS_TEST_SRC)				\
			   $(UTILS_OBJ_PREQS) 				\
			   $(UNITY_OBJ_PREQS)
UTILS_TRNR_OBJ_PREQS	:= $(UTILS_TRNR_SRC)				\
			   $(UTILS_TEST_OBJ_PREQS)
UTILS_TEST_BIN_PREQS	:= $(UTILS_TRNR_OBJ)				\
			   $(UTILS_TEST_OBJ)				\
			   $(UTILS_OBJ)
# ─────────────── targets ──────────────────────────────────────────────────────
TEST_BINARIES		+= $(UTILS_TEST_BIN)
TARGETS			+= $(UTILS_OBJ)					\
			   $(UTILS_TRNR_SRC)				\
			   $(UTILS_TRNR_OBJ)				\
			   $(UTILS_TEST_OBJ)				\
			   $(UTILS_TEST_BIN)



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



## MAKE UNIT TESTS
# ══════════════════════════════════════════════════════════════════════════════
# make test_runners directory
# ──────────────────────────────────────────────────────────────────────────────
$(TEST_RUNNER_DIR):
	$(MKDIR) $(MKDIR_FLAGS) $@

# for mysql_seed_create
# make:
# 	mysql_seed_create_test		binary,
# 	mysql_seed_create_test_runner 	object,
# 	mysql_seed_create_test		object, and
# 	mysql_seed_create_test_runner	source
# ──────────────────────────────────────────────────────────────────────────────
$(CREATE_TEST_BIN): $(CREATE_TEST_BIN_PREQS)
	$(LD) $(LD_FLAGS) $^ $(LD_LIB_FLAGS) -o $@

$(CREATE_TRNR_OBJ): $(CREATE_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(CREATE_TEST_OBJ): $(CREATE_TEST_TEST_PREQS)
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

$(RUN_TRNR_OBJ): $(RUN_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(RUN_TEST_OBJ): $(RUN_TEST_TEST_PREQS)
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

$(EXIT_TRNR_OBJ): $(EXIT_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(EXIT_TEST_OBJ): $(EXIT_TEST_TEST_PREQS)
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

$(COUNT_STRING_TRNR_OBJ): $(COUNT_STRING_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(COUNT_STRING_TEST_OBJ): $(COUNT_STRING_TEST_TEST_PREQS)
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

$(LOG_TRNR_OBJ): $(LOG_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(LOG_TEST_OBJ): $(LOG_TEST_TEST_PREQS)
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

$(PARALLEL_TRNR_OBJ): $(PARALLEL_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(PARALLEL_TEST_OBJ): $(PARALLEL_TEST_TEST_PREQS)
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

$(UTILS_TRNR_OBJ): $(UTILS_TEST_TRNR_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_TEST_OBJ): $(UTILS_TEST_TEST_PREQS)
	$(CC) $(UNITY_CC_FLAGS) -c $< -o $@

$(UTILS_TRNR_SRC): $(UTILS_TRNR_SRC_PREQS)
	$(RUBY) $(RUBY_FLAGS) $(UNITY_GEN_TRNR_SCRIPT) $< $@
