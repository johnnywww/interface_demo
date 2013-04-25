# Make file
ifndef ARCH
ARCH=x86
endif
 
GV_CC_PATH=/gvos/$(ARCH)/crosstool/bin/

## platform:telechips
ifeq ($(ARCH),telechips)
CROSS_COMPILE = $(GV_CC_PATH)arm-none-linux-gnueabi-
CFLAGS= -I/gvos/$(ARCH)/include -I/gvos/$(ARCH)/include/gvos
LDLIBS = -L/gvos/$(ARCH)/lib -lgipcclient -lxml2
endif
## platform:x86
ifeq ($(ARCH),x86)
CROSS_COMPILE = 

endif


#CFLAGS += -Wall

AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
CC      = $(CROSS_COMPILE)gcc
CPP     = $(CROSS_COMPILE)g++
RANLIB  = $(CROSS_COMPILE)ranlib
AR      = $(CROSS_COMPILE)ar
NM      = $(CROSS_COMPILE)nm
STRIP   = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

BINNAME=interface_demo


# Common rules that everyone uses 

%.o: %.c
	@ echo "Compiling $<..."
	@ $(CC) $(CFLAGS) -o $@ -c $<

%.d: %.c
	@ $(CC) -M $(CFLAGS) $< > $@
	@ $(CC) -M $(CFLAGS) $< | sed s/\\.o/.d/ >> $@

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))

all: $(OBJS)  $(BINNAME)

clean:
	@ rm -f $(OBJS) $(BINNAME) *~ core *.a


$(BINNAME):$(OBJS)
	@ echo "Building $(BINNAME)..."
	@ $(CC) -o $(BINNAME) $(OBJS) $(LDLIBS)
	@ rm *.o

