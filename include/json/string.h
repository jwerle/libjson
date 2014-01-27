
/**
 * `string.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "common.h"
#include "value.h"

/**
 * String type
 */

typedef struct json_string_s {
  JSON_VALUE_INTERFACE(char *)
  size_t length;
} json_string_t;

/**
 * Allocates a new `json_string_t`
 * from a `const char *` value
 */

JSON_EXTERN json_string_t *
json_string_new (const char *);

/**
 * Returns a string representation of the
 * string
 */

JSON_EXTERN char *
json_string_to_string (json_string_t *);

#endif
