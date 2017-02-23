#ifndef	__unp_h
#define	__unp_h

#include <stdio.h>
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <netinet/in.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

#define PATHLEN   256

/* prototypes for our socket wrapper functions */
int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
void	 Listen(int, int);
int		 Socket(int, int, int);

/* prototypes for our unix wrapper functions */
void * Calloc(size_t, size_t);
void   Close(int);
pid_t  Fork(void);
void   Ftruncate(int, off_t);
void * Malloc(size_t);
ssize_t  Readline(int, void *, size_t, int);
void   Send(int, const void *, size_t, int);
int    Shm_open(const char *, int, mode_t);
void   Write(int, void *, size_t);
void   err_sys(const char*);

/* prototypes for our pthread wrapper functions */
void  Pthread_mutexattr_init(pthread_mutexattr_t *);
void  Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void  Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void  Pthread_mutex_lock(pthread_mutex_t *);
void  Pthread_mutex_unlock(pthread_mutex_t *);

#endif
