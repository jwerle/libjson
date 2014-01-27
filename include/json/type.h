
/**
 * `type.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_TYPE_H
#define JSON_TYPE_H

#include "common.h"

/**
 * JSON value type strings
 */

#define JSON_TRUE "true"
#define JSON_FALSE "false"
#define JSON_NULL "null"

/**
 * JSON value types
 */

typedef enum {
  JSON_TYPE_GENERIC = 0,
  JSON_TYPE_BOOLEAN,
  JSON_TYPE_NULL,
  JSON_TYPE_NUMBER,
  JSON_TYPE_STRING,
  JSON_TYPE_OBJECT,
  JSON_TYPE_ARRAY
} json_type_t;

/**
 * Returns the type of a given
 * json value
 */

JSON_EXTERN const char *
json_typeof (void *);

#endif
