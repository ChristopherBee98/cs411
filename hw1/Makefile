CROSS_CC ?= aarch64-linux-gnu-gcc
CFLAGS ?= --std=c99 -Wall -O0 -g
LDFLAGS ?=
CROSS_AS ?= aarch64-linux-gnu-as
ASFLAGS ?= -g
bin_PROGRAMS = hw1
OBJS = hw1.o calc_grade.o

$(bin_PROGRAMS): $(OBJS)
	$(CROSS_CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CROSS_CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CROSS_AS) $(ASFLAGS) -o $@ $<

indent:
	indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0 hw1.c

clean:
	-rm -f $(bin_PROGRAMS) $(OBJS)

.PHONY: indent clean
