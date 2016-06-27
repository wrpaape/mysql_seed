.PHONY: all run_tests clean

SRC_DIR = src
MFLAGS  = -j5 LAST=550

all run_tests clean:
	$(MAKE) $(MFLAGS) -C $(SRC_DIR) $@
