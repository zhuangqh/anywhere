SRCS = ./readline.c
SRCS += ./wrapsock.c
SRCS += ./wrapunix.c
SRCS += ./extension.c
SRCS += ./wrapthread.c

FLAGS = -Wall -std=c11

SRCSOBJS=$(SRCS:.c=.o)

LIB = -lpthread

GREEN=\033[0;32m
NC=\033[0m # No Color

AWc = ./concurrent/anywhere.c
AWi = ./iterative/anywhere.c
AWt = ./multithread/anywhere.c

AWBinc = anywhere-concurrent
AWBini = anywhere-iterative
AWBint = anywhere-multithread

all: $(AWBinc) $(AWBini) $(AWBint)

install: anywhere-concurrent
	@cp anywhere-concurrent /usr/local/bin/anywhere
	@mkdir -p ~/.anywhere
	@cp ./content-type-table ~/.anywhere/
	@echo "$(GREEN)successfully install 'anywhere'$(NC)"

$(AWBinc): $(SRCSOBJS) lock.o processpool.o ./concurrent/anywhere.c
	gcc $(FLAGS)  $(SRCSOBJS) lock.o processpool.o $(AWc) -o $(AWBinc) $(LIB)

$(AWBini): $(SRCSOBJS) ./iterative/anywhere.c
	gcc $(FLAGS)  $(SRCSOBJS) $(AWi) -o $(AWBini) $(LIB)

$(AWBint): $(SRCSOBJS) thread.o ./multithread/anywhere.c
	gcc $(FLAGS)  $(SRCSOBJS) thread.o $(AWt) -o $(AWBint) $(LIB)

extension.o: extension.c
	gcc -c $(FLAGS) extension.c
readline.o: readline.c

wrapunix.o: wrapunix.c

wrapsock.o: wrapsock.c

wrapthread.o: wrapthread.c

thread.o: ./multithread/thread.c
	gcc -c $(FLAGS) ./multithread/thread.c

lock.o: ./concurrent/lock.c
	gcc -c ./concurrent/lock.c

processpool.o: ./concurrent/processpool.c
	gcc -c ./concurrent/processpool.c

uninstall: clean
	@rm -f /usr/local/bin/anywhere
	@rm -rf ~/.anywhere
	@echo "$(GREEN)successfully uninstall 'anywhere'$(NC)"

clean:
	rm -f $(AWBinc) $(AWBint) $(AWBini) $(SRCSOBJS) thread.o lock.o processpool.o
