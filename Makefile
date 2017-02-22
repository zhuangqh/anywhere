LIB = ./readline.c
LIB += ./wrapsock.c
LIB += ./wrapunix.c
LIB += ./extension.c
LIB += ./wrapthread.c

GREEN=\033[0;32m
NC=\033[0m # No Color

AWc = ./concurrent/anywhere.c
AWi = ./iterative/anywhere.c
AWt = ./multithread/anywhere.c

AWBinc = anywhere-concurrent
AWBini = anywhere-iterative
AWBint = anywhere-multithread

all: install

install: anywhere
	@cp anywhere /usr/local/bin/anywhere
	@mkdir -p ~/.anywhere
	@cp ./content-type-table ~/.anywhere/
	@echo "$(GREEN)successfully install 'anywhere'$(NC)"

anywhere:	iterative

concurrent: $(LIB) $(AWc)
	gcc -Wall  $(LIB)  $(AWc) -o $(AWBinc)

iterative: $(LIB) $(AWi)
	gcc -Wall  $(LIB) $(AWi) -o $(AWBini)

multithread: $(LIB) $(AWt) ./multithread/thread.c
	gcc -Wall  $(LIB) $(AWt) ./multithread/thread.c -o $(AWBint)

uninstall:
	@rm -f /usr/local/bin/anywhere
	@rm -rf ~/.anywhere
	@rm -f $(AWBinc) $(AWBint) $(AWBini)
	@echo "$(GREEN)successfully uninstall 'anywhere'$(NC)"

clean:
	rm -f $(AWBinc) $(AWBint) $(AWBini)
