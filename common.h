#ifndef	__unp_h
#define	__unp_h

#include <stdio.h>
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <sys/select.h>
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

/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

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
void	 Close(int);
pid_t	 Fork(void);
ssize_t  Readline(int, void *, size_t, int);
void   Send(int, const void *, size_t, int);
void   Write(int, void *, size_t);
void   err_sys(const char*);

#endif
