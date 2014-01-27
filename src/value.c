
/**
 * `value.c` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#include <stdlib.h>
#include <json/type.h>
#include <json/value.h>
#include <json/boolean.h>
#include <json/null.h>
#include <json/number.h>
#include <json/string.h>
#include <json/object.h>
#include <json/array.h>

json_value_t *
json_value_new (void *data) {
  json_value_t *self = (json_value_t *) malloc(sizeof(json_value_t));
  if (NULL == self) return NULL;
  self->name = "value";
  self->data = data;
  self->type = JSON_TYPE_GENERIC;
  self->to_string = json_value_to_string;
  return self;
}

char *
json_value_to_string (json_value_t *self) {
  switch (self->type) {
    case JSON_TYPE_GENERIC:
      return (char *) self->data;

    case JSON_TYPE_BOOLEAN:
      return json_boolean_to_string((json_boolean_t *) self);

    case JSON_TYPE_NULL:
      return json_null_to_string((json_null_t *) self);

    case JSON_TYPE_NUMBER:
      return json_number_to_string((json_number_t *) self);

    case JSON_TYPE_STRING:
      return json_string_to_string((json_string_t *) self);

    case JSON_TYPE_OBJECT:
      return json_object_to_string((json_object_t *) self);

    case JSON_TYPE_ARRAY:
      return json_array_to_string((json_array_t *) self);
  }

  return NULL;
}
