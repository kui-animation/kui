# Specify the assembler and its flags
ASM = nasm
AMFLAGS = -f elf64
LD = ld
LDFLAGS =
SRCDIRS = src

SRCS := $(wildcard $(addsuffix /*.asm, $(SRCDIRS)))
OBJS = $(SRCS:.asm=.o)
TARGET = kui

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.asm
	$(ASM) $(AMFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
