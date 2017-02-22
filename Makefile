LIB = ./readline.c
LIB += ./wrapsock.c
LIB += ./wrapunix.c
LIB += ./extension.c
LIB += ./wrapthread.c

LIBOBJS=$(LIB:.c=.o)

GREEN=\033[0;32m
NC=\033[0m # No Color

AWc = ./concurrent/anywhere.c
AWi = ./iterative/anywhere.c
AWt = ./multithread/anywhere.c

AWBinc = anywhere-concurrent
AWBini = anywhere-iterative
AWBint = anywhere-multithread

all: $(AWBinc) $(AWBini) $(AWBint)

install: anywhere-multithread
	@cp anywhere-multithread /usr/local/bin/anywhere
	@mkdir -p ~/.anywhere
	@cp ./content-type-table ~/.anywhere/
	@echo "$(GREEN)successfully install 'anywhere'$(NC)"

anywhere-concurrent: $(LIBOBJS)
	gcc -Wall  $(LIBOBJS)  $(AWc) -o $(AWBinc)

anywhere-iterative: $(LIBOBJS)
	gcc -Wall  $(LIBOBJS) $(AWi) -o $(AWBini)

anywhere-multithread: $(LIBOBJS) thread.o
	gcc -Wall  $(LIBOBJS) thread.o $(AWt) -o $(AWBint)

extension.o: extension.c

readline.o: readline.c

wrapunix.o: wrapunix.c

wrapsock.o: wrapsock.c

wrapthread.o: wrapthread.c

thread.o:
	gcc -c ./multithread/thread.c

uninstall: clean
	@rm -f /usr/local/bin/anywhere
	@rm -rf ~/.anywhere
	@echo "$(GREEN)successfully uninstall 'anywhere'$(NC)"

clean:
	rm -f $(AWBinc) $(AWBint) $(AWBini) $(LIBOBJS) thread.o
