
/**
 * `string.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <string.h>
#include <stdlib.h>
#include <json/string.h>

json_string_t *
json_string_new (const char *str) {
  json_string_t *self = (json_string_t *) malloc(sizeof(json_string_t));
  if (NULL == self) return NULL;
  size_t len = strlen(str) + 1;
  self->name = "string";
  self->data = (char *) memcpy((void *) malloc(len), str, len);
  self->type = JSON_TYPE_BOOLEAN;
  self->to_string = json_string_to_string;
  return self;
}

char *
json_string_to_string (json_string_t *self) {
  return (char *) self->data;
}
