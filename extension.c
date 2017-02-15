#include "./extension.h"
#include "./common.h"

extern char et_path[PATHLEN];

void
load_table(struct MIMEItem **et)
{
  for (size_t i = 0; i < HASHSIZE; ++i) {
    et[i] = NULL;
  }

  FILE *et_file = fopen(et_path, "r");

  char extension[MIMELEN], type[MIMELEN];

  if (!et_file) {
    err_sys("load extension table");
  } else {
    while (!feof(et_file)) {
      fscanf(et_file, "%s %s", extension, type);
      insert(et, extension, type);
    }
  }

  fclose(et_file);
}

size_t
BKDRHash(const char *str)
{
  size_t hash = 0;
  char c;
  while ((c = *str++)) {
    hash = hash * 31 + *str;
  }
  return hash % HASHSIZE;
}

void
insert(struct MIMEItem **et, const char *extension, const char *type)
{
  struct MIMEItem *new_entry = (struct MIMEItem *) malloc(sizeof(struct MIMEItem));
  strncpy(new_entry->extension, extension, EXTLEN);
  strncpy(new_entry->type, type, MIMELEN);
  new_entry->next = NULL;

  size_t bucket = BKDRHash(extension);
  
  struct MIMEItem *p = et[bucket];
  if (!p) { // empty
    et[bucket] = new_entry;
  } else {
    while (p->next) p = p->next; // find the end of the list
    p->next = new_entry;
  }
}

const char *
lookup(struct MIMEItem **et, const char *extension)
{
  if (!extension) return "text/plain";

  struct MIMEItem *p;
  for (p = et[BKDRHash(extension)]; p != NULL; p = p->next) {
    if (strcmp(p->extension, extension) == 0) {
      return p->type;
    }
  }
  return "text/plain"; // default type
}

void
set_extension(struct MIMEItem **et, const char *filepath, char *content_type)
{
  const char *dot = strrchr(filepath, '.');

  if (!dot) {
    sprintf(content_type, "text/plain");
  } else {
    strncpy(content_type, lookup(et, dot + 1), MIMELEN);
  }
}
