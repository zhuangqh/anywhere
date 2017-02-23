#ifndef __LOCK_H_
#define __LOCK_H_
#include "../common.h"

void  Pthread_mutexattr_init(pthread_mutexattr_t *);
void  Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void  Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void  Pthread_mutex_lock(pthread_mutex_t *);
void  Pthread_mutex_unlock(pthread_mutex_t *);
void *Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
int   Open(const char *pathname, int oflag, mode_t mode);

void  lock_init(char *);
void  lock_wait();
void  lock_release();

#endif
