obj-m += list_tasks.o

# kernel build tree path
KDIR := /lib/modules/$(shell uname -r)/build

PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M="$(PWD)" modules

clean:
	$(MAKE) -C $(KDIR) M="$(PWD)" clean
