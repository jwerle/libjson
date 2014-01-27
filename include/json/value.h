
/**
 * `value.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include "type.h"
#include "common.h"

/**
 * JSON generic value interface
 */

#define JSON_VALUE_INTERFACE(datatype) \
  const char *name;                    \
  json_type_t type;                    \
  datatype data;                       \
  char *(*to_string)();

/**
 * Generic value type
 */

typedef struct json_value_s {
  JSON_VALUE_INTERFACE(void *)
} json_value_t;

/**
 * Allocates a new `json_value_t`
 * with a `void *` value
 */

JSON_EXTERN json_value_t *
json_value_new (void *);

/**
 * Generic to string function
 */

JSON_EXTERN char *
json_value_to_string (json_value_t *);

#endif
