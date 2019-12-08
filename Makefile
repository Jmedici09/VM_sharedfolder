#Makefile for bare metal ARM development on Freedom FRDM-KL25Z
#Douglas Summerville, Binghamton University, 2018
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
OBJSIZE = arm-none-eabi-size
INCLUDES = -Idrivers -Ibaremetal
VPATH = src:drivers:baremetal
SYS_CLOCK = 48000000L

LINKSCRIPT=baremetal/mkl25z4.ld 

DEBUG_OPTS = -g3 -gdwarf-2 -gstrict-dwarf
#OPTS = -O2 "-DSYS_CLOCK=$(SYS_CLOCK)" -DRESET_PIN_DISABLED
OPTS = -O2 "-DSYS_CLOCK=$(SYS_CLOCK)" -DRESET_PIN_DISABLED -DWATCHDOG_DISABLE
TARGET = cortex-m0
CFLAGS = -ffreestanding -nodefaultlibs -nostartfiles \
	 -ffunction-sections -fdata-sections -Wall \
	 -fmessage-length=0 -mcpu=$(TARGET) -mthumb -mfloat-abi=soft \
	 $(DEBUG_OPTS) $(OPTS) $(INCLUDES)

.PHONY:	clean usage

# -----------------------------------------------------------------------------

usage: 
	@echo LIBS=\"list of drivers\" make file.srec

clean:
	-rm -f *.o *.out *.srec *.dump

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.dump: %.out
	$(OBJDUMP) --disassemble $< >$@

%.srec: %.out
	$(OBJCOPY) -O srec $< $@

%.out: %.o $(LIBS) _startup.o
	$(CC) $(CFLAGS) -T $(LINKSCRIPT) -o $@ $^
	@echo Generated Program has the following segment sizes:
	@$(OBJSIZE) $@

