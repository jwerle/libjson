
/**
 * `boolean.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <stdlib.h>
#include <json/type.h>
#include <json/boolean.h>

json_boolean_t *
json_boolean_new (int data) {
  json_boolean_t *self = (json_boolean_t *) malloc(sizeof(json_boolean_t));
  if (NULL == self) return NULL;
  self->name = "boolean";
  self->data = data;
  self->type = JSON_TYPE_BOOLEAN;
  self->to_string = json_boolean_to_string;
  return self;
}

char *
json_boolean_to_string (json_boolean_t *self) {
  if (1 == self->data) {
    return JSON_TRUE;
  }
  return JSON_FALSE;
}
