
/**
 * `number.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_NUMBER_H
#define JSON_NUMBER_H

#include "common.h"
#include "value.h"

/**
 * Number type
 */

typedef struct json_number_s {
  JSON_VALUE_INTERFACE(long double)
} json_number_t;

/**
 * Allocates a new `json_number_t`
 * from a `long double` value
 */

JSON_EXTERN json_number_t *
json_number_new (long double);

/**
 * Returns a string representation of the
 * number
 */

JSON_EXTERN char *
json_number_to_string (json_number_t *);

#endif
