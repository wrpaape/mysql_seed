.PHONY: all clean


CC	 := gcc
CC_FLAGS := -I. -g -O2 -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__


all: ../bin/mysql_seed


../bin/mysql_seed: ../obj/mysql_seed.o 		\
		   ../obj/mysql_seed_create.o 	\
		   ../obj/mysql_seed_run.o	\
	           ../obj/mysql_seed_exit.o
	$(CC) $(CC_FLAGS) $^ -o $@


../obj/mysql_seed.o: mysql_seed.c		\
		     mysql_seed.h		\
		     mysql_seed_create.h	\
		     mysql_seed_run.h		\
		     mysql_seed_exit.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_create.o: mysql_seed_create.c	\
			    mysql_seed_create.h	\
			    mysql_seed_mode.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_run.o: mysql_seed_run.c	\
			 mysql_seed_run.h	\
			 mysql_seed_mode.h
	$(CC) $(CC_FLAGS) -c $< -o $@


../obj/mysql_seed_exit.o: mysql_seed_exit.c	\
			  mysql_seed_exit.h	\
			  mysql_seed_mode.h
	$(CC) $(CC_FLAGS) -c $< -o $@


clean:
	$(RM) ../bin/mysql_seed			\
	      ../obj/mysql_seed_create.o	\
	      ../obj/mysql_seed_run.o		\
	      ../obj/mysql_seed_exit.o
