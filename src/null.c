
/**
 * `null.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <stdlib.h>
#include <json/null.h>

json_null_t *
json_null_new () {
  json_null_t *self = (json_null_t *) malloc(sizeof(json_null_t));
  if (NULL == self) return NULL;
  self->name = JSON_NULL;
  self->data = NULL;
  self->type = JSON_TYPE_NULL;
  self->to_string = json_null_to_string;
  return self;
}

char *
json_null_to_string (json_null_t *self) {
  return (char *) self->name;
}
