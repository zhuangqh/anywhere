#include "../common.h"
#include "./lock.h"

pid_t
child_make(int i, int listenfd, void (*handler)(int))
{
  pid_t	pid;
  void	child_main(int, int, void(*)(int));

  if ( (pid = Fork()) > 0)
    return(pid);		/* parent */

  child_main(i, listenfd, handler);	/* never returns */
  return 0; // cheating compiler
}

void
child_main(int i, int listenfd, void (*handler)(int))
{
  int				connfd;
  socklen_t		clilen;
  struct sockaddr	*cliaddr;

  cliaddr = Malloc(sizeof(struct sockaddr));

  for ( ; ; ) {
    lock_wait();
    connfd = Accept(listenfd, cliaddr, &clilen);
    lock_release();

    handler(connfd);		/* process the request */
    Close(connfd);
  }
}
