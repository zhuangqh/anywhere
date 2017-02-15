#ifndef	__extension_h
#define	__extension_h

#include <stdio.h>

#define HASHSIZE 233 // a prime
#define EXTLEN 10
#define MIMELEN 100

struct MIMEItem {
  struct MIMEItem *next;
  char extension[EXTLEN];
  char type[MIMELEN];
};

size_t   BKDRHash(const char *);
void     insert(struct MIMEItem **, const char *, const char *);
void     load_table(struct MIMEItem **);
const char *   lookup(struct MIMEItem **, const char *);
void     set_extension(struct MIMEItem **, const char *, char *);

#endif
