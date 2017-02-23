#ifndef __PROCESS_POOL_H
#define __PROCESS_POOL_H

#include "../common.h"
#include "./lock.h"

pid_t child_make(int i, int listenfd, void (*handler)(int));
void  child_main(int i, int listenfd, void (*handler)(int));

#endif
