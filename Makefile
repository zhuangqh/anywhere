SRCS = ./anywhere.c
SRCS += ./readline.c
SRCS += ./wrapsock.c
SRCS += ./wrapunix.c

all: anywhere
anywhere: $(SRCS)
	gcc -Wall  $(SRCS) -o anywhere
clean:
	rm anywhere
