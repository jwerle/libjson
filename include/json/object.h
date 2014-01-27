
/**
 * `object.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <hash/hash.h>
#include "common.h"
#include "value.h"
#include "object.h"

/**
 * Object type
 */

typedef struct json_object_s {
  JSON_VALUE_INTERFACE(hash_t **)
  hash_t *hash;
} json_object_t;

/**
 * Allocates a new `json_object_t`
 * with no values
 */

JSON_EXTERN json_object_t *
json_object_new ();

/**
 * Sets a value by key on an object
 */

JSON_EXTERN void
json_object_set (json_object_t *, const char *, json_value_t *);

/**
 * Gets a value by key on an object
 */

JSON_EXTERN json_value_t *
json_object_get (json_object_t *, const char *);

/**
 * Returns a `json_object_t` of keys for
 * a given object
 */

JSON_EXTERN json_object_t *
json_object_keys (json_object_t *);

/**
 * Returns a string representation of the
 * object
 */

JSON_EXTERN char *
json_object_to_string (json_object_t *);

#endif
