
/**
 * `number.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json/number.h>

json_number_t *
json_number_new (long double value) {
  json_number_t *self = (json_number_t *) malloc(sizeof(json_number_t));
  if (NULL == self) return NULL;
  self->name = "number";
  self->data = value;
  self->type = JSON_TYPE_NUMBER;
  self->to_string = json_number_to_string;
  return self;
}

char *
json_number_to_string (json_number_t *self) {
  char *str = NULL;
  sprintf(str, "%Le", self->data);
  return str;
}
