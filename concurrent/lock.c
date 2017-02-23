#include "lock.h"

static pthread_mutex_t	*mptr;	/* actual mutex will be in shared memory */

void
lock_init(char *pathname)
{
	int		fd;
	pthread_mutexattr_t	mattr;

	// open for share memory
	fd = Open("/tmp/anywhere", O_RDWR | O_CREAT, FILE_MODE);

	off_t length = sizeof(pthread_mutex_t);

	Ftruncate(fd, length); // set size

	mptr = Mmap(NULL, length, PROT_READ | PROT_WRITE,
				MAP_SHARED, fd, 0);
	Close(fd);

	Pthread_mutexattr_init(&mattr);
	Pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
	Pthread_mutex_init(mptr, &mattr);
}

void
lock_wait()
{
	Pthread_mutex_lock(mptr);
}

void
lock_release()
{
	Pthread_mutex_unlock(mptr);
}
