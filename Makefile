.PHONY: all clean

SRC_DIR = src
MFLAGS  = -j5 LAST=550

all clean:
		$(MAKE) $(MFLAGS) -C $(SRC_DIR) $@
