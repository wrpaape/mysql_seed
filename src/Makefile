.PHONY: all clean

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



# UTILITY CONFIG
# ══════════════════════════════════════════════════════════════════════════════
# C Compiler
# ──────────────────────────────────────────────────────────────────────────────
CC		:= gcc
CC_ENV_FLAGS	:= -D__USE_FIXED_PROTOTYPES__ $(SYS_ENV_FLAGS)
CC_FLAGS	:= -g -O2 -std=c99 -Wall $(CC_ENV_FLAGS)
# Linker
# ──────────────────────────────────────────────────────────────────────────────
LD		:= ld
LD_FLAGS	:= -no_pie
LD_LIB_FLAGS	:= -lpthread -lc
# Make Directory
# ──────────────────────────────────────────────────────────────────────────────
MKDIR	    	:= mkdir
MKDIR_FLAGS 	:= -p
# Copy File
# ──────────────────────────────────────────────────────────────────────────────
CP		:= cp
CP_FLAGS	:= $(EMPTY)
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



# DIRECTORY CONFIGURATION
# ══════════════════════════════════════════════════════════════════════════════
# Path delimiter
# ──────────────────────────────────────────────────────────────────────────────
ifdef $(SYSTEM_WINDOWS)
PATH_DELIM	:= \\
else
PATH_DELIM	:= /
endif 

PATH_JOIN	 	 = $(subst $(SPACE),$(PATH_DELIM),$(strip $1))

PROJECT 		:= mysql_seed
PROJECT_ROOT		:= ..
SOURCE_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) src)
HEADER_DIR		:= $(SOURCE_DIR)
OBJECT_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) obj)
BINARY_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) bin)
TEST_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) test)
TEST_RUNNER_DIR		:= $(call PATH_JOIN,$(TEST_DIR) test_runners)
UNITY_DIR		:= $(call PATH_JOIN,$(PROJECT_ROOT) unity)
UNITY_SOURCE_DIR	:= $(call PATH_JOIN,$(UNITY_DIR) src)
UNITY_HEADER_DIR	:= $(UNITY_SOURCE_DIR)
UNITY_AUTO_DIR  	:= $(call PATH_JOIN,$(UNITY_DIR) auto)




# PATH CONFIGURATION
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


# MISC
# ══════════════════════════════════════════════════════════════════════════════
EMPTY	:=
SPACE	:= $(EMPTY) $(EMPTY)
TAB	:= $(EMPTY)	$(EMPTY)
define NEWLINE :=


endef

TRIM = $(subst $(SPACE),$(EMPTY),$1)
SOURCE_HEADER_PATHS = $(call SOURCE_PATH,$1) $(call HEADER_PATH,$1)

define GENERATE_TEST_RUNNER
$(NEWLINE)
$(strip $1: $2)
	$(strip $(RUBY) $(RUBY_FLAGS) $(UNITY_SCRIPTS)/generate_test_runner.rb $$< $$@)

TARGETS += $1
$(NEWLINE)
endef



## PROJECT COMPONENTS
# ══════════════════════════════════════════════════════════════════════════════
# mysql_seed (entry point)
# ──────────────────────────────────────────────────────────────────────────────
PROJECT_SRC 		:= $(call SOURCE_PATH,$(EMPTY))
PROJECT_HDR		:= $(call HEADER_PATH,$(EMPTY))
PROJECT_OBJ 		:= $(call OBJECT_PATH,$(EMPTY))
PROJECT_BIN 		:= $(call BINARY_PATH,$(EMPTY))

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

TEST_BINARIES		+= $(CREATE_TEST_BIN)
TARGETS			+= $(CREATE_OBJ)				\
			   $(CREATE_BIN)				\
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

TEST_BINARIES		+= $(RUN_TEST_BIN)
TARGETS			+= $(RUN_OBJ)					\
			   $(RUN_BIN)					\
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

TEST_BINARIES		+= $(EXIT_TEST_BIN)
TARGETS			+= $(EXIT_OBJ)					\
			   $(EXIT_BIN)					\
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

TEST_BINARIES		+= $(COUNT_STRING_TEST_BIN)
TARGETS			+= $(COUNT_STRING_OBJ)				\
			   $(COUNT_STRING_BIN)				\
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

TEST_BINARIES		+= $(LOG_TEST_BIN)
TARGETS			+= $(LOG_OBJ)					\
			   $(LOG_BIN)					\
			   $(LOG_TRNR_SRC)				\
			   $(LOG_TRNR_OBJ)				\
			   $(LOG_TEST_OBJ)				\
			   $(LOG_TEST_BIN)
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

TEST_BINARIES		+= $(UTILS_TEST_BIN)
TARGETS			+= $(UTILS_OBJ)					\
			   $(UTILS_BIN)					\
			   $(UTILS_TRNR_SRC)				\
			   $(UTILS_TRNR_OBJ)				\
			   $(UTILS_TEST_OBJ)				\
			   $(UTILS_TEST_BIN)
# unity (test framework)
# ──────────────────────────────────────────────────────────────────────────────
UNITY_SRC 		:= $(call UNITY_SOURCE_PATH,unity)
UNITY_HDR 		:= $(call UNITY_HEADER_PATH,unity)
UNITY_CONFIG_HDR 	:= $(call UNITY_HEADER_PATH,unity_config)
UNITY_INTERNALS_HDR 	:= $(call UNITY_HEADER_PATH,unity_internals)
UNITY_OBJ 		:= $(call UNITY_OBJECT_PATH,unity)
UNITY_GEN_TRNR_SCRIPT	:= $(call UNITY_AUTO_PATH,generate_test_runner)
UNITY_CC_FLAGS 		:= -DUNITY_INCLUDE_CONFIG_H

TARGETS			+= $(UNITY_OBJ)					\
			   $(UNITY_BIN)					\
			   $(UNITY_TRNR_SRC)				\
			   $(UNITY_TRNR_OBJ)				\
			   $(UNITY_TEST_OBJ)				\
			   $(UNITY_TEST_BIN)

all: $(PROJECT_BINARY)


../bin/mysql_seed: ../obj/mysql_seed.o 				\
		   ../obj/mysql_seed_create.o 			\
		   ../obj/mysql_seed_run.o			\
	           ../obj/mysql_seed_exit.o			\
	           ../obj/mysql_seed_count_string.o		\
	           ../obj/mysql_seed_log.o			\
	           ../obj/mysql_seed_utils.o			\
	$(CC) $(CC_FLAGS) $^ -o $@


../obj/mysql_seed.o: mysql_seed.c				\
		     mysql_seed.h				\
		     mysql_seed_create.h			\
		     mysql_seed_run.h				\
		     mysql_seed_exit.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_create.o: mysql_seed_create.c			\
			    mysql_seed_create.h			\
			    mysql_seed_mode.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_run.o: mysql_seed_run.c			\
			 mysql_seed_run.h			\
			 mysql_seed_mode.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_exit.o: mysql_seed_exit.c			\
			  mysql_seed_exit.h			\
			  mysql_seed_mode.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_count_string.o: mysql_seed_count_string.c	\
				  mysql_seed_count_string.h	\
				  mysql_seed_exit.h		\
				  mysql_seed_utils.h
	$(CC) $(CC_FLAGS) -c $< -o $@

../obj/mysql_seed_log.o: mysql_seed_log.c			\
			 mysql_seed_log.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_utils.o: mysql_seed_utils.c			\
			   mysql_seed_utils.h
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	$(RM) ../bin/mysql_seed			\
	      ../obj/mysql_seed_create.o	\
	      ../obj/mysql_seed_run.o		\
	      ../obj/mysql_seed_exit.o		\
	      ../obj/mysql_seed_utils.o
