LIB = ./readline.c
LIB += ./wrapsock.c
LIB += ./wrapunix.c
LIB += ./extension.c

GREEN=\033[0;32m
NC=\033[0m # No Color

AWc = ./concurrent/anywhere.c
AWi = ./iterative/anywhere.c

all: install
install: anywhere
	@cp anywhere /usr/local/bin/anywhere
	@mkdir -p ~/.anywhere
	@cp ./content-type-table ~/.anywhere/
	@echo "$(GREEN)successfully install 'anywhere'$(NC)"

anywhere:	iterative

concurrent: $(LIB) $(AWc)
	gcc -Wall  $(LIB)  $(AWc) -o anywhere-concurrent

iterative: $(LIB) $(AWi)
	gcc -Wall  $(LIB) $(AWi) -o anywhere-iterative

uninstall:
	@rm /usr/local/bin/anywhere
	@rm -rf ~/.anywhere
	@echo "$(GREEN)successfully uninstall 'anywhere'$(NC)"
