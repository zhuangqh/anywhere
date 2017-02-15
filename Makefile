SRCS = ./anywhere.c
SRCS += ./readline.c
SRCS += ./wrapsock.c
SRCS += ./wrapunix.c
SRCS += ./extension.c

GREEN=\033[0;32m
NC=\033[0m # No Color

all: install
install: anywhere
	@cp anywhere /usr/local/bin/anywhere
	@mkdir -p ~/.anywhere
	@cp ./content-type-table ~/.anywhere/
	@echo "$(GREEN)successfully install 'anywhere'$(NC)"
anywhere: $(SRCS)
	gcc -Wall  $(SRCS) -o anywhere
uninstall:
	@rm /usr/local/bin/anywhere
	@rm -rf ~/.anywhere
	@echo "$(GREEN)successfully uninstall 'anywhere'$(NC)"
