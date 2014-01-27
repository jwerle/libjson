
/**
 * `null.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_NULL_H
#define JSON_NULL_H

#include "common.h"
#include "value.h"

/**
 * null type
 */

typedef struct json_null_s {
  JSON_VALUE_INTERFACE(void *)
} json_null_t;

/**
 * Allocates a new `json_null_t`
 * with a `NULL` value
 */

JSON_EXTERN json_null_t *
json_null_new ();

/**
 * Returns a string representation of the
 * null
 */

JSON_EXTERN char *
json_null_to_string (json_null_t *);

#endif
