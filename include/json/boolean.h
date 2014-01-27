
/**
 * `boolean.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_BOOLEAN_H
#define JSON_BOOLEAN_H

#include "common.h"
#include "value.h"

/**
 * Boolean type
 */

typedef struct json_boolean_s {
  JSON_VALUE_INTERFACE(int)
} json_boolean_t;

/**
 * Allocates a new `json_boolean_t`
 * with an `int` value
 */

JSON_EXTERN json_boolean_t *
json_boolean_new (int);

/**
 * Boolean to string function
 */

JSON_EXTERN char *
json_boolean_to_string (json_boolean_t *);

#endif
