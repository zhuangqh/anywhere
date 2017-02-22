#ifndef __THREAD_H_
#define __THREAD_H_

#include "../common.h"

typedef void(*Handler)(int);

typedef struct {
  Handler handler;
  int index; // index of pthread array
  int count;
} ReqHandler;

pthread_t	*tptr;		/* array of Thread structures; calloc'ed */

int				listenfd, nthreads;
socklen_t		addrlen;
pthread_mutex_t	mlock;

void  Pthread_create(pthread_t *, const pthread_attr_t *,
             void * (*)(void *), void *);
void  Pthread_mutex_lock(pthread_mutex_t *);
void  Pthread_mutex_unlock(pthread_mutex_t *mptr);
void  thread_make(ReqHandler rh);

#endif
