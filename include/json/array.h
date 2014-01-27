
/**
 * `array.h` - libjson
 *
 * copyright (c) 2014 - joseph werle <joseph.werle@gmail.com>
 */

#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <list/list.h>
#include "value.h"
#include "common.h"

/**
 * Array type
 */

typedef struct json_array_s {
  JSON_VALUE_INTERFACE(list_t **)
  list_t *list;
  unsigned int length;
} json_array_t;

/**
 * Allocates a new `json_array_t`
 * with no values
 */

JSON_EXTERN json_array_t *
json_array_new ();

/**
 * Pushes a value to an array
 */

JSON_EXTERN int
json_array_push (json_array_t *, json_value_t *);

/**
 * Pop a value from an array
 */

JSON_EXTERN json_value_t *
json_array_pop (json_array_t *);

/**
 * Shift a value from an array
 */

JSON_EXTERN json_value_t *
json_array_shift (json_array_t *);

/**
 * Unshift a value from an array
 */

JSON_EXTERN int
json_array_unshift (json_array_t *, json_value_t *);

/**
 * Return index of a given value
 */

JSON_EXTERN int
json_array_indexof (json_array_t *, json_value_t *);

/**
 * Returns a string representation of the
 * array
 */

JSON_EXTERN char *
json_array_to_string (json_array_t *);

/**
 * Iterates a block for each element
 * in the array
 */

#define json_array_each(self, value, block) {                                  \
  list_iterator_t *it = list_iterator_new(self->list, LIST_HEAD);              \
  list_node_t *node;                                                           \
  while ((node = list_iterator_next(it))) {                                    \
    json_value_t *value = (json_value_t *) node->val;                          \
    block;                                                                     \
  }                                                                            \
  list_iterator_destroy(it);                                                   \
}

#endif
