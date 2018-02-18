
CC = gcc
AR = ar
RM = rm -f


INCLUDES = -I./ -Iinclude
#LIBINCLUDES = -L.
CFLAGS += -O2 -Werror -Wall $(INCLUDES)
LINKFLAGS =

C_SOURCES = $(wildcard *.c)
C_OBJS = $(patsubst %.c, %.c, $(C_SOURCES))
TARGETS = $(patsubst %.c, %, $(C_SOURCES))

LIBS = 


all:$(TARGETS)


%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

.c.o:
	$(CC) -o $* $(CFLAGS) $(INCLUDES) $*.c

clean:
	-$(RM) *.o $(TARGETS)

