# print the value of PROGS
ifneq ($(KERNELRELEASE),)
obj-m := $(PROGS)
else
KDIR := /home/abd002/ODC-Embedded-linux/linux
# Source files
SRCS := $(wildcard *.c)
# Module object files
PROGS := $(SRCS:.c=.o)
all:
	$(MAKE) -C $(KDIR) M=$$PWD PROGS="$(PROGS)"
	./install.sh
endif

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

# Target to print the values of SRCS and PROGS
print-vars:
	@echo "SRCS = $(SRCS)"
	@echo "PROGS = $(PROGS)"

