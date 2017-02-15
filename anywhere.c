#include "./common.h"
#include "./extension.h"

#define SERVER_STRING "Server: Anywhere\r\n"

char *base_path = ".";
struct MIMEItem *et[EXTLEN]; // extension table

void   accept_request(int);
void   not_found(int);
void   set_header(int, const char *);
void   send_file(int, FILE *);
void   serve_file(int, const char *);
void   unimplemented(int);

void
accept_request(int sockfd)
{
  char buf[MAXLINE];
  char method[255];
  char url[255];
  char path[MAXLINE];
  int char_cnt = 0;
  int i = 0, j = 0;

  char_cnt = Readline(sockfd, buf, MAXLINE);
  printf("%s", buf);

  while ((i < sizeof(method) - 1) && !isspace(buf[i])) {
    method[i] = buf[i];
    ++i;
  }
  method[i] = '\0';

  // if method != GET
  if (strcasecmp(method, "GET")) {
    unimplemented(sockfd);
    return;
  }

  // skip blank space
  while ((i < char_cnt) && isspace(buf[i])) ++i;

  // get url without querystring
  j = 0;
  while ((i < sizeof(url)) && (i < char_cnt) && !isspace(buf[i]) && (buf[i] != '?')) {
    url[j++] = buf[i++];
  }
  url[j] = '\0';

  sprintf(path, "%s%s", base_path, url);
  if (path[strlen(path) - 1] == '/') {
    strcat(path, "index.html");
  }

  serve_file(sockfd, path);
}

void
not_found(int sockfd)
{
  char buf[MAXLINE];

  sprintf(buf, "HTTP/1.1 404 NOT FOUND\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, SERVER_STRING);
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "Content-Type: text/plain\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "not found\r\n");
  Write(sockfd, buf, strlen(buf));
}

void
unimplemented(int sockfd)
{
  char buf[MAXLINE];

  sprintf(buf, "HTTP/1.1 501 Method Not Implemented\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, SERVER_STRING);
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "Content-Type: text/plain\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "method not implemented\r\n");
  Write(sockfd, buf, strlen(buf));
}

void
serve_file(int sockfd, const char *filepath)
{
  FILE *resource = fopen(filepath, "r");
  
  if (resource == NULL) {
    not_found(sockfd);
  } else {
    set_header(sockfd, filepath);
    send_file(sockfd, resource);
  }

  fclose(resource);
}

void
set_header(int sockfd, const char *filepath)
{
  char buf[1024];
  char content_type[1024];

  set_extension(et, filepath, content_type);

  sprintf(buf, "HTTP/1.1 200 OK\r\n");
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, SERVER_STRING);
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "Content-Type: %s\r\n", content_type);
  Write(sockfd, buf, strlen(buf));
  sprintf(buf, "\r\n");
  Write(sockfd, buf, strlen(buf));
}

void
send_file(int sockfd, FILE *resource)
{
  char buf[1024];

  fgets(buf, sizeof(buf), resource);
  while (!feof(resource)) {
    Write(sockfd, buf, strlen(buf));
    fgets(buf, sizeof(buf), resource);
  }
}

void
get_option(int argc, char **argv, uint32_t *port, char **base_path)
{
  int i = 1;
  while (i < argc) {
    if (strcmp(argv[i], "-p") == 0) {
      *port = atoi(argv[i + 1]);
      if (*port <= 1000)
        err_sys("port should be larger than 1000"); // avoid the well-known ports
      ++i;
    } else if (strcmp(argv[i], "-b") == 0) {
      *base_path = argv[i + 1];
      ++i;
    }
    ++i;
  }
}

int
main(int argc, char **argv)
{
  int         listenfd, connfd;
  uint32_t    port = 4000;
  pid_t       childpid;
  socklen_t   clilen;
  struct sockaddr_in	cliaddr, servaddr;

  get_option(argc, argv, &port, &base_path);

  load_table(et); // load extension table

  printf("server running at port `%d` with `%s` as base path\n", port, base_path);

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(port);

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);

  for ( ; ; ) {
    clilen = sizeof(cliaddr);
    if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
      if (errno == EINTR)
        continue;   /* back to for() */
      else
        err_sys("accept error");
    }

    if ( (childpid = Fork()) == 0) {  /* child process */
      Close(listenfd);  /* close listening socket */
      accept_request(connfd); /* process the request */
      Close(connfd);
      exit(0);
    }
    Close(connfd);      /* parent closes connected socket */
  }

  Close(listenfd);
}
